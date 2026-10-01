"""Integration tests for the claim-aware orchestration layer.

Covers the deterministic single-target lifecycle, the canonical queue/lease
contract, the worker contract, bounded failure handling, and the isolation
guarantees around the committed knowledge graph.

Nothing here touches Ghidra, the network, a display, Wine, or the committed
``knowledgegraph/spore.db``: every test builds a synthetic root in its own
tempdir and points the queue at it through ``OPENSPORE_DB`` (see
``tools/mcp/config.db_path``). ``write=False`` everywhere, so no artifact is
produced outside the tempdir.

Run from the repo root::

    python3 -m unittest tests.test_orchestration -v

Known production defects are pinned, never papered over. Each pinned test is
named ``test_pinned_*`` and carries the exact ``file:line`` of the defect in
its docstring; the intent is that the day the defect is fixed, the pinned
assertion is what fails, pointing straight at the fix.
"""
import json
import os
import sqlite3
import subprocess
import sys
import threading
import unittest
from concurrent.futures import ThreadPoolExecutor

from tools.mcp import registry
from tools.reconstruction_tooling import cli as cli_mod
from tools.reconstruction_tooling import orchestrate as orch
from tools.reconstruction_tooling import schedule as sched
from tools.reconstruction_tooling import worker_contract as wc
from tools.reconstruction_tooling import queue as q

from tests import orchestration_fixture as fx

FIXTURES = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fixtures")
FAKE_WORKER = os.path.join(FIXTURES, "fake_worker.py")

# The documented end-to-end op sequence, in order.
HAPPY_PATH_OPS = ["claim", "brief", "launch", "ingest", "validate", "checkpoint",
                  "close"]


def queue_op(**params):
    return registry.dispatch("queue_op", params)


class QueueLeaseContractTest(fx.FixtureTestCase):
    """A1-A15: the canonical ``queue_op`` contract the orchestrator leans on."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A", "B"))
        self.ida = fx.inv_id("A")
        self.idb = fx.inv_id("B")

    # -- A1 --------------------------------------------------------------- #
    def test_happy_path_end_to_end(self):
        self.stub_validator("PASS")
        worker = fx.worker("ok")
        plan = self.plan()
        record = fx.process_target(self.info["root"], plan["targets"][0], worker,
                                   "w-happy", self.info["sha"], write=False)
        self.assertEqual(record["status"], "complete", record)
        self.assertEqual(record["code"], "validated")
        self.assertEqual(record["outcome"], "IMPLEMENTED")
        self.assertEqual(record["validation"], "PASS")
        self.assertEqual([event["op"] for event in record["events"]],
                         HAPPY_PATH_OPS, record["events"])
        self.assertEqual([event["op"] for event in record["events"] if
                          event["op"] == "close"][:1], ["close"])
        self.assertTrue(record["events"][0]["ok"])
        self.assertFalse(record["events"][0]["idempotent"])
        self.assertEqual(fx.row(self.db, self.ida)["status"], "done")
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        self.assertEqual(len(worker.calls), 1)
        self.assertEqual(worker.calls[0]["attempt"], 1)
        self.assertEqual(worker.calls[0]["implementer"], "w-happy")

    # -- A2 --------------------------------------------------------------- #
    def test_claim_race_has_exactly_one_winner(self):
        rows = [self.ida, self.idb]
        for attempt in range(20):
            connection = sqlite3.connect(self.db)
            for inv_id in rows:
                connection.execute(
                    "UPDATE investigations SET status='queued', "
                    "implementer_id=NULL, block_reason=NULL WHERE id=?", (inv_id,))
            connection.commit()
            connection.close()
            inv_id = rows[attempt % len(rows)]
            with ThreadPoolExecutor(max_workers=2) as executor:
                results = list(executor.map(
                    lambda name: queue_op(op="claim", id=inv_id,
                                          implementer_id=name,
                                          binary_sha256=fx.SHA),
                    ("alice", "bob")))
            winners = [item for item in results if item.get("claimed")]
            losers = [item for item in results
                      if item.get("code") == "already_claimed"]
            self.assertEqual(len(winners), 1, (attempt, results))
            self.assertEqual(len(losers), 1, (attempt, results))
            self.assertEqual(winners[0]["idempotent"], False)
            # the loser must not have written anything at all
            self.assertNotIn("investigation", losers[0])
            self.assertEqual(losers[0]["implementer_id"],
                             winners[0]["investigation"]["implementer_id"])
            row = fx.row(self.db, inv_id)
            self.assertEqual(row["status"], "active")
            self.assertEqual(row["implementer_id"],
                             winners[0]["investigation"]["implementer_id"])
            self.assertEqual(len(fx.rows_by_status(self.db, "active")), 1,
                             "a second row was left active")
            other = rows[(attempt + 1) % len(rows)]
            self.assertEqual(fx.row(self.db, other)["status"], "queued")
            self.assertIsNone(fx.row(self.db, other)["implementer_id"])

    # -- A3 --------------------------------------------------------------- #
    def test_duplicate_claim_by_same_worker_is_idempotent(self):
        first = queue_op(op="claim", id=self.ida, implementer_id="alice",
                         binary_sha256=fx.SHA)
        self.assertTrue(first["claimed"])
        stamp = fx.row(self.db, self.ida)["updated_at"]
        second = queue_op(op="claim", id=self.ida, implementer_id="alice",
                          binary_sha256=fx.SHA)
        self.assertIs(second["claimed"], False)
        self.assertIs(second["idempotent"], True)
        self.assertEqual(fx.row(self.db, self.ida)["updated_at"], stamp)
        self.assertEqual(fx.row(self.db, self.ida)["implementer_id"], "alice")

    # -- A4 --------------------------------------------------------------- #
    def test_duplicate_claim_by_other_worker_names_the_winner(self):
        queue_op(op="claim", id=self.ida, implementer_id="alice",
                 binary_sha256=fx.SHA)
        refused = queue_op(op="claim", id=self.ida, implementer_id="bob",
                           binary_sha256=fx.SHA)
        self.assertEqual(refused["code"], "already_claimed")
        self.assertEqual(refused["implementer_id"], "alice")
        self.assertIs(refused["stale"], False)
        self.assertEqual(fx.row(self.db, self.ida)["implementer_id"], "alice")

    # -- A5 --------------------------------------------------------------- #
    def test_stale_lease_is_refused_without_allow_stale(self):
        fx.backdate(self.db, self.ida, when=fx.FIXED_NOW, owner="alice")
        refused = queue_op(op="claim", id=self.ida, implementer_id="bob",
                           binary_sha256=fx.SHA)
        self.assertEqual(refused["code"], "already_claimed")
        self.assertIs(refused["stale"], True, refused)
        self.assertEqual(fx.row(self.db, self.ida)["implementer_id"], "alice")

    # -- A6 --------------------------------------------------------------- #
    def test_stale_lease_reclaim_records_the_displaced_owner(self):
        fx.backdate(self.db, self.ida, when=fx.FIXED_NOW, owner="alice")
        taken = queue_op(op="claim", id=self.ida, implementer_id="bob",
                         binary_sha256=fx.SHA, allow_stale=True,
                         stale_after_seconds=60)
        self.assertTrue(taken["claimed"], taken)
        self.assertEqual(taken["displaced_owner"]["owner"], "alice")
        history = json.loads(fx.row(self.db, self.ida)["checkpoint"])
        self.assertEqual(len(history["lease_history"]), 1)
        self.assertEqual(history["lease_history"][0]["owner"], "alice")
        self.assertEqual(history["lease_history"][0]["stale_after_seconds"], 60)
        self.assertEqual(fx.row(self.db, self.ida)["implementer_id"], "bob")

    # -- A7 --------------------------------------------------------------- #
    def test_iso8601_lease_clock_is_readable(self):
        fx.backdate(self.db, self.ida, when=fx.FIXED_NOW_ISO, owner="alice")
        refused = queue_op(op="claim", id=self.ida, implementer_id="bob",
                           binary_sha256=fx.SHA)
        self.assertEqual(refused["code"], "already_claimed")
        self.assertIs(refused["stale"], True,
                      "ISO-8601 lease clock was not readable: %r" % (refused,))
        allowed = queue_op(op="claim", id=self.ida, implementer_id="bob",
                           binary_sha256=fx.SHA, allow_stale=True,
                           stale_after_seconds=60)
        self.assertTrue(allowed["claimed"], allowed)

    # -- A8 (PINNED DEFECT) ------------------------------------------------ #
    def test_pinned_checkpoint_is_refused_so_the_lease_is_never_renewed(self):
        """PINNED DEFECT -- queue.checkpoint() can never succeed.

        ``tools/reconstruction_tooling/queue.py:137`` always sends
        ``implementer_id`` with ``op=update``, and
        ``tools/mcp/kg_tools.py:901-906`` (``_queue_update_owned``) rejects
        ``implementer_id`` as an update field *after* the owner check. So every
        ``checkpoint`` -- and therefore the lease heartbeat documented at
        queue.py:125-133 -- is refused with ``invalid_params`` and
        ``updated_at`` never moves. Intended assertion once fixed:
        ``q.checkpoint(...)`` returns ``status == "ok"`` and
        ``updated_at`` advances.
        """
        queue_op(op="claim", id=self.ida, implementer_id="alice",
                 binary_sha256=fx.SHA)
        stamp = fx.row(self.db, self.ida)["updated_at"]
        result = q.checkpoint(self.ida, "alice", payload={"stage": "VALIDATE"},
                              stage="VALIDATE")
        self.assertEqual(result["code"], "invalid_params", result)
        self.assertIn("implementer_id", result["message"])
        self.assertEqual(fx.row(self.db, self.ida)["updated_at"], stamp)
        self.assertIsNone(fx.row(self.db, self.ida)["checkpoint"])
        # the safe half of the contract still holds: the row stays locked
        refused = queue_op(op="claim", id=self.ida, implementer_id="bob",
                           binary_sha256=fx.SHA)
        self.assertEqual(refused["code"], "already_claimed")
        self.assertIs(refused["stale"], False)

    # -- A9 --------------------------------------------------------------- #
    def test_release_contract(self):
        queue_op(op="claim", id=self.ida, implementer_id="alice",
                 binary_sha256=fx.SHA)
        self.assertEqual(
            queue_op(op="release", id=self.ida, implementer_id="bob",
                     to="queued")["code"], "not_owner")
        released = queue_op(op="release", id=self.ida, implementer_id="alice",
                            to="queued")
        self.assertTrue(released["released"])
        row = fx.row(self.db, self.ida)
        self.assertEqual(row["status"], "queued")
        self.assertIsNone(row["implementer_id"])
        again = queue_op(op="release", id=self.ida, implementer_id="alice",
                         to="queued")
        self.assertIs(again["released"], False)
        self.assertIs(again["idempotent"], True)
        queue_op(op="close", id=self.ida, implementer_id="alice", status="done")
        self.assertEqual(
            queue_op(op="release", id=self.ida, implementer_id="alice",
                     to="queued")["code"], "already_completed")

    # -- A10 (PARTIALLY PINNED DEFECT) ------------------------------------ #
    def test_update_on_a_leased_row_is_guarded_by_the_lease_token(self):
        """Guards work; the *accept* path is pinned broken.

        PINNED DEFECT: with the correct lease token ``_queue_update_owned``
        still returns ``invalid_params`` (kg_tools.py:901-906), so no queued
        write can ever land. Intended assertion once fixed: ``status == "ok"``
        and the row's ``stage`` becomes ``VALIDATE``.
        """
        queue_op(op="claim", id=self.ida, implementer_id="alice",
                 binary_sha256=fx.SHA)
        without = queue_op(op="update", id=self.ida, stage="VALIDATE")
        self.assertEqual(without["code"], "not_owner")
        foreign = queue_op(op="update", id=self.ida, implementer_id="bob",
                           stage="VALIDATE")
        self.assertEqual(foreign["code"], "not_owner")
        self.assertEqual(foreign["implementer_id"], "alice")
        right = queue_op(op="update", id=self.ida, implementer_id="alice",
                         stage="VALIDATE")
        self.assertEqual(right["code"], "invalid_params", right)
        self.assertEqual(right["field"], "implementer_id")
        self.assertEqual(fx.row(self.db, self.ida)["stage"], "QUEUED")

    # -- A11 -------------------------------------------------------------- #
    def test_terminal_row_cannot_be_resurrected(self):
        queue_op(op="close", id=self.ida, implementer_id="alice", status="done")
        self.assertEqual(
            queue_op(op="update", id=self.ida, implementer_id="alice",
                     stage="VALIDATE")["code"], "already_completed")
        self.assertEqual(
            queue_op(op="update", id=self.ida, status="queued")["code"],
            "already_completed")
        self.assertEqual(
            queue_op(op="claim", id=self.ida, implementer_id="zed",
                     allow_blocked=True)["code"], "already_completed")
        self.assertEqual(fx.row(self.db, self.ida)["status"], "done")

    # -- A12 -------------------------------------------------------------- #
    def test_close_contract(self):
        queue_op(op="claim", id=self.ida, implementer_id="alice",
                 binary_sha256=fx.SHA)
        self.assertEqual(
            queue_op(op="close", id=self.ida, implementer_id="bob",
                     status="done")["code"], "not_owner")
        self.assertEqual(
            queue_op(op="close", id=self.ida, implementer_id="alice",
                     status="done",
                     binary_sha256="e" * 64)["code"], "stale_binary")
        self.assertEqual(fx.row(self.db, self.ida)["status"], "active")
        closed = queue_op(op="close", id=self.ida, implementer_id="alice",
                          status="done", binary_sha256=fx.SHA)
        self.assertTrue(closed["closed"])
        self.assertEqual(closed["previous_status"], "active")
        self.assertIsNotNone(fx.row(self.db, self.ida))
        again = queue_op(op="close", id=self.ida, implementer_id="alice",
                         status="done")
        self.assertIs(again["closed"], False)
        self.assertEqual(again["previous_status"], "done")
        self.assertIsNotNone(fx.row(self.db, self.ida))

    def test_close_of_a_blocked_row_is_an_explicit_adjudication(self):
        """A parked row cannot be unparked by accident, by anybody.

        ``release(to="blocked")`` clears the lease, so there is no owner left to
        compare against: a worker that parked its own target could close it
        again and erase the reason. Closing a ``blocked`` row therefore requires
        ``allow_blocked``, and the refusal must leave the row untouched.
        """
        queue_op(op="claim", id=self.ida, implementer_id="alice",
                 binary_sha256=fx.SHA)
        released = q.release(self.ida, "alice", to="blocked", reason="operator:bad_abi")
        self.assertTrue(released["released"], released)
        parked = fx.row(self.db, self.ida)
        self.assertEqual((parked["status"], parked["implementer_id"],
                          parked["block_reason"]),
                         ("blocked", None, "operator:bad_abi"), parked)
        for implementer in ("alice", "bob"):
            refused = queue_op(op="close", id=self.ida,
                               implementer_id=implementer, status="done")
            self.assertEqual(refused["code"], "blocked", (implementer, refused))
            self.assertEqual(refused["block_reason"], "operator:bad_abi", refused)
        self.assertEqual(fx.row(self.db, self.ida), parked,
                         "a refused close mutated a blocked row")
        # the queue adapter has no way to express the adjudication, so the
        # orchestrator's own close can only ever be refused here
        self.assertEqual(q.close(self.ida, "alice", disposition="done")["code"],
                         "blocked")
        allowed = queue_op(op="close", id=self.ida,
                           implementer_id="adjudicator", status="done",
                           allow_blocked=True)
        self.assertTrue(allowed["closed"], allowed)
        self.assertEqual(allowed["previous_status"], "blocked")
        self.assertEqual(fx.row(self.db, self.ida)["status"], "done")
        # and it is terminal now, so the flag is no longer needed or accepted
        self.assertIs(
            queue_op(op="close", id=self.ida, implementer_id="adjudicator",
                     status="dropped", allow_blocked=True)["closed"], False)

    # -- A13 -------------------------------------------------------------- #
    def test_binary_identity_and_unreadable_clock_fail_closed(self):
        self.assertEqual(
            queue_op(op="claim", id=self.ida, implementer_id="alice",
                     binary_sha256="e" * 64)["code"], "stale_binary")
        self.assertEqual(fx.row(self.db, self.ida)["status"], "queued")
        fx.backdate(self.db, self.idb, when=None, owner="alice")
        self.assertIsNone(fx.row(self.db, self.idb)["updated_at"])
        refused = queue_op(op="claim", id=self.idb, implementer_id="bob",
                           allow_stale=True, stale_after_seconds=60)
        self.assertEqual(refused["code"], "already_claimed")
        self.assertIs(refused["stale"], False,
                      "a NULL lease clock must never be auto-stale")
        self.assertEqual(fx.row(self.db, self.idb)["implementer_id"], "alice")

    # -- A14 -------------------------------------------------------------- #
    def test_stale_after_seconds_below_the_floor_is_rejected(self):
        for value in (0, 1, 59, -5):
            result = queue_op(op="claim", id=self.ida, implementer_id="alice",
                              stale_after_seconds=value)
            self.assertEqual(result["code"], "invalid_params", (value, result))
            self.assertEqual(result["minimum"], 60)
        ok = queue_op(op="claim", id=self.ida, implementer_id="alice",
                      stale_after_seconds=60)
        self.assertTrue(ok["claimed"], ok)
        # and the adapter clamps rather than forwarding a sub-floor TTL
        clamped = q.claim(self.idb, "alice", ttl=5)
        self.assertTrue(clamped["claimed"], clamped)

    # -- A15 -------------------------------------------------------------- #
    def test_queue_va_format_round_trip(self):
        by_prefix = queue_op(op="get", va="0x00b3d300",
                             binary_sha256=fx.SHA)
        by_bare = queue_op(op="get", va="00b3d300", binary_sha256=fx.SHA)
        self.assertEqual(by_prefix["status"], "ok")
        self.assertEqual(by_prefix["investigation"]["id"], self.ida)
        self.assertEqual(by_bare["investigation"], by_prefix["investigation"])
        # A short (non 8-char) address is deliberately NOT normalised: the
        # queue stores bare 8-char hex, and widening the match would alias two
        # different functions onto one row.
        self.assertEqual(queue_op(op="get", va="b3d300",
                                  binary_sha256=fx.SHA)["code"], "not_found")
        self.assertEqual(fx.row(self.db, self.ida)["va"], "00b3d300")
        for value in ("0x00b3d300", "00b3d300", "B3D300"):
            ensured = q.ensure_row(value, binary_sha256=fx.SHA)
            self.assertEqual(ensured["status"], "ok", (value, ensured))
            self.assertEqual(ensured["investigation"]["id"], self.ida)
        rows = queue_op(op="list", limit=50)["investigations"]
        self.assertEqual([item["va"] for item in rows if item["id"] == self.ida],
                         ["00b3d300"])


class WorkerContractTest(fx.FixtureTestCase):
    """B16-B20: the briefing, the result parser, and the launch argv."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A", "B"))
        self.inputs = orch.collect_inputs(self.info["root"], "0x00b3d300",
                                         live=False, write=False)

    def briefing(self, **kwargs):
        params = {"root": self.info["root"],
                  "evidence": self.inputs["evidence"],
                  "context": self.inputs["context"],
                  "validation": self.inputs["validation"],
                  "implementer_id": "w-1", "inv_id": fx.inv_id("A"),
                  "binary_sha256": fx.SHA, "attempt": 1}
        params.update(kwargs)
        return wc.briefing("0x00b3d300", **params)

    # -- B16 -------------------------------------------------------------- #
    def test_briefing_is_deterministic_and_carries_every_section(self):
        from tools.reconstruction_tooling.models import sha256_json
        first = self.briefing()
        second = self.briefing()
        self.assertEqual(first["content_sha256"], second["content_sha256"])
        self.assertEqual(sha256_json(first),
                         sha256_json(first))
        required = {
            "schema", "target", "lease", "objective", "current_status",
            "frontier_reason", "decompilation", "disassembly",
            "ghidra_function", "callers", "callees", "xrefs", "abi", "types",
            "fields_offsets", "globals", "vtables", "services",
            "state_event_links", "semantic_findings", "contradictions",
            "analogues", "dependencies", "existing_reconstruction",
            "reconstruction_constraints", "validation_requirements",
            "evidence", "rules", "result_contract", "content_sha256",
        }
        self.assertEqual(sorted(required - set(first)), [],
                         "briefing is missing section(s)")
        self.assertEqual(first["schema"], wc.BRIEFING_SCHEMA)
        self.assertEqual(first["target"]["va"], "0x00b3d300")
        self.assertEqual(first["target"]["queue_va"], "00b3d300")
        self.assertEqual(first["target"]["queue_id"], fx.inv_id("A"))
        self.assertEqual(first["lease"]["implementer_id"], "w-1")
        self.assertEqual(first["lease"]["attempt"], 1)
        self.assertEqual(first["reconstruction_constraints"]["symbol_must_embed_va"],
                         "00b3d300")
        self.assertEqual(first["result_contract"]["schema"], wc.RESULT_SCHEMA)
        self.assertEqual(first["result_contract"]["outcomes"], list(wc.OUTCOMES))
        self.assertEqual(first["result_contract"]["verdicts"],
                         list(wc.VALIDATION_VERDICTS))
        self.assertEqual(first["rules"], list(wc.WORKER_RULES))
        markdown = wc.render_briefing_markdown(first)
        self.assertIn("0x00b3d300", markdown)
        self.assertIn(first["content_sha256"], markdown)

    # -- B17 -------------------------------------------------------------- #
    def test_briefing_reports_missing_evidence_honestly(self):
        package = self.briefing()
        missing = package["evidence"]["missing_sections"]
        self.assertIn("DECOMPILATION", missing)
        self.assertIn("DISASSEMBLY", missing)
        self.assertTrue(any("decompilation" in item for item in missing), missing)
        self.assertIsNone(package["decompilation"])
        self.assertIsNone(package["disassembly"])
        self.assertIsNone(package["ghidra_function"])
        self.assertEqual(self.inputs["evidence"]["evidence_state"], "PERSISTED")
        self.assertEqual(self.inputs["evidence"]["collector"]["live_attempts"],
                         [])
        # honesty cuts both ways: nothing is invented for a category that
        # *is* available
        self.assertEqual(
            self.inputs["evidence"]["categories"]["function_identity"]
            ["availability"], "available")

    # -- B18 -------------------------------------------------------------- #
    def test_parse_result_accepts_every_valid_outcome(self):
        for outcome in wc.OUTCOMES:
            raw = json.dumps(fx.result_document("A", outcome=outcome))
            parsed = wc.parse_result(raw, va="0x00b3d300", inv_id=fx.inv_id("A"))
            self.assertTrue(parsed["accepted"], (outcome, parsed))
            self.assertEqual(parsed["outcome"], outcome)
            self.assertEqual(parsed["result"]["queue_id"], fx.inv_id("A"))
        template = wc.result_template("0x00b3d300")
        self.assertTrue(wc.parse_result(json.dumps(template),
                                        va="0x00b3d300")["accepted"])
        for raw in (None, "", b"{}", "  \n"):
            self.assertFalse(wc.parse_result(raw, va="0x00b3d300")["accepted"])

    def test_parse_result_rejects_every_invalid_document(self):
        cases = {
            "malformed json": "{not json",
            "json list where an object was required": "[1, 2, 3]",
            "missing required fields": json.dumps(
                {"schema": wc.RESULT_SCHEMA, "va": "0x00b3d300"}),
            "wrong schema": json.dumps(fx.result_document(
                "A", schema="openspore-worker-result-0")),
            "unknown outcome": json.dumps(fx.result_document(
                "A", outcome="ALMOST_DONE")),
            "unparseable va": json.dumps(fx.result_document("A", va="zzz")),
            "mismatched va": json.dumps(fx.result_document(
                "A", va="0x00b3d400")),
            "source_files not a list": json.dumps(dict(
                fx.result_document("A"), source_files="src/a.cpp")),
            "observed_mechanics not a list": json.dumps(dict(
                fx.result_document("A"), observed_mechanics="none")),
            "unresolved_questions not a list": json.dumps(dict(
                fx.result_document("A"), unresolved_questions="q")),
            "evidence_refs not a list": json.dumps(dict(
                fx.result_document("A"), evidence_refs={"a": 1})),
            "unknown validation verdict": json.dumps(dict(
                fx.result_document("A"), validation={"status": "MAYBE"})),
            "oversized payload": "x" * (4 * 1024 * 1024 + 1),
        }
        for label, raw in sorted(cases.items()):
            parsed = wc.parse_result(raw, va="0x00b3d300", inv_id=fx.inv_id("A"))
            self.assertIs(parsed["accepted"], False, (label, parsed))
            self.assertEqual(parsed["code"], "malformed_worker_output",
                             (label, parsed))
            self.assertTrue(parsed["reason"], (label, parsed))
        # every rejection carries a raw digest so the failure is auditable
        for label, raw in sorted(cases.items()):
            parsed = wc.parse_result(raw, va="0x00b3d300")
            if label == "oversized payload":
                self.assertIn("raw_bytes", parsed)
            else:
                self.assertIn("raw_sha256", parsed, label)

    # -- B19 -------------------------------------------------------------- #
    def test_worker_answering_for_the_wrong_va_is_refused(self):
        self.stub_validator("PASS")
        worker = fx.worker("wrong_va")
        plan = self.plan()
        target = [item for item in plan["targets"]
                  if item["va"] == "0x00b3d300"][0]
        record = fx.process_target(self.info["root"], target, worker, "w-wrong",
                                   self.info["sha"], write=False)
        self.assertNotEqual(record["status"], "complete")
        self.assertEqual(record["code"], "malformed_worker_output")
        self.assertEqual(record["status"], "partial")
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["status"], "queued")
        self.assertIsNone(row["implementer_id"])
        self.assertIsNone(row["evidence_refs"],
                          "another function's artifacts were misattributed")
        self.assertIsNone(row["attempts"])
        parsed = wc.parse_result(worker.document(
            {"target": {"va": "0x00b3d300"}}, "A"),
            va="0x00b3d300", inv_id=fx.inv_id("A"))
        self.assertFalse(parsed["accepted"])
        self.assertEqual(parsed["expected_va"], "0x00b3d300")
        self.assertEqual(parsed["reported_va"], "0x00b3d400")

    # -- B20 -------------------------------------------------------------- #
    def test_agent_argv_is_a_pure_function_of_the_briefing(self):
        package = self.briefing()
        first = orch.agent_argv(package)
        second = orch.agent_argv(package)
        self.assertIsInstance(first, list)
        self.assertEqual(first, second)
        self.assertEqual(first[:2], ["opencode", "run"])
        # The prompt is a positional and must precede the flags: OpenCode's
        # ``--file`` is an array option that swallows trailing positionals, so
        # a prompt placed last is read as a filename.
        self.assertIn(package["content_sha256"], first[2])
        # The structured channel is mandatory, not a default: OpenCode's
        # ``--format default`` concatenates every assistant text block into
        # stdout, so a worker that narrates before using a tool makes
        # ``json.loads`` of the whole reply die on its first character.
        self.assertEqual(first[3:5], ["--print-logs", "--format"])
        self.assertEqual(first[5], "json")
        self.assertEqual(len(first), 6)
        for element in first:
            self.assertIsInstance(element, str)
        joined = " ".join(first)
        self.assertNotIn("approve=true", joined)
        self.assertNotIn("--yes", joined)
        with_model = orch.agent_argv(package, model="some/model")
        self.assertEqual(with_model[:5],
                         ["opencode", "run", with_model[2], "--print-logs",
                          "--format"])
        self.assertEqual(with_model[6:8], ["--model", "some/model"])
        self.assertNotEqual(with_model, first)
        # An operator who wants the legacy prose channel can still ask for it;
        # the parser accepts either, so this is a compatibility escape hatch
        # and not a supported way to run a worker.
        default_format = orch.agent_argv(package, output_format="default")
        self.assertIn("default", default_format)
        self.assertNotIn("--format", orch.agent_argv(package,
                                                    output_format=None))
        # ``attach`` exists because a real agent never reads stdin: the Markdown
        # digest is ~1.7KB for a ~25KB briefing, so without the attachment the
        # worker has no evidence at all.
        attached = orch.agent_argv(package, attach="/tmp/briefing.json")
        self.assertEqual(attached[-2:], ["--file", "/tmp/briefing.json"])
        self.assertIn("/tmp/briefing.json", attached[2])
        self.assertIn("authoritative data channel", attached[2])
        self.assertEqual(attached[:2], ["opencode", "run"])
        changed = self.briefing(attempt=2)
        self.assertNotEqual(orch.agent_argv(changed), first)
        self.assertNotEqual(changed["content_sha256"],
                            package["content_sha256"])

    # -- extra: the real launch path through a subprocess ----------------- #
    def test_fake_worker_subprocess_produces_a_contract_valid_reply(self):
        for variant, expected_code, accepted in (
                ("ok", 0, True), ("still_unknown", 0, True),
                ("block", 0, True), ("failed_validation", 0, True),
                ("malformed_json", 1, False), ("malformed_shape", 0, False),
                ("bad_schema", 0, False), ("bad_outcome", 0, False),
                ("wrong_va", 0, False)):
            argv = [sys.executable, FAKE_WORKER, "--variant", variant]
            payload = json.dumps(self.briefing()).encode("utf-8")
            completed = subprocess.run(argv, input=payload,
                                       stdout=subprocess.PIPE,
                                       stderr=subprocess.PIPE, check=False,
                                       timeout=60)
            self.assertEqual(completed.returncode, expected_code,
                             (variant, completed.stderr))
            parsed = orch.ingest(completed.stdout.decode("utf-8"),
                                 "0x00b3d300", fx.inv_id("A"))
            self.assertEqual(parsed["accepted"], accepted,
                             (variant, parsed.get("reason")))
            if accepted:
                self.assertEqual(parsed["result"]["reconstructed_symbol"],
                                 fx.symbol("A"))
            else:
                self.assertEqual(parsed["code"], "malformed_worker_output")

    def test_fake_worker_can_answer_validly_and_still_exit_nonzero(self):
        """The two facts are independent and both observable.

        ``--exit-code`` makes the shape reachable: a worker whose reply satisfies
        the contract and whose process then exits nonzero. Anything that treats
        the exit status as the reply's verdict has to fail here.
        """
        payload = json.dumps(self.briefing()).encode("utf-8")
        completed = subprocess.run(
            [sys.executable, FAKE_WORKER, "--variant", "ok", "--exit-code", "3"],
            input=payload, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            check=False, timeout=60)
        self.assertEqual(completed.returncode, 3)
        self.assertTrue(orch.ingest(completed.stdout.decode("utf-8"),
                                    "0x00b3d300", fx.inv_id("A"))["accepted"])

    def test_launch_feeds_a_worker_its_own_briefing(self):
        """REGRESSION: ``launch`` must encode the briefing to bytes itself.

        ``orchestrate.launch`` built ``canonical_json(...)`` (a ``str``) and
        handed it to ``subprocess.run(input=...)`` with byte pipes. Python 3.13+
        requires ``input`` to be bytes-like, so every subprocess worker raised
        ``TypeError`` -- which was not in the launcher's exception net, so it
        escaped as a crash instead of the documented routable result. The
        briefing is now encoded at the boundary; this pins that.
        """
        argv = [sys.executable, FAKE_WORKER, "--variant", "ok"]
        detail = orch.launch(argv, self.briefing(), timeout=60)
        self.assertIsNone(detail["failure"], detail)
        self.assertEqual(detail["returncode"], 0, detail["stderr"])
        parsed = orch.ingest(detail["stdout"].decode("utf-8"),
                             "0x00b3d300", fx.inv_id("A"))
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        # The two worker adapters go through the same path and must not raise.
        for adapter in (orch.subprocess_worker(lambda _package: argv),
                        orch.command_line(None, argv, "w")):
            raw, launch_detail = adapter(self.briefing())
            self.assertEqual(launch_detail["failure"], None, launch_detail)
            self.assertTrue(orch.ingest(raw.decode("utf-8"), "0x00b3d300",
                                        fx.inv_id("A"))["accepted"])
        # str and bytes payloads are both accepted at the boundary; an empty
        # payload is the worker's business to reject, not a launcher crash.
        for payload in (json.dumps(self.briefing()),
                        json.dumps(self.briefing()).encode("utf-8")):
            self.assertIsNone(orch.launch(argv, payload,
                                          timeout=60)["failure"])
        empty = orch.launch(argv, None, timeout=60)
        self.assertIn(empty["failure"], (None, "nonzero_exit"), empty)
        # a missing binary is still a routable failure, not a crash
        detail = orch.launch(["/nonexistent/openspore-worker"], "",
                             timeout=30)
        self.assertEqual(detail["failure"], "spawn_failed")
        self.assertIsNone(detail["returncode"])


class EvidencePackChoiceTest(fx.FixtureTestCase):
    """``collect_inputs`` must use the pack that exists, not rebuild a weaker one.

    The defect these pin is a single collection that was the *wrong* one.
    ``collect(live=False)`` cannot produce a disassembly listing -- it never calls
    the live disassembly endpoint, so it stores ``disassembly = unavailable`` --
    and it was called unconditionally. So a target with a verified, 39-instruction
    pack on disk was briefed with ``DISASSEMBLY`` in ``missing_sections`` and had
    to go to Ghidra itself, and the listing-less pack was handed to ``validate``
    as ``evidence=``, which *overrides* the validator's own reuse of the
    persisted pack: a candidate that had already reached a static PASS standalone
    came back ``NOT_AVAILABLE`` inside the pipeline.
    """

    # A straight-line two-instruction body: no branch, no transfer, no constant
    # for a check to disagree about. The listing exists to be *present* here.
    LISTING = [{"address": "00b3d300", "instruction": "MOV EAX,0x1"},
               {"address": "00b3d301", "instruction": "RET"}]

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A", "B"))
        self.va = fx.TARGETS["A"]["va"]

    # -- helpers ----------------------------------------------------------- #
    def pack_rel(self, key="A"):
        return os.path.join("reconstruction", "evidence",
                            fx.bare(fx.TARGETS[key]["va"]), "evidence.json")

    def category(self, available, value=None):
        return {"availability": "available" if available else "unavailable",
                "evidence_state": "PERSISTED" if available else "MISSING",
                "evidence_level": "SUPPORTED" if available else "UNKNOWN",
                "provenance": ["synthetic-fixture"], "value": value, "reason": None}

    def persist_pack(self, key="A", listing=True, corrupt=False, va=None,
                     state="PERSISTED"):
        """Write an evidence pack exactly the way ``evidence.collect`` stamps one.

        The digest is stamped over the pack with ``content_sha256`` set to
        ``None`` and no ``paths`` key, because that is the document the stored
        hash covers. Stamping it any other way would produce a fixture the
        resolver is right to refuse -- and then the test would be measuring the
        refusal instead of the reuse.
        """
        from tools.reconstruction_tooling.models import sha256_json

        categories = {"disassembly": self.category(
            listing, {"instructions": [dict(item) for item in self.LISTING]})
            if listing else self.category(False),
            "decompilation": self.category(False)}
        pack = {"schema": "openspore-evidence-pack-1",
                "target": {"va": va or fx.TARGETS[key]["va"],
                           "address_kind": "linked_va"},
                "collector": {"source_policy": "live_with_persisted_fallback",
                              "live_requested": False, "live_attempts": []},
                "evidence_state": state,
                "categories": categories,
                "provenance": [{"ref": "synthetic-fixture", "mode": "persisted",
                                "source_class": "committed_artifact"}],
                "conflicts": [],
                "record": {},
                "content_sha256": None}
        pack["content_sha256"] = ("f" * 64 if corrupt
                                  else sha256_json(pack))
        path = os.path.join(self.info["root"], self.pack_rel(key))
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", encoding="utf-8") as handle:
            json.dump(pack, handle, indent=2, sort_keys=True)
            handle.write("\n")
        return pack

    def brief_of(self, inputs, key="A"):
        """The briefing the real path builds, not a hand-assembled one."""
        va = fx.TARGETS[key]["va"]
        return orch.brief(self.info["root"],
                          {"va": va, "queue_va": fx.bare(va),
                           "queue_id": fx.inv_id(key)},
                          inputs, "w-1", fx.inv_id(key), fx.SHA)

    def live_collection(self, state, digest="a" * 64):
        """A stand-in for a live ``collect``, distinguishable by its digest."""
        calls = []

        def fake_collect(root=None, va=None, live=False, write=True,
                         out_dir=None):
            calls.append({"live": live, "write": write})
            return {"schema": "openspore-evidence-pack-1",
                    "target": {"va": va, "address_kind": "linked_va"},
                    "collector": {"source_policy": "live_with_persisted_fallback",
                                  "live_requested": bool(live),
                                  "live_attempts": []},
                    "evidence_state": state,
                    "categories": {"disassembly": self.category(False)},
                    "provenance": [], "conflicts": [], "record": {},
                    "content_sha256": digest}
        fake_collect.calls = calls
        return fake_collect

    # -- the reuse --------------------------------------------------------- #
    def test_the_verified_persisted_pack_is_used_and_briefing_and_verdict_quote_it(self):
        stored = self.persist_pack()
        inputs = orch.collect_inputs(self.info["root"], self.va, live=False,
                                     write=False)
        # The defect itself, stated first: a pack with a listing is on disk, and
        # the evidence the pipeline used has one too.
        self.assertEqual(inputs["evidence"]["categories"]["disassembly"]
                         ["availability"], "available")
        # The pack that exists is the pack that is used, and the choice is named.
        self.assertEqual(inputs["pack_source"], "persisted_pack")
        self.assertEqual(inputs["pack_state"], "verified")
        self.assertIsNone(inputs["pack_note"])
        self.assertEqual(inputs["evidence"]["content_sha256"],
                         stored["content_sha256"])
        # ``collect`` was never called, so there is still no second round trip.
        self.assertNotIn("paths", inputs["evidence"])
        package = self.brief_of(inputs)
        # The worker is no longer told to go and find the listing itself.
        self.assertNotIn("DISASSEMBLY", package["evidence"]["missing_sections"])
        self.assertIsNotNone(package["disassembly"])
        self.assertEqual(len(package["disassembly"]["instructions"]),
                         len(self.LISTING))
        # One pack, quoted by the briefing, the context and the verdict alike.
        # A verdict reached over a different pack than the worker was shown is
        # the whole defect, so this is the assertion that matters.
        digest = inputs["evidence"]["content_sha256"]
        self.assertEqual(package["evidence"]["content_sha256"], digest)
        self.assertEqual(package["evidence"]["context_content_sha256"],
                         inputs["context"]["content_sha256"])
        self.assertEqual(
            inputs["validation"]["binary_evidence"]["content_sha256"], digest)
        self.assertEqual(
            inputs["validation"]["worker_context"]["pack_content_sha256"], digest)
        # The pack is used as written: a persisted pack is never relabelled live.
        self.assertEqual(package["evidence"]["state"], "PERSISTED")
        self.assertEqual(inputs["evidence"]["evidence_state"], "PERSISTED")

    def test_a_pack_whose_digest_does_not_verify_falls_back_and_says_so(self):
        self.persist_pack(corrupt=True)
        inputs = orch.collect_inputs(self.info["root"], self.va, live=False,
                                     write=False)
        # A pack that cannot be trusted must not vanish silently into a weaker
        # collection: the collection is used and the refusal is on the record.
        self.assertEqual(inputs["pack_source"], "recollected_live_false")
        self.assertEqual(inputs["pack_state"], "digest_mismatch")
        self.assertIn("does not reproduce its own content_sha256",
                      inputs["pack_note"])
        self.assertEqual(inputs["evidence"]["categories"]["disassembly"]
                         ["availability"], "unavailable")
        # The untrusted file is left on disk: a collection on this path cannot
        # produce a listing, so overwriting would destroy the only copy.
        with open(os.path.join(self.info["root"], self.pack_rel()),
                  encoding="utf-8") as handle:
            stored = json.load(handle)
        self.assertEqual(stored["content_sha256"], "f" * 64)
        # And the briefing and the verdict still agree, on the pack actually used.
        package = self.brief_of(inputs)
        self.assertEqual(package["evidence"]["content_sha256"],
                         inputs["evidence"]["content_sha256"])
        self.assertEqual(inputs["validation"]["binary_evidence"]["content_sha256"],
                         inputs["evidence"]["content_sha256"])
        self.assertIn("DISASSEMBLY", package["evidence"]["missing_sections"])

    def test_a_pack_for_another_target_is_refused_rather_than_used(self):
        self.persist_pack(va="0x00b3d400")
        inputs = orch.collect_inputs(self.info["root"], self.va, live=False,
                                     write=False)
        self.assertEqual(inputs["pack_source"], "recollected_live_false")
        self.assertEqual(inputs["pack_state"], "target_mismatch")
        self.assertIn("0x00b3d400", inputs["pack_note"])
        self.assertEqual(inputs["evidence"]["categories"]["disassembly"]
                         ["availability"], "unavailable")

    def test_live_true_prefers_a_genuine_live_read_over_a_persisted_pack(self):
        persisted = self.persist_pack()
        live = self.live_collection("LIVE")
        self.set_production("collect", live)
        inputs = orch.collect_inputs(self.info["root"], self.va, live=True,
                                     write=False)
        self.assertEqual(inputs["pack_source"], "collected_live")
        # The live read won, and it is a different pack from the one on disk.
        self.assertEqual(inputs["evidence"]["content_sha256"], "a" * 64)
        self.assertNotEqual(inputs["evidence"]["content_sha256"],
                            persisted["content_sha256"])
        self.assertEqual(live.calls, [{"live": True, "write": False}])
        package = self.brief_of(inputs)
        self.assertEqual(package["evidence"]["state"], "LIVE")
        self.assertEqual(package["evidence"]["content_sha256"],
                         inputs["validation"]["binary_evidence"]["content_sha256"])

    def test_live_true_falls_back_to_the_verified_pack_when_the_live_read_got_nothing(self):
        persisted = self.persist_pack()
        # A live request whose every endpoint failed: ``collect`` returns a pack
        # stamped PERSISTED, because that is its own word for "no live
        # observation happened". The verified pack is then the only pack that can
        # carry a listing, and losing it would cost the target its evidence.
        self.set_production("collect", self.live_collection("PERSISTED"))
        inputs = orch.collect_inputs(self.info["root"], self.va, live=True,
                                     write=False)
        self.assertEqual(inputs["pack_source"], "persisted_pack")
        self.assertEqual(inputs["pack_state"], "verified")
        self.assertEqual(inputs["evidence"]["content_sha256"],
                         persisted["content_sha256"])
        self.assertEqual(inputs["evidence"]["categories"]["disassembly"]
                         ["availability"], "available")

    def test_no_persisted_pack_behaves_exactly_as_before(self):
        inputs = orch.collect_inputs(self.info["root"], self.va, live=False,
                                     write=False)
        self.assertEqual(inputs["pack_source"], "recollected_live_false")
        self.assertEqual(inputs["pack_state"], "absent")
        self.assertIn("no persisted evidence pack", inputs["pack_note"])
        # The same three documents, the same collection, the same honest gaps.
        self.assertEqual(sorted(inputs),
                         ["context", "evidence", "pack_note", "pack_source",
                          "pack_state", "validation"])
        self.assertEqual(inputs["evidence"]["evidence_state"], "PERSISTED")
        self.assertEqual(inputs["evidence"]["categories"]["function_identity"]
                         ["availability"], "available")
        self.assertEqual(inputs["evidence"]["categories"]["disassembly"]
                         ["availability"], "unavailable")
        package = self.brief_of(inputs)
        self.assertIn("DECOMPILATION", package["evidence"]["missing_sections"])
        self.assertIn("DISASSEMBLY", package["evidence"]["missing_sections"])
        self.assertEqual(inputs["validation"]["binary_evidence"]["content_sha256"],
                         package["evidence"]["content_sha256"])


class WorkerChannelTest(fx.FixtureTestCase):
    """L1/L2/L5: the production adapter, the routing rule, and the launch params.

    These pin the fix for the reason the 4/5 ``malformed_worker_output`` rate
    existed: production went through ``command_line``, which passes the
    operator's argv verbatim, and the documented invocation carried no
    ``--format`` -- so every production worker ran ``--format default``, where
    OpenCode concatenates all assistant text into one stdout blob.
    """

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A", "B"))
        self.inputs = orch.collect_inputs(self.info["root"], "0x00b3d300",
                                         live=False, write=False)
        self.package = wc.briefing(
            "0x00b3d300", root=self.info["root"],
            evidence=self.inputs["evidence"], context=self.inputs["context"],
            validation=self.inputs["validation"], implementer_id="w-1",
            inv_id=fx.inv_id("A"), binary_sha256=fx.SHA, attempt=1)

    def launched_argv(self, worker, package=None):
        """Run the adapter with ``launch`` stubbed; return the argv it built."""
        seen = {}

        def recorder(argv, stdin_payload, cwd=None, env=None, timeout=3600):
            seen.update({"argv": list(argv), "stdin": stdin_payload,
                         "cwd": cwd, "env": env, "timeout": timeout})
            return {"returncode": 0, "timed_out": False, "stdout": b"",
                    "stderr": b"", "argv": list(argv), "failure": None}

        self.set_production("launch", recorder)
        raw, detail = worker(package or self.package)
        self.assertEqual(raw, b"")
        return seen, detail

    # -- L1 --------------------------------------------------------------- #
    def test_opencode_worker_runs_the_documented_jsonl_channel(self):
        worker = orch.opencode_worker()
        self.assertEqual(worker.channel, orch.CHANNEL_JSONL)
        seen, detail = self.launched_argv(worker)
        argv = seen["argv"]
        self.assertEqual(argv[:2], ["opencode", "run"])
        # The prompt is the briefing digest, the data channel is stdin, and the
        # structured channel is mandatory -- see agent_argv's docstring.
        self.assertIn(self.package["content_sha256"], argv[2])
        self.assertEqual(argv[3:], ["--print-logs", "--format", "json"])
        self.assertIs(seen["stdin"], self.package,
                      "the authoritative briefing did not travel on stdin")
        # the reply channel is reported, not inferred
        self.assertEqual(detail["channel"], orch.CHANNEL_JSONL)
        # and the argv is a pure function of the briefing
        again, _ = self.launched_argv(worker)
        self.assertEqual(again["argv"], argv)

    def test_opencode_worker_passes_through_model_agent_and_extra_flags(self):
        worker = orch.opencode_worker(model="some/model", agent="build",
                                     extra_argv=["--thinking"])
        argv = self.launched_argv(worker)[0]["argv"]
        self.assertEqual(argv[3:], ["--print-logs", "--format", "json",
                                    "--model", "some/model", "--agent", "build",
                                    "--thinking"])
        # every element stays a string: argv is never a shell string
        for element in argv:
            self.assertIsInstance(element, str)
        with_attach = orch.opencode_worker(attach="/tmp/briefing.json")
        self.assertEqual(self.launched_argv(with_attach)[0]["argv"][-2:],
                         ["--file", "/tmp/briefing.json"])
        # an operator who wants the prose channel can still ask for it
        prose = orch.opencode_worker(output_format="default")
        self.assertEqual(self.launched_argv(prose)[0]["argv"][3:5],
                         ["--print-logs", "--format"])

    # -- L2 --------------------------------------------------------------- #
    def test_opencode_route_decision_table(self):
        cases = [
            # (argv, mode, channel)
            (["opencode", "run", "--print-logs"], "auto", orch.CHANNEL_JSONL),
            (["/usr/local/bin/opencode", "run"], "auto", orch.CHANNEL_JSONL),
            (["opencode.exe", "run"], "auto", orch.CHANNEL_JSONL),
            (["opencode", "run", "--format", "default"], "auto",
             orch.CHANNEL_ARGV),
            (["opencode", "run", "--format=default"], "auto",
             orch.CHANNEL_ARGV),
            (["python3", "my_worker.py"], "auto", orch.CHANNEL_ARGV),
            (["/opt/bin/worker", "--format", "json"], "auto",
             orch.CHANNEL_ARGV),
            # a wrapper that merely *contains* "opencode" is not opencode
            (["opencode-runner"], "auto", orch.CHANNEL_ARGV),
            ([], "auto", orch.CHANNEL_ARGV),
            # mode overrides the table
            (["opencode", "run"], "argv", orch.CHANNEL_ARGV),
            (["python3", "my_worker.py"], "argv", orch.CHANNEL_ARGV),
            (["opencode", "run"], "jsonl", orch.CHANNEL_JSONL),
        ]
        for argv, mode, expected in cases:
            route = orch.opencode_route(argv, mode=mode)
            self.assertEqual(route["channel"], expected, (argv, mode, route))
            self.assertTrue(route["reason"], (argv, mode, route))
        # jsonl is a claim about a command that cannot honour it
        with self.assertRaises(orch.ToolError) as raised:
            orch.opencode_route(["python3", "my_worker.py"], mode="jsonl")
        self.assertEqual(raised.exception.code, "worker_channel_unsupported")
        with self.assertRaises(orch.ToolError) as raised:
            orch.opencode_route(["opencode"], mode="prose")
        self.assertEqual(raised.exception.code, "worker_channel_invalid")

    def test_worker_adapter_forces_json_and_keeps_the_operator_flags(self):
        worker = orch.worker_adapter(
            ["opencode", "run", "--print-logs", "--agent", "build",
             "--thinking"], "w-1", cwd="/tmp", timeout=42)
        self.assertEqual(worker.channel, orch.CHANNEL_JSONL)
        self.assertEqual(worker.route["extra_argv"], ["--agent", "build",
                                                      "--thinking"])
        argv = self.launched_argv(worker)[0]["argv"]
        self.assertEqual(argv[:2], ["opencode", "run"])
        # --print-logs is not duplicated: agent_argv already emits it, and the
        # adapter's argv is the documented one plus only what the operator added
        self.assertEqual(argv[3:], ["--print-logs", "--format", "json",
                                    "--agent", "build", "--thinking"])
        seen, _ = self.launched_argv(worker)
        self.assertEqual(seen["timeout"], 42)
        # a message positional is the operator's instruction, and the adapter
        # replaces it with the briefing digest rather than sending both
        prompt = orch.worker_adapter(["opencode", "run", "do the thing",
                                      "--pure"], "w-1")
        self.assertEqual(prompt.route["extra_argv"], ["--pure"])
        self.assertNotIn("do the thing",
                         self.launched_argv(prompt)[0]["argv"])
        # the escape hatch is byte-identical to what it always was
        verbatim = orch.worker_adapter(["python3", "w.py", "--flag"], "w-1")
        self.assertEqual(verbatim.channel, orch.CHANNEL_ARGV)
        self.assertEqual(self.launched_argv(verbatim)[0]["argv"],
                         ["python3", "w.py", "--flag"])

    # -- L5 --------------------------------------------------------------- #
    def test_launch_parameters_reach_the_worker(self):
        """``cwd``/``worker_env``/``worker_timeout`` used to be dropped.

        They reached ``process_target`` and were never read, so an operator's
        ``--timeout`` bounded nothing and a worker's cwd was whatever the
        orchestrator happened to inherit. They now travel through the adapter's
        ``configure_launch`` hook, which is the only way to forward them
        without widening the ``package -> (raw, detail)`` worker contract.
        """
        # an explicit value from the caller wins over the adapter's own
        seen, _ = self.launched_argv(orch.opencode_worker(timeout=11))
        self.assertEqual(seen["timeout"], 11)
        worker = orch.opencode_worker(timeout=11)
        self.assertTrue(orch._worker_launch_defaults(worker, timeout=5))
        self.assertEqual(self.launched_argv(worker)[0]["timeout"], 5)
        # a caller that says nothing must not reset a deliberate adapter default
        self.assertTrue(orch._worker_launch_defaults(worker, timeout=None,
                                                    cwd=None, env=None))
        self.assertEqual(self.launched_argv(worker)[0]["timeout"], 5)
        # a worker with no hook is left alone rather than broken
        self.assertFalse(orch._worker_launch_defaults(fx.worker("ok"),
                                                     cwd="/tmp", timeout=5))
        # and the parameters survive the whole lifecycle, not just the adapter.
        # The real launcher is captured from the fixture's saved production
        # value, not from the module: an earlier stub is still installed there.
        env = dict(os.environ, OPENSPORE_WORKER_MARKER="1")
        argv = [sys.executable, FAKE_WORKER, "--variant", "ok"]
        target = self.plan()["targets"][0]
        real_launch = self._saved_production["launch"]
        launches = []

        def recording_launch(argv_, stdin_payload, cwd=None, env=None,
                             timeout=3600):
            launches.append({"cwd": cwd, "env": env, "timeout": timeout})
            return real_launch(argv_, stdin_payload, cwd=cwd, env=env,
                               timeout=timeout)

        self.set_production("launch", recording_launch)
        record = fx.process_target(
            self.info["root"], target,
            orch.command_line(None, argv, "w-1", cwd=self.info["root"]),
            "w-launch", self.info["sha"], write=False,
            cwd=self.info["root"], worker_env=env, worker_timeout=17)
        # the real launcher ran, so this asserts the launch parameters rather
        # than a verdict: the synthetic pack has no decompilation, so the
        # validator's own verdict here is not this test's business
        self.assertTrue([event for event in record["events"]
                         if event["op"] == "ingest"][0]["ok"], record)
        # How many launches happen is the retry loop's business, not this test's
        # -- so every launch is checked, and the count is only bounded.
        self.assertGreaterEqual(len(launches), 1, launches)
        for launch in launches:
            self.assertEqual(launch["timeout"], 17,
                             "worker_timeout never reached launch")
            self.assertEqual(launch["env"], env)
            self.assertEqual(launch["cwd"], self.info["root"])


class WorkerChannelCliTest(fx.FixtureTestCase):
    """L2: the CLI routes ``--worker`` and can be told not to."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A",))

    def run_args(self, **kwargs):
        params = {"action": "run", "va": None, "limit": 1,
                  "worker": "opencode run --print-logs", "worker_id": "w-1",
                  "max_workers": 1, "ttl": 1800, "timeout": 60,
                  "allow_stale": False, "dry_run": True, "vas": None,
                  "out": None, "worker_channel": None}
        params.update(kwargs)
        return type("Args", (), params)()

    def orchestrate_with_spy(self, args):
        """Call the CLI's run path with ``run`` stubbed; return what it built."""
        built = {}
        real_adapter = orch.worker_adapter

        def fake_run(*positional, **named):
            built["worker"] = named.get("worker")
            built["kwargs"] = named
            return {"$schema": orch.RUN_SCHEMA, "status": "ok",
                    "summary": {"targets": 0}, "results": []}

        def fake_adapter(worker_argv, implementer_id=None, mode="auto",
                         cwd=None, env=None, timeout=3600):
            built["argv"] = list(worker_argv)
            built["mode"] = mode
            built["implementer_id"] = implementer_id
            return real_adapter(worker_argv, implementer_id, mode=mode,
                                cwd=cwd, env=env, timeout=timeout)

        self.set_production("run", fake_run)
        self.set_production("worker_adapter", fake_adapter)
        cli_mod._orchestrate(args, True)
        return built

    def test_cli_routes_an_opencode_worker_through_the_jsonl_channel(self):
        built = self.orchestrate_with_spy(self.run_args())
        self.assertEqual(built["argv"], ["opencode", "run", "--print-logs"])
        self.assertEqual(built["mode"], "auto")
        self.assertEqual(built["worker"].channel, orch.CHANNEL_JSONL)

    def test_cli_keeps_the_verbatim_escape_hatch(self):
        built = self.orchestrate_with_spy(
            self.run_args(worker="python3 tests/fixtures/fake_worker.py"))
        self.assertEqual(built["worker"].channel, orch.CHANNEL_ARGV)
        # the flag and the environment both reach the routing decision
        pinned = self.orchestrate_with_spy(
            self.run_args(worker_channel="argv"))
        self.assertEqual(pinned["mode"], "argv")
        self.assertEqual(pinned["worker"].channel, orch.CHANNEL_ARGV)
        os.environ["OPENSPORE_WORKER_CHANNEL"] = "argv"
        self.addCleanup(os.environ.pop, "OPENSPORE_WORKER_CHANNEL", None)
        from_env = self.orchestrate_with_spy(self.run_args())
        self.assertEqual(from_env["mode"], "argv")
        self.assertEqual(from_env["worker"].channel, orch.CHANNEL_ARGV)
        # the flag beats the environment
        explicit = self.orchestrate_with_spy(self.run_args(worker_channel="jsonl"))
        self.assertEqual(explicit["mode"], "jsonl")
        # a typo in the environment fails loudly instead of quietly disabling
        # the deterministic channel
        os.environ["OPENSPORE_WORKER_CHANNEL"] = "prose"
        with self.assertRaises(orch.ToolError) as raised:
            self.orchestrate_with_spy(self.run_args())
        self.assertEqual(raised.exception.code, "worker_channel_invalid")


class LaunchFailurePolicyTest(fx.FixtureTestCase):
    """L3: ``launch_detail["failure"]`` is decided, not ignored."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A",))
        self.target = self.plan()["targets"][0]

    def run_target(self, worker, implementer="w-1"):
        return fx.process_target(self.info["root"], self.target, worker,
                                 implementer, self.info["sha"], write=False)

    def test_spawn_failure_is_never_reported_as_a_malformed_reply(self):
        """A worker that never ran has no reply, so it has no malformed one.

        ``launch`` has always reported ``failure: "spawn_failed"`` and
        ``process_target`` never read it, so a missing binary was ingested as an
        empty reply: ``malformed_worker_output``, a burned malformed attempt, and
        a requeue -- the run blaming the model for an operator's typo.
        """
        worker = orch.command_line(None, ["/nonexistent/openspore-worker"], "w-1")
        with fx.spy_queue() as seen:
            record = self.run_target(worker)
        self.assertEqual(record["status"], "blocked", record)
        self.assertEqual(record["code"], "worker_spawn_failed")
        self.assertEqual(record["launch_failure"], "spawn_failed")
        self.assertNotEqual(record["code"], "malformed_worker_output")
        # the malformed budget is untouched: this is not a reply problem
        self.assertNotIn("_malformed", record["attempts"])
        # and the events say what happened, in the documented order
        self.assertEqual([event["op"] for event in record["events"]],
                         ["claim", "brief", "launch", "release"])
        self.assertEqual(record["events"][2]["failure"], "spawn_failed")
        self.assertNotIn("ingest", [event["op"] for event in record["events"]])
        # a parked row, with a reason a human has to clear, and no live lease
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["status"], "blocked")
        self.assertEqual(row["block_reason"], "escalated:worker_spawn_failed")
        self.assertIsNone(row["implementer_id"])
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        # the attempted checkpoint names the command that failed, argv[0] only
        payload = seen["checkpoint"][0]["kwargs"]["payload"]
        self.assertEqual(payload["worker_command"], "/nonexistent/openspore-worker")
        self.assertEqual(payload["stage"], "LAUNCH")
        self.assertEqual(payload["next_action"], "fix_worker_command")
        self.assertIn("No such file", payload["last_error"])
        # the durable write is refused (kg_tools._queue_update_owned), so the
        # release reason is the only durable artifact
        self.assertEqual(seen["checkpoint"][0]["result"]["code"],
                         "invalid_params")
        self.assertEqual(len(seen["release"]), 1)
        self.assertEqual(seen["release"][0]["kwargs"]["to"], "blocked")
        # an empty command line is the same class of problem: no child ran. It
        # gets its own root because the case above already parked that row.
        self.make_root_at("blank", keys=("A",))
        blank_target = self.plan()["targets"][0]
        blank = fx.process_target(
            self.info["root"], blank_target,
            orch.command_line(None, [], "w-1"), "w-empty",
            self.info["sha"], write=False)
        self.assertEqual(blank["status"], "blocked", blank)
        self.assertEqual(blank["code"], "worker_spawn_failed")

    def test_nonzero_exit_with_a_valid_result_is_accepted_and_recorded(self):
        """Policy: the document is the deliverable; the exit code is metadata.

        A worker that printed a contract-valid result and then crashed has still
        answered, and the static validator -- not the exit status -- is what
        adjudicates the answer. The mirror-image error is worse: treating a
        nonzero exit as a verdict would discard verified work, and treating a
        launch failure as a validation failure would blame a verdict on
        something the validator never saw. So the exit code is recorded in the
        launch event and in the checkpoint, and never acted on.
        """
        self.stub_validator("PASS")
        argv = [sys.executable, FAKE_WORKER, "--variant", "ok",
                "--exit-code", "3"]
        with fx.spy_queue() as seen:
            record = self.run_target(orch.command_line(None, argv, "w-1"))
        self.assertEqual(record["status"], "complete", record)
        self.assertEqual(record["outcome"], "IMPLEMENTED")
        self.assertEqual(record["validation"], "PASS")
        # the happy path op order is unchanged by any of this
        self.assertEqual([event["op"] for event in record["events"]],
                         HAPPY_PATH_OPS, record["events"])
        launch = [event for event in record["events"] if event["op"] == "launch"][0]
        self.assertEqual(launch["returncode"], 3)
        self.assertEqual(launch["failure"], "nonzero_exit")
        # visible in the checkpoint too, so the row carries it after the run
        payload = seen["checkpoint"][0]["kwargs"]["payload"]
        self.assertEqual(payload["launch_failure"], "nonzero_exit")
        # a clean exit records nothing, so the two are never conflated
        self.make_root_at("clean", keys=("A",))
        clean_target = self.plan()["targets"][0]
        clean = fx.process_target(
            self.info["root"], clean_target,
            orch.command_line(None, [sys.executable, FAKE_WORKER,
                                    "--variant", "ok"], "w-2"),
            "w-2", self.info["sha"], write=False)
        self.assertEqual(clean["status"], "complete", clean)
        self.assertIsNone(clean["events"][2]["failure"])
        self.assertNotIn("launch_failure", clean["events"][2])


class LeaseSafetyTest(fx.FixtureTestCase):
    """L4: no lease survives an exception."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A",))

    def exploding_worker(self, package):
        raise RuntimeError("worker callable exploded")

    def test_exception_after_claim_releases_the_lease(self):
        record = fx.process_target(self.info["root"],
                                   self.plan()["targets"][0],
                                   self.exploding_worker, "w-boom",
                                   self.info["sha"], write=False)
        self.assertEqual(record["status"], "error", record)
        self.assertEqual(record["code"], "RuntimeError")
        self.assertIn("worker callable exploded", record["message"])
        self.assertTrue(record["lease_released"], record)
        # the failure is auditable: an event, the attempted checkpoint, and the
        # row's own reason
        self.assertEqual([event["op"] for event in record["events"]],
                         ["claim", "brief", "error", "checkpoint", "release"],
                         record["events"])
        self.assertEqual(record["events"][-1]["to"], "blocked")
        self.assertEqual(record["events"][-1]["ok"], True, record["events"])
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertNotEqual(row["status"], "active", row)
        self.assertEqual(row["status"], "blocked")
        self.assertEqual(row["block_reason"], "escalated:RuntimeError")
        self.assertIsNone(row["implementer_id"])
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_a_run_whose_worker_raises_reports_no_completion(self):
        self.stub_validator("PASS")
        outcome = orch.run(root=self.info["root"], limit=1,
                           worker=self.exploding_worker, implementer_id="orch",
                           write=False)
        self.assertEqual(outcome["status"], "ok")
        self.assertEqual(outcome["summary"]["error"], 1, outcome["summary"])
        self.assertEqual(outcome["summary"]["complete"], 0, outcome["summary"])
        self.assertEqual(outcome["summary"]["errors"], [])
        self.assertEqual(fx.rows_by_status(self.db, "active"), [],
                         "a failed run left a live lease behind")
        self.assertEqual(outcome["results"][0]["code"], "RuntimeError")

    def test_every_post_claim_failure_point_releases_the_lease(self):
        """``worker``, ``validate``, ``checkpoint`` and ``release`` can all raise.

        Each case gets its own root because a handled exception is still
        terminal for the row. The ``release`` case raises on the *first* call
        only, which is the case that proves the release is retried by the
        failure path rather than skipped.
        """
        def raiser(name, calls=()):
            seen = []
            original = getattr(name == "validate" and orch or q, name)

            def boom(*positional, **named):
                seen.append(positional)
                if not calls or len(seen) in calls:
                    raise RuntimeError("%s exploded" % name)
                return original(*positional, **named)
            boom.calls = seen
            return boom

        cases = (("validate", "ok", (2,)), ("checkpoint", "malformed_json", ()),
                 ("release", "malformed_json", (1,)))
        for name, variant, calls in cases:
            self.make_root_at("boom-%s" % name, keys=("A",))
            target = self.plan()["targets"][0]
            # ``validate`` only runs for an accepted reply; the checkpoint and
            # release that follow a *rejected* one are the pair the other two
            # cases break, on the path that actually runs.
            worker = fx.worker(variant)
            if name == "validate":
                # raise on the *second* call: the first is collect_inputs'
                # own, inside its ToolError guard
                self.set_production("validate", raiser(name, calls=calls))
            else:
                original = getattr(q, name)
                setattr(q, name, raiser(name, calls=calls))
            try:
                record = fx.process_target(self.info["root"], target, worker,
                                           "w-%s" % name, self.info["sha"],
                                           write=False)
            finally:
                # restored here, not in a cleanup: the next case must not run
                # under this case's patch
                if name != "validate":
                    setattr(q, name, original)
            self.assertEqual(record["status"], "error", (name, record))
            self.assertIn("%s exploded" % name, record["message"], (name, record))
            self.assertTrue(record["lease_released"], (name, record))
            row = fx.row(self.db, fx.inv_id("A"))
            self.assertNotEqual(row["status"], "active", (name, row))
            self.assertIsNone(row["implementer_id"], (name, row))
            self.assertEqual(fx.rows_by_status(self.db, "active"), [], name)

    def test_a_broken_queue_write_is_reported_not_raised(self):
        """The failure path may not fail, or it loses the lease and the trail.

        If the very write that ends the lease is what is broken, raising out of
        the failure path would leave the row ``active`` *and* discard the events
        that explain it. So the write is attempted, its failure is recorded, and
        the record says plainly that no lease was released.
        """
        self.make_root_at("boom-hard", keys=("A",))
        target = self.plan()["targets"][0]
        original = q.release
        self.addCleanup(setattr, q, "release", original)

        def always_fails(*positional, **named):
            raise RuntimeError("the queue is down")

        setattr(q, "release", always_fails)
        record = fx.process_target(self.info["root"], target,
                                   fx.worker("malformed_json"), "w-down",
                                   self.info["sha"], write=False)
        self.assertEqual(record["status"], "error", record)
        self.assertFalse(record["lease_released"], record)
        self.assertEqual(record["events"][-1]["code"], "queue_write_failed")
        self.assertIn("the queue is down", record["events"][-1]["message"])
        # the row is still leased, and that is now visible rather than silent
        self.assertEqual(len(fx.rows_by_status(self.db, "active")), 1)

    def test_a_displaced_worker_never_releases_another_owners_lease(self):
        """Ownership is checked twice: the flag, and the queue itself.

        A worker that lost its lease mid-run (here: the claim is stolen after
        the launch) must not be able to release the *new* holder's lease, and
        must not report having released anything.
        """
        target = self.plan()["targets"][0]

        def steal_then_answer(package):
            # someone else takes the lease while this worker is running
            queue_op(op="release", id=fx.inv_id("A"), implementer_id="w-1",
                     to="queued")
            queue_op(op="claim", id=fx.inv_id("A"), implementer_id="thief",
                     binary_sha256=fx.SHA)
            return "{not json\n", {"returncode": 1, "timed_out": False,
                                   "failure": "nonzero_exit"}

        record = fx.process_target(self.info["root"], target, steal_then_answer,
                                   "w-1", self.info["sha"], write=False)
        # the malformed path still releases; the queue refuses because the row
        # is no longer this worker's
        self.assertEqual(record["status"], "partial", record)
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["implementer_id"], "thief", row)
        self.assertEqual(row["status"], "active", row)


class PipelineFailureTest(fx.FixtureTestCase):
    """C21-C26: bounded, typed failure handling."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A",))
        self.plan_once = self.plan()
        self.target = self.plan_once["targets"][0]

    def run_target(self, worker, implementer="w-1", **kwargs):
        return fx.process_target(self.info["root"], self.target, worker,
                                 implementer, self.info["sha"], write=False,
                                 **kwargs)

    # -- C21 -------------------------------------------------------------- #
    def test_malformed_output_releases_the_lease_and_counts(self):
        self.stub_validator("PASS")
        worker = fx.worker("malformed_json")
        with fx.spy_queue() as seen:
            record = self.run_target(worker)
        self.assertEqual(record["status"], "partial")
        self.assertEqual(record["code"], "malformed_worker_output")
        self.assertEqual(record["attempts"]["_malformed"], 1)
        self.assertEqual(record["attempts"]["_total"], 1)
        self.assertEqual([event["op"] for event in record["events"]],
                         ["claim", "brief", "launch", "ingest", "release"])
        self.assertFalse(record["events"][3]["ok"])
        self.assertEqual(record["events"][3]["code"],
                         "malformed_worker_output")
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["status"], "queued")
        self.assertIsNone(row["implementer_id"])
        # exactly one release, to queued, and the malformed checkpoint carried
        # the raw digest plus an explicit next action
        self.assertEqual(len(seen["release"]), 1, seen["release"])
        self.assertEqual(seen["release"][0]["kwargs"]["to"], "queued")
        self.assertEqual(len(seen["checkpoint"]), 1, seen["checkpoint"])
        payload = seen["checkpoint"][0]["kwargs"]["payload"]
        import hashlib
        self.assertEqual(payload["raw_sha256"],
                         hashlib.sha256(
                             "{not json at all\n".encode("utf-8")).hexdigest())
        self.assertEqual(payload["next_action"], "respawn_worker")
        self.assertEqual(payload["stage"], "REPLACE")
        self.assertIn("no worker result document found", payload["last_error"])
        self.assertEqual(seen["checkpoint"][0]["kwargs"]["attempts"],
                         {"_malformed": 1, "_total": 1})
        # the durable write is refused (kg_tools._queue_update_owned)
        self.assertEqual(seen["checkpoint"][0]["result"]["code"],
                         "invalid_params")
        self.assertIsNone(row["attempts"])
        self.assertIsNone(row["checkpoint"])
        self.assertEqual(len(worker.calls), 1)

    # -- C22 (PINNED DEFECT) ----------------------------------------------- #
    def test_pinned_malformed_counter_never_reaches_its_bound(self):
        """PINNED DEFECT -- ``MAX_MALFORMED`` is unreachable.

        ``orchestrate.process_target`` returns ``partial`` on the *first*
        malformed reply (orchestrate.py:450-464), and the ``_malformed``
        counter is only ever persisted through ``queue.checkpoint``, which is
        refused (kg_tools.py:901-906). So a target that keeps answering with
        garbage is re-run for ever and never reaches ``blocked``. Intended
        assertion once fixed: the second call returns
        ``status == "blocked"`` with ``code`` starting ``escalated:`` and the
        worker is never invoked a third time.
        """
        self.stub_validator("PASS")
        worker = fx.worker("malformed_json")
        first = self.run_target(worker)
        second = self.run_target(worker, implementer="w-2")
        self.assertEqual(first["status"], "partial")
        self.assertEqual(second["status"], "partial")
        self.assertEqual(fx.row(self.db, fx.inv_id("A"))["status"], "queued")
        self.assertEqual(len(worker.calls), 2,
                         "a third worker invocation would be a bound breach")
        self.assertNotIn("escalated", str(second["code"]))

    # -- C23 -------------------------------------------------------------- #
    def test_validation_fail_retries_then_blocks(self):
        self.make_root(name_="unused") if False else None
        self.make_root_at("fail-root", keys=("A",), conflicts=("A",))
        target = self.plan()["targets"][0]
        worker = fx.worker("ok")
        record = fx.process_target(self.info["root"], target, worker, "w-fail",
                                   self.info["sha"], write=False)
        self.assertEqual(record["status"], "blocked")
        self.assertEqual(record["code"], "escalated:validation_fail")
        self.assertLessEqual(len(worker.calls), orch.MAX_VALIDATION_RETRIES + 1)
        self.assertEqual(len(worker.calls), orch.MAX_VALIDATION_RETRIES + 1)
        verdicts = [event["status"] for event in record["events"]
                    if event["op"] == "validate"]
        self.assertEqual(set(verdicts), {"FAIL"})
        retries = [event for event in record["events"]
                   if event["op"] == "release" and event.get("why") == "retry"]
        self.assertEqual(len(retries), orch.MAX_VALIDATION_RETRIES)
        # the worker was told to address the validator findings each retry
        self.assertEqual(sorted(worker.attempts()), [1, 2, 3])

    # -- C24 -------------------------------------------------------------- #
    def test_validation_warn_requests_review_and_never_closes(self):
        # The verdict is stubbed because this test owns the ``WARN -> review``
        # disposition mapping, not what the real validator says about a synthetic
        # fixture: an orchestration test needs a verdict it chose, not one earned.
        # The real validator over this fixture is exercised by
        # ``tests/test_validation_dimensions.py``.
        self.stub_validator("WARN")
        worker = fx.worker("ok")
        record = self.run_target(worker, implementer="w-warn")
        self.assertEqual(record["status"], "review_required")
        self.assertEqual(record["code"], "validation_warn")
        self.assertEqual(record["validation"], "WARN")
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["status"], "blocked")
        self.assertEqual(row["block_reason"], "validation_warn")
        self.assertIsNone(row["implementer_id"])
        self.assertEqual(len(worker.calls), 1,
                         "a WARN must not burn a retry")
        self.assertNotIn("close", [event["op"] for event in record["events"]])
        self.assertNotIn("close", [event["op"] for event in record["events"]])

    # -- C25 -------------------------------------------------------------- #
    def test_always_failing_target_terminates(self):
        self.make_root_at("bound-root", keys=("A",), conflicts=("A",))
        target = self.plan()["targets"][0]
        worker = fx.worker("ok")
        record = fx.process_target(self.info["root"], target, worker, "w-bound",
                                   self.info["sha"], write=False, iterations=3)
        self.assertEqual(record["status"], "blocked")
        self.assertEqual(len(worker.calls), 3)
        self.assertLessEqual(len(worker.calls), max(3, orch.MAX_ITERATIONS))

    def test_iteration_bound_raises_instead_of_looping_forever(self):
        self.make_root()
        self.set_production("MAX_ITERATIONS", 1)
        plan = self.plan()
        self.assertGreaterEqual(len([wave for wave in plan["waves"]
                                     if wave["reason"] == "ready"]), 2)
        with self.assertRaises(orch.OrchestrationBoundExceeded) as raised:
            orch.run(root=self.info["root"], limit=20, worker=fx.worker("ok"),
                     implementer_id="orch", write=False)
        self.assertEqual(raised.exception.code,
                         "orchestration_bound_exceeded")
        self.assertEqual(raised.exception.details["waves"], 1)

    # -- C26 -------------------------------------------------------------- #
    def test_reconcile_decision_matrix(self):
        target = {"va": "0x00b3d300"}
        expected = [
            ("IMPLEMENTED", "PASS", "complete", "validated"),
            ("PARTIAL", "PASS", "complete", "validated"),
            ("STRUCTURAL_ONLY", "PASS", "complete", "validated"),
            ("IMPLEMENTED", "FAIL", "retry", "validation_fail"),
            ("PARTIAL", "FAIL", "retry", "validation_fail"),
            ("IMPLEMENTED", "WARN", "review", "validation_warn"),
            # A candidate the validator cannot check is a candidate defect, not
            # a review request: retrying is the only thing that fixes it, and
            # the attempt budget bounds it. An honest STILL_UNKNOWN with the
            # same verdict IS a review item -- there is no candidate to retry.
            ("IMPLEMENTED", "UNKNOWN", "retry", "candidate_not_validatable"),
            ("IMPLEMENTED", "NOT_AVAILABLE", "retry",
             "candidate_not_validatable"),
            ("PARTIAL", "NOT_AVAILABLE", "retry", "candidate_not_validatable"),
            ("STILL_UNKNOWN", "NOT_AVAILABLE", "review",
             "validation_not_available"),
            ("STILL_UNKNOWN", "UNKNOWN", "review", "validation_unknown"),
            ("STILL_UNKNOWN", "PASS", "retry", "still_unknown"),
            ("BLOCKED", "NOT_AVAILABLE", "review", "validation_not_available"),
            ("BLOCKED", "PASS", "retry", "blocked"),
            ("BLOCKED", "FAIL", "retry", "validation_fail"),
            ("FAILED_VALIDATION", "PASS", "retry", "failed_validation"),
        ]
        for outcome, verdict, action, code in expected:
            decision = orch.reconcile(outcome, verdict, target, fx.inv_id("A"),
                                      "w", fx.SHA, {"REPLACE": 1}, ["ref"],
                                      detail=None)
            self.assertEqual((decision["action"], decision["code"]),
                             (action, code), (outcome, verdict, decision))
            self.assertEqual(decision["va"], "0x00b3d300")
            self.assertEqual(decision["queue_id"], fx.inv_id("A"))
            self.assertEqual(decision["validation"], verdict)
            self.assertEqual(decision["evidence_refs"], ["ref"])
        for outcome in wc.TERMINAL_OUTCOMES:
            for verdict in ("FAIL", "WARN", "UNKNOWN", "NOT_AVAILABLE"):
                decision = orch.reconcile(outcome, verdict, target, "i", "w",
                                          fx.SHA, {}, [])
                self.assertNotEqual(decision["action"], "complete",
                                    (outcome, verdict))

    # -- C27 (WAS PINNED DEFECT -- now the fixed behaviour) --------------- #
    def test_non_mapping_validation_field_fails_closed_instead_of_raising(self):
        """A hostile ``validation`` field is refused, not raised on.

        This was PINNED DEFECT C27. ``parse_result`` documents "Never raises
        for a bad payload", but it read
        ``(document.get("validation") or {}).get("status")`` without a type
        check, so ``"validation": <list|str>`` raised ``AttributeError``. In
        ``process_target`` that exception escaped the whole retry loop and left
        the queue row ``active`` with a live lease -- the exact unrecoverable
        state the orchestrator exists to avoid (orchestrate.py:16-33), and one
        that would also have corrupted the malformed-output statistics the
        parser rework had to measure.

        The fix type-checks before reading, so the payload is now a *typed*
        refusal: ``malformed_worker_output``, the run ends ``partial``, and the
        row returns to ``queued`` with no live lease.
        """
        self.stub_validator("PASS")
        for value in ("PASS", [1, 2], 7, True):
            document = fx.result_document("A")
            document["validation"] = value
            raw = json.dumps(document)
            parsed = wc.parse_result(raw, va="0x00b3d300")
            self.assertFalse(parsed["accepted"], (value, parsed))
            self.assertEqual(parsed["code"], "malformed_worker_output")
            self.assertIn("'validation' must be an object", parsed["reason"])
            self.assertEqual(parsed["field"], "validation")
            worker = (lambda payload, r=raw: (r, {"returncode": 0,
                                                 "timed_out": False}))
            record = self.run_target(worker)
            self.assertEqual(record["status"], "partial", (value, record))
            self.assertEqual(record["code"], "malformed_worker_output")
            row = fx.row(self.db, fx.inv_id("A"))
            self.assertEqual(row["status"], "queued", (value, row["status"]))
            self.assertIsNone(row["implementer_id"], (value, row))
        # a well-formed verdict mapping is accepted (the control case)
        accepted = wc.parse_result(
            json.dumps(dict(fx.result_document("A"),
                            validation={"status": "WARN"})), va="0x00b3d300")
        self.assertTrue(accepted["accepted"], accepted)


class RunPipelinePinnedDefectTest(fx.FixtureTestCase):
    """``orchestrate.run``'s dispatch loop, end to end.

    Historically a home for pinned defects in ``run`` itself; both are fixed
    now, so the tests here are live regression tests -- a green run must have
    actually dispatched work, and must not have promoted anything it had no
    right to promote.
    """

    def test_run_dispatches_every_ready_wave_target(self):
        """REGRESSION: every dispatch thread must actually receive its unit.

        ``threading.Thread(target=thread_fn, name=...)`` was created without
        ``args=(unit_key, members)``, so every dispatch thread raised
        ``TypeError`` before ``dispatch`` ran. ``run()`` then returned a
        success envelope with ``summary["targets"] == 0`` and
        ``summary["errors"] == []``: a green run that reconstructed nothing and
        reported no error. This pins the real behaviour -- a wave's targets
        appear in ``results`` with a populated event trail, and no thread dies
        silently.

        Note the run below uses the REAL validator (no stub), so every target
        ends ``review_required``/``blocked`` and nothing reaches ``complete``.
        That is what makes this a test of the frozen-plan view: the dependent
        must NOT be promoted here, because a prerequisite that ended
        ``blocked`` has not landed. Promotion itself is covered with a PASSing
        validator in
        ``tests.test_orchestration_scheduling.DispatchOrderingTest``.
        """
        self.make_root()
        plan = self.plan()
        ready = [wave for wave in plan["waves"] if wave["reason"] == "ready"]
        self.assertEqual(len(ready), 2)
        by_va = {item["va"]: item for item in plan["targets"]}
        # Only dispatchable targets are dispatched: a wave also carries the
        # dependents that were scheduled but are not yet eligible, and those
        # must be skipped rather than forced.
        expected = [entry["va"] for wave in ready
                    for entry in wave["targets"]
                    if by_va[entry["va"]]["dispatchable"]]
        deferred = [entry["va"] for wave in ready
                    for entry in wave["targets"]
                    if not by_va[entry["va"]]["dispatchable"]]
        self.assertGreaterEqual(len(expected), 5)
        self.assertTrue(deferred, "fixture should exercise a deferred target")
        failures = []
        original_hook = threading.excepthook

        def recorder(args):
            failures.append("%s: %s" % (args.exc_type.__name__, args.exc_value))

        threading.excepthook = recorder
        self.addCleanup(lambda: setattr(threading, "exceptthook", original_hook))
        outcome = orch.run(root=self.info["root"], limit=20,
                           worker=fx.worker("ok"), implementer_id="orch",
                           write=False)
        threading.excepthook = original_hook
        self.assertEqual(outcome["status"], "ok")
        self.assertEqual(failures, [], "a dispatch thread died silently")
        self.assertEqual(outcome["summary"]["errors"], [])
        # the first wave is fully dispatchable, so it must be fully dispatched
        self.assertEqual(len(outcome["results"]), len(expected), outcome["summary"])
        self.assertEqual(sorted(record["va"] for record in outcome["results"]),
                         sorted(expected))
        # and the deferred dependent was never touched
        for va in deferred:
            self.assertNotIn(va, [record["va"] for record in outcome["results"]])
        self.assertEqual(outcome["summary"]["targets"], len(expected))
        self.assertEqual(outcome["summary"]["error"], 0)
        self.assertEqual(outcome["summary"]["skipped"], 0)
        # nothing completed, so nothing was promoted and the dependent's row
        # was never written
        self.assertEqual(outcome["summary"]["complete"], 0, outcome["summary"])
        for va in deferred:
            row = fx.row(self.db, by_va[va]["queue_id"])
            self.assertEqual(row["status"], "queued", (va, row))
            self.assertIsNone(row["updated_at"], (va, row))
        for record in outcome["results"]:
            self.assertTrue(record["events"],
                            "a dispatched target recorded no events: %r" % record)
            self.assertEqual(record["events"][0]["op"], "claim")
            self.assertTrue(record["events"][0]["ok"])
        # no lease is left behind by a finished run
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        # ``waves`` counts dispatch *rounds*, not waves in the plan: the plan
        # has two ready waves but the second one had nothing dispatchable, so
        # the loop broke out of it without counting a round
        self.assertEqual(outcome["summary"]["waves"], 1, outcome["summary"])

    def test_dry_run_plans_without_dispatching(self):
        self.make_root()
        outcome = orch.run(root=self.info["root"], limit=20,
                           worker=fx.worker("ok"), implementer_id="orch",
                           write=False, dry_run=True)
        self.assertTrue(outcome["dry_run"])
        self.assertEqual(outcome["summary"], {"planned": 6})
        self.assertEqual(outcome["results"], [])
        self.assertEqual(len(fx.rows_by_status(self.db, "queued")), 6)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_run_requires_an_explicit_worker(self):
        self.make_root()
        with self.assertRaises(orch.ToolError) as raised:
            orch.run(root=self.info["root"], limit=1)
        self.assertEqual(raised.exception.code, "worker_required")


class ConcurrencyIsolationTest(fx.FixtureTestCase):
    """E31-E36: concurrency, isolation and determinism."""

    EIGHT = ("A", "B", "C", "D", "P", "Q", "E1", "E2")
    TEN = EIGHT + ("E3", "E4")

    def seeds(self):
        return {key: {"attempts": json.dumps({"REPLACE": index + 1}),
                      "evidence_refs": json.dumps(["seed/%s" % key])}
                for index, key in enumerate(self.EIGHT)}

    def setUp(self):
        super().setUp()
        self.make_root_at("eight", keys=self.TEN)
        self.seed_db(rows=self.seeds())

    # -- E31 -------------------------------------------------------------- #
    def test_concurrent_ingestion_of_eight_targets_is_isolated(self):
        self.stub_validator("PASS")
        plan = self.plan(limit=50)
        by_key = {item["queue_id"]: item for item in plan["targets"]}
        for round_index in range(2):
            fresh = dict(self.seeds())
            for key in fresh:
                fresh[key]["status"] = "queued"
            self.seed_db(rows=fresh)
            worker = fx.worker("ok")
            targets = [by_key[fx.inv_id(key)] for key in self.EIGHT]

            def ingest(item, key):
                return fx.process_target(self.info["root"], item, worker,
                                         "w-%s" % key, self.info["sha"],
                                         write=False)

            with ThreadPoolExecutor(max_workers=8) as executor:
                records = dict(zip(self.EIGHT, executor.map(
                    lambda pair: ingest(*pair),
                    [(item, key) for key, item in zip(self.EIGHT, targets)])))
            self.assertEqual(len(records), 8)
            for index, key in enumerate(self.EIGHT):
                record = records[key]
                self.assertEqual(record["va"], fx.TARGETS[key]["va"], (key, record))
                self.assertEqual(record["status"], "complete", (key, record))
                row = fx.row(self.db, fx.inv_id(key))
                # no cross-contamination of implementer_id
                self.assertEqual(row["implementer_id"], "w-%s" % key, (key, row))
                # no lost update: the row's own seed survived untouched
                self.assertEqual(json.loads(row["attempts"]),
                                 {"REPLACE": index + 1}, (key, row))
                self.assertEqual(json.loads(row["evidence_refs"]),
                                 ["seed/%s" % key], (key, row))
                # the in-memory record only ever carried its own artifacts
                self.assertEqual(record["source_files"], [fx.source_rel(key)])
                self.assertNotIn("seed/%s" % (self.EIGHT[(index + 1) % 8]),
                                 record["source_files"])
            self.assertEqual(fx.rows_by_status(self.db, "active"), [])
            self.assertEqual(len(fx.rows_by_status(self.db, "done")), 8)
            self.assertEqual(len(worker.calls), 8, round_index)
            self.assertEqual(len(set(call["thread"] for call in worker.calls)), 8,
                             "targets were serialised instead of run in parallel")

    # -- E32 -------------------------------------------------------------- #
    def test_ingestion_by_a_non_owner_is_refused(self):
        self.stub_validator("PASS")
        plan = self.plan()
        target = plan["targets"][0]
        queue_op(op="claim", id=target["queue_id"], implementer_id="owner",
                 binary_sha256=fx.SHA)
        worker = fx.worker("ok")
        record = fx.process_target(self.info["root"], target, worker,
                                   "intruder", self.info["sha"], write=False)
        self.assertEqual(record["status"], "skipped")
        self.assertEqual(record["code"], "already_claimed")
        self.assertEqual([event["op"] for event in record["events"]], ["claim"])
        self.assertEqual(worker.calls, [])
        self.assertEqual(fx.row(self.db, target["queue_id"])["implementer_id"],
                         "owner")
        self.assertEqual(fx.row(self.db, target["queue_id"])["status"], "active")
        # and the durable write path is guarded too
        self.assertEqual(
            q.checkpoint(target["queue_id"], "intruder", payload={"x": 1})
            ["code"], "not_owner")

    # -- E33 -------------------------------------------------------------- #
    def test_two_concurrent_orchestrations_claim_each_target_exactly_once(self):
        self.stub_validator("PASS")
        keys = ("A", "B", "D", "E1")
        plan = self.plan(limit=50)
        by_key = {item["queue_id"]: item for item in plan["targets"]}
        barrier = threading.Barrier(2)
        workers = {"left": fx.worker("ok"), "right": fx.worker("ok")}

        def side(name):
            def run():
                barrier.wait(timeout=30)
                return [fx.process_target(self.info["root"],
                                          by_key[fx.inv_id(key)], workers[name],
                                          name, self.info["sha"], write=False)
                        for key in keys]
            return run

        with ThreadPoolExecutor(max_workers=2) as executor:
            left, right = list(executor.map(
                lambda name: side(name)(), ("left", "right")))
        self.assertEqual(len(left), 4)
        self.assertEqual(len(right), 4)
        for key in keys:
            outcomes = [record["status"] for record in left + right
                        if record["va"] == fx.TARGETS[key]["va"]]
            self.assertEqual(outcomes.count("complete"), 1, (key, outcomes))
            self.assertEqual(outcomes.count("skipped"), 1, (key, outcomes))
            row = fx.row(self.db, fx.inv_id(key))
            self.assertEqual(row["status"], "done", (key, row))
            self.assertIn(row["implementer_id"], ("left", "right"))
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        self.assertEqual(len(workers["left"].calls) +
                         len(workers["right"].calls), 4)

    # -- E34 -------------------------------------------------------------- #
    def test_plan_and_lifecycle_are_deterministic(self):
        from tools.reconstruction_tooling.models import canonical_json

        first = self.plan(limit=50)
        second = self.plan(limit=50)
        self.assertEqual(canonical_json(first), canonical_json(second))
        self.assertEqual(first["summary"]["wave_widths"],
                         second["summary"]["wave_widths"])

        summaries = []
        for name in ("repeat-a", "repeat-b"):
            self.make_root_at(name)
            self.stub_validator("PASS")
            plan = self.plan(limit=50)
            records, errors = fx.dispatch_waves(self.info["root"], plan,
                                                fx.worker("ok"), "orch",
                                                max_workers=4, write=False)
            self.assertEqual(errors, [])
            dispatchable = [item for item in plan["targets"]
                            if item["dispatchable"]]
            self.assertEqual(len(records), len(dispatchable), name)
            self.assertEqual(sorted(item["va"] for item in records),
                             sorted(item["va"] for item in dispatchable), name)
            summaries.append(fx.scrub(fx.summary_of(records)))
        self.assertEqual(summaries[0], summaries[1])

    # -- E35 -------------------------------------------------------------- #
    def test_committed_database_and_working_tree_are_untouched(self):
        before_db = fx.committed_db_fingerprint()
        before_git = fx.git_status()
        self.stub_validator("PASS")
        plan = self.plan(limit=50)
        records, errors = fx.dispatch_waves(self.info["root"], plan,
                                            fx.worker("ok"), "orch",
                                            max_workers=4, write=False)
        self.assertEqual(errors, [])
        orch.run(root=self.info["root"], limit=50, worker=fx.worker("ok"),
                 implementer_id="orch", write=False)
        after_db = fx.committed_db_fingerprint()
        after_git = fx.git_status()
        self.assertEqual(after_db, before_db)
        self.assertNotEqual(after_db["sha256"], None)
        # Tracked-file dirt must be identical. Untracked ("??") entries are
        # compared as a set difference only, because other agents share this
        # working tree; a new untracked path is reported, never asserted.
        self.assertEqual([item for item in after_git if item[0] != "??"],
                         [item for item in before_git if item[0] != "??"])
        new_untracked = sorted(set(after_git) - set(before_git))
        self.assertEqual([item for item in new_untracked
                          if not item[1].startswith("tests/")], [],
                         "a pipeline run created files outside tests/: %r"
                         % (new_untracked,))
        self.assertTrue(os.path.abspath(self.info["root"]).startswith(
            os.path.abspath(self.tmpdir) + os.sep))
        self.assertTrue(os.environ["OPENSPORE_DB"].startswith(
            os.path.abspath(self.tmpdir) + os.sep))
        for item in plan["targets"]:
            if not item["dispatchable"]:
                continue
            self.assertIn(fx.row(self.db, item["queue_id"])["status"],
                          ("done", "blocked"), item["va"])

    # -- E36 -------------------------------------------------------------- #
    def test_index_cache_is_the_documented_global_and_is_cleared(self):
        from tools.reconstruction_tooling import frontier as frontier_mod

        self.assertTrue(hasattr(frontier_mod, "_INDEX_CACHE"))
        self.assertIsInstance(frontier_mod._INDEX_CACHE, dict)
        self.make_root_at("cache-one", keys=("A",))
        first = self.plan(limit=50)
        self.assertTrue(frontier_mod._INDEX_CACHE)
        self.make_root_at("cache-two", keys=("P", "Q"))
        self.assertEqual(frontier_mod._INDEX_CACHE, {},
                         "a new root must not inherit a cached projection")
        second = self.plan(limit=50)
        self.assertEqual(sorted(item["va"] for item in first["targets"]),
                         ["0x00b3d300"])
        self.assertEqual(sorted(item["va"] for item in second["targets"]),
                         ["0x00b3d700", "0x00b3d800"])
        self.assertEqual(second["summary"]["coordinated_units"], 2)
        # two plans over the SAME root are served from the cache and agree
        self.assertEqual(second["summary"],
                         self.plan(limit=50)["summary"])
        fx.clear_index_cache()
        self.assertEqual(frontier_mod._INDEX_CACHE, {})

    def test_base_class_clears_the_cache_before_and_after_every_test(self):
        from tools.reconstruction_tooling import frontier as frontier_mod

        # clean on entry: setUp() already emptied the process-global cache
        self.assertEqual(frontier_mod._INDEX_CACHE, {})
        self.make_root()
        self.plan(limit=1)
        self.assertNotEqual(frontier_mod._INDEX_CACHE, {})
        # dirty now; setUp() registered clear_index_cache() *before*
        # _assert_cache_empty(), so LIFO order empties it and then checks it


if __name__ == "__main__":
    unittest.main()


class ProjectionStalenessTest(fx.FixtureTestCase):
    """The orchestrator reports projection staleness and never regenerates."""

    def test_staleness_is_reported_and_never_regenerates(self):
        self.make_root(keys=("A", "B", "C"))
        knowledge = os.path.join(self.info["root"], "reconstruction", "knowledge")
        before = {name: _fingerprint(os.path.join(knowledge, name))
                  for name in ("index.json", "bootstrap.json")}
        report = orch.projection_staleness(self.info["root"])
        self.assertIn(report["status"], ("PASS", "WARN", "NOT_AVAILABLE",
                                        "UNKNOWN"), report)
        for key in ("index_match", "bootstrap_match", "source_of_truth",
                    "generated_behind_inputs", "regeneration_command", "note"):
            self.assertIn(key, report)
        self.assertIn("integrate apply", report["regeneration_command"])
        after = {name: _fingerprint(os.path.join(knowledge, name))
                 for name in ("index.json", "bootstrap.json")}
        # The whole point: reporting must not rewrite the generated projection.
        self.assertEqual(before, after)
        # A synthetic root has no generated projection at all.
        self.assertEqual(report["status"], "NOT_AVAILABLE", report)
        self.assertIs(report["index_match"], None)

    def test_run_summary_carries_the_staleness_report(self):
        self.make_root(keys=("A",))
        self.stub_validator("PASS")
        outcome = orch.run(root=self.info["root"], limit=1,
                           worker=fx.worker("ok"), implementer_id="orch",
                           write=False)
        self.assertIn("projection", outcome["summary"])
        self.assertIn("regeneration_command", outcome["summary"]["projection"])


def _fingerprint(path):
    import hashlib
    import os
    if not os.path.exists(path):
        return None
    with open(path, "rb") as handle:
        return hashlib.sha256(handle.read()).hexdigest()


# --------------------------------------------------------------------------- #
# native child sessions: the primary worker transport
# --------------------------------------------------------------------------- #
class SessionTransportTest(fx.FixtureTestCase):
    """N1-N3: a child session is a worker, held to the same contract.

    A reconstruction worker is a native child session of the orchestrating agent
    session. This module is not that session: it hands out a machine-readable plan
    and one brief per target, and reads back the children's final messages as if
    they were a subprocess's stdout. The property under test throughout is that
    the disposition loop cannot tell the two apart, and that the strict result
    contract still decides everything.
    """

    def setUp(self):
        super().setUp()
        # Five *independent* targets. A dependent is not dispatchable until its
        # prerequisites land, so a test about what a single target's reply does
        # cannot use one; the wave/promotion test builds its own graph instead.
        self.make_root(keys=("A", "B", "D", "E1", "E2"))

    # -- helpers ----------------------------------------------------------- #
    def reply(self, key, outcome="IMPLEMENTED", **kwargs):
        """A child session's final message: prose, then one fenced result."""
        document = fx.result_document(key, outcome=outcome, **kwargs)
        return ("I read the briefing and reconstructed the body.\n\n"
                "```json\n%s\n```\n" % json.dumps(document, sort_keys=True))

    def reply_dir(self, replies):
        """Materialise ``<va8>.txt`` reply files under the test tempdir.

        The name is spelled out here rather than built from the adapter's own
        path helper, because the naming convention *is* the documented contract
        between an orchestrating session and this transport and a test that
        generated it from the implementation would pin nothing.
        """
        directory = os.path.join(self.tmpdir, "replies-%d"
                                 % (len(os.listdir(self.tmpdir)) + 1))
        os.makedirs(directory, exist_ok=True)
        for key, text in sorted(replies.items()):
            self.write_reply(directory, key, text)
        return directory

    def write_reply(self, directory, key, text):
        path = os.path.join(directory, fx.bare(fx.TARGETS[key]["va"]) + ".txt")
        with open(path, "w", encoding="utf-8") as handle:
            handle.write(text)
        return path

    def plan_entry(self, key):
        planning = orch.session_plan(root=self.info["root"], limit=20)
        wanted = fx.TARGETS[key]["va"]
        return next(item for item in planning["targets"] if item["va"] == wanted)

    def run_native(self, replies, keys=("A", "B"), implementer_id="native-1",
                   **kwargs):
        """The whole lifecycle over a reply directory, as ``session-run`` does."""
        self.stub_validator("PASS")
        kwargs.setdefault(
            "vas", [fx.TARGETS[key]["va"] for key in keys])
        return orch.run(
            root=self.info["root"], limit=20,
            worker=orch.session_result_worker(reply_dir=self.reply_dir(replies)),
            implementer_id=implementer_id, write=False, **kwargs)

    # -- N1 ---------------------------------------------------------------- #
    def test_session_plan_is_deterministic_and_reports_evidence_not_a_verdict(self):
        from tools.reconstruction_tooling.models import canonical_json

        first = orch.session_plan(root=self.info["root"], limit=20)
        second = orch.session_plan(root=self.info["root"], limit=20)
        self.assertEqual(canonical_json(first), canonical_json(second))
        self.assertEqual(first["$schema"], orch.SESSION_PLAN_SCHEMA)
        # No wall clock, no absolute path and no temp dir may leak into a
        # document two sessions compare byte for byte.
        from tests.test_orchestration_scheduling import clock_leaks

        self.assertEqual(clock_leaks(first), [])
        self.assertEqual(clock_leaks(first["targets"]), [])
        # The one absolute path a plan may carry is the database it was computed
        # against, and it is the root's own -- a plan built against some other
        # queue is a real hazard, so the path is reported rather than hidden.
        self.assertEqual(first["database"],
                         os.path.join(self.info["root"], "knowledgegraph",
                                      "spore.db"))
        without_database = dict(first)
        without_database.pop("database")
        self.assertNotIn(self.tmpdir, canonical_json(without_database))
        self.assertNotIn(self.tmpdir, canonical_json(first["targets"]))
        self.assertIs(first["claimed"], False)
        self.assertIn("transport", first)
        self.assertEqual(first["transport"]["channel"], orch.CHANNEL_NATIVE)
        for name in ("eligible", "deferred", "excluded"):
            self.assertIn(name, first["counts"])
        entry = self.plan_entry("A")
        for key in ("va", "queue_id", "name", "package", "subsystem", "role",
                    "reason", "dispatchable", "priority", "open_callees",
                    "evidence_level", "expected_static_evidence"):
            self.assertIn(key, entry, entry)
        # Evidence availability only, and each fact is one the validator's own
        # checks are decided by. No verdict is predicted anywhere: the synthetic
        # root has no candidate source for A, so anything that predicted a PASS
        # would be predicting from evidence rather than from a reconstruction.
        evidence = entry["expected_static_evidence"]
        self.assertEqual(evidence["evidence_pack"]["state"], "absent")
        self.assertIs(evidence["evidence_pack"]["verified"], False)
        self.assertIs(evidence["listing"]["available"], False)
        self.assertIsNone(evidence["listing"]["instructions"])
        self.assertNotIn("verdict", evidence)
        self.assertNotIn("status", evidence)
        self.assertNotIn("expected_validation", evidence)
        # The three facts are measured, not hard-coded. A canonical source span
        # that really resolves is reported resolved...
        self.assertIs(evidence["source_span"]["resolved"], True, evidence)
        self.assertEqual(evidence["source_span"]["role"], "canonical", evidence)
        self.assertEqual(evidence["source_span"]["artifact"],
                         fx.source_rel("A"), evidence)
        # ...and one whose artifact is gone is reported unresolved, with no
        # artifact named, so a caller can never read a missing span as present.
        os.unlink(os.path.join(self.info["root"], fx.source_rel("A")))
        fx.clear_index_cache()
        gone = self.plan_entry("A")["expected_static_evidence"]
        self.assertIs(gone["source_span"]["resolved"], False, gone)
        self.assertIsNone(gone["source_span"]["artifact"], gone)

    def test_session_plan_selection_and_filtering_are_the_plans_own(self):
        planning = orch.session_plan(root=self.info["root"], limit=1)
        self.assertEqual(planning["selected"], 1, planning["counts"])
        self.assertEqual(planning["counts"]["eligible"], 1)
        # ``include_deferred`` is what makes a later wave visible, and without it
        # the deferred half of the frontier is not in the document at all -- so
        # the count is 0 rather than a number for targets that are not there.
        self.assertEqual(planning["counts"]["deferred"], 0)
        # A dependent is a deferred target: it is scheduled, visible, and
        # explicitly not dispatchable, with its open callee named.
        self.make_root_at("with-dependent", keys=("A", "B", "C", "D"))
        wide = orch.session_plan(root=self.info["root"], limit=20,
                                 include_deferred=True)
        self.assertGreater(wide["selected"], planning["selected"])
        self.assertGreater(wide["counts"]["deferred"], 0, wide["counts"])
        dependent = next(item for item in wide["targets"]
                         if item["va"] == fx.TARGETS["C"]["va"])
        self.assertFalse(dependent["dispatchable"])
        self.assertEqual(dependent["role"], "dependent")
        self.assertEqual(dependent["open_callees"],
                         sorted(fx.TARGETS[key]["va"] for key in ("A", "B", "D")))
        # A named batch narrows it, and a VA the plan does not carry is
        # reported rather than silently dropped.
        named = orch.session_plan(root=self.info["root"], limit=20,
                                  targets=[fx.TARGETS["A"]["va"], "0x00badbad"])
        self.assertEqual([item["va"] for item in named["targets"]],
                         [fx.TARGETS["A"]["va"]])
        self.assertEqual(named["requested_absent"], ["0x00badbad"])
        # An unusable VA is a typed refusal, not a dropped filter.
        with self.assertRaises(orch.ToolError) as raised:
            orch.session_plan(root=self.info["root"], targets=["not-a-va"])
        self.assertEqual(raised.exception.code, "invalid_va")

    def test_session_plan_claims_nothing(self):
        before = {key: fx.row(self.db, fx.inv_id(key))
                  for key in ("A", "B", "D", "E1", "E2")}
        orch.session_plan(root=self.info["root"], limit=20,
                          include_deferred=True)
        after = {key: fx.row(self.db, fx.inv_id(key))
                 for key in ("A", "B", "D", "E1", "E2")}
        self.assertEqual(before, after)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    # -- N2 ---------------------------------------------------------------- #
    def test_session_task_is_a_contract_valid_brief_that_claims_nothing(self):
        before = fx.row(self.db, fx.inv_id("A"))
        task = orch.session_task(self.info["root"], self.plan_entry("A"),
                                 "child-a", live=False, write=False)
        self.assertEqual(task["$schema"], orch.SESSION_TASK_SCHEMA)
        self.assertIs(task["claim_taken"], False)
        self.assertEqual(fx.row(self.db, fx.inv_id("A")), before)
        # The child can emit the template verbatim and be accepted by the same
        # strict parser a subprocess worker's stdout goes through.
        parsed = orch.ingest(json.dumps(task["result_template"]),
                             task["va"], task["queue_id"])
        self.assertTrue(parsed["accepted"], parsed)
        self.assertEqual(parsed["result"]["va"], task["va"])
        for key in ("va", "queue_id", "name", "subsystem", "briefing",
                    "prompt_markdown", "result_contract", "result_template",
                    "write_under", "metadata_sidecar", "reply_format",
                    "binary_sha256", "attempt", "max_attempts"):
            self.assertIn(key, task, task.keys())
        self.assertEqual(task["result_contract"],
                         task["briefing"]["result_contract"])
        self.assertEqual(task["max_attempts"], orch.MAX_ATTEMPTS)
        self.assertEqual(task["write_under"],
                         task["briefing"]["reconstruction_constraints"]["write_under"])
        # The Markdown digest is the same package, and it carries the fence
        # instruction the child has to obey.
        self.assertIn(task["briefing"]["content_sha256"],
                      task["prompt_markdown"])
        self.assertIn("```json", task["prompt_markdown"])
        # The transport is stated in machine-readable form, not in prose only.
        transport = task["reply_format"]
        self.assertEqual(transport["channel"], orch.CHANNEL_NATIVE)
        self.assertIn("FINAL message", transport["instruction"])
        self.assertIn("final text block", transport["parser_reads"])
        self.assertIn("discarded and retried", transport["no_result"])
        self.assertIn("<va8>.txt", transport["reply_file"])
        # Every part of the document is JSON-serialisable as one value.
        json.dumps(task, sort_keys=True)

    def test_session_task_briefs_a_target_the_plan_does_not_carry(self):
        # A follow-up on a VA the frontier does not schedule must still be
        # briefable: the scheduler is not the gate on reading a row, and ``brief``
        # tolerates both record shapes for exactly this reason.
        task = orch.session_task(self.info["root"],
                                 {"va": "0x00badbad", "queue_id": None},
                                 "child-a")
        self.assertEqual(task["va"], "0x00badbad")
        self.assertIs(task["dispatchable"], False)
        self.assertIsNone(task["role"])
        self.assertTrue(orch.ingest(json.dumps(task["result_template"]),
                                    task["va"], None)["accepted"])

    # -- N3 ---------------------------------------------------------------- #
    def test_session_result_worker_returns_the_reply_for_the_right_va(self):
        worker = orch.session_result_worker(
            replies={fx.TARGETS["B"]["va"]: self.reply("B")})
        package = {"target": {"va": fx.TARGETS["A"]["va"]},
                   "lease": {"attempt": 1, "implementer_id": "child-a"}}
        raw, detail = worker(package)
        self.assertIsNone(raw, "a reply for another VA was served")
        self.assertEqual(detail["source"], "absent")
        self.assertIs(detail["exhausted"], True)
        # Nothing was ever handed over for this VA, so the transport is empty
        # rather than spent. The two are different facts and only this adapter
        # can tell them apart, so it reports them separately.
        self.assertIs(detail["delivered"], False)
        got, detail = worker({"target": {"va": fx.TARGETS["B"]["va"]}})
        self.assertEqual(got, self.reply("B"))
        self.assertEqual(detail, {"returncode": 0, "timed_out": False,
                                  "failure": None, "channel": "native-session",
                                  "transport": "child_session",
                                  "source": "reply_map", "exhausted": False,
                                  "delivered": True})
        self.assertEqual(worker.channel, orch.CHANNEL_NATIVE)

    def test_a_consumed_reply_is_never_replayed(self):
        """A retry is a new child session, not a re-read of the last one."""
        worker = orch.session_result_worker(
            replies={fx.TARGETS["A"]["va"]: self.reply("A")})
        package = {"target": {"va": fx.TARGETS["A"]["va"]}}
        first, _ = worker(package)
        self.assertIsNotNone(first)
        again, detail = worker(package)
        self.assertIsNone(again, "the same bytes were served twice")
        self.assertEqual(detail["source"], "absent")
        self.assertIs(detail["exhausted"], True)
        # And the absence is the existing fail-closed refusal, verbatim.
        self.assertEqual(orch.ingest(again, fx.TARGETS["A"]["va"],
                                     fx.inv_id("A"))["reason"],
                         "worker produced no output")

    def test_reply_dir_is_read_lazily_so_a_reply_may_land_after_the_plan(self):
        directory = os.path.join(self.tmpdir, "late-replies")
        os.makedirs(directory, exist_ok=True)
        worker = orch.session_result_worker(reply_dir=directory)
        package = {"target": {"va": fx.TARGETS["A"]["va"]}}
        # The plan is built first, and no child has answered yet.
        self.assertIsNone(worker(package)[0])
        # The child answers afterwards, and a second worker sees it: the read
        # happens at call time, not when the adapter was built.
        self.write_reply(directory, "A", self.reply("A"))
        later = orch.session_result_worker(reply_dir=directory)
        raw, detail = later(package)
        self.assertEqual(raw, self.reply("A"))
        self.assertEqual(detail["source"], "reply_dir")
        # The file is not deleted, so the second adapter still reports the same
        # bytes -- what is consumed is this adapter's claim on the reply.
        third = orch.session_result_worker(reply_dir=directory)
        self.assertEqual(third(package)[0], self.reply("A"))
        self.assertIsNone(third(package)[0], "the third call replayed the file")

    def test_default_raw_backs_a_reply_map_or_a_directory(self):
        fallback = self.reply("A")
        worker = orch.session_result_worker(default_raw=fallback)
        raw, detail = worker({"target": {"va": fx.TARGETS["A"]["va"]}})
        self.assertEqual(raw, fallback)
        self.assertEqual(detail["source"], "reply_map")
        self.assertIsNone(worker({"target": {"va": fx.TARGETS["A"]["va"]}})[0])
        # With no default and nothing else, the transport says so honestly.
        bare = orch.session_result_worker()
        raw, detail = bare({"target": {"va": fx.TARGETS["A"]["va"]}})
        self.assertIsNone(raw)
        self.assertEqual(detail["source"], "absent")
        self.assertIs(detail["exhausted"], True)

    def test_an_empty_reply_file_is_not_a_missing_reply(self):
        """``parse_result`` has two refusals here and they stay distinct.

        "the child wrote an empty file" and "the child wrote no file" are
        different facts, and the strict contract already words them differently
        (``worker produced empty output`` versus ``worker produced no output``).
        Collapsing an empty file into an absence in the adapter would lose that
        before the contract ever saw it, and would report a child that answered
        with nothing as one that never answered at all.
        """
        directory = os.path.join(self.tmpdir, "empty-replies")
        os.makedirs(directory, exist_ok=True)
        self.write_reply(directory, "A", "")
        worker = orch.session_result_worker(reply_dir=directory)
        raw, detail = worker({"target": {"va": fx.TARGETS["A"]["va"]}})
        self.assertEqual(raw, "")
        self.assertEqual(detail["source"], "reply_dir")
        self.assertIs(detail["exhausted"], False)
        self.assertEqual(orch.ingest(raw, fx.TARGETS["A"]["va"],
                                     fx.inv_id("A"))["reason"],
                         "worker produced empty output")
        missing = orch.ingest(None, fx.TARGETS["A"]["va"], fx.inv_id("A"))
        self.assertEqual(missing["reason"], "worker produced no output")
        self.assertNotEqual(missing["reason"],
                            orch.ingest("", fx.TARGETS["A"]["va"],
                                        fx.inv_id("A"))["reason"])

    def test_the_adapter_does_not_parse_the_reply(self):
        """A reply goes into ``parse_result`` byte for byte.

        The adapter must not normalise, decode, repair or pre-validate anything,
        because the only thing that decides whether a reply is a result is the
        strict contract -- and a child session is not more trusted than a
        subprocess. A reply the parser refuses is refused here too.
        """
        worker = orch.session_result_worker(
            replies={fx.TARGETS["A"]["va"]: self.reply("A", schema="nope-9")})
        raw, _ = worker({"target": {"va": fx.TARGETS["A"]["va"]}})
        self.assertIsInstance(raw, str)
        parsed = orch.ingest(raw, fx.TARGETS["A"]["va"], fx.inv_id("A"))
        self.assertFalse(parsed["accepted"], parsed)
        self.assertEqual(parsed["code"], "malformed_worker_output")
        self.assertIn("schema", parsed["reason"])

    # -- the four ways a child session fails, all of them closed ---------- #
    def test_a_valid_reply_completes_and_the_three_broken_ones_fail_closed(self):
        # (1) one valid result object -> complete, on a static PASS.
        outcome = self.run_native({"A": self.reply("A")}, keys=("A",),
                                  implementer_id="child-ok")
        record = outcome["results"][0]
        self.assertEqual((record["status"], record["code"], record["outcome"]),
                         ("complete", "validated", "IMPLEMENTED"), record)
        self.assertEqual(fx.row(self.db, fx.inv_id("A"))["status"], "done")

        # (2) TWO result objects -> ambiguous, never picked between. The row
        # goes back to ``queued`` with the lease released and the attempt counted.
        two = (self.reply("B")
               + "\nand a second, better answer:\n\n```json\n%s\n```\n"
               % json.dumps(fx.result_document("B", summary="second"),
                            sort_keys=True))
        outcome = self.run_native({"B": two}, keys=("B",),
                                  implementer_id="child-two")
        record = outcome["results"][0]
        self.assertEqual(record["status"], "partial", record)
        self.assertEqual(record["code"], "malformed_worker_output", record)
        self.assertIn("ambiguous", record["detail"])
        self.assertEqual(fx.row(self.db, fx.inv_id("B"))["status"], "queued")
        self.assertIsNone(fx.row(self.db, fx.inv_id("B"))["implementer_id"])
        self.assertEqual(record["attempts"]["_malformed"], 1, record["attempts"])

        # (3) no result object at all -> the same typed refusal.
        outcome = self.run_native({"D": "I investigated but could not finish.\n"},
                                  keys=("D",), implementer_id="child-none")
        record = outcome["results"][0]
        self.assertEqual(record["status"], "partial", record)
        self.assertEqual(record["code"], "malformed_worker_output", record)
        self.assertIn("no worker result document found", record["detail"])
        self.assertEqual(fx.row(self.db, fx.inv_id("D"))["status"], "queued")

        # (4) no reply file at all -> ``parse_result(None)``, the empty-reply
        # refusal, which is the honest "this transport has no more replies".
        outcome = self.run_native({}, keys=("E1",),
                                  implementer_id="child-absent")
        record = outcome["results"][0]
        self.assertEqual(record["status"], "partial", record)
        self.assertEqual(record["code"], "malformed_worker_output", record)
        self.assertEqual(record["detail"], "worker produced no output")
        self.assertEqual(fx.row(self.db, fx.inv_id("E1"))["status"], "queued")
        launch = [event for event in record["events"]
                  if event["op"] == "launch"][0]
        self.assertEqual(launch["source"], "absent")
        self.assertIs(launch["failure"], None)
        self.assertIs(launch["returncode"], 0)
        # None of the four ever closed a row, and none left a lease behind.
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_a_reply_for_the_wrong_va_is_refused(self):
        confused = self.reply("A", va=fx.TARGETS["B"]["va"])
        outcome = self.run_native({"A": confused}, keys=("A",),
                                  implementer_id="child-confused")
        record = outcome["results"][0]
        self.assertEqual(record["status"], "partial", record)
        self.assertEqual(record["code"], "malformed_worker_output", record)
        self.assertIn("does not match the assigned target", record["detail"])
        self.assertIsNone(fx.row(self.db, fx.inv_id("A"))["implementer_id"])

    # -- N5: the two axes, counted apart ---------------------------------- #
    def test_run_summary_separates_static_from_runtime(self):
        outcome = self.run_native({"A": self.reply("A"), "B": self.reply("B")},
                                  keys=("A", "B"), implementer_id="child-axes")
        summary = outcome["summary"]
        self.assertEqual(summary["static_validated"], 2, summary)
        # The runtime axis is derived from ``runtime.status == "PASS"`` and from
        # nothing else. A static PASS is a claim about the reconstruction, and
        # letting it count here would report the original process as observed
        # when it never was -- so this is 0, and 0 is the correct answer.
        self.assertEqual(summary["runtime_validated"], 0, summary)
        self.assertEqual(summary["runtime_gated"], 2, summary)
        for record in outcome["results"]:
            self.assertEqual(record["static_validation"], "PASS", record)
            self.assertEqual(record["runtime_status"], "GATED", record)
            # The runtime axis is on the record whole, so a reader can check
            # that the status was not asserted rather than take it on trust: a
            # ``PASS`` here is only reachable with a positive ``validated``.
            self.assertEqual(record["runtime"]["status"], "GATED", record)
            self.assertEqual(record["runtime"]["validated"], 0, record)
            self.assertIs(record["runtime"]["gated"], True, record)
            # The full validation report is deliberately *not* attached to a
            # record: a run over twenty targets would carry twenty of them, and
            # these are the two numbers a caller reads off them.
            self.assertNotIn("validation_detail", record, record)

    def test_a_runtime_pass_is_the_only_thing_that_counts_as_runtime_validated(self):
        """The counter reads the runtime axis, so a stubbed PASS does move it.

        Without this, a reader could believe ``runtime_validated`` is hard-wired
        to 0. It is not: it is 0 because ``runtime.validated`` is 0 everywhere
        in this repository, and a canonical record that reports an observation
        moves it.
        """

        class RuntimeObserved(fx.StubValidator):
            def __call__(self, root=None, va=None, write=True, out_dir=None,
                         **kwargs):
                report = fx.StubValidator.__call__(self, root=root, va=va,
                                                   write=write, out_dir=out_dir,
                                                   **kwargs)
                report["runtime"] = {"dimension": "RUNTIME", "status": "PASS",
                                     "validated": 1, "gated": False,
                                     "gates": [],
                                     "reason": "stub: the original process was observed"}
                return report

        self.set_production("validate", RuntimeObserved("PASS"))
        outcome = orch.run(
            root=self.info["root"], limit=20,
            worker=orch.session_result_worker(
                reply_dir=self.reply_dir({"A": self.reply("A")})),
            implementer_id="child-runtime", write=False,
            vas=[fx.TARGETS["A"]["va"]])
        self.assertEqual(outcome["summary"]["static_validated"], 1)
        self.assertEqual(outcome["summary"]["runtime_validated"], 1,
                         outcome["summary"])
        self.assertEqual(outcome["summary"]["runtime_gated"], 0)
        self.assertEqual(outcome["results"][0]["runtime_status"], "PASS")

    # -- N6: the transport is reported ------------------------------------- #
    def test_a_run_proves_which_transport_produced_it(self):
        outcome = self.run_native({"A": self.reply("A")}, keys=("A",),
                                  implementer_id="child-report")
        summary = outcome["summary"]
        self.assertEqual(summary["worker_channel"], orch.CHANNEL_NATIVE)
        self.assertEqual(summary["worker_channel"], "native-session")
        self.assertEqual(summary["worker_transport"], "child_session")
        launch = [event for event in outcome["results"][0]["events"]
                  if event["op"] == "launch"][0]
        self.assertEqual(launch["channel"], "native-session")
        self.assertEqual(launch["transport"], "child_session")
        self.assertEqual(launch["source"], "reply_dir")

    def test_the_happy_path_events_are_identical_to_a_subprocess_worker(self):
        """``process_target`` cannot tell a child session from a subprocess.

        The only difference between the two runs is which worker callable was
        handed in. The op sequence, the decision and the queue state are the
        same, which is the property that makes the native path safe to use: the
        disposition loop was not taught a new branch.
        """
        native = self.run_native({"A": self.reply("A")}, keys=("A",),
                                 implementer_id="child-happy")
        self.make_root_at("subprocess-root", keys=("A",))
        self.stub_validator("PASS")
        worker = fx.worker("ok")
        subprocess = orch.process_target(
            self.info["root"], orch.plan(self.info["root"], limit=20)["targets"][0],
            worker, "sub-happy", fx.SHA, write=False)
        native_ops = [event["op"] for event in native["results"][0]["events"]]
        subprocess_ops = [event["op"] for event in subprocess["events"]]
        self.assertEqual(native_ops, HAPPY_PATH_OPS, native_ops)
        self.assertEqual(native_ops, subprocess_ops)
        for key in ("status", "code", "outcome", "validation",
                    "validation_dimension", "static_validation",
                    "runtime_status"):
            self.assertEqual(native["results"][0][key], subprocess[key], key)
        self.assertEqual(len(worker.calls), 1, "the subprocess worker ran once")

    def test_a_dependent_is_dispatched_in_a_later_wave_after_its_prerequisites(self):
        # A/B/D -> C: three prerequisites, one dependent, two dispatch rounds in
        # one run, exactly as a subprocess run behaves.
        self.make_root_at("waves", keys=("A", "B", "C", "D"))
        self.stub_validator("PASS")
        outcome = orch.run(
            root=self.info["root"], limit=20,
            worker=orch.session_result_worker(reply_dir=self.reply_dir(
                {key: self.reply(key) for key in ("A", "B", "C", "D")})),
            implementer_id="child-waves", write=False)
        self.assertEqual(outcome["summary"]["complete"], 4, outcome["summary"])
        self.assertEqual(outcome["summary"]["waves"], 2, outcome["summary"])
        promoted = next(record for record in outcome["results"]
                        if record["va"] == fx.TARGETS["C"]["va"])
        self.assertEqual((promoted["status"], promoted["outcome"]),
                         ("complete", "IMPLEMENTED"), promoted)
        for key in ("A", "B", "C", "D"):
            self.assertEqual(fx.row(self.db, fx.inv_id(key))["status"], "done")
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        self.assertEqual(outcome["summary"]["errors"], [])

    def test_a_target_claimed_by_another_implementer_is_skipped_not_run(self):
        """The claim is the authority, and it is the plan's race that loses.

        A target the plan dispatched can still be lost: another orchestrating
        session claimed the row between the plan and the claim. The loser records
        ``skipped`` with the plan's own events -- ``claim`` and nothing else --
        and never briefs, launches or ingests, so the winner's work is untouched
        and this one costs no attempt.
        """
        planning = orch.plan(self.info["root"], limit=20)

        def plan_then_someone_else_claims(*positional, **named):
            q.claim(fx.inv_id("A"), "other-owner", binary_sha256=fx.SHA)
            return planning
        self.set_production("plan", plan_then_someone_else_claims)
        self.stub_validator("PASS")
        worker = orch.session_result_worker(
            reply_dir=self.reply_dir({"A": self.reply("A")}))
        outcome = orch.run(root=self.info["root"], limit=20, worker=worker,
                           implementer_id="child-late", write=False)
        record = outcome["results"][0]
        self.assertEqual(record["status"], "skipped", record)
        self.assertEqual(record["code"], "already_claimed")
        self.assertEqual([event["op"] for event in record["events"]], ["claim"])
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["status"], "active")
        self.assertEqual(row["implementer_id"], "other-owner")
        # The displaced owner's answer was never read, so its bytes are still
        # there for whoever asks for them.
        self.assertEqual(worker({"target": {"va": fx.TARGETS["A"]["va"]}})[0],
                         self.reply("A"))


class _VerdictByTarget(fx.StubValidator):
    """A stub whose verdict depends on the target, so one run can hold both cases.

    The status is set and read inside one lock because ``orchestrate.run``
    dispatches a wave concurrently and a verdict read as another target's would
    make this test flaky rather than wrong.
    """

    def __init__(self, verdicts, default="PASS"):
        super().__init__(default)
        self.verdicts = dict(verdicts)
        self._verdict_lock = threading.Lock()

    def __call__(self, root=None, va=None, write=True, out_dir=None, **kwargs):
        with self._verdict_lock:
            self.status = self.verdicts.get(va, self.verdicts.get("default",
                                                                  "PASS"))
            return fx.StubValidator.__call__(self, root=root, va=va,
                                            write=write, out_dir=out_dir,
                                            **kwargs)


class TransportExhaustionTest(fx.FixtureTestCase):
    """N7: "no more replies" is not a malformed answer.

    A child-session transport pops each reply once. The second call for a target
    therefore finds nothing, and the run used to report that as
    ``malformed_worker_output`` -- blaming the worker's answer for a transport
    condition and spending the malformed budget on something no reply could fix.
    It is the single most misleading thing a run summary can say.

    The two facts are separated here by what the adapter knows and only the
    adapter knows: whether it already handed a reply over for that target.

    * delivered -> the answer arrived, was judged, the disposition is a retry, and
      the retry needs another child session, which only the orchestrating session
      can spawn: ``retry_pending``.
    * never delivered -> the child never answered and no ``<va8>.txt`` was
      written: still ``malformed_worker_output``, counted and bounded. A child
      that never answered is a real failure and keeps failing closed.
    """

    def setUp(self):
        super().setUp()
        # Two independent targets, so both are dispatched in the first wave and
        # one run can hold one case of each side.
        self.make_root(keys=("A", "B"))

    # -- helpers ----------------------------------------------------------- #
    def reply(self, key, outcome="IMPLEMENTED", **kwargs):
        document = fx.result_document(key, outcome=outcome, **kwargs)
        return ("I read the briefing and reconstructed the body.\n\n"
                "```json\n%s\n```\n" % json.dumps(document, sort_keys=True))

    def reply_dir(self, replies):
        directory = os.path.join(self.tmpdir, "replies-%d"
                                 % (len(os.listdir(self.tmpdir)) + 1))
        os.makedirs(directory, exist_ok=True)
        for key, text in sorted(replies.items()):
            with open(os.path.join(directory, fx.bare(fx.TARGETS[key]["va"])
                                   + ".txt"), "w", encoding="utf-8") as handle:
                handle.write(text)
        return directory

    def run_native(self, replies, keys, validator):
        self.set_production("validate", validator)
        return orch.run(
            root=self.info["root"], limit=20,
            worker=orch.session_result_worker(reply_dir=self.reply_dir(replies)),
            implementer_id="child-exhaust", write=False,
            vas=[fx.TARGETS[key]["va"] for key in keys])

    def record_for(self, outcome, key):
        va = fx.TARGETS[key]["va"]
        return next(item for item in outcome["results"] if item["va"] == va)

    # -- the two cases ----------------------------------------------------- #
    def test_an_ingested_reply_dispositioned_retry_is_retry_pending(self):
        """The observed defect, exactly: answered, judged, retried, no second reply.

        The child answered, the reply ingested, the validator said FAIL, so
        ``reconcile`` dispositioned a retry -- and the retry iteration found the
        transport spent. That is not a malformed answer and must not be counted
        as one.
        """
        with fx.spy_queue() as seen:
            outcome = self.run_native({"A": self.reply("A")}, ("A",),
                                      fx.StubValidator("FAIL"))
        record = self.record_for(outcome, "A")
        self.assertEqual(record["status"], "retry_pending", record)
        self.assertEqual(record["code"], "retry_pending_child_session")
        self.assertNotEqual(record["code"], "malformed_worker_output")
        # The malformed budget is untouched: no reply could have fixed this.
        self.assertNotIn("_malformed", record["attempts"])
        # The retry is still a retry: the answer was received and judged, and the
        # disposition counters were spent as a retry spends them. ``_bump`` raises
        # ``_total`` on every call, so a named ``_total`` bump raises it twice --
        # the documented costing (docs/tooling/orchestration.md, "The ``_total``
        # counter is incremented by every counter bump"). Pinned so the cost of a
        # transport-exhausted dispatch stays visible.
        self.assertEqual(record["attempts"]["VALIDATE"], 1)
        self.assertEqual(record["attempts"]["_total"], 4, record["attempts"])
        # The row is queued for the next session, with no lease left behind.
        row = fx.row(self.db, fx.inv_id("A"))
        self.assertEqual(row["status"], "queued")
        self.assertIsNone(row["implementer_id"])
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])
        # The record that names the only thing that can move it is the
        # *attempted* checkpoint: ``q.checkpoint`` is refused repo-wide today
        # (QueueLeaseContractTest.test_pinned_checkpoint_is_refused...), so the
        # attempted payload is where it is readable. The last two assertions pin
        # that refusal and are expected to change with it -- not before.
        attempted = [item["kwargs"]["payload"] for item in seen["checkpoint"]
                     if item["kwargs"].get("stage") == "REPLACE"]
        self.assertEqual(len(attempted), 1, seen["checkpoint"])
        self.assertEqual(attempted[0]["next_action"],
                         "spawn_another_child_session")
        self.assertEqual(attempted[0]["stage"], "REPLACE")
        self.assertEqual(attempted[0]["last_error"], "worker produced no output")
        self.assertEqual(seen["checkpoint"][-1]["result"]["code"],
                         "invalid_params")
        self.assertIsNone(row["checkpoint"])
        # Both iterations are on the event trail: the answer, then the exhaustion.
        # A ``checkpoint`` event is not one of them -- as on the malformed path,
        # the attempted checkpoint is read from the queue calls, because the
        # refused write is what makes the events the audit trail for it.
        ops = [event["op"] for event in record["events"]]
        self.assertEqual(ops, ["claim", "brief", "launch", "ingest", "validate",
                               "checkpoint", "release", "brief", "launch",
                               "ingest", "release"], ops)
        ingests = [event for event in record["events"] if event["op"] == "ingest"]
        self.assertIs(ingests[0]["ok"], True)
        self.assertEqual(ingests[0]["outcome"], "IMPLEMENTED")
        self.assertIs(ingests[1]["ok"], False)
        self.assertIs(ingests[1]["transport_exhausted"], True)
        self.assertEqual(ingests[1]["reason"], "worker produced no output")
        self.assertEqual([event for event in record["events"]
                          if event["op"] == "release"][-1]["to"], "queued")
        self.assertEqual(len(seen["release"]), 2)

    def test_a_target_with_no_reply_at_all_is_still_malformed(self):
        """A child that never answered is a real failure and keeps failing closed."""
        with fx.spy_queue() as seen:
            outcome = self.run_native({}, ("A",), fx.StubValidator("PASS"))
        record = self.record_for(outcome, "A")
        self.assertEqual(record["status"], "partial", record)
        self.assertEqual(record["code"], "malformed_worker_output", record)
        self.assertEqual(record["detail"], "worker produced no output")
        self.assertEqual(record["attempts"]["_malformed"], 1)
        self.assertNotIn("retry_pending", record)
        self.assertEqual(fx.row(self.db, fx.inv_id("A"))["status"], "queued")
        # The attempted checkpoint asks for a respawn, not for a new child
        # session: this target has no answer to build on, so the next thing that
        # can help is another run of the transport.
        attempted = [item["kwargs"]["payload"] for item in seen["checkpoint"]]
        self.assertEqual(len(attempted), 1, seen["checkpoint"])
        self.assertEqual(attempted[0]["next_action"], "respawn_worker")
        ingest = [event for event in record["events"] if event["op"] == "ingest"][0]
        self.assertNotIn("transport_exhausted", ingest)
        # One iteration only: the malformed budget, not a retry, is what is spent.
        self.assertEqual([event["op"] for event in record["events"]],
                         ["claim", "brief", "launch", "ingest", "release"])
        self.assertEqual(len(seen["release"]), 1)

    def test_a_subprocess_worker_with_empty_stdout_is_still_malformed(self):
        """The subprocess transport has no ``delivered`` key, so it cannot drift.

        The new branch reads the *detail*, never the reply, and a subprocess
        worker never reports one. A worker that printed nothing therefore keeps
        the existing refusal, its own counter and its own bound.
        """
        adapter = orch.command_line(None, [sys.executable, "-c", "pass"], "w-1")
        raw, detail = adapter({"target": {"va": fx.TARGETS["A"]["va"]}})
        self.assertEqual(raw, b"")
        self.assertNotIn("delivered", detail)
        record = fx.process_target(
            self.info["root"], self.plan()["targets"][0], adapter, "w-1",
            self.info["sha"], write=False)
        self.assertEqual(record["status"], "partial", record)
        self.assertEqual(record["code"], "malformed_worker_output", record)
        self.assertEqual(record["attempts"]["_malformed"], 1)
        self.assertNotIn("retry_pending", record)
        self.assertEqual(fx.row(self.db, fx.inv_id("A"))["status"], "queued")

    def test_the_happy_path_is_unchanged_by_the_new_branch(self):
        outcome = self.run_native({"A": self.reply("A")}, ("A",),
                                  fx.StubValidator("PASS"))
        record = self.record_for(outcome, "A")
        self.assertEqual(record["status"], "complete", record)
        self.assertEqual([event["op"] for event in record["events"]],
                         HAPPY_PATH_OPS, record["events"])
        self.assertEqual(sorted(record["events"][0]), ["idempotent", "ok", "op"])
        self.assertEqual(outcome["summary"]["complete"], 1)
        self.assertEqual(outcome["summary"]["retry_pending"], 0)

    def test_the_run_summary_counts_retry_pending_apart_from_partial(self):
        """Both cases, one run: the counters have to be distinguishable."""
        outcome = self.run_native(
            {"A": self.reply("A")}, ("A", "B"),
            _VerdictByTarget({fx.TARGETS["A"]["va"]: "FAIL"}))
        answered = self.record_for(outcome, "A")
        never = self.record_for(outcome, "B")
        self.assertEqual(answered["status"], "retry_pending", answered)
        self.assertEqual(never["status"], "partial", never)
        self.assertEqual(never["code"], "malformed_worker_output", never)
        summary = outcome["summary"]
        # Same run, same transport, two different facts and two different counts.
        self.assertEqual(summary["targets"], 2)
        self.assertEqual(summary["retry_pending"], 1, summary)
        self.assertEqual(summary["partial"], 1, summary)
        self.assertEqual(summary["complete"], 0, summary)
        self.assertEqual(summary["review_required"], 0, summary)
        self.assertEqual(summary["blocked"], 0, summary)
        self.assertEqual(summary["error"], 0, summary)
        # The dispositions are distinct strings, so neither counter can stand in
        # for the other, and the total is conserved.
        self.assertNotIn("retry_pending",
                         [item.get("status") for item in outcome["results"]
                          if item.get("status") == "partial"])
        self.assertEqual(sum(summary[name] for name in
                             ("complete", "review_required", "blocked",
                              "skipped", "partial", "retry_pending", "error")),
                         summary["targets"])
        # One row is queued for a new child session, one for a new answer: both
        # leases are released and neither row is left active.
        self.assertEqual(fx.row(self.db, fx.inv_id("A"))["status"], "queued")
        self.assertEqual(fx.row(self.db, fx.inv_id("B"))["status"], "queued")
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])


class SessionCliTest(fx.FixtureTestCase):
    """N4: the three child-session verbs on the CLI."""

    def setUp(self):
        super().setUp()
        self.make_root(keys=("A", "B"))
        # The CLI verbs resolve their root from ``cli.ROOT``. Pointing that at the
        # synthetic root is what keeps these tests off the real repository and
        # off the real queue -- the alternative, a test that plans the real
        # frontier, is both slow and an accidental write against shared state.
        original = cli_mod.ROOT
        cli_mod.ROOT = self.info["root"]
        self.addCleanup(setattr, cli_mod, "ROOT", original)

    def run_main(self, argv):
        """``cli.main`` with stdout captured; return ``(code, envelope)``."""
        captured = []
        original = sys.stdout.write

        def capture(text):
            captured.append(text)

        sys.stdout.write = capture
        try:
            code = cli_mod.main(argv)
        finally:
            sys.stdout.write = original
        payload = "".join(captured)
        return code, json.loads(payload) if payload.strip() else {}

    def test_session_plan_verb_emits_the_session_plan_document(self):
        code, envelope = self.run_main(
            ["orchestrate", "session-plan", "--limit", "2", "--json"])
        self.assertEqual(code, 0, envelope)
        result = envelope["result"]
        self.assertIs(envelope["ok"], True)
        self.assertEqual(result["$schema"], orch.SESSION_PLAN_SCHEMA)
        self.assertEqual(result["selected"], 2)
        self.assertIs(result["claimed"], False)
        self.assertEqual(fx.rows_by_status(self.db, "active"), [])

    def test_session_task_verb_emits_the_task_document_and_needs_an_id(self):
        code, envelope = self.run_main(
            ["orchestrate", "session-task", fx.TARGETS["A"]["va"],
             "--worker-id", "child-cli", "--json"])
        self.assertEqual(code, 0, envelope)
        result = envelope["result"]
        self.assertEqual(result["$schema"], orch.SESSION_TASK_SCHEMA)
        self.assertEqual(result["va"], fx.TARGETS["A"]["va"])
        self.assertIs(result["claim_taken"], False)
        # Without a worker id there is no honest lease identity to put in the
        # briefing, so it is a typed refusal rather than a fabricated one.
        code, envelope = self.run_main(
            ["orchestrate", "session-task", fx.TARGETS["A"]["va"], "--json"])
        self.assertEqual(code, 2, envelope)
        self.assertIs(envelope["ok"], False)
        self.assertEqual(envelope["code"], "worker_id_required")

    def test_session_run_verb_drives_the_batch_over_a_reply_directory(self):
        self.stub_validator("PASS")
        directory = os.path.join(self.tmpdir, "cli-replies")
        os.makedirs(directory, exist_ok=True)
        for key in ("A", "B"):
            with open(os.path.join(directory,
                                   fx.bare(fx.TARGETS[key]["va"]) + ".txt"),
                      "w", encoding="utf-8") as handle:
                handle.write("```json\n%s\n```\n"
                             % json.dumps(fx.result_document(key),
                                          sort_keys=True))
        code, envelope = self.run_main(
            ["orchestrate", "session-run", "--replies", directory,
             "--worker-id", "child-cli-run", "--limit", "2", "--json"])
        self.assertEqual(code, 0, envelope)
        self.assertIs(envelope["ok"], True, envelope)
        result = envelope["result"]
        self.assertEqual(result["summary"]["worker_channel"], "native-session")
        self.assertEqual(result["summary"]["complete"], 2, result["summary"])
        self.assertEqual(result["summary"]["static_validated"], 2)
        self.assertEqual(result["summary"]["runtime_validated"], 0)
        for key in ("A", "B"):
            self.assertEqual(fx.row(self.db, fx.inv_id(key))["status"], "done")

    def test_session_run_requires_a_reply_directory_and_an_owner(self):
        code, envelope = self.run_main(
            ["orchestrate", "session-run", "--worker-id", "x", "--json"])
        self.assertEqual(code, 2, envelope)
        self.assertEqual(envelope["code"], "replies_required")
        code, envelope = self.run_main(
            ["orchestrate", "session-run", "--replies", self.tmpdir, "--json"])
        self.assertEqual(code, 2, envelope)
        self.assertEqual(envelope["code"], "worker_id_required")
        code, envelope = self.run_main(
            ["orchestrate", "session-run", "--replies",
             os.path.join(self.tmpdir, "nope"), "--worker-id", "x", "--json"])
        self.assertEqual(code, 2, envelope)
        self.assertEqual(envelope["code"], "replies_not_a_directory")

    def test_a_blocked_target_in_a_batch_is_not_reported_as_a_failed_command(self):
        """The envelope rule is fixed; the verb's report is shaped to suit it.

        ``_envelope`` calls ``result["status"] in ("error", "FAIL", "blocked")`` an
        error. A per-target ``blocked`` disposition means the same word with the
        opposite meaning, so the batch's top-level status is the batch outcome and
        the per-target statuses stay exactly as the lifecycle produced them.
        """
        self.stub_validator("WARN")
        directory = os.path.join(self.tmpdir, "cli-warn")
        os.makedirs(directory, exist_ok=True)
        with open(os.path.join(directory,
                               fx.bare(fx.TARGETS["A"]["va"]) + ".txt"),
                  "w", encoding="utf-8") as handle:
            handle.write("```json\n%s\n```\n"
                         % json.dumps(fx.result_document("A"), sort_keys=True))
        code, envelope = self.run_main(
            ["orchestrate", "session-run", "--replies", directory,
             "--worker-id", "child-warn", "--limit", "1", "--json"])
        self.assertEqual(code, 0, envelope)
        self.assertEqual(envelope["status"], "ok", envelope)
        self.assertIs(envelope["ok"], True)
        # The per-target disposition is untouched: a WARN is a review request
        # and is reported as one.
        self.assertEqual(envelope["result"]["summary"]["review_required"], 1)
        self.assertEqual(envelope["result"]["summary"]["static_validated"], 0)
        self.assertTrue(any("blocked" in warning
                            for warning in envelope["warnings"]), envelope)
        # A batch that adjudicated nothing is the opposite case, and it is an
        # error: the run could not reach a target, so nothing was decided.
        empty = os.path.join(self.tmpdir, "cli-empty")
        os.makedirs(empty, exist_ok=True)
        code, envelope = self.run_main(
            ["orchestrate", "session-run", "--replies", empty,
             "--worker-id", "child-empty", "--json", "--va", "0x00badbad"])
        self.assertEqual(code, 0, envelope)
        self.assertEqual(envelope["status"], "error", envelope)
        self.assertIs(envelope["ok"], False)
        self.assertEqual(envelope["code"], "no_dispatchable_targets")
        self.assertEqual(envelope["result"]["summary"]["targets"], 0)

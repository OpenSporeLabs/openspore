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

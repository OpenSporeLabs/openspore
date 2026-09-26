"""Worker-output parsing: the shapes real workers actually produce.

The bug this module exists for was not hypothetical. In a live dogfood, 4 of 5
real ``opencode run`` invocations came back ``malformed_worker_output`` because
``parse_result`` did ``json.loads(stdout.strip())`` and OpenCode's stdout is not
a JSON document.

The captures under ``tests/fixtures/worker_output/`` are byte-exact real
``opencode`` 1.18.31 output. What they establish, measured rather than assumed:

* ``--format default`` writes **every** assistant text block to stdout, joined by
  newlines. A worker that narrates before it uses a tool -- the normal shape of
  a real reconstruction -- therefore emits its preamble *and* its answer as one
  blob, and ``json.loads`` of that blob dies on the very first character
  (``Expecting value: line 1 column 1 (char 0)``). This is the root cause.
* ``--format json`` writes a **newline-delimited event stream**, not one
  document, so ``json.loads`` of the whole stdout dies with
  ``Extra data: line 2 column 1 (char 250)``.
* A single turn that uses a tool emits **two** ``text`` events: a pre-tool
  narration and the real answer. Tool calls and tool results are their own
  typed events and never appear in ``text``.
* ``--print-logs`` keeps diagnostics on stderr; stdout stays clean.

Each capture is kept in two forms: the raw probe (``real_*``, whose toy payload
is deliberately *not* a worker result) and a ``case_*`` variant whose real
envelope -- event types, ordering, narration block, tool payload -- is preserved
byte-for-byte with only the model's text payload replaced by a contract-valid
result. Proving the parser on the raw probes alone would prove nothing, and
proving it on pure synthetic strings would prove nothing about the real channel.

Nothing here touches Ghidra, the network, or the committed knowledge graph, and
no test in this module may pass by accepting a merely-plausible JSON object: the
whole point of the negative controls is that a decoy must never be selected.

Run from the repo root::

    python3 -m unittest tests.test_worker_result_parsing -v
"""
import json
import os
import unittest

from tools.reconstruction_tooling import orchestrate as orch
from tools.reconstruction_tooling import worker_contract as wc

FIXTURES = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fixtures")
WORKER_OUTPUT = os.path.join(FIXTURES, "worker_output")

VA = "0x005c5ee0"
OTHER_VA = "0x00b3d400"
PROBE_VA = "0x005c5ee0"


def capture(name):
    """Read one byte-exact capture as text."""
    with open(os.path.join(WORKER_OUTPUT, name), encoding="utf-8") as handle:
        return handle.read()


def result_document(**overrides):
    """A contract-valid result for VA, as a dict."""
    document = {
        "schema": wc.RESULT_SCHEMA,
        "va": VA,
        "outcome": "IMPLEMENTED",
        "summary": "Reconstructed all eleven instructions of 0x005c5ee0.",
        "normalized_symbol": "palettes_palette_main_get_category_005c5ee0",
        "reconstructed_symbol": "palettes_palette_main_get_category_005c5ee0",
        "source_files": [
            "reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/"
            "dogfood_005c5ee0.cpp"],
        "observed_mechanics": ["copies ECX to ESI before the call"],
        "semantic_findings": [{"claim": "returns the receiver word in EAX"}],
        "unresolved_questions": ["native return type"],
        "evidence_refs": ["reconstruction/knowledge/index.json#/0x005c5ee0"],
    }
    document.update(overrides)
    return document


def jtext(document=None, indent=None):
    """Serialise a result document the way a worker would emit it."""
    return json.dumps(result_document() if document is None else document,
                      indent=indent)


def dumped(**overrides):
    """The contract-valid result, serialised, with field overrides applied."""
    return jtext(result_document(**overrides))


def fenced(body, marker="json"):
    return "```%s\n%s\n```" % (marker, body)


class RealCaptureChannelTest(unittest.TestCase):
    """What the real OpenCode output actually is, asserted against real bytes."""

    def test_every_raw_capture_reproduces_the_original_failure(self):
        """The bug, reproduced. These four captures are what the old
        single-document parse choked on, so the regression is pinned to real
        output rather than to a story about it."""
        expected = {
            "real_opencode_default_prose_then_json.txt":
                "Expecting value",
            "real_opencode_default_narration_then_result.txt":
                "Expecting value",
            "real_opencode_json_prose_then_json.jsonl":
                "Extra data",
            "real_opencode_json_tool_two_text_blocks.jsonl":
                "Extra data",
        }
        for name, marker in sorted(expected.items()):
            raw = capture(name)
            with self.subTest(capture=name):
                with self.assertRaises(ValueError) as caught:
                    json.loads(raw.strip())
                self.assertIn(marker, str(caught.exception))

    def test_default_format_concatenates_every_assistant_text_block(self):
        """The root cause, stated exactly.

        A tool-using turn under ``--format default`` writes the pre-tool
        narration *and* the answer to stdout. So the first text block is not the
        result, and the reply is not a JSON document.
        """
        raw = capture("real_opencode_default_narration_then_result.txt")
        lines = [line for line in raw.splitlines() if line.strip()]
        self.assertEqual(len(lines), 2)
        self.assertTrue(lines[0].startswith("I'll run"),
                        "first block is narration, not the result")
        self.assertEqual(json.loads(lines[1]), {"result": "HELLO_FROM_TOOL"})

    def test_json_format_is_a_newline_delimited_event_stream(self):
        raw = capture("real_opencode_json_prose_then_json.jsonl")
        events = [json.loads(line) for line in raw.splitlines() if line.strip()]
        self.assertEqual([event["type"] for event in events],
                         ["step_start", "text", "step_finish"])
        # The whole stdout is not one document, which is why json.loads fails.
        with self.assertRaises(ValueError):
            json.loads(raw.strip())

    def test_a_tool_using_turn_emits_two_text_events(self):
        """Prose and answer are separate, ordered events -- separable by
        structure, not by guessing at a blob of text."""
        raw = capture("real_opencode_json_tool_two_text_blocks.jsonl")
        events = [json.loads(line) for line in raw.splitlines() if line.strip()]
        texts = [event for event in events if event["type"] == "text"]
        tools = [event for event in events if event["type"] == "tool_use"]
        self.assertEqual(len(texts), 2)
        self.assertEqual(len(tools), 1)
        self.assertEqual(tools[0]["part"]["state"]["output"], "HELLO_FROM_TOOL\n")
        self.assertIn("I'll run", texts[0]["part"]["text"])
        self.assertIn("```json", texts[1]["part"]["text"])
        # Different messages, so "the final text event" is well defined.
        self.assertNotEqual(texts[0]["part"]["messageID"],
                            texts[1]["part"]["messageID"])

    def test_logs_go_to_stderr_and_are_not_part_of_the_reply(self):
        """``--print-logs`` is a stderr feature. If it ever leaked into stdout
        the reply would be unrecoverable, so the launcher must keep it -- and
        must pair it with the structured channel, since that is what keeps
        stdout to the reply alone."""
        argv = orch.agent_argv(
            {"target": {"va": VA},
             "lease": {"attempt": 1, "max_attempts": 3},
             "objective": "x", "rules": [],
             "evidence": {"missing_sections": []},
             "result_contract": {"outcomes": []},
             "content_sha256": "d" * 64})
        self.assertIn("--print-logs", argv)
        self.assertEqual(argv[3:6], ["--print-logs", "--format", "json"])


class UnwrapReplyTest(unittest.TestCase):
    """``unwrap_reply`` classifies the channel; it never decides meaning."""

    def test_a_bare_json_object_is_the_json_document_channel(self):
        envelope = wc.unwrap_reply(dumped())
        self.assertEqual(envelope["channel"], wc.CHANNEL_JSON_DOCUMENT)
        self.assertEqual(envelope["document"]["va"], VA)
        self.assertEqual(envelope["blocks"], [dumped()])

    def test_a_json_list_is_not_a_result_document(self):
        """A list is well-formed JSON but never a result. It must not be
        promoted into the document slot, or extraction would be skipped."""
        envelope = wc.unwrap_reply("prose\n" + json.dumps([1, 2, 3]))
        self.assertIsNone(envelope["document"])

    def test_an_event_stream_is_detected_structurally_not_by_guess(self):
        envelope = wc.unwrap_reply(
            capture("real_opencode_json_tool_two_text_blocks.jsonl"))
        self.assertEqual(envelope["channel"], wc.CHANNEL_EVENT_STREAM)
        self.assertEqual(len(envelope["blocks"]), 2)
        self.assertEqual(envelope["tool_calls"], 1)

    def test_prose_containing_one_json_object_is_not_an_event_stream(self):
        """The event-stream test must not be satisfiable by ordinary text, or a
        prose reply with a result in it would be misread as events."""
        envelope = wc.unwrap_reply("here you go\n" + dumped())
        self.assertEqual(envelope["channel"], wc.CHANNEL_TEXT)
        self.assertIsNone(envelope["document"])
        self.assertEqual(envelope["tool_calls"], 0)

    def test_oversized_and_empty_replies_are_flagged_not_parsed(self):
        self.assertTrue(wc.unwrap_reply("x" * 64, max_bytes=16)["oversized"])
        self.assertTrue(wc.unwrap_reply("")["empty"])
        self.assertTrue(wc.unwrap_reply("   \n ")["empty"])
        self.assertTrue(wc.unwrap_reply(None)["empty"])


class RequiredFixtureTest(unittest.TestCase):
    """The eight reply shapes, named as the contract requires."""

    def accepted(self, raw, **kwargs):
        parsed = wc.parse_result(raw, va=VA, **kwargs)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["result"]["va"], VA)
        self.assertEqual(parsed["result"]["summary"],
                         result_document()["summary"])
        return parsed

    def test_fixture_1_single_result_block(self):
        parsed = self.accepted(dumped())
        self.assertEqual(parsed["channel"], wc.CHANNEL_JSON_DOCUMENT)
        self.assertEqual(parsed["outcome"], "IMPLEMENTED")

    def test_fixture_2_explanatory_text_followed_by_result(self):
        parsed = self.accepted(
            "I decompiled the target and traced all eleven instructions.\n"
            "The call at 0x5e90 is unconditional and ECX is unchanged.\n"
            "Here is the result document:\n" + dumped(indent=2) + "\n")
        self.assertEqual(parsed["extraction_stage"], "whole_reply")

    def test_fixture_3_multiple_text_blocks(self):
        """An OpenCode event stream with narration, tool use, then the answer."""
        parsed = self.accepted(
            capture("case_event_stream_tool_then_result.jsonl"))
        self.assertEqual(parsed["channel"], wc.CHANNEL_EVENT_STREAM)
        self.assertEqual(parsed["text_blocks"], 2)
        self.assertEqual(parsed["tool_calls"], 1)
        # The narration block is not silently treated as the result, and the
        # fenced answer is found in the final block.
        self.assertTrue(parsed["extraction_stage"].startswith("fenced_result"),
                        parsed["extraction_stage"])

    def test_fixture_4_tool_output_before_result(self):
        """The default-format shape: narration and result share one stdout."""
        parsed = self.accepted(
            capture("case_default_narration_then_result.txt"))
        self.assertEqual(parsed["extraction_stage"], "whole_reply")
        self.assertIn("I'll stage the candidate",
                      capture("case_default_narration_then_result.txt"))

    def test_fixture_5_malformed_trailing_content(self):
        """Valid result, garbage after it. Trailing noise is not the result and
        must not invalidate a result that is already unambiguous."""
        parsed = self.accepted(
            dumped() + "\n\n<<<end of transmission>>>\n"
            "[note: I ran out of time before checking the unwind scope]\n")
        self.assertEqual(parsed["extraction_stage"], "whole_reply")

    def test_fixture_6_valid_json_embedded_in_surrounding_text(self):
        parsed = self.accepted(
            "Result follows.\n\n" + jtext(indent=2)
            + "\n\nLet me know if you want the model test as well.\n")
        self.assertEqual(parsed["extraction_stage"], "whole_reply")

    def test_fixture_7_missing_result_is_rejected(self):
        """A fluent, confident, entirely prose reply is not a result."""
        for raw in (
                "I could not reconstruct this function; the evidence is thin.",
                "I staged the candidate and the model test passes at -O0 and "
                "-O2. Everything looks good.",
                fenced("def reconstruct():\n    pass\n", marker="python"),
                "The result is below.\n\n" + dumped()[:140],   # truncated
        ):
            with self.subTest(raw=raw[:40]):
                parsed = wc.parse_result(raw, va=VA)
                self.assertFalse(parsed["accepted"], raw[:60])
                self.assertEqual(parsed["code"], "malformed_worker_output")
                self.assertIn("no worker result document found",
                              parsed["reason"])

    def test_fixture_8_ambiguous_multiple_result_objects_is_rejected(self):
        """Two plausible payloads is a refusal, never a coin flip."""
        for label, raw in (
            ("distinct outcomes",
             dumped() + "\nand, if you prefer the conservative reading:\n"
             + dumped(outcome="STILL_UNKNOWN")),
            ("byte-identical duplicates", dumped() + "\n" + dumped()),
            ("one fenced, one bare",
             fenced(dumped()) + "\n" + dumped(outcome="PARTIAL")),
            ("nested alongside a real answer",
             "Example of the shape:\n" + jtext({"example": result_document()})
             + "\nMy actual answer:\n" + dumped()),
        ):
            with self.subTest(case=label):
                parsed = wc.parse_result(raw, va=VA)
                self.assertFalse(parsed["accepted"], label)
                self.assertEqual(parsed["code"], "malformed_worker_output")
                self.assertIn("ambiguous worker output", parsed["reason"])
                self.assertGreaterEqual(parsed["candidates"], 2)


class NegativeControlTest(unittest.TestCase):
    """The parser must not silently select the wrong JSON object.

    Each case puts a decoy in front of, or beside, a real result. The parser is
    allowed to reach the result; what it must never do is reach a *decoy* and
    report success, and what it must never do is pick between two results.
    """

    def test_a_non_result_json_object_is_not_mistaken_for_the_result(self):
        """Tool traffic, log lines and config echoes are JSON objects that do
        not claim to be results. They must be stepped over, and the result found
        beside them, in either order."""
        decoys = ['{"command": "ls -la"}', '{"status": 200, "body": "{}"}',
                  '{"a": 1, "b": 2}', '{"result": "HELLO_FROM_TOOL"}',
                  '{"events": []}', '{"exit": 0}']
        for decoy in decoys:
            for raw in (decoy + "\n" + dumped(), dumped() + "\n" + decoy,
                        "log line\n" + decoy + "\nprose\n" + dumped()):
                with self.subTest(decoy=decoy):
                    parsed = wc.parse_result(raw, va=VA)
                    self.assertTrue(parsed["accepted"],
                                    (decoy, parsed.get("reason")))
                    self.assertEqual(parsed["result"]["summary"],
                                     result_document()["summary"])
                    self.assertEqual(parsed["candidates"] if
                                     "candidates" in parsed else 1, 1)

    def test_a_result_shaped_object_with_a_wrong_va_is_refused_not_relabelled(self):
        """Extraction may *find* a wrong-VA result; validation must still
        refuse it. This is the control that proves VA binding survived the
        parser rework."""
        parsed = wc.parse_result("here you go\n" + dumped(va=OTHER_VA), va=VA)
        self.assertFalse(parsed["accepted"])
        self.assertEqual(parsed["expected_va"], VA)
        self.assertEqual(parsed["reported_va"], OTHER_VA)
        self.assertIn("does not match the assigned target", parsed["reason"])

    def test_a_wrong_va_alongside_a_correct_result_is_ambiguous_not_rescued(self):
        """The dangerous shape: a correct result is present *and* a result for
        another function is present. Preferring the matching one would be a
        guess, and a guess here is a misattribution."""
        parsed = wc.parse_result(
            dumped(va=OTHER_VA) + "\nand for the target itself:\n" + dumped(),
            va=VA)
        self.assertFalse(parsed["accepted"])
        self.assertIn("ambiguous worker output", parsed["reason"])

    def test_a_fenced_decoy_does_not_outrank_a_bare_real_result(self):
        """The fence is an explicit marker, so a fence wins -- which means a
        fenced decoy plus a bare real result must be *ambiguous*, not silently
        resolved in favour of the fence."""
        parsed = wc.parse_result(
            fenced(dumped(outcome="STILL_UNKNOWN", summary="template"))
            + "\nmy real answer:\n" + dumped(), va=VA)
        self.assertFalse(parsed["accepted"])
        self.assertIn("ambiguous worker output", parsed["reason"])

    def test_brace_noise_inside_strings_does_not_split_or_invent_candidates(self):
        """A summary containing braces and quotes must survive intact, and must
        not make the scanner see a second object."""
        summary = 'body is "{" then "}" then "," and \\ backslash'
        parsed = wc.parse_result(dumped(summary=summary), va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["result"]["summary"], summary)

    def test_a_nested_only_result_is_flagged_as_nested(self):
        """Accepting a result found inside a wrapper is allowed, but it is
        recorded so the shape is visible in the evidence instead of looking
        like a clean top-level answer."""
        parsed = wc.parse_result("wrapper:\n"
                                 + jtext({"payload": result_document()}),
                                 va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertTrue(parsed["nested_result"])
        top = wc.parse_result(dumped(), va=VA)
        self.assertFalse(top["nested_result"])

    def test_a_nested_decoy_is_counted_so_it_cannot_be_silently_dropped(self):
        """Regression guard for the scanner itself. An earlier implementation
        reported only outermost spans, so a quoted example result vanished and
        the parser picked the remaining real one -- a silent selection between
        two results. Nested spans must now be counted."""
        spans = wc._balanced_spans('{"a": {"b": {"c": 1}}, "d": 2}')
        self.assertEqual(len(spans), 3, spans)
        found = wc._candidates('{"a": ' + dumped() + '}')
        self.assertEqual(len(found), 1)
        self.assertTrue(found[0]["nested"])


class StrictnessPreservedTest(unittest.TestCase):
    """Reaching more replies must not accept more replies.

    Every rejection below is one the single-document parser already made. Each
    is re-asserted *inside* prose and inside a fence, so the extraction rework
    cannot have quietly converted a refusal into an acceptance.
    """

    def invalid(self, document, extra_raw=""):
        raw = "chatter before\n" + jtext(document) + "\nchatter after\n"
        for candidate in (raw, "chatter\n" + fenced(jtext(document))
                          + "\nmore chatter\n", extra_raw + raw):
            with self.subTest(raw=candidate[:40]):
                parsed = wc.parse_result(candidate, va=VA)
                self.assertFalse(parsed["accepted"], candidate[:60])
                self.assertEqual(parsed["code"], "malformed_worker_output")
                self.assertTrue(parsed["reason"])

    def test_wrong_schema_is_still_refused(self):
        self.invalid(result_document(schema="openspore-worker-result-0"))

    def test_unknown_outcome_is_still_refused(self):
        self.invalid(result_document(outcome="ALMOST_DONE"))

    def test_missing_required_fields_are_still_refused(self):
        self.invalid({"schema": wc.RESULT_SCHEMA, "va": VA,
                      "outcome": "IMPLEMENTED"})

    def test_unparseable_va_is_still_refused(self):
        self.invalid(result_document(va="not-an-address"))

    def test_non_list_fields_are_still_refused(self):
        for field in ("source_files", "observed_mechanics",
                      "unresolved_questions", "evidence_refs"):
            with self.subTest(field=field):
                self.invalid(result_document(**{field: "a string"}))

    def test_unknown_validation_verdict_is_still_refused(self):
        self.invalid(result_document(validation={"status": "MAYBE"}))

    def test_non_mapping_validation_is_refused_and_does_not_raise(self):
        for value in ("PASS", [1, 2], 7, True):
            with self.subTest(value=repr(value)):
                parsed = wc.parse_result(
                    "prose\n" + jtext(result_document(validation=value)),
                    va=VA)
                self.assertFalse(parsed["accepted"])
                self.assertEqual(parsed["field"], "validation")

    def test_a_json_array_reply_is_still_refused(self):
        parsed = wc.parse_result("prose\n" + json.dumps([1, 2, 3]), va=VA)
        self.assertFalse(parsed["accepted"])

    def test_every_rejection_carries_an_auditable_digest(self):
        import hashlib
        for raw in ("", "   \n", "prose only", "{not json",
                    dumped(outcome="NOPE"), "x" * (4 * 1024 * 1024 + 1)):
            with self.subTest(raw=raw[:20]):
                parsed = wc.parse_result(raw, va=VA)
                self.assertFalse(parsed["accepted"])
                if parsed.get("reason") == "worker result exceeds the size bound":
                    self.assertIn("raw_bytes", parsed)
                else:
                    expected = hashlib.sha256(
                        raw.encode("utf-8")).hexdigest() if raw else None
                    self.assertIn("raw_sha256", parsed)
                    if expected:
                        self.assertEqual(parsed["raw_sha256"], expected)

    def test_reported_failures_say_which_channel_and_stage_arrived(self):
        parsed = wc.parse_result("just prose, no result here", va=VA)
        self.assertEqual(parsed["channel"], wc.CHANNEL_TEXT)
        self.assertEqual(parsed["extraction_stage"], "no_result")
        self.assertEqual(parsed["candidates"], 0)
        self.assertEqual(parsed["text_blocks"], 1)


class BriefingContractTest(unittest.TestCase):
    """The briefing has to teach the channel the parser relies on."""

    def test_the_rules_demand_an_explicit_fenced_result(self):
        rules = " ".join(wc.WORKER_RULES)
        self.assertIn("```json", rules)
        self.assertIn("exactly once", rules)
        self.assertIn("ambiguous", rules)

    def test_the_result_contract_publishes_the_fence_markers(self):
        package = wc.briefing(VA)
        contract = package["result_contract"]
        self.assertEqual(contract["schema"], wc.RESULT_SCHEMA)
        self.assertEqual(contract["fence_markers"],
                         list(wc.RESULT_FENCE_MARKERS))
        self.assertIn("```json", contract["fence"])
        self.assertEqual(contract["required"],
                         list(wc.RESULT_RESULT_FIELDS
                              if hasattr(wc, "RESULT_RESULT_FIELDS")
                              else wc.REQUIRED_RESULT_FIELDS))

    def test_every_published_fence_marker_is_one_the_parser_honours(self):
        """A marker the briefing advertises but the parser ignores would send a
        compliant worker down the fallback path for no reason."""
        for marker in wc.RESULT_FENCE_MARKERS:
            with self.subTest(marker=marker):
                raw = fenced(dumped(), marker=marker)
                parsed = wc.parse_result(raw, va=VA)
                self.assertTrue(parsed["accepted"], (marker, parsed.get("reason")))
                self.assertTrue(parsed["extraction_stage"].startswith("fenced_result"),
                        parsed["extraction_stage"])

    def test_an_unmarked_fence_is_not_claimed_as_the_result_channel(self):
        """```python is not a result marker, so a fenced code sample must not
        outrank anything -- it simply is not a candidate."""
        parsed = wc.parse_result(
            fenced("int reconstruct_005c5ee0() { return 1; }", marker="cpp")
            + "\nand the result:\n" + dumped(), va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["extraction_stage"], "whole_reply")


if __name__ == "__main__":  # pragma: no cover
    unittest.main()

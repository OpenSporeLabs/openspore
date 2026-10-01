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


def text_event(text, message="msg_case"):
    """One ``text`` event of an OpenCode event stream, as a JSONL line.

    Only the fields the classifier looks at are filled in; the real captures
    carry ids, timestamps and token counts, and none of them can change how a
    line is classified.
    """
    return json.dumps({"type": "text", "timestamp": 1790389672945,
                       "sessionID": "ses_case", "part": {
                           "id": "prt_case", "messageID": message,
                           "sessionID": "ses_case", "text": text,
                           "type": "text"}})


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

    def test_the_raw_captures_still_parse_the_same_way_after_the_extraction_rework(self):
        """Regression guard on the real bytes, in the other direction.

        These four captures were read before the parser rework and must read the
        same way after it: each is rejected, because each carries a toy probe
        payload (``{"a": 1, "b": 2}``, ``{"result": "HELLO_FROM_TOOL"}``) that
        makes no result claim. A capture that started being *accepted* would mean
        the strictness was lost somewhere in the rework; a capture that started
        being read as a document, or off a different channel, would mean the
        channel classification drifted. The one thing allowed to move is the
        ``extraction_stage`` string, which is provenance, not decision.
        """
        expected = {
            "real_opencode_default_prose_then_json.txt": wc.CHANNEL_TEXT,
            "real_opencode_default_narration_then_result.txt": wc.CHANNEL_TEXT,
            "real_opencode_json_prose_then_json.jsonl": wc.CHANNEL_EVENT_STREAM,
            "real_opencode_json_tool_two_text_blocks.jsonl": wc.CHANNEL_EVENT_STREAM,
        }
        for name, channel in sorted(expected.items()):
            with self.subTest(capture=name):
                parsed = wc.parse_result(capture(name), va=VA)
                self.assertFalse(parsed["accepted"])
                self.assertEqual(parsed["code"], "malformed_worker_output")
                self.assertEqual(parsed["channel"], channel)
                self.assertEqual(parsed["candidates"], 0)
                self.assertIn(parsed["extraction_stage"],
                              ("no_result", "no_result_in_final_text_block"))


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

    def test_a_single_event_is_an_event_not_a_bare_document(self):
        """A one-line JSONL reply is also a bare JSON object.

        ``case_event_stream_single_text_event.jsonl`` is a real ``opencode``
        turn short enough to produce exactly one ``text`` event -- the shape a
        worker that never calls a tool emits. Read as a bare document, the
        json_document channel claims the event *envelope*, ``document`` becomes
        the event, extraction is skipped, and the result sitting in the event's
        ``part.text`` is never looked at. The event test has to come first, and
        the report has to say the result came off the event stream.
        """
        envelope = wc.unwrap_reply(
            capture("case_event_stream_single_text_event.jsonl"))
        self.assertEqual(envelope["channel"], wc.CHANNEL_EVENT_STREAM)
        self.assertIsNone(envelope["document"])
        self.assertEqual(len(envelope["blocks"]), 1)
        parsed = wc.parse_result(
            capture("case_event_stream_single_text_event.jsonl"), va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["channel"], wc.CHANNEL_EVENT_STREAM)
        self.assertEqual(parsed["result"]["summary"],
                         result_document()["summary"])

    def test_a_document_is_still_a_document(self):
        """The control for the event test above: the same shape *without* the
        ``part`` key is a real document and must keep taking the channel, so the
        event rule cannot swallow ordinary payloads."""
        for document in (dumped(), jtext({"type": "IMPLEMENTED", "va": VA})):
            with self.subTest(document=document[:40]):
                envelope = wc.unwrap_reply(document)
                self.assertEqual(envelope["channel"], wc.CHANNEL_JSON_DOCUMENT)
                self.assertIsNotNone(envelope["document"])


class FinalTextBlockTest(unittest.TestCase):
    """Which block of a multi-block reply the result may be read from.

    The rule is structural, not a heuristic: OpenCode emits one ``text`` event
    per assistant message, and the answer to a turn is its last message. So a
    reply with more than one text block is searched in the FINAL block only.

    Both directions are tested, because the rule has to be safe in both: a
    result that only an earlier block carries must NOT be read (it is a
    superseded answer), and a result-shaped decoy in a narration block must not
    make the reply ambiguous (it was never offered as the answer). Neither is a
    tie-break between candidates -- it is a decision about which text is a
    candidate at all.
    """

    def parsed(self, name):
        parsed = wc.parse_result(capture(name), va=VA)
        self.assertEqual(parsed["channel"], wc.CHANNEL_EVENT_STREAM)
        self.assertEqual(parsed["text_blocks"], 2, name)
        return parsed

    def test_a_result_in_an_earlier_block_is_not_the_answer(self):
        """A worker that answers, then keeps talking, has produced a superseded
        answer. Reading it is how a run gets recorded against something the
        worker had already revised, so the final block governs and the earlier
        one is never a fallback -- even though it holds a result that would
        otherwise have validated perfectly.

        Rejecting it is a bounded false reject: the worker can fix it by ending
        its turn with the result. Accepting it is not fixable at all.
        """
        parsed = self.parsed(
            "case_event_stream_stale_result_then_narration.jsonl")
        self.assertFalse(parsed["accepted"])
        self.assertEqual(parsed["code"], "malformed_worker_output")
        self.assertEqual(parsed["extraction_stage"],
                         "no_result_in_final_text_block")
        self.assertEqual(parsed["candidates"], 0)
        self.assertIn("no worker result document found", parsed["reason"])
        self.assertIn("final assistant text block", parsed["reason"])

    def test_a_result_shaped_decoy_in_narration_is_not_a_second_claim(self):
        """The mirror case, and the one that provably failed before.

        A worker that shows the template it was handed before filling it in
        writes a result-shaped object into a narration block. Joined, that is
        two claims and the reply is ambiguous. Read structurally, the template
        was never the answer -- it is text the reply did not end on -- so the
        real result in the final block is the only candidate, and it is accepted
        with ``candidates == 1`` proving the decoy was never counted.
        """
        parsed = self.parsed(
            "case_event_stream_decoy_narration_then_result.jsonl")
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["candidates"], 1)
        self.assertEqual(parsed["result"]["summary"],
                         result_document()["summary"])
        self.assertTrue(parsed["extraction_stage"].startswith("fenced_result"))

    def test_the_report_names_the_final_block_as_the_source(self):
        """Provenance, and the only part of the rule an operator can act on: a
        result read out of the final block says so, so a change in what a worker
        puts in its last message is visible in the record instead of silently
        changing which text was read."""
        answer = jtext(result_document(), indent=2)
        blocks = ["narration, then the candidate:\n"
                  + jtext(result_document(outcome="STILL_UNKNOWN",
                                          summary="superseded draft")),
                  "settled. Here it is:\n" + answer]
        raw = text_event(blocks[0]) + "\n" + text_event(blocks[1])
        parsed = wc.parse_result(raw, va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["extraction_stage"], "final_text_block")
        self.assertEqual(parsed["candidates"], 1)
        self.assertEqual(parsed["text_blocks"], 2)
        # A fenced answer in the final block keeps the fence in the report -- the
        # fence is the more specific statement of the same fact.
        fenced_raw = (text_event(blocks[0]) + "\n"
                      + text_event("```json\n" + answer + "\n```"))
        fenced = wc.parse_result(fenced_raw, va=VA)
        self.assertTrue(fenced["accepted"], fenced.get("reason"))
        self.assertTrue(fenced["extraction_stage"].startswith("fenced_result"))

    def test_ambiguity_inside_the_final_block_is_still_a_refusal(self):
        """Restricting the search does not make the final block lenient. Two
        answers in the text the reply ended on is still two answers."""
        for tail in (dumped() + "\n" + dumped(outcome="PARTIAL"),
                     jtext({"payload": result_document()}) + "\n" + dumped()):
            with self.subTest(tail=tail[:40]):
                raw = (text_event("narration only, no result here")
                       + "\n" + text_event(tail))
                parsed = wc.parse_result(raw, va=VA)
                self.assertFalse(parsed["accepted"])
                self.assertIn("ambiguous worker output", parsed["reason"])
                self.assertEqual(parsed["extraction_stage"],
                                 "ambiguous_in_final_text_block")
                self.assertGreaterEqual(parsed["candidates"], 2)

    def test_a_single_block_reply_is_still_searched_whole(self):
        """The restriction is conditional on there being a choice to make. One
        block has no ``final``, so the whole reply is searched -- which is what
        keeps the default-format blob and the bare-document channel working."""
        found = wc._searchable_span("only block", ["only block"])
        self.assertEqual(found, (0, len("only block"), "whole_reply"))
        self.assertEqual(wc._searchable_span("only block", None)[2],
                         "whole_reply")
        self.assertEqual(wc._searchable_span("only block", [])[2],
                         "whole_reply")

    def test_an_empty_block_does_not_make_the_answer_unreadable(self):
        """A stream can carry an empty ``text`` part. The last block with
        *content* is the answer, so an empty leading block must not make the
        restriction point at nothing."""
        answer = dumped()
        raw = text_event("") + "\n" + text_event(answer)
        parsed = wc.parse_result(raw, va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["text_blocks"], 2)
        span = wc._searchable_span("\n" + answer, ["", answer])
        self.assertEqual(span, (1, 1 + len(answer), "final_text_block"))


class UnbalancedQuoteProseTest(unittest.TestCase):
    """One stray ``"`` in prose must not hide a valid result.

    The scanner tracked quoting for the *whole* text, so a single unbalanced
    quote in the narration -- ``He said "hello``, ``x " y``, a Windows path --
    put it in string mode to the end of the reply. No ``{`` could then open a
    span and a perfectly valid result was rejected as ``candidates=0``. That is
    a false reject on a *compliant* worker, which is still a wasted attempt, so
    the scanner recovers at line boundaries.
    """

    def test_one_unbalanced_quote_in_prose_does_not_hide_a_valid_result(self):
        parsed = wc.parse_result(
            capture("case_unbalanced_quote_prose_then_result.txt"), va=VA)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["candidates"], 1)
        self.assertEqual(parsed["result"]["summary"],
                         result_document()["summary"])

    def test_every_verified_false_reject_shape_is_now_accepted(self):
        """The three shapes the false reject was measured on, one at a time, and
        each with a result *after* the stray quote."""
        for shape in ('He said "hello', 'x " y', 'path "C:\\x',
                      'a " b " c " d', 'he said "ok" but then " cut off'):
            with self.subTest(shape=shape):
                parsed = wc.parse_result(shape + "\n" + dumped(), va=VA)
                self.assertTrue(parsed["accepted"], (shape, parsed.get("reason")))
                self.assertEqual(parsed["candidates"], 1)
                self.assertEqual(parsed["extraction_stage"], "whole_reply")

    def test_recovery_cannot_split_a_string_inside_an_object(self):
        """The guard that makes recovery safe, pinned directly.

        Recovery is refused while any ``{``-opened span is outstanding, because
        that is the only state in which a brace could be a string's content
        rather than the start of a payload. An odd quote *inside* an object is
        therefore left alone: the span never closes, nothing is invented, and
        the reply is a false reject -- the pre-existing and safe direction.
        """
        raw = ('prose\n{\n  "summary": "he said "hi {"\n'
               '  "va": "0x005c5ee0"\n}\n')
        self.assertEqual(wc._balanced_spans(raw), [])
        parsed = wc.parse_result(raw, va=VA)
        self.assertFalse(parsed["accepted"])
        self.assertEqual(parsed["candidates"], 0)

    def test_recovery_does_not_invent_a_candidate_out_of_prose_braces(self):
        """Recovery can only ever *expose* text for the ordinary candidate test
        to judge, so prose that merely looks brace-ish still cannot produce a
        result. The shapes below are the ones recovery newly lets the scanner
        *see*; none of them is a result claim, so none of them may be counted."""
        for shape in ('He said "hello\nthe shape is { "a": 1 } and that is all\n',
                      'x " y\n{}\n', 'path "C:\\x\n{,}\n',
                      'he said "hi\n[1, 2, {"b": 2}]\n'):
            with self.subTest(shape=shape):
                parsed = wc.parse_result(shape, va=VA)
                self.assertFalse(parsed["accepted"], shape)
                self.assertEqual(parsed["candidates"], 0)
                self.assertEqual(parsed["code"], "malformed_worker_output")

    def test_brace_noise_inside_a_recovered_reply_still_survives_intact(self):
        """Both fixes at once: a stray quote in the prose *and* a summary full
        of braces and escaped quotes in the payload. The payload must arrive
        byte-identical and be counted exactly once."""
        summary = 'body is "{" then "}" then "," and \\ backslash'
        for shape in ('He said "hello', 'x " y', 'path "C:\\x'):
            with self.subTest(shape=shape):
                parsed = wc.parse_result(
                    shape + "\n" + dumped(summary=summary), va=VA)
                self.assertTrue(parsed["accepted"], (shape, parsed.get("reason")))
                self.assertEqual(parsed["result"]["summary"], summary)
                self.assertEqual(parsed["candidates"], 1)


class RequiredFixtureTest(unittest.TestCase):
    """The eight reply shapes, named as the contract requires."""

    def accepted(self, raw, **kwargs):
        parsed = wc.parse_result(raw, va=VA, **kwargs)
        self.assertTrue(parsed["accepted"], parsed.get("reason"))
        self.assertEqual(parsed["result"]["va"], VA)
        self.assertEqual(parsed["result"]["summary"],
                         result_document()["summary"])
        # D6: the count of claims the scan saw is reported on success too, so a
        # decoy that was stepped over is visible in the accepted record and not
        # merely inferred from the absence of an error.
        self.assertEqual(parsed["candidates"], 1, parsed.get("reason"))
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

    def test_fixture_2b_default_format_prose_wrapped_result(self):
        """The ``--format default`` shape, from a real capture: one stdout
        carrying the preamble and the payload, with the payload on a single
        line. One block, so the whole reply is searched and nothing is lost to
        the block restriction."""
        parsed = self.accepted(capture("case_default_prose_then_result.txt"))
        self.assertEqual(parsed["channel"], wc.CHANNEL_TEXT)
        self.assertEqual(parsed["text_blocks"], 1)
        self.assertEqual(parsed["tool_calls"], 0)
        self.assertEqual(parsed["extraction_stage"], "whole_reply")
        self.assertEqual(parsed["candidates"], 1)

    def test_fixture_2c_event_stream_prose_wrapped_result(self):
        """The other real-envelope variant: a stream whose *single* text event
        carries narration and the payload together. One block, so this is the
        ``whole_reply`` path again -- the restriction only engages when the
        worker really did emit more than one message."""
        parsed = self.accepted(
            capture("case_event_stream_prose_then_result.jsonl"))
        self.assertEqual(parsed["channel"], wc.CHANNEL_EVENT_STREAM)
        self.assertEqual(parsed["text_blocks"], 1)
        self.assertEqual(parsed["extraction_stage"], "whole_reply")
        self.assertEqual(parsed["candidates"], 1)

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
                    # D6: the report says how many claims the scan saw, so a
                    # decoy that was stepped over is visible as 1 rather than
                    # inferred from the absence of an error.
                    self.assertEqual(parsed["candidates"], 1)

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

    def test_a_missing_reply_is_audited_as_the_empty_reply(self):
        """A worker that produced no output at all is the most common failure
        there is, so it is the last one that may go unrecorded: the failure
        carries the digest of the empty reply, which is the bytes it would have
        had. Auditing it costs one constant and closes the only hole in the
        rule that every rejection is tieable to a run."""
        import hashlib
        parsed = wc.parse_result(None, va=VA)
        self.assertFalse(parsed["accepted"])
        self.assertEqual(parsed["reason"], "worker produced no output")
        self.assertEqual(parsed["raw_sha256"],
                         hashlib.sha256(b"").hexdigest())

    def test_a_bad_va_argument_is_a_typed_failure_not_an_exception(self):
        """``va`` is an argument, but it was the one input that was trusted
        blindly: it was normalized inline at four separate use sites with no
        guard, so ``parse_result(valid_doc, va="not-an-address")`` raised
        ``ValueError`` out of a function whose docstring promises it never
        raises. ``orchestrate.ingest`` is called with no guard, so the escaping
        exception left the queue row ``active`` with a lease still held -- the
        same unrecoverable state as pinned defect C27, reached through the
        orchestrator's own claim instead of through the worker's payload.

        An unusable claim is refused like any other bad input: typed, counted,
        and with the offending value attached so the operator can see which
        address was nonsense.
        """
        for bad in ("not-an-address", True, 0x1_0000_0000, -1, [VA], {},
                    "0x", 1.5):
            with self.subTest(va=bad):
                parsed = wc.parse_result(dumped(), va=bad)
                self.assertFalse(parsed["accepted"], bad)
                self.assertEqual(parsed["code"], "malformed_worker_output")
                self.assertIn("assigned target va is not a valid address",
                              parsed["reason"])
                self.assertEqual(parsed["va"], bad)
                self.assertIn("raw_sha256", parsed)
        # A well-formed claim in every accepted spelling still binds, and
        # ``None`` still means "cross-check against nothing".
        for good in (VA, "5c5ee0", "0x5C5EE0", 0x005C5EE0, "rva:005c5ee0"):
            with self.subTest(va=good):
                parsed = wc.parse_result(dumped(), va=good)
                self.assertTrue(parsed["accepted"], (good, parsed.get("reason")))
                self.assertEqual(parsed["result"]["va"], VA)
        unbound = wc.parse_result(dumped())
        self.assertTrue(unbound["accepted"], unbound.get("reason"))
        self.assertEqual(unbound["result"]["va"], VA)

    def test_every_validation_refusal_carries_extraction_provenance(self):
        """A refusal is the report an operator reads, and "unknown outcome" or
        "wrong VA" says nothing about *how* the reply was read -- which channel,
        which stage, how many claims were seen, how many blocks the worker wrote.
        The two earliest refusals already reported those; the validation refusals
        that follow did not, so the most confusing failures were the least
        diagnosable. All of them report the same keys now, and none of them
        changes its decision."""
        provenance = ("channel", "extraction_stage", "candidates",
                      "text_blocks", "tool_calls")
        refusals = {
            "wrong schema": jtext(result_document(schema="nope")),
            "unknown outcome": jtext(result_document(outcome="ALMOST_DONE")),
            "missing fields": jtext({"schema": wc.RESULT_SCHEMA, "va": VA}),
            "unparseable payload va": jtext(result_document(va="zzz")),
            "wrong va": jtext(result_document(va=OTHER_VA)),
            "source_files not a list": jtext(
                result_document(source_files="src/a.cpp")),
            "non-mapping validation": jtext(
                result_document(validation="PASS")),
            "unknown verdict": jtext(
                result_document(validation={"status": "MAYBE"})),
        }
        for label, raw in sorted(refusals.items()):
            for envelope in (raw, "prose before\n" + raw + "\nprose after\n",
                             "narration\n" + raw + "\nand the answer:\n" + raw):
                with self.subTest(refusal=label, envelope=envelope[:30]):
                    parsed = wc.parse_result(envelope, va=VA)
                    self.assertFalse(parsed["accepted"], label)
                    self.assertEqual(parsed["code"], "malformed_worker_output")
                    for key in provenance:
                        self.assertIn(key, parsed, (label, key))
                    self.assertIsNotNone(parsed["channel"])
                    self.assertIsNotNone(parsed["extraction_stage"])
        # The wrong-VA refusal still reports both addresses, and the
        # unknown-outcome refusal still reports the rejected value.
        wrong = wc.parse_result("chatter\n" + jtext(result_document(va=OTHER_VA)),
                                va=VA)
        self.assertEqual(wrong["expected_va"], VA)
        self.assertEqual(wrong["reported_va"], OTHER_VA)
        self.assertEqual(wrong["extraction_stage"], "whole_reply")
        unknown = wc.parse_result("chatter\n"
                                  + jtext(result_document(outcome="ALMOST")),
                                  va=VA)
        self.assertEqual(unknown["outcome"], "ALMOST")
        self.assertEqual(unknown["channel"], wc.CHANNEL_TEXT)
        self.assertEqual(unknown["text_blocks"], 1)

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

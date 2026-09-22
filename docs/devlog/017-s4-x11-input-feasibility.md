# 017 — S4: X11 input feasibility

Date: 2026-09-22. Status: **Done (PASS WITH FALLBACK / PRIMARY INCONCLUSIVE).**
Predecessor: chapter [016](016-gui-automation-shell.md) (S3). This chapter records
S4 only; it does not start S5 or promote Cell evidence.

## Experiment

The controlled question was whether `xdotool --window` XSendEvent input produced an
attributable visible response in the Spore registration UI under KDE Wayland/XWayland.
The final run was `S4-20260922T171504Z-379947`, recorded in the ignored artifact
directory `tools/observatory/out/S4-20260922T171504Z-379947/`.

The run used `DISPLAY=:0`, KDE Wayland/XWayland, Wine 11.17, xdotool 4.20260303.1,
xwininfo 1.1.7, and maim 5.8.2. The accepted window identity was `44040193`, WM_CLASS
`sporeapp.exe`, with a fresh renderer generation marker. Its geometry remained stable at
`2304x1296+2561+144`. The executable SHA256 was
`25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e`.

## Controlled Attempts

The primary path sent Return twice and clicked the center twice using
`xdotool --window`. Before/after screenshots remained on animated/loading/splash
progression. No attributable primary UI response was established, so the primary result
is **INCONCLUSIVE**. This is negative/inconclusive evidence about attribution, not proof
that the UI cannot accept the event.

The approved fallback was run exactly once: `xdotool windowactivate --sync 44040193`,
then `xdotool key --clearmodifiers Return` to the focused window. The registration form
visibly changed from no validation text to:

`Email is required. Screen Name is required. Password is required.`

This is an attributable visual-response pass. It is not an exit-code or focus inference.
The final classification is **S4 PASS WITH FALLBACK / PRIMARY INCONCLUSIVE**.

## Teardown And Limits

Cleanup passed: no S4 Spore, Wine, or overlay processes remained. A separate post-teardown
lock probe verified `machine_locked=false`. The cleanup and stop-event records are in the
run artifact. The physical Ctrl+Alt+Backspace stop key was not performed, so
`HUMAN_ACTION_REQUIRED` remains unresolved. The recorded synthetic `xdotool key
ctrl+alt+BackSpace` event is a plumbing substitute only, not the required human action.

Independent review assigned the same classification. The run is documented by
`manifest.json`, `input.jsonl`, `shots.jsonl`, the fallback images, `cleanup.txt`, and
`stop_events.jsonl`. No proprietary bytes were added.

No S5 walk was run. No Cell trace, Cell reachability claim, status update, or evidence
promotion was made. S5 remains not started and requires separate approval and a
human-watched run.

#!/usr/bin/env python3
"""Canonical 7-level evidence/confidence scale — single source of truth.

Defined verbatim by docs/RE-AUTOMATION-ARCHITECTURE.md §3 (Map A and Map B).
No other module may define status→evidence or level→confidence mappings.
"""

# Level → confidence REAL (display only).
EV = {
    "UNKNOWN": 0.0,
    "APPROXIMATION": 0.3,
    "INFERRED": 0.5,
    "SUPPORTED": 0.75,
    "OBSERVED": 0.85,
    "CONFIRMED": 0.9,
    "VERIFIED": 1.0,
}

# Explicit ordering, weakest → strongest.
EV_ORDER = ("UNKNOWN", "APPROXIMATION", "INFERRED",
            "SUPPORTED", "OBSERVED", "CONFIRMED", "VERIFIED")

# Map A — 9-status replacement vocabulary (docs/replacement-status.json)
# → 7-level evidence.
STATUS2EV = {
    "unknown": "UNKNOWN",
    "hypothesis": "INFERRED",
    "inferred": "INFERRED",
    "supported": "SUPPORTED",
    "verified": "VERIFIED",
    "approximated": "APPROXIMATION",
    "replaced-stub": "SUPPORTED",
    "replaced-approx": "APPROXIMATION",
    "replaced-verified": "VERIFIED",
}

# Map B — legacy 5-level KG strings → 7-level. READ-ONLY BACK-COMPAT: the
# only translation path for pre-existing persisted values (e.g. legacy
# "HYPOTHESIS" in spore.db attrs). New writes always use the 7-level scale.
LEGACY_EV = {
    "UNKNOWN": "UNKNOWN",
    "HYPOTHESIS": "INFERRED",
    "INFERRED": "INFERRED",
    "SUPPORTED": "SUPPORTED",
    "VERIFIED": "VERIFIED",
}


def evidence_for_status(status):
    """Map A: replacement status → 7-level evidence.

    Raises ValueError (listing the valid statuses), never KeyError.
    """
    try:
        return STATUS2EV[status]
    except KeyError:
        raise ValueError(
            f"unknown replacement status {status!r}; valid statuses: "
            f"{', '.join(STATUS2EV)}") from None


def legacy_evidence(value):
    """Map B: legacy 5-level evidence string → 7-level evidence.

    Read-only back-compat for values persisted before the 7-level scale;
    never a path for new writes. Raises ValueError for non-legacy values.
    """
    try:
        return LEGACY_EV[value]
    except KeyError:
        raise ValueError(
            f"not a legacy evidence value {value!r}; legacy values: "
            f"{', '.join(LEGACY_EV)}") from None

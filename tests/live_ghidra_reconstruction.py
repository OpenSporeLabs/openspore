import os
import sys
import unittest

# Running this file directly puts tests/ on sys.path[0], not the repository
# root, so the ``tools`` package is unimportable and the module-level import
# below fails before any test runs. Since this file is deliberately NOT named
# test_*.py (unittest discovery must not require a live Ghidra), no suite
# catches that, so the documented invocation has to work on its own.
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.reconstruction_tooling.evidence import collect


class LiveGhidraReconstructionTest(unittest.TestCase):
    def test_real_va_live_function_and_decompilation(self):
        pack = collect(va="0x00e5b790", live=True, write=False)
        self.assertEqual(pack["evidence_state"], "LIVE")
        self.assertEqual(pack["categories"]["ghidra_function"]["evidence_state"], "LIVE")
        self.assertEqual(pack["categories"]["decompilation"]["evidence_state"], "LIVE")
        self.assertEqual(pack["categories"]["ghidra_function"]["availability"], "available")
        self.assertEqual(pack["categories"]["decompilation"]["availability"], "available")


if __name__ == "__main__":
    unittest.main()

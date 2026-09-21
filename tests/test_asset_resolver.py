#!/usr/bin/env python3
"""Unit tests for the Spore asset resolver."""
import json
import os
import sys
import unittest

_HERE = os.path.dirname(os.path.abspath(__file__))
_TOOLS = os.path.join(_HERE, '..', 'tools', 'spore')
sys.path.insert(0, os.path.join(_TOOLS, 'dbpf'))
sys.path.insert(0, _TOOLS)

from asset_resolver import (  # noqa: E402
    _load_maps, type4cc, type_name, group_name,
    stage_byte, category_byte, fmt_rec,
)


class TestTypeMaps(unittest.TestCase):

    def setUp(self):
        _load_maps()

    def test_typenames_loaded(self):
        from asset_resolver import TYPES
        self.assertGreater(len(TYPES), 10)

    def test_known_types(self):
        self.assertEqual(type_name(0x00E6BCE5), 'gmdl')
        self.assertEqual(type_name(0x2F4E681C), 'raster')
        self.assertEqual(type_name(0x3D97A8E4), 'cll')
        self.assertEqual(type_name(0x2F4E681B), 'rw4')
        self.assertEqual(type_name(0x1A99B06B), 'bem')

    def test_unknown_type_falls_back_to_4cc(self):
        name = type_name(0x0F43029A)
        self.assertNotEqual(name, '')

    def test_groupnames_loaded(self):
        from asset_resolver import GROUPS
        self.assertGreater(len(GROUPS), 5)

    def test_known_groups(self):
        self.assertEqual(group_name(0x40616200), 'CellModels')
        self.assertEqual(group_name(0x40626200), 'CreatureModels')
        self.assertEqual(group_name(0x40636200), 'BuildingModels')

    def test_unknown_group_empty(self):
        self.assertEqual(group_name(0x40637E02), '')


class TestStructHelpers(unittest.TestCase):

    def test_stage_byte(self):
        self.assertEqual(stage_byte(0x40637E02), 0x7E)
        self.assertEqual(stage_byte(0x40616200), 0x62)

    def test_category_byte(self):
        self.assertEqual(category_byte(0x40637E02), 0x63)
        self.assertEqual(category_byte(0x40616200), 0x61)

    def test_type4cc(self):
        s = type4cc(0x00E6BCE5)
        self.assertEqual(len(s), 4)


class TestFmtRec(unittest.TestCase):

    def setUp(self):
        _load_maps()

    def test_fmt_rec_known(self):
        rec = {'type': 0x00E6BCE5, 'group': 0x40616200, 'inst': 0x12345678,
               'msize': 1000, 'off': 0x1000, 'comp': False}
        line = fmt_rec(0, rec)
        self.assertIn('gmdl', line)
        self.assertIn('CellModels', line)
        self.assertIn('0x40616200', line)

    def test_fmt_rec_unknown_group(self):
        rec = {'type': 0x00E6BCE5, 'group': 0x40637E02, 'inst': 0x067A0801,
               'msize': 7012, 'off': 0x0597C163, 'comp': True}
        line = fmt_rec(16013, rec)
        self.assertIn('0x40637e02', line)
        self.assertIn('0x067a0801', line)
        self.assertIn('7012', line)


class TestResolverCLI(unittest.TestCase):
    """Integration tests: run the resolver against a real package."""

    PKG = os.path.join(_HERE, '..', 'SPORE', 'Data', 'Spore_Content.package')

    def setUp(self):
        if not os.path.exists(self.PKG):
            self.skipTest("Spore_Content.package not available")

    def _run(self, *args):
        import subprocess
        script = os.path.join(_TOOLS, 'asset_resolver.py')
        result = subprocess.run(
            [sys.executable, script, self.PKG, *args],
            capture_output=True, text=True, timeout=120,
        )
        return result

    def test_typeinfo(self):
        r = self._run('--typeinfo')
        self.assertEqual(r.returncode, 0)
        self.assertIn('gmdl', r.stdout)
        self.assertIn('raster', r.stdout)

    def test_record_standin(self):
        r = self._run('--record', '0x00E6BCE5:0x40637E02:0x067A0801')
        self.assertEqual(r.returncode, 0)
        self.assertIn('0x40637e02', r.stdout)
        self.assertIn('0x067a0801', r.stdout)
        self.assertIn('7012', r.stdout)

    def test_record_json(self):
        r = self._run('--record', '0x00E6BCE5:0x40637E02:0x067A0801', '--json')
        self.assertEqual(r.returncode, 0)
        data = json.loads(r.stdout)
        self.assertEqual(data['type'], '0x00e6bce5')
        self.assertEqual(data['type_name'], 'gmdl')
        self.assertEqual(data['group'], '0x40637e02')
        self.assertEqual(data['stage'], '0x7e')
        self.assertEqual(data['category'], '0x63')

    def test_record_not_found(self):
        r = self._run('--record', '0xDEADBEEF:0x12345678:0xABCDEF00')
        self.assertIn('not found', r.stdout)

    def test_type_filter(self):
        r = self._run('--type', '0x00E6BCE5')
        self.assertEqual(r.returncode, 0)
        self.assertIn('gmdl', r.stdout)
        self.assertIn('4209', r.stdout)

    def test_group_filter(self):
        r = self._run('--group', '0x40637E02')
        self.assertEqual(r.returncode, 0)
        self.assertIn('164 records', r.stdout)

    def test_near(self):
        r = self._run('--near', '0x40637E02', '0x067A0801', '--near-count', '5')
        self.assertEqual(r.returncode, 0)
        self.assertIn('0x067a0801', r.stdout)
        self.assertIn('0x067a07ff', r.stdout)

    def test_map(self):
        r = self._run('--map')
        self.assertEqual(r.returncode, 0)
        self.assertIn('gmdl', r.stdout)
        self.assertIn('CellModels', r.stdout)


if __name__ == '__main__':
    unittest.main()

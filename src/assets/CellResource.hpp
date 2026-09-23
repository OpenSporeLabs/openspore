// Clean-room decoder for the cell-stage `cCellGlobalsResource` record.
//
// Independently authored for OpenSpore. The single stage-wide globals record
// (TYPE 0x2A3CE5B7, 276 bytes) lives in SPORE/DataEP1/Spore_EP1_Data.package
// (group 0, instance 0xa426730b). It is a DIRECT field-by-field serialization
// of the runtime struct `Simulator::Cell::cCellGlobalsResource` (Ghidra struct
// 61843 family, 276 bytes) — not wrapped in a CellSerializer name/ID envelope.
//
// The layout is evidence-confirmed: all 69 fields decode to clean hand-authored
// tuning values (round floats, small enums, u32 resource-reference keys), and
// the last field ends exactly at byte 276.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::assets {

// One decoded globals field. `u` is meaningful for u32/ref fields, `f` for
// float fields.
struct CellField {
  std::string name;
  size_t offset = 0; // byte offset from record start
  bool isFloat = false;
  uint32_t u = 0;
  float f = 0.0F;
};

// The decoded cCellGlobalsResource.
struct CellGlobals {
  static constexpr uint32_t kType = 0x2A3CE5B7;
  static constexpr size_t kSize = 276;
  static constexpr size_t kFieldCount = 69;

  size_t size = 0;
  std::vector<CellField> fields;

  // Convenience accessors (index into `fields`, safe when complete).
  uint32_t gameMode() const;
  float flowMultiplier() const;

  // True when every byte is accounted (size == kSize and field span == size).
  bool complete() const;
  size_t accounted() const; // end offset of the last field
};

// Parses a globals record. True + populated on a complete decode. False +
// error when the blob is not exactly kSize bytes.
bool parseCellGlobals(const uint8_t *data, size_t size, CellGlobals &out,
                      std::string &error);

} // namespace openspore::assets

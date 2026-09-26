#include "editor_model_min_height_getter.hpp"

#include <cstdio>
#include <cstring>

int main() {
  using namespace openspore::reconstruction::wave13_w1_dispatch_b03;

  OpaqueEditorModel model;
  std::memset(&model, 0, sizeof(model));
  model.mBounds = 10.0f;
  model.mFeetBounds = 1.0f;
  model.mMinHeight = -2.0f;
  model.mMaxHeight = 2.0f;
  model.mShowHiddenHandles = 1;
  model.mShowBoneLengthHandles = 0;
  model.mUseBoundsForDelete = 1;

  int failures = 0;
  const float got = editor_model_min_height_getter_004adb00(&model);
  if (got != -2.0f) {
    std::printf("FAIL expected -2.0, got %f\n", static_cast<double>(got));
    ++failures;
  }

  // The read must be of +0x40 specifically, not of a neighbour: perturbing the
  // two adjacent floats must not change the answer.
  model.mMaxHeight = 1234.5f;
  model.mFeetBounds = -987.25f;
  if (editor_model_min_height_getter_004adb00(&model) != -2.0f) {
    std::printf("FAIL the read is not isolated to +0x40\n");
    ++failures;
  }

  if (failures == 0) {
    std::printf("004adb00 model test: all cases passed\n");
    return 0;
  }
  std::printf("004adb00 model test: %d failure(s)\n", failures);
  return 1;
}

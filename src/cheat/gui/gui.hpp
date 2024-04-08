#pragma once

// links together menu elements

#include "watermark/watermark.hpp"

#include <memory>

namespace gui {
  inline auto watermark = std::make_unique<c_watermark>();
}
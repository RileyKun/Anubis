#pragma once

#include <memory>

class c_factory{
public:
  void startup();
  void shutdown();

private:
  void hooks();
  void interfaces();
};

inline auto factory = std::unique_ptr<c_factory>();
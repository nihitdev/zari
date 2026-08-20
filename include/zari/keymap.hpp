#pragma once
#include "zari/types.hpp"
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace zari {
struct Binding { std::vector<std::string> keys; std::string action, arg, description; };
class Keymap {
 public:
  static Keymap defaults();
  bool overlay(const fs::path& path, std::vector<std::string>& warnings);
  const std::vector<Binding>& bindings() const { return bindings_; }
  std::optional<Binding> exact(const std::vector<std::string>& seq) const;
  bool is_prefix(const std::vector<std::string>& seq) const;
 private: std::vector<Binding> bindings_;
};
std::string key_name(int ch);
}

#pragma once
#include "zari/types.hpp"
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace zari {
struct Color { int r=255,g=255,b=255; int ansi=-1; };
struct Style { std::optional<Color> fg, bg; bool bold=false, italic=false, underline=false, dim=false; };
struct Theme { std::string name="default"; std::map<std::string,Style> styles; const Style& get(const std::string& key) const; };
Theme builtin_theme(const std::string& name);
bool overlay_theme_file(Theme& theme, const fs::path& path, std::vector<std::string>& warnings);
std::optional<Color> parse_color(const std::string& value);
}

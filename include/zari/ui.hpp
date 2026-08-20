#pragma once
#include "zari/manager.hpp"
#include "zari/theme.hpp"
#include <ncurses.h>
namespace zari {
class Terminal { public: Terminal(); ~Terminal(); Terminal(const Terminal&)=delete; Terminal& operator=(const Terminal&)=delete; };
class Ui { public: explicit Ui(Theme theme); void apply_theme(Theme); void draw(const Manager&, Mode, const std::string&, const std::string&, const Keymap&); private: Theme theme_; void text(int,int,int,std::string_view,int=0) const; };
}

#pragma once
#include "zari/ui.hpp"
namespace zari {
struct Cli { fs::path start="."; std::optional<fs::path> config; std::optional<std::string> theme; bool debug=false, help=false, version=false; };
std::optional<Cli> parse_cli(int argc, char** argv, std::string& error);
class App { public: explicit App(Cli); int run(); private: void execute(const Binding&); void reload(); void prompt(std::string,std::function<void(const std::string&)>); Cli cli_; Config config_; Keymap keymap_; Theme theme_; std::unique_ptr<Manager> manager_; Mode mode_=Mode::normal; std::string message_, input_; bool running_=true; std::vector<std::string> sequence_; };
}

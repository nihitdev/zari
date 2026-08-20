# Zari

**A fast, keyboard-driven terminal file manager for Linux, written in C++20.**

<p align="center">
  <a href="https://github.com/nihitdev/zari/releases/latest"><img alt="Latest release" src="https://img.shields.io/github/v/release/nihitdev/zari?style=flat-square"></a>
  <a href="https://github.com/nihitdev/zari/actions/workflows/release.yml"><img alt="Release builds" src="https://img.shields.io/github/actions/workflow/status/nihitdev/zari/release.yml?style=flat-square&label=release"></a>
  <a href="LICENSE"><img alt="GPL-3.0-or-later" src="https://img.shields.io/badge/license-GPL--3.0--or--later-blue?style=flat-square"></a>
  <img alt="C++20" src="https://img.shields.io/badge/C%2B%2B-20-00599C?style=flat-square">
</p>

<p align="center">
  <a href="https://get-zari.vercel.app">Website</a> ·
  <a href="https://get-zari.vercel.app/docs/">Documentation</a> ·
  <a href="https://github.com/nihitdev/zari/releases/latest">Releases</a>
</p>

> Zari is inspired by modern terminal file managers but is an independent C++ implementation.

<div align="center">
  <img src="docs/zari-preview.svg" alt="Zari three-pane terminal file manager preview" width="100%" />
</div>

<p align="center"><sub>Illustrated preview — exact colors and glyphs depend on your terminal and active theme.</sub></p>

Zari focuses on predictable filesystem behavior, a clean three-pane interface, and useful defaults that can be overridden without copying a complete configuration. It has no plugin or scripting system; functionality is implemented natively in the C++ codebase.

## Project status

Zari is under active development. Version `0.1.x` is usable, but interfaces and configuration details may evolve before `1.0`. Filesystem operations should always be tested on non-critical data when evaluating a new release.

Current targets:

- Linux on `x86_64` and `aarch64`
- C++20 with GCC or Clang
- UTF-8 terminals supported by `ncursesw`
- Arch Linux and Debian/Ubuntu packaging

## Features

| Area | Implemented capabilities |
| --- | --- |
| Interface | Wide-character ncurses UI, configurable three-pane layout, resize handling, tabs, status bar, and help overlay |
| Navigation | Vim-style movement, directory history, page scrolling, cursor restoration, bookmarks, and multi-key chords |
| Files | Metadata, hidden-file toggle, multi-selection, copy, cut, collision-safe paste, rename, create, trash, and permanent delete |
| Listing | Natural, alphabetical, extension, size, time, random, and unsorted modes; reverse and directories-first controls |
| Preview | Text, directory, binary, symlink, and general metadata previews with size limits and tab expansion |
| Search | Incremental fuzzy find and native recursive filename search |
| Customization | Layered TOML configuration, remappable keybindings, six built-in themes, custom theme overrides, and runtime reload |
| Runtime | XDG-aware paths, background task primitives, diagnostic logging, and RAII-based terminal restoration |

## Installation

Choose the method that fits your system:

| Platform | Recommended method |
| --- | --- |
| Any supported Linux distribution | Verified release installer |
| Arch Linux | Signed binary repository or AUR |
| Debian / Ubuntu | Release `.deb` package |
| Developers | CMake build from source |

### Installer

Release binaries install into `~/.local` by default and are verified against the release checksum:

```sh
curl -fsSL https://raw.githubusercontent.com/nihitdev/zari/main/install.sh | sh
```

Use `ZARI_INSTALL_ROOT=/custom/prefix` to choose another prefix, or `ZARI_VERSION=0.1.0` to pin a release. The installer never uses `sudo`.

### Debian and Ubuntu

Download the `.deb` for your architecture from [GitHub Releases](https://github.com/nihitdev/zari/releases), then install it with APT so dependencies are resolved:

```sh
sudo apt install ./zari_0.1.0_amd64.deb
```

### Arch Linux binary repository

Import and locally trust the repository signing key:

```sh
curl -fsSL https://raw.githubusercontent.com/nihitdev/zari-arch-repo/main/zari.gpg | sudo pacman-key --add -
sudo pacman-key --lsign-key B387DD74A0087C2D0C96F7C50FF0CC0AC49F9149
```

Verify the key fingerprint before trusting it:

```text
B387 DD74 A008 7C2D 0C96 F7C5 0FF0 CC0A C49F 9149
```

Add the repository to `/etc/pacman.conf`:

```ini
[zari]
SigLevel = Required DatabaseOptional
Server = https://raw.githubusercontent.com/nihitdev/zari-arch-repo/main/$arch
```

Then synchronize package databases and install Zari:

```sh
sudo pacman -Syu zari
```

### Arch Linux / AUR

Zari is available from the [Arch User Repository](https://aur.archlinux.org/packages/zari). Install it with your preferred AUR helper:

```sh
yay -S zari
# or
paru -S zari
```

The maintained package manifest also lives in [`packaging/aur`](packaging/aur/PKGBUILD).

### Build from source

Linux, CMake 3.20+, a C++20 compiler, and ncursesw development headers are required. On Debian/Ubuntu: `sudo apt install cmake g++ libncursesw5-dev`.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
sudo cmake --install build
```

The executable installs to `${CMAKE_INSTALL_PREFIX}/bin/zari`; themes install below `${CMAKE_INSTALL_PREFIX}/share/zari/themes`. Run `zari`, `zari .`, or `zari /some/path`.

## Quick start

Launch Zari in the current directory or open a specific path:

```sh
zari
zari ~/Projects
```

Useful command-line options:

```text
zari --help
zari --version
zari --config /path/to/zari.toml
zari --theme catppuccin-mocha
zari --debug
```

Press `?` at any time to open the interactive help overlay. Press `q` to quit.

## Keyboard shortcuts

| Keys | Action |
| --- | --- |
| `j` / `k`, arrows | Move cursor |
| `h` / `l` | Parent directory / enter directory or open file |
| `gg` / `G` | Jump to top / bottom |
| `Space`, `v` | Toggle selection / visual selection mode |
| `y` / `x` / `p` | Copy / cut / paste |
| `d` / `D` | Move to trash / permanently delete |
| `r`, `a`, `A` | Rename / create file / create directory |
| `.` | Toggle hidden files |
| `/`, `f` | Incremental find / recursive filename search |
| `tt`, `[` / `]`, `Ctrl-w` | Create, switch, or close tabs |
| `R` | Reload configuration, keymap, and theme |
| `?`, `q` | Open help / quit |

These are defaults. The in-application help overlay is generated from the active keymap and reflects user overrides.

## Configuration

Files are read from `$ZARI_CONFIG_HOME`, then `$XDG_CONFIG_HOME/zari`, then `~/.config/zari`. Missing files are fine.

```text
~/.config/zari/
├── zari.toml      # manager, preview, UI, confirmation, and theme settings
├── keymap.toml    # key sequences and actions
└── theme.toml     # style overrides
```

```toml
[manager]
show_hidden = false
sort_by = "natural"
directories_first = true
layout = [1, 3, 2]

[preview]
enabled = true
max_file_size = 10485760
tab_size = 4

[theme]
name = "catppuccin-mocha"
```

Use `--config PATH` for an alternate main file and `--theme NAME` for a one-run theme choice. Zari configurations are its own format and are not compatible with Yazi configurations.

### Custom keybindings

```toml
[[manager.bind]]
keys = ["g", "d"]
action = "cd"
arg = "~/Downloads"
description = "Go to Downloads"
```

### Themes

Built-ins: `default`, `catppuccin-mocha`, `gruvbox-dark`, `dracula`, `nord`, and `tokyo-night`. Override individual styles in `theme.toml` with hex or ANSI colors and `bold`, `italic`, `underline`, or `dim` flags. Presets use the commonly published palettes associated with their respective community themes; names belong to their projects.

## Search dependencies

Incremental and recursive filename searches are native. Content-search UI integration with `rg` and richer search-result navigation are roadmap work; Zari never executes files for previewing.

## Filesystem safety

- File operations use `std::filesystem` and direct process APIs instead of interpolating filenames into shell commands.
- Paste operations detect collisions and do not silently overwrite existing paths.
- Trash operations use the freedesktop trash layout where practical; permanent deletion is a separate action.
- Symlinks are represented explicitly and are not followed unexpectedly during destructive traversal.
- Terminal ownership is RAII-based so normal exits and handled failures restore terminal state.

Please report any filesystem-safety issue privately before publishing reproduction details. Do not test destructive operations against irreplaceable data.

## Architecture

`App` owns the event loop, `Ui` owns rendering, `Manager` coordinates independent `Tab` state, and focused modules handle configuration, themes, keymaps, filesystem operations, previews, search, and background tasks. Ownership is RAII-based and filesystem calls avoid shell interpolation.

```text
include/zari/   Public module interfaces
src/            Application and module implementations
tests/          Non-TUI test harness
themes/         Installed built-in theme presets
packaging/      Debian and Arch package metadata
docs/wiki/      Repository documentation
site/           Next.js documentation website
```

## Development

Configure a warning-enabled debug build and run the tests:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

The project compiles with `-Wall -Wextra -Wpedantic`. Keep UI-independent behavior in testable modules and add regression coverage for configuration, sorting, path handling, selection, tabs, search, and filesystem operations.

## Contributing

Issues and focused pull requests are welcome. Before submitting a change:

1. Keep the implementation native C++20; Zari intentionally does not support plugins or embedded scripting runtimes.
2. Preserve safe behavior for spaces, Unicode names, leading dashes, symlinks, and recursive operations.
3. Build with the warning flags enabled and run the complete test suite.
4. Update the README or wiki when behavior, keybindings, configuration, or packaging changes.

For substantial changes, open an issue first so the design and scope can be discussed before implementation.

## Roadmap

- Search-result views and `rg` content-search integration
- Cancellable progress dialogs for long-running operations
- Bulk rename and an open-with rules interface
- Optional terminal image-protocol support
- Syntax-highlighted source previews
- Additional metadata columns and UI polish

## Troubleshooting

- Garbled UI: verify a UTF-8 locale and a terminal with Unicode support.
- No colors: check `$TERM` and terminal color capability.
- Config warning: press `R` after correcting the named file; the last working configuration is retained on invalid reload.
- Open fails: ensure `xdg-open` is installed or configure `[open] default`.

## Documentation and website

The repository wiki lives in [`docs/wiki`](docs/wiki/README.md). A deploy-ready static Next.js website, including browsable documentation, lives in [`site`](site/README.md).

## License

Zari is free software licensed under the [GNU General Public License, version 3 or later](LICENSE). See [COPYRIGHT](COPYRIGHT) for the project notice.

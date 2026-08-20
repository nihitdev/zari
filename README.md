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

Zari focuses on predictable filesystem behavior, a clean three-pane interface, and useful defaults that can be overridden without copying a complete configuration. It has no plugin or scripting system.

## Features

- Wide-character ncurses UI with parent, current, and preview panes
- Vim-style navigation, scrolling, history, tabs, selection, and multi-key chords
- Natural/alphabetical/extension/size/time/random sorting
- Text, directory, binary, symlink, and metadata previews
- Copy, cut, collision-safe paste, rename, create, trash, and permanent delete
- Incremental fuzzy find and native recursive filename search
- Layered TOML configuration, keymap, built-in themes, and runtime reload
- XDG-aware config/state paths and safe terminal restoration through RAII

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

`j/k` move, `h/l` leave/enter, `gg/G` top/bottom, `Space` select, `y/x/p` copy/cut/paste, `d/D` trash/delete, `r` rename, `a/A` create file/directory, `.` hidden files, `/` incremental find, `f` recursive filename search, `tt` new tab, `[`/`]` switch tabs, `Ctrl-w` close tab, `?` help, `R` reload, and `q` quit. The help overlay reflects active bindings.

## Configuration

Files are read from `$ZARI_CONFIG_HOME`, then `$XDG_CONFIG_HOME/zari`, then `~/.config/zari`. Missing files are fine.

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

## Architecture

`App` owns the event loop, `Ui` owns rendering, `Manager` coordinates independent `Tab` state, and focused modules handle configuration, themes, keymaps, filesystem operations, previews, search, and background tasks. Ownership is RAII-based and filesystem calls avoid shell interpolation.

## Roadmap

Search-result views, `rg` integration, cancellable progress dialogs for large operations, bulk rename, open-with rules UI, image protocols, syntax highlighting, and more metadata columns.

## Troubleshooting

- Garbled UI: verify a UTF-8 locale and a terminal with Unicode support.
- No colors: check `$TERM` and terminal color capability.
- Config warning: press `R` after correcting the named file; the last working configuration is retained on invalid reload.
- Open fails: ensure `xdg-open` is installed or configure `[open] default`.

## Documentation and website

The repository wiki lives in [`docs/wiki`](docs/wiki/README.md). A deploy-ready static Next.js website, including browsable documentation, lives in [`site`](site/README.md).

## License

Zari is free software licensed under the [GNU General Public License, version 3 or later](LICENSE). See [COPYRIGHT](COPYRIGHT) for the project notice.

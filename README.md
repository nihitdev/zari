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
  <a href="https://github.com/nihitdev/zari/releases/latest">Releases</a> ·
  <a href="https://aur.archlinux.org/packages/zari">AUR</a>
</p>

> Zari is inspired by modern terminal file managers but is an independent C++ implementation.

<div align="center">
  <img src="docs/zari-preview.svg" alt="Zari three-pane terminal file manager preview" width="100%" />
</div>

<p align="center"><sub>Illustrated preview — exact colors and glyphs depend on your terminal and active theme.</sub></p>

Zari provides a wide-character ncurses interface, Vim-style navigation, tabs, selection, sorting, previews, safe file operations, recursive filename search, TOML configuration, remappable keybindings, and themes. It has no plugin or scripting runtime.

Zari `0.1.x` is usable and under active development. Test destructive operations on non-critical data when evaluating a release.

## Install

The verified installer selects the correct Linux release archive and installs into `~/.local` without `sudo`:

```sh
curl -fsSL https://raw.githubusercontent.com/nihitdev/zari/main/install.sh | sh
```

Other supported methods:

- **Arch binary repository:** follow the [signed pacman repository guide](https://get-zari.vercel.app/docs/installation/#arch-signed-binary-repository-trust-key)
- **Arch User Repository:** `yay -S zari` or `paru -S zari`
- **Debian / Ubuntu:** install the matching `.deb` from [GitHub Releases](https://github.com/nihitdev/zari/releases/latest)
- **Source build:** follow the [build instructions](https://get-zari.vercel.app/docs/installation/#build-from-source)

Launch the current directory or pass a path:

```sh
zari
zari ~/Projects
```

## Documentation

| Guide | Contents |
| --- | --- |
| [Getting started](https://get-zari.vercel.app/docs/getting-started/) | Interface, essential keys, paths, and CLI options |
| [Installation](https://get-zari.vercel.app/docs/installation/) | Releases, Debian/Ubuntu, signed Arch repository, AUR, and source builds |
| [Configuration](https://get-zari.vercel.app/docs/configuration/) | XDG paths, manager settings, preview settings, and safe reload |
| [Keybindings](https://get-zari.vercel.app/docs/keybindings/) | Default controls, remapping, multi-key chords, and bookmarks |
| [Themes](https://get-zari.vercel.app/docs/themes/) | Built-in presets and custom style overrides |
| [File operations](https://get-zari.vercel.app/docs/file-operations/) | Selection, clipboard, collisions, trash, and permanent deletion |
| [Architecture](https://get-zari.vercel.app/docs/architecture/) | C++ modules, ownership boundaries, and repository layout |
| [Development](https://get-zari.vercel.app/docs/development/) | Tests, contribution checklist, design constraints, and roadmap |
| [Troubleshooting](https://get-zari.vercel.app/docs/troubleshooting/) | Terminal, build, configuration, and opener problems |

Press `?` inside Zari for help generated from the active keymap.

## Build and test

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

The project targets C++20 and compiles with `-Wall -Wextra -Wpedantic`. Issues and focused pull requests are welcome; read the [development guide](https://get-zari.vercel.app/docs/development/) before making substantial changes.

## License

Zari is free software licensed under the [GNU General Public License, version 3 or later](LICENSE). See [COPYRIGHT](COPYRIGHT) for the project notice.

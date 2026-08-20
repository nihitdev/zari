# Getting started

## Requirements

- Linux and a UTF-8 locale
- CMake 3.20+
- A C++20 compiler
- ncursesw development headers

## Install a release

```sh
curl -fsSL https://raw.githubusercontent.com/nihitdev/zari/main/install.sh | sh
```

The installer verifies the release checksum and installs into `~/.local` without `sudo`. Set `ZARI_INSTALL_ROOT` to choose another prefix or `ZARI_VERSION` to pin a release.

Debian and Ubuntu users can download a `.deb` from GitHub Releases and run `sudo apt install ./zari_0.1.0_amd64.deb`. The AUR package can be installed with `yay -S zari` after its first publication.

## Build from source

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
./build/zari
```

Pass a directory to open it directly: `zari ~/Projects`. Start with `j`, `k`, `h`, and `l` for movement, `Space` for selection, `?` for help, and `q` to quit.

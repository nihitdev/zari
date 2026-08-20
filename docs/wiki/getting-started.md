# Getting started

## Requirements

- Linux and a UTF-8 locale
- CMake 3.20+
- A C++20 compiler
- ncursesw development headers

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
./build/zari
```

Pass a directory to open it directly: `zari ~/Projects`. Start with `j`, `k`, `h`, and `l` for movement, `Space` for selection, `?` for help, and `q` to quit.

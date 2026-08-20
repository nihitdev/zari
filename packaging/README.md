# Packaging Zari

Zari uses one tagged release as the source of truth for every distribution format.

## GitHub releases

Pushing a tag such as `v0.1.0` runs `.github/workflows/release.yml`. It builds and tests x86_64 and aarch64 binaries, creates portable archives and Debian packages, generates `SHA256SUMS`, and publishes all artifacts to the matching GitHub release.

## Debian package

CPack can build a binary package locally:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
cd build && cpack -G DEB
```

The `packaging/debian` directory also contains source-package metadata for Debian tooling. Copy or symlink it to `debian` in a packaging checkout before running `dpkg-buildpackage`.

## AUR

Update `pkgver`, reset `pkgrel` to `1`, regenerate `.SRCINFO` with `makepkg --printsrcinfo > .SRCINFO`, and test with `makepkg --cleanbuild`. The package expects the corresponding `v$pkgver` Git tag to exist.

Publishing to the AUR requires a separately registered AUR account and SSH key; no credentials belong in this repository.

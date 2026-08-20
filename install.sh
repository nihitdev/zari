#!/bin/sh
# Install the latest Zari release for the current user.
set -eu

repo="nihitdev/zari"
install_root="${ZARI_INSTALL_ROOT:-${HOME}/.local}"
version="${ZARI_VERSION:-latest}"

die() { printf 'zari installer: %s\n' "$*" >&2; exit 1; }
need() { command -v "$1" >/dev/null 2>&1 || die "required command not found: $1"; }

need curl
need tar
need sha256sum
need mktemp

case "$(uname -s)" in Linux) ;; *) die "only Linux is currently supported" ;; esac
case "$(uname -m)" in
  x86_64|amd64) arch="x86_64" ;;
  aarch64|arm64) arch="aarch64" ;;
  *) die "unsupported architecture: $(uname -m)" ;;
esac

asset="zari-linux-${arch}.tar.gz"
if [ "$version" = latest ]; then
  base="https://github.com/${repo}/releases/latest/download"
else
  case "$version" in v*) tag="$version" ;; *) tag="v$version" ;; esac
  base="https://github.com/${repo}/releases/download/${tag}"
fi

tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT HUP INT TERM

printf 'Downloading %s...\n' "$asset"
curl --fail --location --proto '=https' --tlsv1.2 --output "$tmp/$asset" "$base/$asset"
curl --fail --location --proto '=https' --tlsv1.2 --output "$tmp/SHA256SUMS" "$base/SHA256SUMS"

(cd "$tmp" && grep "  ${asset}$" SHA256SUMS | sha256sum --check --status -) || die "checksum verification failed"
tar -xzf "$tmp/$asset" -C "$tmp"

mkdir -p "$install_root/bin" "$install_root/share/zari/themes"
install -m 0755 "$tmp/bin/zari" "$install_root/bin/zari"
cp -R "$tmp/share/zari/themes/." "$install_root/share/zari/themes/"

printf '\nZari installed to %s/bin/zari\n' "$install_root"
case ":${PATH}:" in
  *":${install_root}/bin:"*) ;;
  *) printf 'Add %s/bin to PATH to run zari from anywhere.\n' "$install_root" ;;
esac

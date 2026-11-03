# moonlight-appimage

ARM64 (aarch64) AppImage builds of [moonlight-qt](https://github.com/moonlight-stream/moonlight-qt)
for [DroidDeck](https://github.com/Droid-Deck/DroidDeck).

Upstream publishes an x86_64 AppImage only; aarch64 ships as distro packages. These binaries are
built from the upstream repository at the tag pinned in `.github/workflows/build.yml` (`v6.2.0`
today), on a native `ubuntu-24.04-arm` runner, with the Qt stack from Ubuntu 24.04 and the same
SDL3 / sdl2-compat / SDL_ttf / libva / libplacebo / dav1d / FFmpeg revisions upstream's own
AppImage job uses.

Asset name: `Moonlight-<version>-aarch64.AppImage`, with a sibling `.sha256`.

## License

Moonlight is licensed under GPL-3.0. The corresponding source for every binary published here is:

- the upstream repository at the built tag:
  `https://github.com/moonlight-stream/moonlight-qt/tree/v6.2.0`, and
- the single patch applied to it before building:
  [`patches/0001-apprun-prefer-x11.patch`](patches/0001-apprun-prefer-x11.patch) in this repository
  (sets `SDL_VIDEODRIVER=x11` in the AppRun when an X server is reachable, matching the UI backend
  this AppImage is built with).

Everything else in the image comes from those sources and the pinned dependency revisions in the
workflow.

## Install on DroidDeck

1. Setup → Launcher → **Linux apps (beta)** → turn **AppImages** on.
2. Apps → **Add app** → **GitHub** tab → enter `moronigranja/moonlight-appimage` → Add.

DroidDeck downloads this repository's newest release asset, unpacks it once into the Linux runtime
(`/opt/appimages/user/<dir>`) and adds a menu entry. The image is not re-extracted on every launch.

## Rebuild / bump

Run the **Build - Linux AppImage (aarch64)** workflow with a new `tag` input, or push a `v*` tag.
The release asset is always `Moonlight-<version>-aarch64.AppImage` plus its `.sha256`; the workflow
fails before publishing unless the image is an AArch64 type-2 AppImage whose AppRun carries the X11
pin and whose Qt platform plugin is xcb.

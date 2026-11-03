ARM64 (aarch64) AppImage of **Moonlight**, built from
[`moonlight-stream/moonlight-qt`](https://github.com/moonlight-stream/moonlight-qt) at the tag this
release is named after, on a native arm64 runner. Upstream ships only an x86_64 AppImage.

- Source: `https://github.com/moonlight-stream/moonlight-qt/tree/v6.2.0`
- Build patch: `patches/0001-apprun-prefer-x11.patch` in this repository
- Asset: `Moonlight-6.2.0-aarch64.AppImage`
- Integrity: `Moonlight-6.2.0-aarch64.AppImage.sha256` (`sha256sum -c` it after downloading)

Moonlight is GPL-3.0. The build log for this release is attached to the workflow run that produced
it (Actions → Build - Linux AppImage (aarch64)).

## Install on DroidDeck

1. Setup → Launcher → **Linux apps (beta)** → turn **AppImages** on.
2. Apps → **Add app** → **GitHub** tab → enter `moronigranja/moonlight-appimage` → Add.

DroidDeck picks the `aarch64` asset from the newest release, unpacks it once into the Linux runtime
and adds a menu entry.

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
- the patches applied to it before building, both in this repository:
  - [`patches/0001-apprun-prefer-x11.patch`](patches/0001-apprun-prefer-x11.patch) — sets
    `SDL_VIDEODRIVER=x11` in the AppRun when an X server is reachable, matching the UI backend this
    AppImage is built with.
  - [`patches/0002-sdl-pulse-default-guard.patch`](patches/0002-sdl-pulse-default-guard.patch) — applied to SDL 3.4.18
    before it is built. SDL's PulseAudio backend hands the server's default sink/source names to
    `SDL_strdup()`/`SDL_strcmp()` unchecked, so it segfaults against a PulseAudio server that has no
    sinks or sources (such a server reports NULL names). DroidDeck's Linux runtime runs exactly such
    a server, which is why unpatched Moonlight dies with SIGSEGV as soon as a stream starts and audio
    is initialised.

Everything else in the image comes from those sources and the pinned dependency revisions in the
workflow.

## Install on DroidDeck

1. Setup → Launcher → **Linux apps (beta)** → turn **AppImages** on.
2. Apps → **Add app** → **GitHub** tab → enter `moronigranja/moonlight-appimage` → Add.

DroidDeck downloads this repository's newest release asset, unpacks it once into the Linux runtime
(`/opt/appimages/user/<dir>`) and adds a menu entry. The image is not re-extracted on every launch.

### Decoding

The image is built with VA-API, Vulkan video and VDPAU decoding enabled, and Moonlight picks whichever
the Linux runtime can actually open at launch. Where the runtime has no GPU decoder driver it prints
"No functioning hardware accelerated video decoder was detected" once and falls back to FFmpeg
software decoding; choose **Video codec = H.264** and **Decoder = Software** in Moonlight's settings if
software HEVC/AV1 is too slow.

### Audio

Moonlight opens the PulseAudio device the Linux runtime exposes. Where the runtime's PulseAudio server
has no sink at all (it then reports `Default Sink: (null)`), the stream still starts and video plays,
but Moonlight logs `Failed to open audio device: No default audio device available` and stays silent.
The sink has to exist in the runtime — the image cannot invent one.

Older builds of this image died with SIGSEGV in that situation, because SDL's PulseAudio backend
passed the NULL default device names to `SDL_strdup()`; `patches/0002-sdl-pulse-default-guard.patch`
removes that crash.

## Rebuild / bump

Run the **Build - Linux AppImage (aarch64)** workflow with a new `tag` input, or push a `v*` tag.
The release asset is always `Moonlight-<version>-aarch64.AppImage` plus its `.sha256`; the workflow
fails before publishing unless the image is an AArch64 type-2 AppImage whose AppRun carries the X11
pin and whose Qt platform plugin is xcb.

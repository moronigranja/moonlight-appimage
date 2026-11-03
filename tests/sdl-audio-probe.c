// Minimal check that SDL's audio subsystem initializes against a PulseAudio server that has
// no sinks or sources. Such a server reports NULL default device names, and SDL 3.4's pulse
// backend used to pass those straight to SDL_strdup()/SDL_strcmp(), which segfaults.
// See patches/0002-sdl-pulse-default-guard.patch.
#include <SDL3/SDL.h>

int main(void)
{
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("SDL_Init(SDL_INIT_AUDIO) failed: %s", SDL_GetError());
        return 1;
    }
    int count = 0;
    SDL_GetAudioPlaybackDevices(&count);
    SDL_Log("audio initialised, %d playback device(s)", count);
    SDL_Quit();
    return 0;
}

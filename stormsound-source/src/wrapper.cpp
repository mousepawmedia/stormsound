#include "wrapper.hpp"

using namespace StormSound;

int initialize_library(int flags)
{
    int status = Mix_Init(flags);
    if ((flags & status) != DEFAULT_FLAGS) {
        return 0;
    } else {
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
        return 1;
    }
}

int quit_library()
{
    while (Mix_Quit(0))
        Mix_Quit();
    return 1;
}

Mix_Chunk* load_event_audio(const onestring& file_name)
{
    return Mix_LoadWAV(file_name.c_str());
}

Mix_Music* load_music_audio(const onestring& file_name)
{
   return Mix_LoadMUS(file_name.c_str());
}
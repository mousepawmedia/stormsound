#include "stormsound/stormsound.hpp"

stormsound::stormsound() {
    /* Initialize SDL_Mixer with a certain configuration,
     * then check for errors
     */
    int status = Mix_Init(DEFAULT_FLAGS);
    if ((DEFAULT_FLAGS & status) != DEFAULT_FLAGS) {
        throw "Couldn't iniitalize SDL_Mixer!\n";
    }

    Mix_OpenAudio(info.frequency, info.format, info.channels, DEFAULT_CHUNK_SIZE);
}

stormsound::~stormsound() {
    Mix_Quit();
}

stormsound& stormsound::get_instance() {
    static stormsound storm_sound_instance;
    return storm_sound_instance;
}

void stormsound::bind_data(const AudioInfo& info) {
    std::scoped_lock lock(this->m);
    Mix_CloseAudio();
    this->info = info;
    Mix_OpenAudio(info.frequency, info.format, info.channels, 2);
}

void stormsound::register_music_audio(const onestring& file_name)
{
    // Open File, do necessary actions
    std::scoped_lock lock(this->m);
    Mix_Music* temp = Mix_LoadMUS(file_name.c_str());
    if (temp == nullptr)
    {
        throw "Failed to load music.\n";
    }
    this->music_sound = temp;
}

void stormsound::create_batch(const onestring& batch_name)
{
    // TODO: Simplify
    std::scoped_lock(this->m);
    this->event_batch[batch_name][onestring()] = nullptr;
}

bool stormsound::bind_batch(const onestring& batch_name)
{
    std::scoped_lock(this->m);
    if (this->event_batch.find(batch_name) != this->event_batch.end())
    {
        this->current_batch = batch_name;
        return true;
    }
    return false;
}

bool stormsound::delete_batch(const onestring& batch_name)
{
    std::scoped_lock(this->m);
    if (this->event_batch.find(batch_name) == this->event_batch.end())
        return false;
    auto& v = this->event_batch[batch_name];
    for (auto& sound : v)
    {
        Mix_FreeChunk(sound.second);
    }
    this->event_batch.erase(batch_name);
    return true;
}

bool stormsound::register_event_audio(const onestring& file_name, const onestring& batch_name)
{
    std::scoped_lock(this->m);
    if (this->event_batch.find(batch_name) == this->event_batch.end())
        return false;
    Mix_Chunk* temp = Mix_LoadWAV(file_name.c_str());
    if (temp == nullptr)
    {
        throw "Failed to load event audio.\n";
    }
    this->event_batch[batch_name][file_name] = temp;

}

void stormsound::register_event_audio(const onestring& file_name)
{
    // Open File, do necessary actions
    std::scoped_lock lock(this->m);
    Mix_Chunk* temp = Mix_LoadWAV(file_name.c_str());
    if (temp == nullptr)
    {
        throw "Failed to load event audio.\n";
    }
    this->event_batch[this->current_batch][file_name] = temp;
}

void stormsound::delete_event_audio(const onestring& file_name, const onestring& batch_name)
{
    std::scoped_lock lock(this->m);
    // Delete the audio_id from the current batch
    Mix_FreeChunk(this->event_batch[batch_name][file_name]);
    this->event_batch[batch_name].erase(file_name);
}

void stormsound::delete_event_audio(const onestring& file_name)
{
    std::scoped_lock lock(this->m);
    // Delete the audio_id from the current batch
    Mix_FreeChunk(this->event_batch[current_batch][file_name]);
    this->event_batch[current_batch].erase(file_name);
}

void stormsound::clear_music_audio()
{
    std::scoped_lock lock(this->m);
    // Removes music audio
    Mix_HaltMusic();
    this->music_sound = nullptr;
}

void stormsound::play_event_audio(const onestring& file_name, const onestring& batch_name) const
{
    std::scoped_lock lock(this->m);
    // Play the specified audio from the specified batch
    // NOTE: Using .at() to avoid clashing with const
    Mix_PlayChannel(-1, this->event_batch.at(batch_name).at(file_name), 0);
}

void stormsound::play_event_audio(const onestring& file_name) const
{
    std::scoped_lock lock(this->m);
    //Play the specified audio
    Mix_PlayChannel(-1, this->event_batch.at(current_batch).at(file_name), 0);
}

void stormsound::start_music_audio() const
{
    std::scoped_lock lock(this->m);
    //Starts music, -1 plays for an infinite amount
    Mix_PlayMusic(this->music_sound, -1);
}

void stormsound::pause_music_audio() const
{
    std::scoped_lock lock(this->m);
    //Pauses music
    Mix_PauseMusic();
}

void stormsound::resume_music_audio() const
{
    std::scoped_lock lock(this->m);
    //Resumes music
    Mix_ResumeMusic();
}
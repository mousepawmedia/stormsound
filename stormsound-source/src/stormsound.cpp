#include "stormsound/stormsound.hpp"

StormSound::StormSound()
{
	/* Initialize SDL_Mixer with a certain configuration,
	 * then check for errors
	 */
	int status = Mix_Init(DEFAULT_FLAGS);
	if ((DEFAULT_FLAGS & status) != DEFAULT_FLAGS) {
		throw "Couldn't iniitalize SDL_Mixer!\n";
	}
	Mix_OpenAudio(info.frequency, info.format, info.channels, info.samples);
}

StormSound::~StormSound() { Mix_Quit(DEFAULT_FLAGS); }

StormSound& StormSound::get_instance()
{
	static StormSound storm_sound_instance;
	return storm_sound_instance;
}

void StormSound::bind_data(const AudioInfo& info)
{
	std::scoped_lock lock(this->m);
	Mix_CloseAudio();
	this->info = info;
	Mix_OpenAudio(info.frequency, info.format, info.channels, info.samples);
}

void StormSound::register_music_audio(const onestring& file_name)
{
	// Open File, do necessary actions
	std::scoped_lock lock(this->m);
	Mix_Music* temp = Mix_LoadMUS(file_name.c_str());
	if (temp == nullptr) {
		throw "Failed to load music.\n";
	}
	this->music_sound = temp;
}

void StormSound::register_event_audio(const onestring& file_name)
{
	// Open File, do necessary actions
	std::scoped_lock lock(this->m);
	Mix_Music* temp = Mix_LoadWAV(file_name.c_str());
	if (temp == nullptr) {
		throw "Failed to load event audio.\n";
	}
	this->loop_sounds[file_name] = temp;
}

void StormSound::delete_event_audio(const onestring& audio_id)
{
	std::scoped_lock lock(this->m);
	// Delete the audio_id from the hash map
	Mix_FreeChunk(this->event_sounds[audio_id]);
	this->event_sounds.erase(audio_id);
}

void StormSound::clear_music_audio()
{
	std::scoped_lock lock(this->m);
	// Removes music audio
	Mix_HaltMusic(this->music_sound);
	this->music_sound = nullptr;
}

void StormSound::play_event_audio(const onestring& audio_id) const
{
	std::scoped_lock lock(this->m);
	// Play the audio at the proper index
	Mix_PlayChannel(-1, this->event_sounds[audio_id], 0);
}

void StormSound::start_music_audio() const
{
	std::scoped_lock lock(this->m);
	// Starts music, -1 plays for an infinite amount
	Mix_PlayMusic(this->music_sound, -1);
}

void StormSound::pause_music_audio() const
{
	std::scoped_lock lock(this->m);
	// Pauses music
	Mix_PauseMusic();
}

void StormSound::resume_music_audio() const
{
	std::scoped_lock lock(this->m);
	// Resumes music
	Mix_ResumeMusic();
}
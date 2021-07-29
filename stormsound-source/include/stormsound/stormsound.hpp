#ifndef STORMSOUND_HPP
#define STORMSOUND_HPP

/** Main StormSound class [Stormsound]
 * Version: 0.1
 *
 * A Singleton class to be used for registering, deleting, and playing audio for
 * both events and loops.
 *
 * Author(s): Manuel Mateo
 */

/* LICENSE
 * Copyright (C) 2021 MousePaw Media.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <SDL2/SDL_mixer.h>
#include <mutex>
#include <unordered_map>
#include <vector>  // Temporary

#include "onestring/onestring.hpp"

// Placeholder for future struct that will hold data (ie bitrate, volume, etc.)
const unsigned int DEFAULT_CHUNK_SIZE = 2048;
const int DEFAULT_FLAGS =
	MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_FLAC | MIX_INIT_MP3;

struct AudioInfo {
	int frequency = MIX_DEFAULT_FREQUENCY;
	uint16_t format = MIX_DEFAULT_FORMAT;
	int channels = MIX_DEFAULT_CHANNELS;
	int chunk_size = DEFAULT_CHUNK_SIZE;
};

class StormSound
{
private:
	AudioInfo info;
	std::mutex m;
	Mix_Music* music_sound;
	// std::vector<Mix_Chunk*> event_sounds;
	std::unordered_map<onestring, Mix_Chunk*> event_sounds;

	StormSound();

public:
	/* Default Destructor */
	~StormSound();

	/* Deleted copy constructor and assignment operator to
	 * avoid multiple instances/better error messages
	 */

	StormSound(const StormSound&) = delete;
	void operator=(const StormSound&) = delete;

	// Gets the current instance
	[[nodiscard]] static StormSound& get_instance();

	/* Changes the working information to the information indicated
	 * \param info The new info to use when playing sounds
	 */
	void bind_data(const AudioInfo& info);

	/* Registers an audio file for an event
	 * \param file_name Audio file to use for the event
	 */
	void register_event_audio(const onestring& file_name);

	/* Registers an audio file to be played for the loop
	 * \param file_name Audio file to add to the loop
	 */
	void register_music_audio(const onestring& file_name);

	/* Deletes a specific event
	 * \param audio_id The ID of the audio to be removed
	 */
	void delete_event_audio(const onestring& audio_id);

	/* Deletes all audio in the loop
	 */
	void clear_music_audio();

	/* Plays a specified event audio
	 * \param audio_id Audio's ID to play
	 */
	void play_event_audio(const onestring& audio_id) const;

	/* Play all the audio in the loop
	 */
	void start_music_audio() const;

	/* Pause all the audio in the loop
	 */
	void pause_music_audio() const;

	/* Resume all the audio in the loop
	 */
	void resume_music_audio() const;
};

#endif
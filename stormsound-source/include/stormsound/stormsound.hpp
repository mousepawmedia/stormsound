#ifndef STORMSOUND_HPP
#define STORMSOUND_HPP

/** Main StormSound class [Stormsound]
  * Version: 0.1
  *
  * A Singleton class to be used for registering, deleting, and playing audio for both events and loops.
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
#include <vector> // Temporary
#include <mutex>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>
#include "onestring/onestring.hpp"

/* TODO: Add delay between sounds in a batch
 *
 */
const unsigned int DEFAULT_CHUNK_SIZE = 2048;
const int DEFAULT_FLAGS = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_FLAC | MIX_INIT_MP3;

struct AudioInfo
{
    // cppcheck-suppress unusedStructMember
    int frequency = MIX_DEFAULT_FREQUENCY;
    // cppcheck-suppress unusedStructMember
    uint16_t format = MIX_DEFAULT_FORMAT;
    // cppcheck-suppress unusedStructMember
    int channels = MIX_DEFAULT_CHANNELS;
    // cppcheck-suppress unusedStructMember
    int chunk_size = DEFAULT_CHUNK_SIZE;
};

class stormsound
{
    private:
        AudioInfo info;
        std::mutex m;
        Mix_Music* music_sound;
        onestring current_batch;

        std::unordered_map<onestring, std::unordered_map<onestring, Mix_Chunk*>> event_batch;

        stormsound();

    public:

        /* Default Destructor */
        ~stormsound();

        /** Deleted copy constructor and assignment operator to
          * avoid multiple instances/better error messages
          */

        stormsound(const stormsound&) = delete;
        void operator=(const stormsound&) = delete;

        /// Gets the current instance
        [[nodiscard]] static stormsound& get_instance();

        /** Changes the working information to the information indicated
          * \param info The new info to use when playing sounds
          */
        void bind_data(const AudioInfo& info);

        /** Creates a batch of event sounds
          * \param batch_name Name to refer to batch
          */
        void create_batch(const onestring& batch_name);

        /** Bind a batch of event sounds
          * \param batch_name Name to refer to batch
          * \return true if the batch was bound, false if the batch_name does not exist
          */
        bool bind_batch(const onestring& batch_name);

        /** Deletes a batch
          * \param batch_name Name to refer to batch
          * \return true if the batch was succesfully deleted, false if not
          */
        bool delete_batch(const onestring& batch_name);

        /** Register an event audio to a batch
          * \param batch_name Name to refer to batch
          * \return true if the batch was succesfully deleted, false if not
          */
        bool register_event_audio(const onestring& file_name, const onestring& batch_name);

        /** Registers an audio file for an event to the current batch
          * \param file_name Audio file to use for the event
          */
        void register_event_audio(const onestring& file_name);

        /** Registers an audio file to be played for the loop
          * \param file_name Audio file to add to the loop
          */
        void register_music_audio(const onestring& file_name);

        /** Deletes a specific event audio from the specified batch
          * \param file_name The filename of the audio to remove
          * \param batch_name The name of the batch which contains the audio
          */
        void delete_event_audio(const onestring& file_name, const onestring& batch_name);

        /** Deletes a specific event audio from the current batch
          * \param file_name The filename of the audio to be removed
          */
        void delete_event_audio(const onestring& file_name);

        /** Deletes all audio in the loop
          */
        void clear_music_audio();

         /** Plays a specified event audio
           * \param file_name Play a specified audio event from the specified batch
           * \param batch_name The batch from which to play the audio from
           */
        void play_event_audio(const onestring& audio_id, const onestring& batch_name) const;

        /** Plays a specified event audio
          * \param file_name Play a specified audio event from the current batch
          */
        void play_event_audio(const onestring& audio_id) const;

        /** Play all the audio in the loop
          */
        void start_music_audio() const;

         /** Pause all the audio in the loop
           */
        void pause_music_audio() const;

         /** Resume all the audio in the loop
           */
        void resume_music_audio() const;
};

#endif

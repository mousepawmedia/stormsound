#ifndef WRAPPER_HPP
#define WRAPPER_HPP

/** Sound Library Wrapper [Stormsound]
  * Version: 0.1
  *
  * A a namespace with functions that abstract away certain library functionalities.
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

#include "onestring/onestring.hpp"
#include <SDL2/SDL_mixer.h>

namespace StormSound
{
    int initalize_library(int flags = 0);
    int quit_library();
    Mix_Chunk* load_event_audio(const onestring& file_name);
    Mix_Music* load_music_audio(const onestring& file_name);
}

#endif // WRAPPER_HPP
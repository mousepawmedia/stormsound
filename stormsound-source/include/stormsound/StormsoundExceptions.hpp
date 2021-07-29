/** Stormsound Exceptions [Stormsound]
 * Version: 0.1
 *
 * A temporary test class for Stormsound. This will be removed later
 * when we have other functionality to build and test with.
 *
 * Author(s): John Fu, Manuel Mateo
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

#ifndef STORMSOUND_EXCEPTIONS_H
#define STORMSOUND_EXCEPTIONS_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "SDL2/SDL.h"

class StormsoundException : public std::exception
{
private:
	std::string msg;

public:
	StormsoundException(const std::string& msg) : msg(msg){};

	virtual const char* what() const noexcept override { return msg.c_str(); }
};
#endif
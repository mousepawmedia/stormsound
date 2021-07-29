/** Stormsound Exceptions [Stormsound]
 * Version: 0.1
 *
 * A volume header class for Stormsound that controls volume
 *
 *
 * Author(s): John Fu
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

//#TODO
// volume and pan control, audio position in 3D, and audio animation
#ifndef volume_H
#define volume_H
#define PI 3.14159265
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

#include "SDL2/SDL.h"

#include "stormsound/StormsoundExceptions.hpp"
class volume
{
private:
	unsigned int previous_volume;

public:
	volume();
	~volume();
	/* Get the current volume of the all channels
	 * \return the volume
	 */
	int get_volume();
	/* Set volume for all allocated channels
	 * \return true if the volume was changed, false if the volume wasn't
	 * changed
	 */
	bool set_volume(const unsigned int& volume);
	/* Increase volume for all allocated channels
	 * \return true if the volume was increased, false if the volume wasn't
	 * changed
	 */
	bool increase_volume();
	/* Decrase volume for all allocated channels
	 * \return true if the volume was decreased, false if the volume wasn't
	 * changed
	 */
	bool decrease_volume();
	/* Get volume for selected chunk
	 * \return volume of selected chunk
	 */
	int get_chunk_volume(Mix_Chunk* chunk);
	/* Set volume for selected chunk
	 * \return true if the volume was changed, false if the volume wasn't
	 * changed
	 */
	bool set_chunk_volume(Mix_Chunk* chunk, const unsigned int& volume);
	/* Increase volume for selected chunk
	 * \return true if the volume was increased, false if the volume wasn't
	 * changed
	 */
	bool increase_chunk_volume(Mix_Chunk* chunk);
	/* Decrase volume for selected chunk
	 * \return true if the volume was decreased, false if the volume wasn't
	 * changed
	 */
	bool decrease_chunk_volume(Mix_Chunk* chunk);
	/* Get volume for music
	 * \return volume for music
	 */
	int get_music_volume();
	/* Set volume for music played
	 * \return true if the volume was changed, false if the volume wasn't
	 * changed
	 */
	bool set_music_volume(const unsigned int& volume);
	/* Increase volume for music played
	 * \return true if the volume was increased, false if the volume wasn't
	 * changed
	 */
	bool increase_music_volume();
	/* Decrase volume for music played
	 * \return true if the volume was decreased, false if the volume wasn't
	 * changed
	 */
	bool decrease_music_volume();
	/* Set panning for audio being played
	 * \return 0 is there was an error and 1 is successsful
	 */
	int set_panning(const int& left, const int& right) const;
	/* Get the angle relative to the user of where the sound is being played
	 * \return the angle
	 */
	int get_angle(const double& x, const double& y) const;
	/* Set the position (angle and distance) on a 2D grid with the user at the
	 * origin (0,0) does not return anything
	 */
	void set_2D_position(const double& x, const double& y) const;
	/* Set the position on a 3D grid with the user at the origin (0,0)
	 * Not yet implmented, would need two angles
	 */
	void set_3D_position(const double& x,
						 const double& y,
						 const double& z) const;
	/* Set the audio position on a 2D grid that moves
	 * closer to the user as time passes
	 * TODO: implement it in 3D
	 */
	void audio_animation(const double& x, const double& y) const;
};
#endif
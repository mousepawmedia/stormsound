/** Stormsound Exceptions [Stormsound]
 * Version: 0.1
 *
 * A volume class for Stormsound that controls volume
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
#include "stormsound/volume.hpp"

/*  1) Programatically checking audio chanels for expected changes
	Pros: It should work
	Pros: Automated
	Pros: Precise
	Cons: Extremely difficult
	Cons: Not sure how it would work with cloud-based jenkins

	2) Physically checking audio chanels for change
	Pros: Much easier
	Cons: Not precise
	Cons: Hard to unit test
	Cons: Requires ton of human time

	3) Checking Values
	Pros: Simple
	Pros: Precise
	Cons: Just because values are right doesn't mean the sound will be

	4) Programtically checking audio chanels for expected changes in different
 higher level language Pros: It should work Pros: Automated Pros: Precise Pros:
 Sounds easier upfront Cons: Does Python work well with older computers Cons:
 Won't know difficulty until we try Cons: Inconsistent with other tests
 (randomly python)

	5) Looking for an audio testing library?

 *
 */

volume::volume()
{
	SDL_Init(SDL_INIT_AUDIO);
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	if (Mix_OpenAudio(audio_rate,
					  audio_format,
					  audio_channels,
					  audio_buffers) == -1) {
		throw StormsoundException("Couldn't init audio");
	}
}
volume::~volume()
{
	SDL_Quit();
	SDL_CloseAudio();
	Mix_Quit();
}
int volume::get_volume() { return Mix_Volume(-1, -1); }
bool volume::set_volume(const unsigned int& volume)
{
	previous_volume = Mix_Volume(-1, -1);
	Mix_Volume(-1, volume);
	if ((volume != previous_volume) &&
		(Mix_Volume(-1, -1) != previous_volume)) {
		return true;
	}
	if ((volume == previous_volume) &&
		(Mix_Volume(-1, -1) == previous_volume)) {
		return true;
	}
	return false;
}
bool volume::increase_volume()
{
	previous_volume = Mix_Volume(-1, -1);
	if (previous_volume < MIX_MAX_VOLUME) {
		set_volume(previous_volume + 16);
	}
	if (Mix_Volume(-1, -1) > previous_volume) {
		return true;
	}
	return false;
}
bool volume::decrease_volume()
{
	previous_volume = Mix_Volume(-1, -1);
	if (previous_volume > 0) {
		set_volume(previous_volume - 16);
	}
	if (Mix_Volume(-1, -1) < previous_volume) {
		return true;
	}
	return false;
}
int volume::get_chunk_volume(Mix_Chunk* chunk)
{
	return Mix_VolumeChunk(chunk, -1);
}
bool volume::set_chunk_volume(Mix_Chunk* chunk, const unsigned int& volume)
{
	previous_volume = Mix_VolumeChunk(chunk, -1);
	Mix_VolumeChunk(chunk, volume);
	if ((volume != previous_volume) &&
		(Mix_VolumeChunk(chunk, -1) != previous_volume)) {
		return true;
	}
	if ((volume == previous_volume) &&
		(Mix_VolumeChunk(chunk, -1) == previous_volume)) {
		return true;
	}
	return false;
}
bool volume::increase_chunk_volume(Mix_Chunk* chunk)
{
	previous_volume = Mix_VolumeChunk(chunk, -1);
	if (previous_volume < MIX_MAX_VOLUME) {
		set_chunk_volume(chunk, previous_volume + 16);
	}
	if (Mix_VolumeChunk(chunk, -1) > previous_volume) {
		return true;
	}
	return false;
}
bool volume::decrease_chunk_volume(Mix_Chunk* chunk)
{
	previous_volume = Mix_VolumeChunk(chunk, -1);
	if (previous_volume > 0) {
		set_chunk_volume(chunk, previous_volume - 16);
	}
	if (Mix_VolumeChunk(chunk, -1) < previous_volume) {
		return true;
	}
	return false;
}
int volume::get_music_volume() { return Mix_VolumeMusic(-1); }
bool volume::set_music_volume(const unsigned int& volume)
{
	previous_volume = Mix_VolumeMusic(-1);
	Mix_VolumeMusic(volume);
	if ((volume != previous_volume) &&
		(Mix_VolumeMusic(-1) != previous_volume)) {
		return true;
	}
	if ((volume == previous_volume) &&
		(Mix_VolumeMusic(-1) == previous_volume)) {
		return true;
	}
	return false;
}
bool volume::increase_music_volume()
{
	previous_volume = Mix_VolumeMusic(-1);
	if (previous_volume < MIX_MAX_VOLUME) {
		set_music_volume(previous_volume + 16);
	}
	if (Mix_VolumeMusic(-1) > previous_volume) {
		return true;
	}
	return false;
}
bool volume::decrease_music_volume()
{
	previous_volume = Mix_VolumeMusic(-1);
	if (previous_volume > 0) {
		set_music_volume(previous_volume - 16);
	}
	if (Mix_VolumeMusic(-1) < previous_volume) {
		return true;
	}
	return false;
}
int volume::set_panning(const int& left, const int& right) const
{
	return Mix_SetPanning(MIX_CHANNEL_POST, left, right);
}
int volume::get_angle(const double& x, const double& y) const
{
	double direc = atan(y / x) * (180 / PI);
	if (y > 0 && x < 0) {
		direc += 180;
	} else if (y < 0 && x < 0) {
		direc += 180;
	} else if (x > 0 && y < 0) {
		direc += 360;
	}
	direc = (-direc + 360) + 90;
	return (int)direc % 360;
}
void volume::set_2D_position(const double& x, const double& y) const
{
	int angle = get_angle(x, y);
	uint distance = sqrt(pow(x, 2) + pow(y, 2));
	Mix_SetPosition(MIX_CHANNEL_POST, angle, distance);
}

void volume::audio_animation(const double& x, const double& y) const
{
	int angle = get_angle(x, y);
	uint distance = sqrt(pow(x, 2) + pow(y, 2));
	while (distance != 0) {
		sleep(2);
		Mix_SetPosition(MIX_CHANNEL_POST, angle, distance);
		distance -= 2;
	}
}
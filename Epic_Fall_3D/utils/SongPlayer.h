#pragma once
#include "../Music.h"

using SetSongToPlayCallback = void ( * )( Music& );

enum class SongFlag {
	MENU = 0,
	PLAYING = 1,
	GAME_OVER = 2,
};

void setSongToPlayCallback(Music& musicToPlay);

void setSongToPlay(Music& musicToPlay, SongFlag& currentSong, const SongFlag& songToPlay, SetSongToPlayCallback callback);

#include "SongPlayer.h"

void setSongToPlayCallback(Music& musicToPlay) {
	//Music::haltMusic();
	musicToPlay.playMusic();
}

void setSongToPlay(Music& musicToPlay, SongFlag& currentSong, const SongFlag& songToPlay ,SetSongToPlayCallback callback) {
	if( currentSong != songToPlay )
	{
	callback(musicToPlay);
	currentSong = songToPlay;
	}
}


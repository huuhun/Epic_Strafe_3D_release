#pragma once
#include <iostream>
#include <SDL_mixer.h>
#include <Windows.h>

class Music
{
public:
	Music(const std::string& path);
	~Music();

	void playMusic();

	static void haltMusic();

private:
	Mix_Music* m_Music;
};

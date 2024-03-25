#include "Music.h"

Music::Music(const std::string& path)
{
    m_Music = Mix_LoadMUS(path.c_str());
    if( !m_Music ) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
    }
}

Music::~Music()
{
    Mix_HaltMusic();
    if( m_Music != nullptr )
    {
        Mix_FreeMusic(m_Music);
        std::cout << "Freed music\n";
    }
    Mix_CloseAudio();
}

void Music::playMusic()
{
    if( Mix_PlayMusic(m_Music, -1) == -1 ) { // -1 for infinite loop, 0 to play once
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(m_Music);
        Mix_CloseAudio();
    }
}

void Music::haltMusic() {
    // Stop the first music
    Mix_HaltMusic();
}


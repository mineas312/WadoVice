#pragma once
#include <string>

class MP3Player
{
    public:
        MP3Player();
        void LoadRes(std::string res_name);
        void LoadFile(std::string mp3_path, std::string alias);
        void Play(std::string alias, bool loop);
        void Stop(std::string alias);
};

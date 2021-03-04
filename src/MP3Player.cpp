#pragma comment(lib, "Winmm.lib")
#include "MP3Player.hpp"
#include <windows.h>
#include <winbase.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include "ResourceUtil.hpp"
#include <string>

MP3Player::MP3Player()
{}

void MP3Player::LoadRes(std::string res_name)
{
    LoadFile(GetResourcePath(res_name, ".mp3").string(), res_name);
}

void MP3Player::LoadFile(std::string mp3_path, std::string alias)
{
    std::string command = "open \"" + mp3_path + "\" TYPE mpegvideo alias " + alias;
    mciSendString(command.c_str(), NULL, 0, 0);
}

void MP3Player::Play(std::string alias, bool loop)
{
    std::string command = "play " + alias + (loop ? " repeat" : " from 0");
    mciSendString(command.c_str(), NULL, 0, 0);
}

void MP3Player::Stop(std::string alias)
{
    std::string command = "stop " + alias;
    mciSendString(command.c_str(), NULL, 0, 0);
}

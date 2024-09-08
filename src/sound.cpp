#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "sound.hpp"
#include "constants.hpp"

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;
using constants::SOUND_DEAD;
using constants::SOUND_FOOD;
using constants::SOUND_PORTAL;
using constants::SOUND_SNAKE;
using constants::SOUND_BUTTON_UP;
using constants::SOUND_BUTTON_DOWN;
using constants::SOUND_BUTTON_ENTER;
using constants::SOUND_QUIT;
using constants::SOUND_BLIP;
using constants::FAILED_TO_LOAD_FILE_ERR;

sound::sound (const string& filepath)
{
    init(filepath);
}

void sound::playSound ()
{
    soundObj.play();
}

void sound::setPitch (const float& pitch)
{
    soundObj.setPitch(pitch);
}

void sound::init (const string& filepath)
{
    if (!buffer.loadFromFile(filepath))
        throw std::runtime_error(FAILED_TO_LOAD_FILE_ERR + " '" + filepath + "'");
    soundObj.setBuffer(buffer);
    soundObj.setVolume(50.0f);
}

SoundManager::SoundManager ()
{
    audioInit();
}

void SoundManager::audioInit ()
{
    audioCont["dead"] =         make_unique<sound>(SOUND_DEAD);
    audioCont["food"] =         make_unique<sound>(SOUND_FOOD);
    audioCont["portal"] =       make_unique<sound>(SOUND_PORTAL);
    audioCont["snake"] =        make_unique<sound>(SOUND_SNAKE);
    audioCont["button_up"] =    make_unique<sound>(SOUND_BUTTON_UP);
    audioCont["button_down"] =  make_unique<sound>(SOUND_BUTTON_DOWN);
    audioCont["button_enter"] = make_unique<sound>(SOUND_BUTTON_ENTER);
    audioCont["quit"] =         make_unique<sound>(SOUND_QUIT);
    audioCont["blip"] =         make_unique<sound>(SOUND_BLIP);
}

void SoundManager::playAudio (const string& name)
{
    if (audioCont.find(name) != audioCont.end())
        audioCont[name]->playSound();
}

void SoundManager::setPitch (const string& name, const float& pitch)
{
    if (audioCont.find(name) != audioCont.end())
        audioCont[name]->setPitch(pitch);
}


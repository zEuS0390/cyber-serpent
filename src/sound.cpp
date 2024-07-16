#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "sound.h"

using std::string;
using std::cout;
using std::endl;

sound::sound (string name, string filepath)
:   name(name) {
        init(filepath);
}

void sound::playSound () {
    soundObj.play();
}

void sound::setPitch (float pitch) {
    soundObj.setPitch(pitch);
}

void sound::init (string filepath) {
    if (!buffer.loadFromFile(filepath)) {
        cout << "Error loading sound file." << endl;
        return;
    }
    soundObj.setBuffer(buffer);
    soundObj.setVolume(50.0f);
}

SoundManager::SoundManager () {
    audioInit();
}

SoundManager::~SoundManager () {
    terminateAudioThreads();
}

void SoundManager::audioInit () {
    audioCont.push_back(new sound("dead", "sfx/dead.wav"));
    audioCont.push_back(new sound("food", "sfx/food.wav"));
    audioCont.push_back(new sound("portal", "sfx/portal.wav"));
    audioCont.push_back(new sound("snake", "sfx/snake.wav"));
    audioCont.push_back(new sound("button_up", "sfx/button_up.wav"));
    audioCont.push_back(new sound("button_down", "sfx/button_down.wav"));
    audioCont.push_back(new sound("button_enter", "sfx/button_enter.wav"));
    audioCont.push_back(new sound("quit", "sfx/quit.wav"));
    audioCont.push_back(new sound("blip", "sfx/blip.wav"));
}

void SoundManager::playAudio (string name) {
    for (unsigned int index = 0; index < audioCont.size(); index++) {
        if (name == audioCont[index]->name)
            audioCont[index]->playSound();
    }
}

void SoundManager::setPitch (string name, float pitch) {
    for (unsigned int index = 0; index < audioCont.size(); index++) {
        if (name == audioCont[index]->name)
            audioCont[index]->setPitch(pitch);
    }
}

void SoundManager::terminateAudioThreads () {
    while (!audioCont.empty()) {
        delete audioCont.back();
        audioCont.pop_back();
    }
}

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "sound.h"

sound::sound (std::string name, std::string filepath)
:   name(name) {
        init(filepath);
}

void sound::playSound (void) {
    soundObj.play();
    return;
}

void sound::setPitch (float pitch) {
    soundObj.setPitch(pitch);
    return;
}

void sound::init (std::string filepath) {
    if (!buffer.loadFromFile(filepath)) {
        std::cout << "Error loading sound file." << std::endl;
        return;
    }
    soundObj.setBuffer(buffer);
    soundObj.setVolume(50.0f);
    return;
}

SoundManager::SoundManager (void) {
    audioInit();
}

SoundManager::~SoundManager (void) {
    terminateAudioThreads();
}

void SoundManager::audioInit (void) {
    audioCont.push_back(new sound("dead", "sfx/dead.wav"));
    audioCont.push_back(new sound("food", "sfx/food.wav"));
    audioCont.push_back(new sound("portal", "sfx/portal.wav"));
    audioCont.push_back(new sound("snake", "sfx/snake.wav"));
    audioCont.push_back(new sound("button_up", "sfx/button_up.wav"));
    audioCont.push_back(new sound("button_down", "sfx/button_down.wav"));
    audioCont.push_back(new sound("button_enter", "sfx/button_enter.wav"));
    audioCont.push_back(new sound("quit", "sfx/quit.wav"));
    audioCont.push_back(new sound("blip", "sfx/blip.wav"));
    return;
}

void SoundManager::playAudio (std::string name) {
    for (unsigned int index = 0; index < audioCont.size(); index++) {
        if (name == audioCont[index]->name) {
            audioCont[index]->playSound();
        }
    }
    return;
}

void SoundManager::setPitch (std::string name, float pitch) {
    for (unsigned int index = 0; index < audioCont.size(); index++) {
        if (name == audioCont[index]->name) {
            audioCont[index]->setPitch(pitch);
        }
    }
}

void SoundManager::terminateAudioThreads (void) {
    while (!audioCont.empty()) {
        delete audioCont.back();
        audioCont.pop_back();
    }
    return;
}

#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>
#include <string>

// sound class
class sound {
    public:
        std::string name;
        sound (std::string, std::string);
    public:
        void playSound  ();
        void setPitch   (float);
    private:
        void init       (std::string);
    private:
        sf::SoundBuffer buffer;
        sf::Sound       soundObj;
};

// soundManager class
class SoundManager {
    public:
        SoundManager                ();
        ~SoundManager               ();
        void audioInit              ();
        void playAudio              (std::string);
        void setPitch               (std::string, float);
        void terminateAudioThreads  ();
    private:
        std::vector<sound*> audioCont;
};

#endif

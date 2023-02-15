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
        void playSound  (void);
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
        SoundManager                (void);
        ~SoundManager               (void);
        void audioInit              (void);
        void playAudio              (std::string);
        void setPitch               (std::string, float);
        void terminateAudioThreads  (void);
    private:
        std::vector<sound*> audioCont;
};

#endif

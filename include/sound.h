#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <string>

using std::string;
using std::vector;

// sound class
class sound {
    public:
        string name;
        sound (string, string);
        void playSound  ();
        void setPitch   (float);
    private:
        sf::SoundBuffer buffer;
        sf::Sound       soundObj;
	void init       (string);
};

// soundManager class
class SoundManager {
    public:
        SoundManager                ();
        ~SoundManager               ();
        void audioInit              ();
        void playAudio              (string);
        void setPitch               (string, float);
        void terminateAudioThreads  ();
    private:
        vector<sound*> audioCont;
};

#endif

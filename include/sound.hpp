#ifndef SOUND_HPP
#define SOUND_HPP

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <string>

using std::string;
using sf::SoundBuffer;
using sf::Sound;
using std::unordered_map;
using std::unique_ptr;

// sound class
class sound
{
public:
        explicit sound                                  (const string&);
        void playSound                                  ();
        void setPitch                                   (const float&);
private:
        SoundBuffer                                     buffer;
        Sound                                           soundObj;
	void init                                       (const string&);
};

// soundManager class
class SoundManager
{
public:
        SoundManager                                    ();
        void audioInit                                  ();
        void playAudio                                  (const string&);
        void setPitch                                   (const string&, const float&);
private:
	unordered_map<string, unique_ptr<sound>>        audioCont;
};

#endif

#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

class ScoreManager
{
public:
    ScoreManager            (int);
    ScoreManager            ();
    int getScore            () const;
    void addScore           (int);
    void resetScore         ();
    int getHighScore        () const;
    void saveHighScore      ();
    void loadHighScore      ();
private:
    int score;
    int high_score;
};

#endif


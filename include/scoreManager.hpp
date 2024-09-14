#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

class ScoreManager
{
public:
    ScoreManager        (int);
    ScoreManager        ();
    void setScore       (int);
    int getScore        () const;
    void addScore       (int);
    void resetScore     ();
private:
    int score;
};

#endif


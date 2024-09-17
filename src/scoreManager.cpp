#include "scoreManager.hpp"

ScoreManager::ScoreManager (int value)
:   score{value}
{
}

ScoreManager::ScoreManager ()
:   score{0}
{
}

void ScoreManager::setScore(int value)
{
    score = value;
}

int ScoreManager::getScore() const
{
    return score;
}

void ScoreManager::addScore(int value)
{
    score += value;
}

void ScoreManager::resetScore()
{
    score = 0;
}


#include "scoreManager.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <fstream>
#include <sstream>

using constants::HIGH_SCORE_FILENAME;
using constants::FAILED_TO_LOAD_FILE_ERR;

ScoreManager::ScoreManager (int value)
:   score{value}
{
    loadHighScore();
}

ScoreManager::ScoreManager ()
:   score{0}
{
    loadHighScore();
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

int ScoreManager::getHighScore() const
{
    return high_score;
}

void ScoreManager::loadHighScore()
{
    std::ifstream highScoreFile(joinPath(getExecutableDir(), HIGH_SCORE_FILENAME));
    if (!highScoreFile.is_open())
    {
        high_score = 0;
        return;
    }

    std::string line;
    if (!std::getline(highScoreFile, line))
    {
        high_score = 0;
        return;
    }

    // Use a stringstream to parse the number safely
    int temp_score;
    std::istringstream iss(line);
    if (!(iss >> temp_score) || !(iss >> std::ws).eof())
    {
        high_score = 0;
        return;
    }

    high_score = temp_score;
}

void ScoreManager::saveHighScore()
{
    high_score = (score > high_score)? score : high_score;

    std::ofstream highScoreFile(joinPath(getExecutableDir(), HIGH_SCORE_FILENAME));
    if (!highScoreFile)
    {
        throw std::runtime_error(FAILED_TO_LOAD_FILE_ERR + ": '" + HIGH_SCORE_FILENAME + "'");
    }
    highScoreFile << high_score;
}


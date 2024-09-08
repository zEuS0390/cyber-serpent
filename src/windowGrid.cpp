#include "windowGrid.hpp"
#include "constants.hpp"

using constants::GRID_SCALE;

windowGrid::windowGrid (unsigned int winX, unsigned int winY)
:   winX(winX),
    winY(winY),
    scale(GRID_SCALE)
{
}


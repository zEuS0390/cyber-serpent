#include "windowGrid.h"
#include "constants.h"

using constants::GRID_SCALE;

windowGrid::windowGrid (unsigned int winX, unsigned int winY)
: winX(winX), winY(winY), scale(GRID_SCALE) {}

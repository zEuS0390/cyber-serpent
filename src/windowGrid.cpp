#include "windowGrid.h"

point::point (float x, float y)
: x(x), y(y) {
}

line::line (point _p1, point _p2)
: _p1(_p1), _p2(_p2) {
}

windowGrid::windowGrid (unsigned int winX, unsigned int winY)
: scale(20) {
    for (unsigned int i = 0; i < winX; i++) {
        if (i%scale == 0) {
            point* _p1 = new point((float)i, scale);
            point* _p2 = new point((float)i, winY-scale);
            line* _l = new line(*_p1, *_p2);
            vertLines.push_back(*_l);
            delete _p1;
            delete _p2;
            delete _l;
        }
    }
    for (unsigned int i = 0; i < winY; i++) {
        if (i%scale == 0) {
            point* _p1 = new point(scale, (float)i);
            point* _p2 = new point(winX-scale, (float)i);
            line* _l = new line(*_p1, *_p2);
            horiLines.push_back(*_l);
            delete _p1;
            delete _p2;
            delete _l;
        }
    }
}

std::vector<line> windowGrid::getVertLines (void) {
    return vertLines;
}

std::vector<line> windowGrid::getHoriLines (void) {
    return horiLines;
}

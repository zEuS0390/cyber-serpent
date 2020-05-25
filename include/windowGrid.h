#ifndef WINDOWGRID_H
#define WINDOWGRID_H
#include <vector>

class point {
    public:
        float x;
        float y;
        point (float, float);
};

class line {
    public:
        point _p1;
        point _p2;
        line (point, point);
};

class windowGrid {
    public:
        unsigned int scale;
        windowGrid(const unsigned int, const unsigned int);
        std::vector<line> getVertLines(void);
        std::vector<line> getHoriLines(void);
    private:
        std::vector<line> vertLines;
        std::vector<line> horiLines;
};

#endif

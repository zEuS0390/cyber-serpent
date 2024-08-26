#include <string>
#include <sstream>
#include "utils.hpp"

using std::string;
using std::stringstream;

string intToStr (const int& number)
{
    stringstream str;
    str << number;
    return str.str();
}


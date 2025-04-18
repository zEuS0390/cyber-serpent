#include <string>
#include <sstream>
#include "utils.hpp"

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#endif

using std::string;
using std::stringstream;

string intToStr (const int& number)
{
    stringstream str;
    str << number;
    return str.str();
}

string getExecutablePath ()
{
    char buffer[1024];

#ifdef _WIN32
    GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
#elif __linux__
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) buffer[len] = '\0';
#endif

    return string(buffer);
}

std::string getExecutableDir() {
    std::string path = getExecutablePath();
    size_t slash = path.find_last_of("/\\");
    return path.substr(0, slash);
}

string joinPath (const string& dir, const string& file)
{
    if (dir.empty()) return file;

    char sep =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif

    if (dir.back() == sep)
    {
        return dir + file;
    }
    else
    {
        return dir + sep + file;
    }
}


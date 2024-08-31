# CyberSerpent

CyberSerpent is essentially a classic snake game that moves in different directions, passes through borders, and appears on the other side. With its neon-lit grid design, it gives players a sense of nostalgia while remaining fun at the same time.

<b>Demo Video:</b> https://youtu.be/nnagibXqy0g

## Installation
The binaries I have made so far are for Linux and Windows machines; I haven’t tried to build them on macOS. Just go to the latest release link and download the installer or archive file for your operating system.

<b>Download the Latest Release:</b> https://github.com/zEuS0390/cpp-sfml-snake-game/releases/latest

## Build from Source
You can build the game from the source using the [CMake](https://cmake.org/download/) tool, so make sure you have it installed. I designed it to allow you to easily build it on your own machine. The game was created with the SFML library, but since it's already defined in the CMake configuration file, you don’t need to handle it manually.

If you are using Linux, make sure that the following [dependencies](https://gist.github.com/zEuS0390/1b2dfd25e01692e6c1cd1d86fd72b4df) are present on your system; otherwise, it will not work properly:

- libfreetype6-dev
- libx11-dev
- libxrandr-dev
- libudev-dev
- libgl1-mesa-dev
- libflac-dev
- libsndfile1-dev
- libvorbis-dev
- libvorbisenc2
- libvorbisfile3
- libopenal-dev
- libpthread-stubs0-dev
- libjpeg8-dev
- libxcursor-dev

**Note:** Make sure you have [Git](https://git-scm.com/downloads) installed, as it will be used by CMake to download SFML.

Follow these steps:

1. Open a terminal and navigate to the root directory of the project.
2. Create an empty directory: `mkdir build/`.
3. Generate the build system files in it: `cmake -S . -B build/`.
4. Build the project: `cmake --build build/`.
5. Finally, navigate to the `build/bin` directory and run the game.

## Demo Screenshots
<p align="center">
  <img src="https://user-images.githubusercontent.com/39390245/218938173-03587f41-be8e-4ac1-9cca-610c372623ce.png" alt="menu"><br><br>
  <img src="https://user-images.githubusercontent.com/39390245/218938167-27d25246-636d-428c-bfed-9b49bd266f96.png" alt="gameplay-2"><br><br>
  <img src="https://user-images.githubusercontent.com/39390245/218938176-216a014a-e3e2-4a65-8cdb-7591cd629c1e.png" alt="gameplay-1"><br><br>
  <img src="https://github.com/zEuS0390/cpp-sfml-snake-game/assets/39390245/86ae6f20-384d-4666-8ac6-b5c321a16a5d" alt="gameplay-3">
</p>

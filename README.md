# SFML Snake Game

Demo Video: https://youtu.be/nnagibXqy0g

## How to Build?
1. Download the latest version of [SFML 2.x](https://www.sfml-dev.org/download.php), make sure it is compatible to your platform. After that, extract and place it in the libs directory. If you want to let the CMake handle it for you, just set the ```SNAKE_AUTO_DOWNLOAD``` to ```TRUE```.
3. Open the terminal or command prompt and navigate to the project's build directory.
4. Proceed to step 5 if you're not using Linux. Install the required dependency ```libopenal-dev```.
5. Execute the command ```cmake ..``` followed by ```mingw32-make```, ```cmake --build .``` or ```make```.
6. A bin directory will be created, which contains the executable program. Go there and run it.

## Screenshots
<p align="center">
  <img src="https://user-images.githubusercontent.com/39390245/218938173-03587f41-be8e-4ac1-9cca-610c372623ce.png" alt="menu"><br><br>
  <img src="https://user-images.githubusercontent.com/39390245/218938167-27d25246-636d-428c-bfed-9b49bd266f96.png" alt="gameplay-2"><br><br>
  <img src="https://user-images.githubusercontent.com/39390245/218938176-216a014a-e3e2-4a65-8cdb-7591cd629c1e.png" alt="gameplay-1">
</p>

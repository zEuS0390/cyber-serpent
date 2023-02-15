cmake_minimum_required(VERSION 3.21)
project(SFML_SNAKE_GAME)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS audio graphics window system REQUIRED)
add_executable(SFML_SNAKE_GAME
	src/anim.cpp src/food.cpp
	src/food.cpp src/interface.cpp
	src/intro.cpp src/main.cpp
	src/snake.cpp src/snakeGame.cpp
	src/sound.cpp src/windowGrid.cpp
)
target_link_libraries(SFML_SNAKE_GAME sfml-audio sfml-graphics sfml-window sfml-system)
target_include_directories(SFML_SNAKE_GAME PRIVATE include)

add_custom_command(TARGET SFML_SNAKE_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:SFML_SNAKE_GAME>/gfx)
add_custom_command(TARGET SFML_SNAKE_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:SFML_SNAKE_GAME>/sfx)
add_custom_command(TARGET SFML_SNAKE_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/november.ttf $<TARGET_FILE_DIR:SFML_SNAKE_GAME>)

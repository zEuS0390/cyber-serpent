cmake_minimum_required(VERSION 3.21)
project(SFML_SNAKE_GAME)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_BUILD_TYPE "Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(APP_ICON_RC "${CMAKE_SOURCE_DIR}/rc/icon.rc")
set(APP_SRC_FILES
	src/anim.cpp src/food.cpp
	src/food.cpp src/interface.cpp
	src/intro.cpp src/main.cpp
	src/snake.cpp src/snakeGame.cpp
	src/sound.cpp src/windowGrid.cpp
)

find_package(SFML COMPONENTS audio graphics window system REQUIRED)
if (WIN32)
	add_executable(SFML_SNAKE_GAME WIN32 ${APP_SRC_FILES} $<$<PLATFORM_ID:Windows>:${APP_ICON_RC}>)
else()
	add_executable(SFML_SNAKE_GAME ${APP_SRC_FILES} $<$<PLATFORM_ID:Windows>:${APP_ICON_RC}>)
endif()	

target_link_libraries(SFML_SNAKE_GAME sfml-audio sfml-graphics sfml-window sfml-system)
target_include_directories(SFML_SNAKE_GAME PRIVATE include)

add_custom_command(TARGET SFML_SNAKE_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:SFML_SNAKE_GAME>/gfx)
add_custom_command(TARGET SFML_SNAKE_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:SFML_SNAKE_GAME>/sfx)
add_custom_command(TARGET SFML_SNAKE_GAME POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/november.ttf $<TARGET_FILE_DIR:SFML_SNAKE_GAME>)

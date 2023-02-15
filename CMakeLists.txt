cmake_minimum_required(VERSION 3.21)
project(snake_game_by_zEuS0390 VERSION 1.0.0)

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
	add_executable(${PROJECT_NAME} WIN32 ${APP_SRC_FILES} $<$<PLATFORM_ID:Windows>:${APP_ICON_RC}>)
else()
	add_executable(${PROJECT_NAME} ${APP_SRC_FILES} $<$<PLATFORM_ID:Windows>:${APP_ICON_RC}>)
endif()	

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
target_include_directories(${PROJECT_NAME} PRIVATE include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/sfx)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/november.ttf $<TARGET_FILE_DIR:${PROJECT_NAME}>)

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/gfx DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/sfx DESTINATION ".")
install(FILES ${PROJECT_SOURCE_DIR}/november.ttf DESTINATION ".")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_NAME "snake_game_by_zEuS0390")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)

cmake_minimum_required(VERSION 3.21)
project(snake_game_by_zEuS0390 VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 17)
set(SFML_NAME "SFML-2.5.1")
set(SFML_DIR "libs/${SFML_NAME}/lib/cmake/SFML")
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
SET(SFML_BUILD_TYPE "Release")
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
if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	add_executable(${PROJECT_NAME} WIN32 ${APP_SRC_FILES} $<$<PLATFORM_ID:Windows>:${APP_ICON_RC}>)
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system 
		-static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
else()
	add_executable(${PROJECT_NAME} ${APP_SRC_FILES})
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)
endif()	
target_include_directories(${PROJECT_NAME} PRIVATE include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/sfx)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/november.ttf $<TARGET_FILE_DIR:${PROJECT_NAME}>)
if (CMAKE_SYSTEM_NAME MATCHES Windows)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/libs/${SFML_NAME}/bin/openal32.dll 
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/gfx DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/sfx DESTINATION ".")
install(FILES ${PROJECT_SOURCE_DIR}/november.ttf 
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/libs/${SFML_NAME}/bin/openal32.dll> 
	DESTINATION ".")

set(CPACK_GENERATOR "NSIS")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_NAME "snake_game_by_zEuS0390")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
if (CPACK_GENERATOR MATCHES "NSIS")
	list(APPEND CPACK_NSIS_CREATE_ICONS_EXTRA
		"CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\${PROJECT_NAME}.exe'"
		"CreateShortCut '$DESKTOP\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\${PROJECT_NAME}.exe'")
	list(APPEND CPACK_NSIS_DELETE_ICONS_EXTRA
		"Delete '$SMPROGRAMS\\\\$START_MENU\\\\${PROJECT_NAME}.lnk'"
		"Delete '$DESKTOP\\\\${PROJECT_NAME}.lnk'")
	string(REPLACE ";" "\n" CPACK_NSIS_CREATE_ICONS_EXTRA "${CPACK_NSIS_CREATE_ICONS_EXTRA}")
	string(REPLACE ";" "\n" CPACK_NSIS_DELETE_ICONS_EXTRA "${CPACK_NSIS_DELETE_ICONS_EXTRA}")
endif()

include(CPack)

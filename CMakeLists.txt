cmake_minimum_required(VERSION 3.9)
project(KingsBountyUnitDisplay)

set(EXE kb_unit_display)

set(SRC
	src/main.cpp
	src/unit.cpp
)

add_executable(${EXE} ${SRC})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(${EXE} sfml-graphics)

add_custom_target(copy-runtime-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXE}>
    DEPENDS ${EXE})

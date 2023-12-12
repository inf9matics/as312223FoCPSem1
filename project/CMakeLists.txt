project(project)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(project ${SOURCES})

add_subdirectory(test)
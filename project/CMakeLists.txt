project(project)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(project_exec ${SOURCES})
enable_testing()
add_subdirectory(test)
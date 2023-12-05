project(lab-10)

include_directories(project_ex)

file(GLOB SOURCES project_ex/*.cpp)

add_executable(lab-10 ${SOURCES})
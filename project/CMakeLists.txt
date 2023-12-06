project(project)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(project ${SOURCES})

add_test(NAME project_test1_c COMMAND project -i testingAssets/project_test1.raw -o testingAssets/project_test1.compressed -t c -n 4096000 -k 4096000)
add_test(NAME project_test1_d COMMAND project -i testingAssets/project_test1.compressed -o testingAssets/project_test1.decompressed -t d -n 4096000 -k 4096000)
set_tests_properties(project_test1_d PROPERTIES DEPENDS project_test1_c)
add_test(NAME project_test1_d_check COMMAND cmp testingAssets/project_test1.raw testingAssets/project_test1.decompressed)
set_tests_properties(project_test1_d_check PROPERTIES DEPENDS project_test1_d)

add_test(NAME project_test2_c COMMAND project -i testingAssets/project_test2.raw -o testingAssets/project_test2.compressed -t c -n 4096000 -k 4096000)
add_test(NAME project_test2_d COMMAND project -i testingAssets/project_test2.compressed -o testingAssets/project_test2.decompressed -t d -n 4096000 -k 4096000)
set_tests_properties(project_test2_d PROPERTIES DEPENDS project_test2_c)
add_test(NAME project_test2_d_check COMMAND cmp testingAssets/project_test2.raw testingAssets/project_test2.decompressed)
set_tests_properties(project_test2_d_check PROPERTIES DEPENDS project_test1_d)
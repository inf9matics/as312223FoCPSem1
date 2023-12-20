enable_testing()
include(CTest)

set(assets_trabus322_eu "https://assets.trabus322.eu/jenkins.trabus322.eu/FoCPProject")

add_test(NAME project_test1_c COMMAND $<TARGET_FILE:project_exec> -i ${PROJECT_SOURCE_DIR}/test/res/project_test1.raw.txt -o project_test1.txt.compressed -t c -n 4096000 -k 4096000)
set_tests_properties(project_test1_c PROPERTIES LABELS "project")

add_test(NAME project_test1_d COMMAND $<TARGET_FILE:project_exec> -i project_test1.txt.compressed -o project_test1.decompressed.txt -t d -n 4096000 -k 4096000)
set_tests_properties(project_test1_d PROPERTIES LABELS "project")
set_tests_properties(project_test1_d PROPERTIES DEPENDS project_test1_c)

add_test(NAME project_test1_d_check COMMAND cmp ${PROJECT_SOURCE_DIR}/test/res/project_test1.raw.txt project_test1.decompressed.txt)
set_tests_properties(project_test1_d_check PROPERTIES LABELS "project")
set_tests_properties(project_test1_d_check PROPERTIES DEPENDS project_test1_d)

add_test(NAME project_test1_cp_compressed COMMAND cp project_test1.txt.compressed ${PROJECT_SOURCE_DIR}/test/result)
set_tests_properties(project_test1_cp_compressed PROPERTIES LABELS "project")

add_test(NAME project_test1_cp_decompressed COMMAND cp project_test1.decompressed.txt ${PROJECT_SOURCE_DIR}/test/result)
set_tests_properties(project_test1_cp_decompressed PROPERTIES LABELS "project")



add_test(NAME project_test2_c COMMAND $<TARGET_FILE:project_exec> -i ${PROJECT_SOURCE_DIR}/test/res/project_test2.raw.txt -o project_test2.txt.compressed -t c -n 4096000 -k 4096000)
set_tests_properties(project_test2_c PROPERTIES LABELS "project")

add_test(NAME project_test2_d COMMAND $<TARGET_FILE:project_exec> -i project_test2.txt.compressed -o project_test2.decompressed.txt -t d -n 4096000 -k 4096000)
set_tests_properties(project_test2_d PROPERTIES LABELS "project")
set_tests_properties(project_test2_d PROPERTIES DEPENDS project_test2_c)

add_test(NAME project_test2_d_check COMMAND cmp ${PROJECT_SOURCE_DIR}/test/res/project_test2.raw.txt project_test2.decompressed.txt)
set_tests_properties(project_test2_d_check PROPERTIES LABELS "project")
set_tests_properties(project_test2_d_check PROPERTIES DEPENDS project_test2_d)

add_test(NAME project_test2_cp_compressed COMMAND cp project_test2.txt.compressed ${PROJECT_SOURCE_DIR}/test/result)
set_tests_properties(project_test2_cp_compressed PROPERTIES LABELS "project")

add_test(NAME project_test2_cp_decompressed COMMAND cp project_test2.decompressed.txt ${PROJECT_SOURCE_DIR}/test/result)
set_tests_properties(project_test2_cp_decompressed PROPERTIES LABELS "project")



add_test(NAME project_test3_prepare COMMAND curl "${assets_trabus322_eu}/1.raw.png" --output 1.raw.png)
set_tests_properties(project_test3_prepare PROPERTIES LABELS "project")

add_test(NAME project_test3_c COMMAND $<TARGET_FILE:project_exec> -i 1.raw.png -o 1.png.compressed -t c -n 4096000 -k 4096000)
set_tests_properties(project_test3_c PROPERTIES LABELS "project")
set_tests_properties(project_test3_c PROPERTIES DEPENDS project_test3_prepare)

add_test(NAME project_test3_d COMMAND $<TARGET_FILE:project_exec> -i 1.png.compressed -o 1.uncompressed.png -t d -n 4096000 -k 4096000)
set_tests_properties(project_test3_d PROPERTIES LABELS "project")
set_tests_properties(project_test3_d PROPERTIES DEPENDS project_test3_c)

add_test(NAME project_test3_d_check COMMAND cmp 1.raw.png 1.uncompressed.png)
set_tests_properties(project_test3_d_check PROPERTIES LABELS "project")
set_tests_properties(project_test3_d_check PROPERTIES DEPENDS project_test3_d)

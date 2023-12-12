add_test(NAME project_test1_c COMMAND $<TARGET_FILE:project> -i ${PROJECT_SOURCE_DIR}/test/res/project_test1.raw -o ${PROJECT_SOURCE_DIR}/test/res/project_test1.compressed -t c -n 4096000 -k 4096000)
set_tests_properties(project_test1_c PROPERTIES LABELS "project")

add_test(NAME project_test1_d COMMAND $<TARGET_FILE:project> -i ${PROJECT_SOURCE_DIR}/test/res/project_test1.compressed -o ${PROJECT_SOURCE_DIR}/test/res/project_test1.decompressed -t d -n 4096000 -k 4096000)
set_tests_properties(project_test1_d PROPERTIES LABELS "project")
set_tests_properties(project_test1_d PROPERTIES DEPENDS project_test1_c)

add_test(NAME project_test1_d_check COMMAND cmp ${PROJECT_SOURCE_DIR}/test/res/project_test1.raw ${PROJECT_SOURCE_DIR}/test/res/project_test1.decompressed)
set_tests_properties(project_test1_d_check PROPERTIES LABELS "project")
set_tests_properties(project_test1_d_check PROPERTIES DEPENDS project_test1_d)



add_test(NAME project_test2_c COMMAND $<TARGET_FILE:project> -i ${PROJECT_SOURCE_DIR}/test/res/project_test2.raw -o ${PROJECT_SOURCE_DIR}/test/res/project_test2.compressed -t c -n 4096000 -k 4096000)
set_tests_properties(project_test2_c PROPERTIES LABELS "project")

add_test(NAME project_test2_d COMMAND $<TARGET_FILE:project> -i ${PROJECT_SOURCE_DIR}/test/res/project_test2.compressed -o ${PROJECT_SOURCE_DIR}/test/res/project_test2.decompressed -t d -n 4096000 -k 4096000)
set_tests_properties(project_test2_d PROPERTIES LABELS "project")
set_tests_properties(project_test2_d PROPERTIES DEPENDS project_test2_c)

add_test(NAME project_test2_d_check COMMAND cmp ${PROJECT_SOURCE_DIR}/test/res/project_test2.raw ${PROJECT_SOURCE_DIR}/test/res/project_test2.decompressed)
set_tests_properties(project_test2_d_check PROPERTIES LABELS "project")
set_tests_properties(project_test2_d_check PROPERTIES DEPENDS project_test2_d)
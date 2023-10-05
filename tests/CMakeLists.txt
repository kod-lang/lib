
enable_testing()

add_executable(config-test
  ../src/config.c
  config_test.c)

add_executable(status-test
  ../src/status.c
  status_test.c)

add_executable(string-test
  ../src/string.c
  string_test.c)

add_executable(value-test
  ../src/value.c
  value_test.c)

add_test(NAME config-test COMMAND config-test)
add_test(NAME status-test COMMAND status-test)
add_test(NAME string-test COMMAND string-test)
add_test(NAME value-test  COMMAND value-test)

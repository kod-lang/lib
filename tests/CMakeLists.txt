
enable_testing()

add_executable(value-test
  ../src/value.c
  value_test.c)

add_test(NAME value-test COMMAND value-test)


enable_testing()

add_executable(chunk-test
  ../src/chunk.c
  ../src/memory.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  chunk_test.c)

add_executable(memory-test
  ../src/memory.c
  ../src/status.c
  memory_test.c)

add_executable(status-test
  ../src/status.c
  status_test.c)

add_executable(string-test
  ../src/memory.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  string_test.c)

add_executable(utils-test
  ../src/utils.c
  utils_test.c)

add_executable(value-test
  ../src/memory.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  ../src/value.c
  value_test.c)

add_test(NAME chunk-test  COMMAND chunk-test)
add_test(NAME memory-test COMMAND memory-test)
add_test(NAME status-test COMMAND status-test)
add_test(NAME string-test COMMAND string-test)
add_test(NAME utils-test  COMMAND utils-test)
add_test(NAME value-test  COMMAND value-test)

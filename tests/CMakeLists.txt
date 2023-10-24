
enable_testing()

add_executable(chunk-test
  ../src/chunk.c
  ../src/memory.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  chunk_test.c)

add_executable(function-test
  ../src/chunk.c
  ../src/function.c
  ../src/memory.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  function_test.c)

add_executable(memory-test
  ../src/memory.c
  ../src/status.c
  memory_test.c)

add_executable(range-test
  ../src/memory.c
  ../src/range.c
  ../src/status.c
  range_test.c)

add_executable(stack-test
  ../src/memory.c
  ../src/range.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  ../src/value.c
  stack_test.c)

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
  ../src/range.c
  ../src/status.c
  ../src/string.c
  ../src/utils.c
  ../src/value.c
  value_test.c)

add_executable(vector-test
  ../src/memory.c
  ../src/status.c
  ../src/utils.c
  vector_test.c)

add_test(NAME chunk-test    COMMAND chunk-test)
add_test(NAME function-test COMMAND function-test)
add_test(NAME memory-test   COMMAND memory-test)
add_test(NAME range-test    COMMAND range-test)
add_test(NAME stack-test    COMMAND stack-test)
add_test(NAME status-test   COMMAND status-test)
add_test(NAME string-test   COMMAND string-test)
add_test(NAME utils-test    COMMAND utils-test)
add_test(NAME value-test    COMMAND value-test)
add_test(NAME vector-test   COMMAND vector-test)

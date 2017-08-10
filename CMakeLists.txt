cmake_minimum_required(VERSION 3.6)
project(crypto_book_excercises)

find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})



set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/botan-1.10")
include_directories("cpp_utils/headers")

set(UTILS cpp_utils/src/utils.cpp cpp_utils/src/modes.cpp)

set(3_8_SOURCES 3_8/cpp/solution.cpp ${UTILS})

set(SOURCE_FILES ${3_8_SOURCES})

set(HEADERS cpp_utils/headers/modes.h cpp_utils/headers/utils.h cpp_utils/headers/sha512n.hxx)


add_executable(3_8 ${3_8_SOURCES})
target_link_libraries(3_8 "botan-1.10")
add_executable(3_9 3_9/cpp/solution.cpp ${UTILS})
target_link_libraries(3_9 "botan-1.10")
add_executable(4_3 4/4_3/solution.cpp ${UTILS})
target_link_libraries(4_3 "botan-1.10")

add_executable(4_4 4/4_4/solution.cpp ${UTILS})
target_link_libraries(4_4 "botan-1.10")

add_executable(4_5 4/4_5/solution.cpp ${UTILS})
target_link_libraries(4_5 "botan-1.10")


add_executable(5_2 5/5_2/solution.cpp ${UTILS})
target_link_libraries(5_2 "botan-1.10")

add_executable(5_3 5/5_3/solution.cpp ${UTILS})
target_link_libraries(5_3 "botan-1.10")


add_executable(tests cpp_utils/test/tests.cpp ${UTILS})
target_link_libraries(tests "botan-1.10")
target_link_libraries(tests ${Boost_LIBRARIES})

add_executable(workaround_header ${3_8_SOURCES} ${HEADERS})
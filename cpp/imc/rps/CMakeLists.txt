cmake_minimum_required (VERSION 3.5)
project (rps)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options(-Wall)
include_directories(include)

add_executable(rps
	src/RPS.cpp
	src/RPSApp.cpp
	src/ConsoleReader.cpp
	src/ConsoleWriter.cpp
	src/ComputerPlayer.cpp
	src/HumanPlayer.cpp
	)


#if (UNIT_TEST)
#	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#	enable_testing()
#
#	include(GoogleTest)
#	add_executable(guessing_game_test
#		test/main.cpp)
#	gtest_add_tests(TARGET guessing_game_test)
#	add_dependencies(guessing_game_test guessing_game)
#
#	target_link_libraries (guessing_game_test
#		gg
#		gcov
#		pthread
#		gtest
#		gmock)
#endif (UNIT_TEST)

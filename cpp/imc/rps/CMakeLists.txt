cmake_minimum_required (VERSION 3.5)
project (rps)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options(-Wall)
include_directories(include)

add_library(rps
	src/RPSApp.cpp
	src/IPlayer.cpp
	src/ConsoleReader.cpp
	src/ConsoleWriter.cpp
	src/ComputerPlayer.cpp
	src/HumanPlayer.cpp
	)

add_executable(rps_game
	src/RPS.cpp
	)

target_link_libraries(rps_game rps)

if (UNIT_TEST)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
	enable_testing()

	include(GoogleTest)
	add_executable(rps_test
		test/main.cpp
		test/RPSTest.cpp)
	gtest_add_tests(TARGET rps_test)
	add_dependencies(rps_test rps_game)

	target_link_libraries (rps_test
		rps
		gcov
		pthread
		gtest
		gmock)
endif (UNIT_TEST)

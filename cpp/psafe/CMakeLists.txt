cmake_minimum_required (VERSION 3.5)
project (guess_game)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options(-Wall)
include_directories(include)

add_library(gg
	src/ConsoleView.cpp
	src/DecisionTreeModel.cpp
	src/GamePresenter.cpp)

add_executable(guess_game
	src/GameApp.cpp
)

target_link_libraries (guess_game gg)

if (UNIT_TEST)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
	enable_testing()

	include(GoogleTest)
	add_executable(guess_game_test
		test/main.cpp)
	gtest_add_tests(TARGET guess_game_test)
	add_dependencies(guess_game_test guess_game)

	target_link_libraries (guess_game_test
		gg
		gcov
		pthread
		gtest
		gmock)
endif (UNIT_TEST)

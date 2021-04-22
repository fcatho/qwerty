cmake_minimum_required (VERSION 3.5)
project (guess_game)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options(-Wall)
include_directories(include)

add_executable(guess_game
	src/GameApp.cpp
	src/ConsoleView.cpp
	src/DecisionTreeModel.cpp
	src/GamePresenter.cpp
 )


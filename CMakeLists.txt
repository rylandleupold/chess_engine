cmake_minimum_required(VERSION 3.28.0)

project(ChessEngine LANGUAGES C CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} chess_engine.cpp)

add_subdirectory(src)
add_subdirectory(tests)
target_link_libraries(${PROJECT_NAME} ChessEngineLib)

if (NOT googletest) # is googletest defined if already built?
	include(FetchContent)
	FetchContent_Declare(
		googletest
		# Specify the commit you depend on and update it regularly.
		URL https://github.com/google/googletest/archive/refs/heads/master.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
endif()

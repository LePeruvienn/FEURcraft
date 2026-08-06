# CMakeLists.txt pour la liaison des librairie nécessaire à la compilation

# Ajout des libarie présente en locale
add_subdirectory(glad)
add_subdirectory(stb)

# Recherche des paquets nécessaire à la compilation du projet
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)


#### SEARCHING AND CLONING PACKAGE IF DONT EXISTS TO REFACTO

# Package checking for GLFW
find_package(glfw3 QUIET)

if(NOT glfw3_FOUND)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/GLFW/CMakeLists.txt")
		message(FATAL_ERROR "GLFW is not intsalled and submodule is missing, run : git submodule update --init --recursive")
	endif()

	message(STATUS "GLFW not installed, compiling it locally")
	add_subdirectory(GLFW EXCLUDE_FROM_ALL)
endif()

# Package checking for OpenAL
find_package(OpenAL QUIET)

if(NOT OpenAL_FOUND)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/OpenAL/CMakeLists.txt")
		message(FATAL_ERROR "OpenAL is not installed and submodule is missing, run : git submodule update --init --recursive")
	endif()

	message(STATUS "OpenAL not installed, compiling it locally")
	add_subdirectory(OpenAL EXCLUDE_FROM_ALL)
endif()

# Package checking for sndfile
find_package(SndFile QUIET)

if(NOT SndFile_FOUND)
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/sndfile/CMakeLists.txt")
		message(FATAL_ERROR
			"SndFile is not installed and submodule is missing, run : git submodule update --init --recursive"
		)
	endif()

	message(STATUS "SndFile not installed, compiling it locally")
	add_subdirectory(sndfile EXCLUDE_FROM_ALL)
endif()

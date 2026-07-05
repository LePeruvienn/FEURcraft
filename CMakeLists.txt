cmake_minimum_required(VERSION 3.23)

project(FEURcraft)

set(CMAKE_BUILD_TYPE Debug)

# Passage du standart C99 en C11
set(CMAKE_C_STANDARD 11)
# Pour que les extension d'autocomplétion fonctionne pour nvim / vscode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tout les binaire sont mis dans le dossier bin/ et les objets dans obj/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj)

# L'exutable principale à pour nom le nom du projet
add_executable(${PROJECT_NAME})

# Configuration des flags de compilation différentes sur Windows et Linux
if(MSVC)
	# Flag de warnings
	# target_compile_options(${EXECUTABLE_NAME} PRIVATE /W4 /WX)
	target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
else()
	# Flag warnings
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)
endif()

# Ajout du dossiers des dépendances
add_subdirectory(deps)
# Dossier du projet
add_subdirectory(FEURcraft)

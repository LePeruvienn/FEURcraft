# Get current dir name that is gonna be used as the current lib name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(LIB_NAME ${DIR_NAME})

# Création de la librairie
add_library(${LIB_NAME} STATIC)

# Flag de compilation
if(MSVC)
	# Windows est chiant
	# target_compile_options(${LIB_NAME} PRIVATE /W4 /WX)
else()
	target_compile_options(${LIB_NAME} PRIVATE -Wall -Werror -Wextra)
endif()

# Ajout des includes de la librairie
target_include_directories(${LIB_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private
)

# Fichiers sources de la librairie
target_sources(${LIB_NAME}
	PRIVATE
		src/file_helper.c
		src/window.c
		src/env_helper.c
		src/image.c
		src/keyboard.c
		src/keyboard_key.c
		src/mouse_input.c
		src/program_status.c
		src/feur_file.c
)

# On link les librarie nécessaire à la compilation de la lib
target_link_libraries(${LIB_NAME} PUBLIC utils math glfw glad stb_image data)

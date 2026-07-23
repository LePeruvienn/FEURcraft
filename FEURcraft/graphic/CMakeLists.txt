# ------------------------------#
# CMAKE FILE FOR GRAPHIC MODULE #
# ----------------------------- #

# Get current dir name that is gonna be used as the current lib name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(LIB_NAME ${DIR_NAME})

# Création de la librairie
add_library(${LIB_NAME} SHARED)

# Flag de compilation
target_compile_options(${LIB_NAME} PRIVATE -Wall -Werror -Wextra)

# Ajout des includes de la librairie
target_include_directories(${LIB_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private
)

# Fichiers sources de la librairie
target_sources(${LIB_NAME}
	PRIVATE
		src/vertex_layout.c
		src/mesh.c
		src/geometry.c
		src/shader.c
		src/shader_program.c
		src/camera.c
)


find_package(OpenGL REQUIRED)

# On link les librarie nécessaire à la compilation de la lib
target_link_libraries(${LIB_NAME}
	PUBLIC
		OpenGL::GL
		glad
		stb_image
		utils
		math
		system
)

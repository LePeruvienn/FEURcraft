# Ajout des sous dossiers qui représente des modules C
add_subdirectory(utils)
add_subdirectory(math)
add_subdirectory(graphic)

# Sources seulement présente dans l'exec
target_sources(${PROJECT_NAME}
	PRIVATE
		main.c 
)

# On link les librarie nécessaire à la compilation du projet
target_link_libraries(${PROJECT_NAME} PUBLIC utils)

# Ajout des sous dossiers qui représente des modules C
add_subdirectory(utils)
add_subdirectory(math)
add_subdirectory(data)
add_subdirectory(system)
add_subdirectory(world)
add_subdirectory(graphic)
add_subdirectory(audio)

# Sources seulement présente dans l'exec
target_sources(${PROJECT_NAME}
	PRIVATE
		main.c 
)

# On link les librarie nécessaire à la compilation du projet
target_link_libraries(${PROJECT_NAME} PUBLIC utils math system graphic audio)

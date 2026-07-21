# ---------------- #
# CODE EXAMPLES    #
# ---------------- #

# They can be used to setup the code in a specific situation,
# or just simple code samples

# Get all examples source files in the src/ dir
file(GLOB EXAMPLE_SOURCES "src/*.c")

# compile all the examples
foreach(SOURCE_FILE ${EXAMPLE_SOURCES})

	get_filename_component(EXAMPLE_NAME ${SOURCE_FILE} NAME_WE)

	set(EXEC_NAME "${EXAMPLE_NAME}.ex")

	add_executable(${EXEC_NAME} ${SOURCE_FILE})

	# Link all libs
	target_link_libraries(${EXEC_NAME} PRIVATE
		graphic
		math
		utils
		system
	)

endforeach()


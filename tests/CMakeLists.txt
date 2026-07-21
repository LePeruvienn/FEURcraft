# ---------------- #
# FEUR TESTS BUILD #
# ---------------- #

# Unit test with the FEUR_TEST lib 😎

# Get all test source files in the src/ dir
file(GLOB TEST_SOURCES "src/*.c")

# compile all the tests
foreach(SOURCE_FILE ${TEST_SOURCES})

	# Exclude template
	if(SOURCE_FILE MATCHES "template\\.c$")
		continue()
	endif()

	get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)

	set(EXEC_NAME "${TEST_NAME}.tst")

	add_executable(${EXEC_NAME} ${SOURCE_FILE})

	# Link all libs
	target_link_libraries(${EXEC_NAME} PRIVATE 
		graphic 
		math 
		utils 
		system
	)

endforeach()

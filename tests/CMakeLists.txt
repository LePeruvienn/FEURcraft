# ---------------- #
# FEUR TESTS BUILD #
# ---------------- #

# Addings tests to compile ...

# Template test you can take example from
add_executable(template.tst src/template.c)
target_link_libraries(template.tst PRIVATE utils)

# Testing if window creation wtih OpenGL context is working
add_executable(create_window.tst src/create_window.c)
target_link_libraries(create_window.tst PRIVATE system)


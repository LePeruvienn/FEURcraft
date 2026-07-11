# ---------------- #
# FEUR TESTS BUILD #
# ---------------- #

# Addings tests to compile ...

# Template test you can take example from
add_executable(template.tst src/template.c)
target_link_libraries(template.tst PRIVATE utils)


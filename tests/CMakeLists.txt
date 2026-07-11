# ---------------- #
# FEUR TESTS BUILD #
# ---------------- #

# Addings tests to compile ...

# Template test you can take example from
add_executable(template.tst src/template.c)
target_link_libraries(template.tst PRIVATE utils)

# Vec2 math test
add_executable(vec2.tst src/vec2.c)
target_link_libraries(vec2.tst PRIVATE math utils)

# Vec3 math test
add_executable(vec3.tst src/vec3.c)
target_link_libraries(vec3.tst PRIVATE math utils)

# Vec4 math test
add_executable(vec4.tst src/vec4.c)
target_link_libraries(vec4.tst PRIVATE math utils)

# Mat4 math test
add_executable(mat4.tst src/mat4.c)
target_link_libraries(mat4.tst PRIVATE math utils)

# Testing if window creation wtih OpenGL context is working
add_executable(create_window.tst src/create_window.c)
target_link_libraries(create_window.tst PRIVATE system utils)


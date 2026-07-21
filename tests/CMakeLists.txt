# ---------------- #
# FEUR TESTS BUILD #
# ---------------- #

# Addings tests to compile ...

# Template test you can take example from
add_executable(template.tst src/template.c)
target_link_libraries(template.tst PRIVATE utils system)

# Vec2 math test
add_executable(vec2.tst src/vec2.c)
target_link_libraries(vec2.tst PRIVATE math utils system)

# Vec3 math test
add_executable(vec3.tst src/vec3.c)
target_link_libraries(vec3.tst PRIVATE math utils system)

# Vec4 math test
add_executable(vec4.tst src/vec4.c)
target_link_libraries(vec4.tst PRIVATE math utils system)

# Mat4 math test
add_executable(mat4.tst src/mat4.c)
target_link_libraries(mat4.tst PRIVATE math utils system)

# Shader test
add_executable(shader.tst src/shader.c)
target_link_libraries(shader.tst PRIVATE utils graphic)

# ---------------- #
# CODE EXAMPLES    #
# ---------------- #

# They can be used to setup the code in a specific situation,
# or just simple code samples

# Draw something on screen
add_executable(simple_draw.ex src/simple_draw.c)
target_link_libraries(simple_draw.ex PRIVATE utils system graphic)


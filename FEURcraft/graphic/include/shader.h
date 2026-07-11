#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <stddef.h>

/**
 * \file shader.h
 * \brief Structure représentant les programme GPU (shader) OpenGL.
 *
 * Structure représentant les programme GPU (shader) OpenGL
 * et ses varaibles uniform modifiable via le programme C.
 */

/**
* \brief Type représentant un programme GPU (shader)
*/
typedef struct shader* shader;

/**
* \brief Compile le shader passer en praramêtre et renvoie son ID
*
* \param path chemin de fichier vers le shader glsl
* \param type type de shader à compiler (vertex ou fragment shader)
* \param out variable de retour pour l'ID du shader compiler
* \return statut de la compilation, 0 shader OK, autre erreur lors de la compilation
*/
int compile_shader(const char* path, GLuint type, GLuint* out);

/**
* \brief Assemble des shaders pour créer un programme GPU utilisable
*
* Prend une listes d'ID de shader déjà compiler, et les assemble pour créer un programme GPU utilisable.
*
* \param shaders listes des shaders à assembler
* \param size nombre de shader total à assembler
* \param out variable de retour pour l'ID du programme GPU
* \return statut de la compilation, 0 shader OK, autre erreur lors de la compilation
*/
int compile_shader_program(GLuint* shaders, unsigned int size, GLuint* out);

/**
* \brief Créer un shader à partir du code de son vertex et fragment.
* \param vert_shader_path chemin de fichier vers le vertex shader glsl
* \param frag_shader_path chemin de fichier vers le fragment shader glsl
* \return shader créée
*/
shader create_shader(const char* vert_shader_path, const char* frag_shader_path);

/**
* \brief Libère la mémoire alloué par le shader
* \param s shader à libérer
*/
void free_shader(shader s);

/**
* \brief Lie au GPU le shader s en paramêtre
* \param s shader à lier
*/
void bind_shader(shader s);

/**
* \brief Dé-Lie le shader actuelle lié
*/
void unbind_shader();

#endif // SHADER_H

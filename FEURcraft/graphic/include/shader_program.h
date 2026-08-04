#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "shader.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#include "glad/glad.h"

#include <stddef.h>
#include <stdbool.h>

/**
 * \file shader_programme.h
 * \brief Gestion des programmes GPU
 */

/**
 * \brief Représente le status du programme actuelle (lié, erreur, non lié)
 */
typedef enum ProgramStatus ProgramStatus;

enum ProgramStatus
{
	PROGRAM_STATUS_LINKED,
	PROGRAM_STATUS_NOT_LINKED,
	PROGRAM_STATUS_LINK_FAILED
};

/**
 * \brief Type représentnant un programme GPU pouvant être utilsé
 */
typedef struct ShaderProgram ShaderProgram;

struct ShaderProgram
{
	GLuint id;
	ProgramStatus status;

	Shader* shaders[SHADER_TYPE_COUNT];
};

/**
 * \brief Créer un nouveau \ref ShaderProgram
 * \brief retourn une pointeur sur un programme alloué sur le GPU et le tas
 */
ShaderProgram* shader_program_create();

/**
 * \brief Libère la mémoier du \ref ShaderProgram en paramêtre
 * \return le \ref ShaderProgram à libérer
 */
void shader_program_free(ShaderProgram* program);

/**
 * \brief Attache au programme le \ref Shader en paramêtre 
 * \param program \ref ShaderProgram cible
 * \param shader \ref Shader qu'on veut lui attacher
 */
void shader_program_attach(ShaderProgram* program, Shader* shader);

/**
 * \brief Détache du programme le \ref Shader en paramêtre 
 * \param program \ref ShaderProgram cible
 * \param shader \ref Shader qu'on veut lui détacher
 */
void shader_program_detach(ShaderProgram* program, Shader* shader);

/**
 * \brief Détache du programme tout les \ref Shader qui lui sont attaché
 * \param program \ref ShaderProgram cible
 */
void shader_program_detach_all(ShaderProgram* program);

/**
 * \brief Lie tout les \ref Shader attacher au \ref ShaderProgram
 * \note Après la liason des shaders on peut consulter le status du programme dans son attribut \b status
 * \param program \ref ShaderProgram cible
 */
void shader_program_link(ShaderProgram* program);

/**
 * \brief Affecte le programme en paramêtre comme celui actuellement utilisé pour le rendu
 * \param program \ref ShaderProgram cible
 */
void shader_program_use(ShaderProgram* program);

/**
 * \brief Déaffecte le shader actuellement utilisé pour le rendu
 */
void shader_program_unbind();

/**
 * \brief Affect à l'uniforme du programme la valeur booléenne donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_bool(ShaderProgram* program, const char* uniform, bool value);

/**
 * \brief Affect à l'uniforme du programme la valeur flottante donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_float(ShaderProgram* program, const char* uniform, float value);

/**
 * \brief Affect à l'uniforme du programme la valeur \ref Vec2 donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_vec2(ShaderProgram* program, const char* uniform, Vec2 vec);

/**
 * \brief Affect à l'uniforme du programme la valeur du \ref Vec3 donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_vec3(ShaderProgram* program, const char* uniform, Vec3 vec);

/**
 * \brief Affect à l'uniforme du programme la valeur du \ref Vec4 donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_vec4(ShaderProgram* program, const char* uniform, Vec4 vec);

/**
 * \brief Affect à l'uniforme du programme la valeur de la matrice 4 \times 4 \ref Mat4 donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_mat4(ShaderProgram* program, const char* uniform, Mat4 mat);

/**
 * \brief Affect à l'uniforme du programme la valeur de l'entier non signé donnée en paramêtre
 * \param programe \ref ShaderProgram cible
 * \param uniform nom de la variable uniforme
 * \param value valeur à lui attribuer
 */
void shader_program_set_texture_unit(ShaderProgram* program, const char* uniform, unsigned int unit);

#endif // SHADER_PROGRAM_H

#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

/**
 * \file shader.h
 * \brief Gestion et compilation des shaders
 *
 * Ce fichier est la pour représenter un Shader sur le GPU, \b et \b non \b pas \b son \b programm.
 * Il représente du coup souvent un fichier \c .glsl qui après être compiler peut être attacher
 * à un \ref ShaderProgram pour l'utiliser dans le pipeline de rendu
 */

/**
 * \brief Enum qui représente le un type de shader (Vertex, Fragment, ...)
 */
typedef enum ShaderType ShaderType;

/**
 * \brief Enum qui représente le status du shader actuelle (complié, erreur, non compilé)
 */
typedef enum ShaderStatus ShaderStatus;

enum ShaderType
{
	SHADER_TYPE_VERT,
	SHADER_TYPE_FRAG,

	SHADER_TYPE_COUNT
};

enum ShaderStatus
{
	SHADER_STATUS_COMPILED,
	SHADER_STATUS_NOT_COMPILED,
	SHADER_STATUS_COMPILE_FAILED
};


/**
 * \brief Structure représentant un Shader glsl
 */
typedef struct Shader Shader;

struct Shader
{
	GLuint id;

	const char* file_path;

	ShaderType type;
	ShaderStatus status;
};

/**
 * \brief Créer un Shader à partir d'un fichier \c .glsl
 * \param file_path chemin vers le fichier \c .glsl
 * \param type type du shader
 * \return Shader alloué sur le tas et le GPU
 */
Shader* shader_create(const char* file_path, ShaderType type);

/**
 * \brief Libèer la mémoier du Shader en paramêtre
 * \param shader Shader à libérer
 */
void shader_free(Shader* shader);

/**
 * \brief Compile le Shader en paramêtre
 * \note Après la compilaton, son status peut être consulter via son attribut \c status
 * \param shader Shader à compiler
 */
void shader_compile(Shader* shader);

/* move to private */
GLenum shader_type_to_gl_enum(ShaderType type);

/**
 * \brief Permet de récupérer le chaine de caractère du type de Shader en paramêtre
 * \param type le type de Shader dont on veut récupérer le nom
 * \return chaine de caractère immutable du nom du type
 */
const char* shader_type_get_name(ShaderType type);

#endif // SHADER_H

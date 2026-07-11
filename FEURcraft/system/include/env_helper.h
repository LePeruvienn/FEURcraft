#ifndef ENV_HELPER_H
#define ENV_HELPER_H

#include <stdbool.h>

/**
 * \brief Essaye de récupérer un entier dans la variable d'environnement donner en paramêtre.
 * 
 * \return 0 si la valeur est valide, autre sinon
 */
int env_get_int(char* name, int* out);

/**
 * \brief Essaye de récupérer un flottant dans la variable d'environnement donner en paramêtre.
 * 
 * \return 0 si la valeur est valide, autre sinon
 */
int env_get_float(char* name, float* out);

/**
 * \brief Permet d'interpréter la valeur d'une variable d'environnement comme un booléen
 * 
 * \return faux si la valeur n'est pas vide ou si elle vaut 0 ou 'false', vrai sinon 
 */
bool env_get_bool(char* name);


#endif // ENV_HELPER_H

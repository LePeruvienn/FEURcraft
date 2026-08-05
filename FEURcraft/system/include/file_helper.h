#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stddef.h>
#include <stdbool.h>

/**
 * \file file_helper.h
 * \brief Fichier implémentant des fonction permettant de manipuler des fichiers du système facilement.
 */

/**
 * \brief Lit le fichier binaire en paramêtre
 * \param path chemin vers le fichier à lire
 * \param out_size varaible de sortie pour la taille du fichier lu
 * \return le buffer d'octet du fichier
 */
void* file_read_bin(const char* path, size_t* out_size);

/**
 * \brief Lit le fichier textuelle en paramêtre
 * \param path chemin vers le fichier à lire
 * \return le buffer de char du fichier
 */
char* file_read_txt(const char* path);

/**
 * \brief écris dans le chemin du ficher le buffer donnée
 * \param path chemin vers le fichier à écrie
 * \param buffer buffer de données à écrire
 * \param size taille du buffere en octet
 */
void file_write_data(const char* path, void* buffer, size_t size);

/**
 * \brief Vérifie si le fichier existe
 * \param path chemin vers le fichier à vérifier
 * \return \c true si je fichier existe \c false sinon
 */
bool file_exists(const char* path);

/**
 * \brief récupère la taille du ficher en paramêtre
 * \param path chemin vers le fichier à avoir la taille
 * \return retourne la taille en octet du fichier
 */
size_t file_get_size(const char* path);


#endif // FILE_HELPER_H

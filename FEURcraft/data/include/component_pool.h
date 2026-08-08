#ifndef COMPONENT_POOL_H
#define COMPONENT_POOL_H

#include "component_handle.h"

#include "array_list.h"

#include <stddef.h>

/**
 * \brief Représente une pool de composant (ECS)
 */
typedef struct ComponentPool ComponentPool;

/**
 * \brief Représente une pool de composant (ECS)
 */
struct ComponentPool
{
	size_t component_size;

	ArrayList* components; ///< Contient les données de tout les composants
	ArrayList* free_indices; ///< Contient la liste des indices libre dans \a components
	ArrayList* states; ///< Contient à l'indice \c i le status du composant \c i
};

/**
 * \brief Permet de créer un nouvelle pool d'un structure représentant un composant
 * \param taille d'un composant/élément de la pool
 * \return pointeur vers un \ref \ComponentPool dont la méméoire à été alloué
 */
ComponentPool* component_pool_create(size_t component_size);

/**
 * \brief libére la mémoire alloué par par la pool
 * \param pool \ref ComponentPool à libérer
 */
void component_pool_free(ComponentPool* pool);

/**
 * \brief retourn la taille de la pool paramêtre
 * \param le nombre de composant dans la pool
 */
size_t component_pool_get_length(ComponentPool* pool);

/**
 * \brief Permet de récupérer le pointeur du composant ciblé par le handle
 *
 * \warning Après le réallocation (à l'ajout d'un élément par exemple)
 *          le pointeur peut ne peut pointé à une adrese valide
 *
 * \param pool pool de composants dont on veut récupérer l'élément
 * \param handle composant cible
 * \return pointeur vers le composant ciblé par le handle en paramêtre,
 *         retourn \c NULL si le composant par l'handle n'existe plus.
 */
void* component_pool_get(ComponentPool* pool, ComponentHandle handle);

/**
 * \brief retourn le composant à l'indice donné
 * \param pool \ref ComponentPool dont on veut récupérer la donnée
 * \param index indice ou on veut récupérer la donnée
 * \return NULL si le composant à cette index est mort,
 *         ou un pointeur vers le composant trouver
 */
void* component_pool_get_at(ComponentPool* pool, size_t index);

/**
 * \brief permet d'ajouter un nouveau composant à la pool
 * \param pool ComponentPool auquel on veut ajouter un nouveau composant
 * \param owner_id id de l'entité qui possède ce composant
 * \return \ref ComponentHandle qui cible la nouveau place du composant
 */
ComponentHandle component_pool_new(ComponentPool* pool, uint owner_id);

/**
 * \brief Supprime le composant de la pool ciblé par l'handle
 * \param pool \ref ComponentPool auquel on veut supprimer le composant
 * \param handle \ref ComponentHandle qui cible le composant à supprimer
 */
void component_pool_delete(ComponentPool* pool, ComponentHandle handle);

#endif // COMPONENT_POOL_H

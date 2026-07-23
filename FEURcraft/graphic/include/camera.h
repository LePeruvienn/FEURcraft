#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "mat4.h"

/**
 * \file camera.h
 * \brief Structure et fonctions pour la caméra 3D.
 *
 * Ce fichier décrit le type camera et les fonctions permettant
 * de positionner et déplacer la caméra 3D.
 */

/**
 * \brief Type représentant une caméra 3D
 */
typedef struct Camera Camera;

struct Camera
{
	Vec3 pos;  // position de la caméra dans le monde
	Vec3 target;    // point visé par la caméra

	float yaw;      // rotation haut/bas
	float pitch;    // rotation gauche/droite

	float fov;      // champ de vision en degrés
	float near;     // distance de rendu de début de la caméra
	float far;      // distance de rendu de fin de la caméra
	float aspect;   // distance de rendu de fin de la caméra
};

/**
 * \brief Crée une caméra positionnée en (px,py,pz), visant (tx,ty,tz).
 *
 * \param pos vecteur position de la caméra
 * \param target vecteur target de la caméra
 * \param fov champ de vision en degrés
 * \param near distance de début du rendu de la caméra
 * \param far distance de fin du rendu de de la caméra
 * \param width largeur de la fenêtre de sortie
 * \param height hauteur de la fenêtre de sortie
 */
void camera_init(Camera* c, Vec3 pos, Vec3 target,
                 float fov, float near, float far,
                 unsigned int width, unsigned int height);

/**
 * \brief Translation de la caméra et de sa cible de (dx, dy, dz).
 */
void camera_translate(Camera* c, float dx, float dy, float dz);


/**
 * \brief Tourne la caméra par rapport à une vue première personne
 *
 * Tourne la camera à l'horizontal et à la vertical en fonction
 * de l'angle données en paramêtre.
 *
 * \param c caméra
 * \param dyaw angle horizontal à ajouter
 * \param dpitch angle vertical à ajouter
 */
void camera_rotate(Camera* c, float dyaw, float dpitch);

/**
 * \brief Met à jour le ratio hauteur longeur de la caméra
 *
 * Met à jour le variable \a aspect de la caméra
 * à l'aide des données de taille de la fenêtre
 *
 * \param c caméra
 * \param width largeur de la fenêtre
 * \param height hauteur de la fenêtre
 */
void camera_update_aspect(Camera* c, unsigned int width, unsigned int height);

/**
 * \brief Met à jour les angles yaw pitch,
 * par rapport au vecteur target
 *
 * \param c caméra
 */
void camera_update_yaw_pitch(Camera* c);


/**
 * \brief Retourne la matrice de vue de la caméra
 *
 * Calcul la matrice de vue actuelle à l'aide des données de la caméra.
 *
 * \param c caméra
 * \return matrice 4x4 vue
 */
Mat4 camera_compute_view(Camera* c);

/**
 * \brief Retourne la matrice de projection de la caméra
 *
 * Calcul la matrice de projection actuelle à l'aide des données de la caméra.
 *
 * \param c caméra
 * \return matrice 4x4 projection
 */
Mat4 camera_compute_project(Camera* c);

#endif // CAMERA_H


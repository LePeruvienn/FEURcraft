#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "matrix.h"

/**
 * \file camera.h
 * \brief Structure et fonctions pour la caméra 3D.
 *
 * Ce fichier décrit le type camera et les fonctions permettant
 * de positionner et déplacer la caméra dans l'environnement 3D.
 *
 * Mouvements prédéfinis :
 *  - CAMERA_STATIQUE    : caméra fixe
 *  - CAMERA_TRANSLATION : déplacement linéaire
 *  - CAMERA_CERCLE      : orbite autour du point visé
 */

// Constantes de mouvement
#define CAMERA_STATIQUE     0
#define CAMERA_TRANSLATION  1
#define CAMERA_CERCLE       2

/**
 * \brief Type représentant une caméra 3D
 */
typedef struct camera* camera;

/**
 * \brief Crée une caméra positionnée en (px,py,pz), visant (tx,ty,tz).
 *
 * \param px position x de la caméra
 * \param py position y de la caméra
 * \param pz position z de la caméra
 * \param tx coordonnée x du point visé
 * \param ty coordonnée y du point visé
 * \param tz coordonnée z du point visé
 * \param fov champ de vision en degrés
 * \param near distance de début du rendu de la caméra
 * \param far distance de fin du rendu de de la caméra
 * \param window_width largeur de la fenêtre de sortie
 * \param window_height hauteur de la fenêtre de sortie
 * \return caméra créée
 */
camera create_camera(float px, float py, float pz,
                     float tx, float ty, float tz,
                     float fov, float near, float far,
                     unsigned int window_width, unsigned int window_height);

/**
 * \brief Libère la mémoire de la caméra.
 * \param c caméra à libérer
 */
void free_camera(camera c);

/**
 * \brief Renvoie le vecteur position de la caméra.
 */
vec camera_get_position(camera c);

/**
 * \brief Renvoie le vecteur du point visé.
 */
vec camera_get_target(camera c);

/**
 * \brief Renvoie le champ de vision en degrés.
 */
float camera_get_fov(camera c);


/**
 * \brief Retourne de ration largeur/hauteur de l'écran de sortie
 */
float camera_get_aspect(camera c);

/**
 * \brief Retourne la distance de début de rendu
 */
float camera_get_near(camera c);

/**
 * \brief Retourne la distance de fin de rendu
 */
float camera_get_far(camera c);


/**
 * \brief Change la position de la caméra.
 */
void camera_set_position(camera c, float x, float y, float z);

/**
 * \brief Change le point visé par la caméra.
 */
void camera_set_target(camera c, float x, float y, float z);

/**
 * \brief Projette un point 3D sur l'image 2D via la caméra.
 *
 * \param c caméra
 * \param wx coordonnée x du point monde
 * \param wy coordonnée y du point monde
 * \param wz coordonnée z du point monde
 * \param img_w largeur image en pixels
 * \param img_h hauteur image en pixels
 * \param px sortie : colonne dans l'image
 * \param py sortie : ligne dans l'image
 * \return 1 si le point est visible, 0 sinon
 */
int camera_project(camera c, float wx, float wy, float wz,
                   int img_w, int img_h, int *px, int *py);

/**
 * \brief Translation de la caméra et de sa cible de (dx, dy, dz).
 */
void camera_translate(camera c, float dx, float dy, float dz);

/**
 * \brief Fait orbiter la caméra autour de son point visé.
 *
 * Rotation dans le plan horizontal (autour de l'axe Z).
 *
 * \param c caméra
 * \param angle angle de rotation en radians
 */
void camera_orbiter(camera c, float angle);


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
void camera_rotate(camera c, float dyaw, float dpitch);

/**
 * \brief Met à jour le ratio hauteur longeur de la caméra
 *
 * Met à jour le variable \a aspect de la caméra
 * à l'aide des données de taille de la fenêtre
 *
 * \param c caméra
 * \param window_width largeur de la fenêtre
 * \param window_height hauteur de la fenêtre
 */
void set_camera_aspect(camera c, unsigned int window_width, unsigned int window_height);

/**
 * \brief Retourne la matrice de vue de la caméra
 *
 * Calcul la matrice de vue actuelle à l'aide des données de la caméra.
 *
 * \param c caméra
 * \return matrice 4x4 alloué
 */
mat4 get_camera_view(camera c);

/**
 * \brief Retourne la matrice de projection de la caméra
 *
 * Calcul la matrice de projection de la caméra.
 *
 * Définit le volume de vision (Frustum) pour le rendu et le culling,
 * à l'aide du plan \a near et le plan \a far de la caméra, ainsi que sont \a aspect.
 *
 *  - Les élément se trouvant devant le plan \a near ne seront pas afficher
 *  - Les élément se trouvant après le plan \a far ne seront pas afficher
 *
 * Technique utilisé : Frustum Culling
 *
 * \param c caméra
 * \return matrice 4x4 alloué
 */
mat4 get_camera_projection(camera c);

#endif // CAMERA_H

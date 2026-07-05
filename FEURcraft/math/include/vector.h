#ifndef VECTOR_H
#define VECTOR_H

#include "stdbool.h"

/**
* \file vector.h
* 
* \brief Ce fichier décrit le type \a vec ainsi que toutes les fonctions qui lui sont propres
*
* Le type \a vec représente un vecteur et toutes les opération mathématique qui lui sont associé.
*/

/**
* \brief Type représentant un vecteur.
*/
typedef struct vec* vec;

/** 
* \brief Créer un vecteur de taille définit et l'intialise à zéro
* \param size taille du vecteur
* \return nouveau vecteur 
*/
vec create_vec(unsigned int size);

/** 
* \brief Créer un vecteur de taille 2
* \param x valeur à l'index 0 du vecteur
* \param y valeur à l'index 1 du vecteur
* \return nouveau vecteur de taille 2
*/
vec create_vec2(float x, float y);

/** 
* \brief Créer un vecteur de taille 3
* \param x valeur à l'index 0 du vecteur
* \param y valeur à l'index 1 du vecteur
* \param z valeur à l'index 2 du vecteur
* \return nouveau vecteur de taille 3
*/
vec create_vec3(float x, float y, float z);

/** 
* \brief Créer un vecteur de taille 4
* \param x valeur à l'index 0 du vecteur
* \param y valeur à l'index 1 du vecteur
* \param z valeur à l'index 2 du vecteur
* \param w valeur à l'index 4 du vecteur
* \return nouveau vecteur de taille 4
*/
vec create_vec4(float x, float y, float z, float w);

/** 
* \brief Créer une copie du vecteur en paramêtre
* \param v vecteur source à copier
* \return nouveau vecteur 
*/
vec vec_copy(vec v);

/** 
* \brief Copie les valeur du vecteur \a v vers le vecteur \a u
* \param u vecteur destination
* \param v vecteur source
*/
void vec_copy_inplace(vec u, vec v);

/** 
* \brief Libère la mémoire du vecteur \a v
* \param v vecteur à libérer
*/
void free_vec(vec v);

/** 
* \brief Compare la taille des deux vecteur \a u et \a v
* \param u vecteur \a u
* \param v vecteur \a v
* \return vrai si les vecteur sont de même taille, faux sinon
*/
bool vec_same_size(vec u, vec v);

/** 
* \brief Compare les valeurs des deux vecteurs \a u et \a v
* \param u vecteur \a u
* \param v vecteur \a v
* \return vrai si les vecteur sont identique, faux sinon
*/
bool vec_equal(vec u, vec v);

/** 
* \brief Récupère la taille du vecteur \a v
* \param v vecteur \a v
* \return taille du vecteur \a v
*/
unsigned int vec_get_size(vec v);

/** 
* \brief Récupère la valeur du vecteur \a v à l'index donnée
* \param v vecteur \a v
* \param index index de la valeur à récupérer
* \return valeur du vecteur \a v à l'index donnée
*/
float vec_get_value(vec v, unsigned int index);

/** 
* \brief Récupère la valeur du vecteur \a v à l'index 0
* \param v vecteur \a v
* \return valeur à l'index 0 du vecteur \a v
*/
float vec_get_x(vec v);

/** 
* \brief Récupère la valeur du vecteur \a v à l'index 1
* \param v vecteur \a v
* \return valeur à l'index 1 du vecteur \a v
*/
float vec_get_y(vec v);

/** 
* \brief Récupère la valeur du vecteur \a v à l'index 2
* \param v vecteur \a v
* \return valeur à l'index 2 du vecteur \a v
*/
float vec_get_z(vec v);

/** 
* \brief Récupère la valeur du vecteur \a v à l'index 3
* \param v vecteur \a v
* \return valeur à l'index 3 du vecteur \a v
*/
float vec_get_w(vec v);

/** 
* \brief Met la valeur à l'index donnée du vecteur \a v à la valeur en paramêtre
* \param v vecteur \a v
* \param index index ou mettre la valeur
* \param value valeur à mettre
*/
void vec_set_value(vec v, unsigned int index, float value);

/** 
* \brief Mets les valeurs du vecteur \a v aux valeurs du buffer
* \param v vecteur \a v
* \param buf buffer avec les valeurs à mettre
* \param size taille du buffer
*/
void vec_set_values(vec v, float* buf, unsigned int size);

/** 
* \brief Mets les valeurs en paramêtre l'index 0 et 1 du vecteur \a v
* \param v vecteur \a v
* \param x valeur à mettre à l'index \a 0
* \param y valeur à mettre à l'index \a 1
*/
void vec_set_xy(vec v, float x, float y);

/** 
* \brief Mets les valeurs en paramêtre l'index 0, 1 et 2 du vecteur \a v
* \param v vecteur \a v
* \param x valeur à mettre à l'index \a 0
* \param y valeur à mettre à l'index \a 1
* \param z valeur à mettre à l'index \a 2
*/
void vec_set_xyz(vec v, float x, float y, float z);

/** 
* \brief Mets les valeurs en paramêtre l'index 0, 1, 2 et 3 du vecteur \a v
* \param v vecteur \a v
* \param x valeur à mettre à l'index \a 0
* \param y valeur à mettre à l'index \a 1
* \param z valeur à mettre à l'index \a 2
* \param w valeur à mettre à l'index \a 3
*/
void vec_set_xyzw(vec v, float x, float y, float z, float w);

/** 
* \brief Mets la valeurs en paramêtre l'index 0 du vecteur \a v
* \param v vecteur \a v
* \param value valeur à mettre à l'index \a 0
*/
void vec_set_x(vec v, float value);

/** 
* \brief Mets la valeurs en paramêtre l'index 1 du vecteur \a v
* \param v vecteur \a v
* \param value valeur à mettre à l'index \a 1
*/
void vec_set_y(vec v, float value);

/** 
* \brief Mets la valeurs en paramêtre l'index 2 du vecteur \a v
* \param v vecteur \a v
* \param value valeur à mettre à l'index \a 2
*/
void vec_set_z(vec v, float value);

/** 
* \brief Mets la valeurs en paramêtre l'index 3 du vecteur \a v
* \param v vecteur \a v
* \param value valeur à mettre à l'index \a 3
*/
void vec_set_w(vec v, float value);

/** 
* \brief Calcul la norme du vecteur \a v
* \param v vecteur \a v
* \return la norme du vecteur \a v
*/
float vec_length(vec v);

/** 
* \brief Calcul la norme au carré du vecteur \a v
* \warning La norme renvoyer est à la puissance 2 !!! 
* \param v vecteur \a v
* \return la norme du vecteur \a v
*/
float vec_fast_length(vec v);

/** 
* \brief Calcul la distance entre les vecteurs \a u et \a v
* \param v vecteur \a v
* \param u vecteur \a u
* \return distance entre les vecteurs \a u et \a v
*/
float vec_dist(vec u, vec v);

/** 
* \brief Calcul la distance au carré entre les vecteurs \a u et \a v
* \warning La distance renvoyer est à la puissance 2 !!! 
* \param v vecteur \a v
* \param u vecteur \a u
* \return distance entre les vecteurs \a u et \a v
*/
float vec_fast_dist(vec u, vec v);

/** 
* \brief Calcul le produit scalaire entre les deux vecteurs \a u et \a v
* \param v vecteur \a v
* \param u vecteur \a u
* \return résultat du produit scalaire entre les vecteurs \a u et \a v
*/
float vec_dot(vec u, vec v);

/** 
* \brief Additione les deux vecteurs \a u et \a v et met le résultat dans un nouveau vecteur
* \param v vecteur \a v
* \param u vecteur \a u
* \return nouveau vecteur du résultat de l'addition entre les vecteurs \a u et \a v
*/
vec vec_add(vec u, vec v);

/** 
* \brief Soustrait les deux vecteurs \a u et \a v et met le résultat dans un nouveau vecteur
* \param v vecteur \a v
* \param u vecteur \a u
* \return nouveau vecteur du résultat de la soustraction entre les vecteurs \a u et \a v
*/
vec vec_substract(vec u, vec v);

/** 
* \brief Fait ma multiplication par le scalaire \a lambda du vecteur \a u et met le résultat dans un nouveau vecteur
* \param u vecteur \a u
* \return nouveau vecteur du résultat de la multiplication du sclaire \a lambda sur la vecteur \a u
*/
vec vec_scale(vec u, float lambda);

/** 
* \brief Créer un nouveau vecteur qui est le résultat de la normalisation du vecteur \a v
* \param v vecteur \a v
* \return nouveau vecteur du résultat de la normalisation du vecteur \a v
*/
vec vec_normalize(vec v);


/** 
* \brief Calcul l'addition des vecteurs \a u et \a v et met le résultat dans le vecteur \a u
* \param u vecteur \a u
* \param v vecteur \a v
*/
void vec_add_inplace(vec u, vec v);

/** 
* \brief Calcul la soustraction des vecteurs \a u et \a v et met le résultat dans le vecteur \a u
* \param u vecteur \a u
* \param v vecteur \a v
*/
void vec_substract_inplace(vec u, vec v);

/** 
* \brief Calcul la multiplication par un scalaire du vecteur \a u et met le résultat dans celui-ci
* \param u vecteur \a u
*/
void vec_scale_inplace(vec u, float lambda);

/** 
* \brief Normalise le vecteur \a v et met le résultat dans celui-ci
* \param u vecteur \a u
*/
void vec_normalize_inplace(vec v);

/** 
* \brief Fait un produit vectorielle entre deux vecteur de taille 3 et met le résultat dans un nouveau vecteur
* \param u vecteur \a u
* \param v vecteur \a v
* \return nouveau vecteur de taille 3
*/
vec vec3_cross(vec u, vec v);

/** 
* \brief Fait un produit vectorielle entre deux vecteur de taille 3 \a u et \a v, et met le résultat dans le vecteur \a u
* \param u vecteur \a u
* \param v vecteur \a v
*/
void vec3_cross_inplace(vec u, vec v);

/** 
* \brief Calcule l'angle (non-orienté) entre deux vecteurs en radians
* \param u vecteur \a u
* \param v vecteur \a v
* \return angle entre u et v en radians [0, PI]
*/
float vec_angle(vec u, vec v);

/** 
* \brief Calcule l'angle orienté entre deux vecteurs de taille 2
* \return angle en radians entre [-PI, PI]
*/
float vec2_angle_oriented(vec u, vec v);

/** 
* \brief Calcule l'angle orienté entre deux vecteurs de taille 3 par rapport à un axe de référence
* \param u vecteur u
* \param v vecteur v
* \param axis vecteur normal définissant le plan de rotation
* \return angle en radians entre [-PI, PI]
*/
float vec3_angle_oriented(vec u, vec v, vec axis);

/** 
* \brief Créer un nouveau vecteur qui est le résultat de la  rotation du vecteur \a v de taille 2 d'un angle \a alpha
* \param v vecteur \a v à tourner
* \param alpha angle de rotation en radians
* \return nouveau vecteur de taille 2 après rotation
*/
vec vec2_rotate(vec v, float alpha);

/** 
* \brief Effectue une rotation du vecteur \a v de taille 2 d'un angle \a alpha et modifie le vecteur \a v de taille 2
* \param v vecteur \a v à modifier
* \param alpha angle de rotation en radians
*/
void vec2_rotate_inplace(vec v, float alpha);

/** 
* \brief Créer un nouveau vecteur qui est le résultat 3D autour d'un axe du vecteur \a v de taille 3
* \param v vecteur \a v à tourner
* \param axis axe de rotation (doit être normalisé)
* \param alpha angle en radians
* \return nouveau vecteur de taille 3 après rotation
*/
vec vec3_rotate(vec v, vec axis, float alpha);

/** 
* \brief Effectue une rotation autour d'un axe du vecteur \a v de taille 3 d'un angle \a alpha et modifie le vecteur \a v
* \param v vecteur \a v à modifier
* \param alpha angle de rotation en radians
*/
void vec3_rotate_inplace(vec v, vec axis, float alpha);

/** 
* \brief Convertit un angle de degrés vers radians
* \param deg angle en degrés
* \return angle en radians
*/
float vec_deg_to_rad(float deg);

/** 
* \brief Convertit un angle de radians vers degrés
* \param rad angle en radians
* \return angle en degrés
*/
float vec_rad_to_deg(float rad);

#endif // VECTOR_H


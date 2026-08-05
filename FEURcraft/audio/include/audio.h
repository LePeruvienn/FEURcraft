#ifndef AUDIO_H
#define AUDIO_H

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include "vec3.h"


/**
 * \file audio.h
 * \brief Structure et fonctions permettant de gérer l'audio
 *
 * Ce fichier contient toute les fonction permettant de controller l'audio du jeu.
 */


// =========== Types definitions ===============


/**
 * \brief Type représentant les données de config d'OpenAL.
 */
typedef struct AudioConfigStruct* AudioConfig;


/**
 * \brief Type représentant les donnée d'un sons
 */
typedef ALuint AudioSource;


/**
 * \brief Type représentant l'audio listener, l'élément qui reçoit le sons.
 */
typedef struct AudioListenerStruct* AudioListener;



/**
 * \brief Type représentant un audio emitter, un élément qui émèts du sons
 */
typedef struct AudioEmitterStruct* AudioEmitter;


/**
 * \brief État de lecture d'un AudioEmitter.
 */
typedef enum AudioEmitterState
{
    PLAYING, /**< Audio is playing */
    STOPPED, /**< Audio is not playing */
    PAUSED /**< Audio is paused */
} AudioEmitterState;





// ============= Function Definitions ==============

/**
 * \brief Instantie OpenAL et renvoit les données associée.
 *
 * \return Une structure contenant les donnée de config d'OpenAL
 */
AudioConfig AUDIO_INSTANTIATE();

/**
 * \brief Libère toute les donnée liée à OpenAL.
 *
 * \param audioConf Les donnée de configuration d'OpenAL
 */
void AUDIO_FREE(AudioConfig audioConf);


/**
 * \brief Créer un audio source qui est en réalité un audio buffer pour OpenAL.
 *
 * \param filename Un fichier audio. (.wav, .mp3, ...)
 *
 * \return Une structure contenant le buffer possèdant les donnée d'un sons.
 */
AudioSource AUDIO_SOURCE_CREATE(const char *filename);

/**
 * \brief Détruit l'AudioSource.
 *
 * \param audioSource L'AudioSource.
 */
void AUDIO_SOURCE_FREE(AudioSource audioSource);











// AudioListener
// -------------------------

/**
 * \brief Créer une structure représentant l'AudioListener.
 *
 * \param pos La position initial de l'audio listener.
 * \param atVector Vecteur direction initial de l'audio listener.
 * \param upVector Vecteur initial indiquant le haut de l'audio listener.
 *
 * \return Une structure représentant l'audio listener.
 */
AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(Vec3 pos, Vec3 atVector, Vec3 upVector);

/**
 * \brief Créer une structure représentant l'audio listener.
 *
 * \param pos La position initial de l'audio listener.
 *
 * \return Une structure représentant l'audio listener.
 */
AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION(Vec3 pos);

/**
 * \brief Créer une structure représentant l'audio listener.
 *
 * \return Une structure représentant l'audio listener.
 */
AudioListener AUDIO_LISTENER_CREATE();



/**
 * \brief Détruit l'AudioListener
 *
 * \param audioLi L'AudioListener.
 */
void AUDIO_LISTENER_FREE(AudioListener audioLi);


/**
 * \brief Mets à jours le gain de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 * \param gain Le nouveau gain de l'AudioListener.
 */
void AUDIO_LISTENER_SET_GAIN(AudioListener audioLi, float gain);

/**
 * \brief Mets à jours la position de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 * \param pos La nouvelle position de l'AudioListener.
 */
void AUDIO_LISTENER_SET_POSITION(AudioListener audioLi, Vec3 pos);

/**
 * \brief Mets à jours la rotation de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 * \param at Le nouveau vecteur direction de l'AudioListener
 * \param up Le nouveau vecteur indiquant le haut de l'AudioListener.
 */
void AUDIO_LISTENER_SET_ROTATION(AudioListener audioLi, Vec3 at, Vec3 up);


/**
 * \brief Renvoit le gain de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 *
 * \return Le gain de l'AudioListener.
 */
float AUDIO_LISTENER_GET_GAIN(AudioListener audioLi);

/**
 * \brief Renvoit la position de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 *
 * \return La position de l'AudioListener.
 */
Vec3 AUDIO_LISTENER_GET_POSITION(AudioListener audioLi);

/**
 * \brief Renvoit le vecteur direction de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 *
 * \return Le vecteur direction de l'AudioListener.
 */
Vec3 AUDIO_LISTENER_GET_AT_VECTOR(AudioListener audioLi);

/**
 * \brief Renvoit le vecteur indiquant le haut de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 *
 * \return Le vecteur indiquant le haut de l'AudioListener.
 */
Vec3 AUDIO_LISTENER_GET_UP_VECTOR(AudioListener audioLi);

/**
 * \brief Mets à jours l'état de l'AudioListener.
 *
 * \param audioLi L'AudioListener.
 */
//void AUDIO_LISTENER_UPDATE(AudioListener);







// AudioEmitter
// -------------------------

/**
 * \brief Créer un AudioEmitter.
 *
 * \param audioSource L'AudioSource.
 * \param pos La position initial de l'AudioEmitter.
 *
 * \return L'AudioEmitter.
 */
AudioEmitter AUDIO_EMITTER_CREATE_WITH_POSITION(AudioSource audioSource, Vec3 pos);



/**
 * \brief Créer un AudioEmitter attaché à une transform.
 *
 * \return L'AudioEmitter.
 */
AudioEmitter AUDIO_EMITTER_CREATE(AudioSource audioSource);

/**
 * \brief Détruit un AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 */
void AUDIO_EMITTER_FREE(AudioEmitter audioEm);




/**
 * \brief Mets à jours le gain de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 * \param gain Le nouveau gain de l'AudioEmitter.
 */
void AUDIO_EMITTER_SET_GAIN(AudioEmitter audioEm, float gain);

/**
 * \brief Configure si l'AudioEmitter doit boucler ou non.
 *
 * \param audioEm L'AudioEmitter.
 * \param is_looping 1 AudioEmitter vas boucler, 0 AudioEmitter ne vas pas boucler
 */
void AUDIO_EMITTER_SET_IS_LOOPING(AudioEmitter audioEm, int is_looping);

/**
 * \brief Mets à jours la position de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 * \param pos La nouvelle position de l'AudioEmitter.
 */
void AUDIO_EMITTER_SET_POSITION(AudioEmitter audioEm, Vec3 pos);

/**
 * \brief Mets à jours la direction de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 * \param direction La nouvelle direction de l'AudioEmitter.
 */
void AUDIO_EMITTER_SET_DIRECTION(AudioEmitter audioEm, Vec3 direction);


/**
 * \brief Renvoit le gain de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 *
 * \return Le gain de l'AudioEmitter.
 */
float AUDIO_EMITTER_GET_GAIN(AudioEmitter audioEm);

/**
 * \brief Renvoit si l'AudioEmitter boucle ou non.
 *
 * \param audioEm L'AudioEmitter.
 *
 * \return 1 Si l'AudioEmitter boucle, 0 sinon.
 */
int AUDIO_EMITTER_GET_IS_LOOPING(AudioEmitter audioEm);

/**
 * \brief Renvoit la position de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 *
 * \return La position de l'AudioEmitter.
 */
Vec3 AUDIO_EMITTER_GET_POSITION(AudioEmitter audioEm);

/**
 * \brief Renvoit la direction de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 *
 * \return La direction de l'AudioEmitter.
 */
Vec3 AUDIO_EMITTER_GET_DIRECTION(AudioEmitter audioEm);

/**
 * \brief Renvoit l'état de lecture de l'AudioEmitter.
 *
 * \param audioEm L'AudioEmitter.
 *
 * \return L'état de lecture de l'AudioEmitter.
 */
AudioEmitterState AUDIO_EMITTER_GET_STATE(AudioEmitter audioEm);

/**
 * \brief Mets à jours l'état de l'AudioEmitter
 *
 * \param audioEm L'AudioEmitter.
 */
//void AUDIO_EMITTER_UPDATE(AudioEmitter);

/**
 * \brief Joue le sons ou reprends la lecture du sons de l'AudioEmitter
 *
 * \param audioEm L'AudioEmitter.
 */
void AUDIO_EMITTER_PLAY(AudioEmitter audioEm);

/**
 * \brief Stop le sons de l'AudioEmitter
 *
 * \param audioEm L'AudioEmitter.
 */
void AUDIO_EMITTER_STOP(AudioEmitter audioEm);

/**
 * \brief Mets en pause le sons de l'AudioEmitter
 *
 * \param audioEm L'AudioEmitter.
 */
void AUDIO_EMITTER_PAUSE(AudioEmitter audioEm);




#endif

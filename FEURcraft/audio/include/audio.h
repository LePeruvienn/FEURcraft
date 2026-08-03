# ifndef AUDIO

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

# endif

#include "vec3.h"

// =========== Types definitions ===============

typedef struct
{
    int error;

    ALCdevice *device;
    ALCcontext *context;
} AudioConfigStruct;

typedef AudioConfigStruct* AudioConfig;

typedef ALuint AudioSource;


typedef struct
{
    float gain;
    Vec3 pos;
    Vec3 atVector;
    Vec3 upVector;
} AudioListenerStruct;

typedef AudioListenerStruct* AudioListener;


typedef struct
{
    AudioSource audioSource;
    float gain;
    Vec3 pos;
    Vec3 direction;
} AudioEmitterStruct;

typedef AudioEmitterStruct* AudioEmitter;

// ============= Function Definitions ==============

AudioConfig AUDIO_INSTANTIATE();

AudioSource AUDIO_SOURCE_CREATE(const char *filename);



// AudioListener
// -------------------------
AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(Vec3 pos, Vec3 atVector, Vec3 upVector);
AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION(Vec3 pos){return AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(pos, VEC3(0.f, 0.f, -1.f), VEC3(0.f, 1.f, 0.f));};
AudioListener AUDIO_LISTENER_CREATE(){return AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(VEC3(0.f, 0.f, 0.f), VEC3(0.f, 0.f, -1.f), VEC3(0.f, 1.f, 0.f));};

void AUDIO_LISTENER_SET_GAIN(AudioListener, float);
void AUDIO_LISTENER_SET_POSITION(AudioListener, Vec3);
void AUDIO_LISTENER_SET_ROTATION(AudioListener audioLi, Vec3 at, Vec3 up);

float AUDIO_LISTENER_GET_GAIN(AudioListener audioLi){return audioLi->gain;};
Vec3 AUDIO_LISTENER_GET_POSITION(AudioListener audioLi){return audioLi->pos;};
Vec3 AUDIO_LISTENER_GET_AT_VECTOR(AudioListener audioLi){return audioLi->atVector;};
Vec3 AUDIO_LISTENER_GET_UP_VECTOR(AudioListener audioLi){return audioLi->upVector;};

void AUDIO_LISTENER_UPDATE(AudioListener);



// AudioEmitter
// -------------------------

AudioEmitter AUDIO_EMITTER_CREATE_WITH_POSITION(AudioSource, Vec3);
AudioEmitter AUDIO_EMITTER_CREATE(AudioSource audioSource){return AUDIO_EMITTER_CREATE_WITH_POSITION(audioSource, VEC3(0.f, 0.f, 0.f));};

void AUDIO_EMITTER_SET_GAIN(AudioEmitter, float);
void AUDIO_EMITTER_SET_POSITION(AudioEmitter, Vec3);
void AUDIO_EMITTER_SET_DIRECTION(AudioEmitter, Vec3);

float AUDIO_EMITTER_GET_GAIN(AudioEmitter audioEm){return audioEm->gain;};
Vec3 AUDIO_EMITTER_GET_POSITION(AudioEmitter audioEm){return audioEm->pos;};
Vec3 AUDIO_EMITTER_GET_DIRECTION(AudioEmitter audioEm){return audioEm->direction;};


void AUDIO_EMITTER_UPDATE(AudioEmitter);

void AUDIO_EMITTER_PLAY(AudioEmitter audioEm) {alSourcePlay(audioEm->audioSource);}
void AUDIO_EMITTER_STOP(AudioEmitter audioEm) {alSourceStop(audioEm->audioSource);};
void AUDIO_EMITTER_PAUSE(AudioEmitter audioEm) {alSourcePause(audioEm->audioSource);};






#include "audio.h"

#include <AL/al.h>
#include <stddef.h>
#include <stdlib.h>

// ================= Structures =================

struct AudioConfigStruct
{
    int error; // Vaut 1 en cas d'érreur, 0 sinon

    ALCdevice *device;  // Le pointeur vers le l'appareille utilisé.
    ALCcontext *context; // Le context d'OpenAL.
};


struct AudioListenerStruct
{
    float gain;
    Vec3 pos;
    Vec3 atVector;
    Vec3 upVector;
};



struct AudioEmitterStruct
{
    AudioSource audioSource;
    float gain;
    Vec3 pos;
    Vec3 direction;
};


// ================= Functions ==================

AudioConfig AUDIO_INSTANTIATE()
{
    AudioConfig audioConf = malloc(sizeof(struct AudioConfigStruct));

    /* Open the default playback device */
    audioConf->device = alcOpenDevice(NULL);
    if (!audioConf->device) {
        fprintf(stderr, "Failed to open audio device.\n");
        audioConf->error = 1;
    }



    /* Create and set the audio context */
    audioConf->context = alcCreateContext(audioConf->device, NULL);
    if (!audioConf->context || !alcMakeContextCurrent(audioConf->context)) {
        fprintf(stderr, "Failed to set audio context.\n");
        if (audioConf->context) alcDestroyContext(audioConf->context);
        alcCloseDevice(audioConf->device);
        audioConf->error = 1;
    }

    return audioConf;
}


void AUDIO_FREE(AudioConfig audioConf)
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(audioConf->context);
    alcCloseDevice(audioConf->device);

    free(audioConf);
}



AudioSource AUDIO_SOURCE_CREATE(const char *filename)
{
    SF_INFO sfinfo = {0};
    SNDFILE *sndfile = sf_open(filename, SFM_READ, &sfinfo);

    if (!sndfile) {
        fprintf(stderr, "Failed to open sound file '%s': %s\n", filename, sf_strerror(NULL));
        return 0;
    }

    /* Total raw frames in the file */
    sf_count_t num_frames = sfinfo.frames;
    sf_count_t total_samples = num_frames * sfinfo.channels;

    short *pcm_data = (short *)malloc(total_samples * sizeof(short));
    if (!pcm_data) {
        fprintf(stderr, "Memory allocation error\n");
        sf_close(sndfile);
        return 0;
    }

    /* Read all audio data as 16-bit PCM */
    sf_count_t read_count = sf_read_short(sndfile, pcm_data, total_samples);
    sf_close(sndfile);

    short *mono_data = NULL;
    sf_count_t mono_samples = 0;

    if (sfinfo.channels == 1) {
        /* Already mono: use data directly */
        mono_data = pcm_data;
        mono_samples = read_count;
    }
    else if (sfinfo.channels == 2) {
        /* Downmix stereo to mono in-memory */
        mono_samples = num_frames;
        mono_data = (short *)malloc(mono_samples * sizeof(short));

        for (sf_count_t i = 0; i < mono_samples; i++) {
            int left  = pcm_data[i * 2];
            int right = pcm_data[i * 2 + 1];

            /* Average L & R channels (divide first or sum as int to avoid 16-bit overflow) */
            mono_data[i] = (short)((left + right) / 2);
        }

        /* Free original stereo raw buffer */
        free(pcm_data);
    }
    else {
        fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
        free(pcm_data);
        return 0;
    }

    /* Upload the buffer as AL_FORMAT_MONO16 */
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO16, mono_data,
                 (ALsizei)(mono_samples * sizeof(short)),
                 sfinfo.samplerate);

    free(mono_data);

    return buffer;
}

void AUDIO_SOURCE_FREE(AudioSource audioSource)
{
    alDeleteBuffers(1, &audioSource);
}







// AudioListener
// ----------------



AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(Vec3 pos, Vec3 atVector, Vec3 upVector)
{
    AudioListener audioList = malloc(sizeof(struct AudioListenerStruct));

    audioList->gain = 1;
    audioList->pos = pos;
    audioList->atVector = atVector;
    audioList->upVector = upVector;

    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
    ALfloat listenerOri[] = {atVector.x, atVector.y, atVector.z, upVector.x, upVector.y, upVector.z};
    alListenerfv(AL_ORIENTATION, listenerOri);

    return audioList;
}

AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION(Vec3 pos){return AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(pos, VEC3(0.f, 0.f, -1.f), VEC3(0.f, 1.f, 0.f));};
AudioListener AUDIO_LISTENER_CREATE(){return AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(VEC3(0.f, 0.f, 0.f), VEC3(0.f, 0.f, -1.f), VEC3(0.f, 1.f, 0.f));};

void AUDIO_LISTENER_FREE(AudioListener audioLi)
{
    free(audioLi);
}


void AUDIO_LISTENER_SET_GAIN(AudioListener audioLi, float gain)
{
    audioLi->gain = gain;
    alListenerf(AL_GAIN, gain);
}

void AUDIO_LISTENER_SET_POSITION(AudioListener audioLi, Vec3 pos)
{
    audioLi->pos = pos;
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
}

void AUDIO_LISTENER_SET_ROTATION(AudioListener audioLi, Vec3 at, Vec3 up)
{
    audioLi->atVector = at;
    audioLi->upVector = up;

    ALfloat listenerOri[] = {at.x, at.y, at.z, up.x, up.y, up.z};
    alListenerfv(AL_ORIENTATION, listenerOri);
}


float AUDIO_LISTENER_GET_GAIN(AudioListener audioLi){return audioLi->gain;};


Vec3 AUDIO_LISTENER_GET_POSITION(AudioListener audioLi){return audioLi->pos;};


Vec3 AUDIO_LISTENER_GET_AT_VECTOR(AudioListener audioLi){return audioLi->atVector;};


Vec3 AUDIO_LISTENER_GET_UP_VECTOR(AudioListener audioLi){return audioLi->upVector;};




void AUDIO_LISTENER_UPDATE(AudioListener audioLi)
{
    // Update OpenAL data

    float* openALGain = 0;
    alGetListenerf(AL_GAIN, openALGain);
    if (audioLi->gain != *openALGain){alListenerf(AL_GAIN, audioLi->gain);}

    float* openALx=0; float* openALy=0; float* openALz=0;
    alGetListener3f(AL_POSITION, openALx, openALy, openALz);
    if (!(audioLi->pos.x == *openALx && audioLi->pos.y == *openALy && audioLi->pos.z == *openALz))
    {alListener3f(AL_POSITION, audioLi->pos.x, audioLi->pos.y, audioLi->pos.z);}


    ALfloat* openALvalues = malloc(6*sizeof(ALfloat));
    alGetListenerfv(AL_ORIENTATION, openALvalues);
    if (!(audioLi->atVector.x == openALvalues[0] && audioLi->atVector.y == openALvalues[1] && audioLi->atVector.z == openALvalues[2] &&
          audioLi->upVector.x == openALvalues[3] && audioLi->upVector.y == openALvalues[4] && audioLi->upVector.z == openALvalues[5]))
    {
        ALfloat listenerOri[] = {audioLi->atVector.x, audioLi->atVector.y, audioLi->atVector.z,
                                audioLi->upVector.x, audioLi->upVector.y, audioLi->upVector.z};
        alListenerfv(AL_ORIENTATION, listenerOri);
    }

}


// AudioEmitter
// ----------------
AudioEmitter AUDIO_EMITTER_CREATE_WITH_POSITION(AudioSource audioSource, Vec3 pos)
{
    AudioEmitter audioEm = malloc(sizeof(struct AudioEmitterStruct));
    audioEm->gain = 1;
    audioEm->pos = pos;
    audioEm->direction = VEC3(0.f, 0.f, 0.f);

    alGenSources(1, &audioEm->audioSource);
    alSourcei(audioEm->audioSource, AL_BUFFER, audioSource);
    alSource3f(audioEm->audioSource, AL_POSITION, pos.x, pos.y, pos.z);


    return audioEm;
}

AudioEmitter AUDIO_EMITTER_CREATE(AudioSource audioSource){return AUDIO_EMITTER_CREATE_WITH_POSITION(audioSource, VEC3(0.f, 0.f, 0.f));};

void AUDIO_EMITTER_FREE(AudioEmitter audioEm)
{
    alDeleteSources(1, &audioEm->audioSource);

    free(audioEm);
}


void AUDIO_EMITTER_SET_GAIN(AudioEmitter audioEm, float gain)
{
    audioEm->gain = gain;
    alSourcef(audioEm->audioSource, AL_GAIN, gain);
}

void AUDIO_EMITTER_SET_POSITION(AudioEmitter audioEm, Vec3 pos)
{
    audioEm->pos = pos;
    alSource3f(audioEm->audioSource, AL_POSITION, pos.x, pos.y, pos.z);
}

void AUDIO_EMITTER_SET_DIRECTION(AudioEmitter audioEm, Vec3 dir)
{
    audioEm->direction = dir;
    alSource3f(audioEm->audioSource, AL_DIRECTION, dir.x, dir.y, dir.z);
}


float AUDIO_EMITTER_GET_GAIN(AudioEmitter audioEm){return audioEm->gain;};

Vec3 AUDIO_EMITTER_GET_POSITION(AudioEmitter audioEm){return audioEm->pos;};

Vec3 AUDIO_EMITTER_GET_DIRECTION(AudioEmitter audioEm){return audioEm->direction;};





void AUDIO_EMITTER_UPDATE(AudioEmitter audioEm)
{
    // Update OpenAL data

    float* openALGain = 0;
    alGetSourcef(audioEm->audioSource, AL_GAIN, openALGain);
    if (audioEm->gain != *openALGain){alListenerf(AL_GAIN, audioEm->gain);}

    float* openALx=0; float* openALy=0; float* openALz=0;
    alGetSource3f(audioEm->audioSource, AL_POSITION, openALx, openALy, openALz);
    if (!(audioEm->pos.x == *openALx && audioEm->pos.y == *openALy && audioEm->pos.z == *openALz))
    {alSource3f(audioEm->audioSource, AL_POSITION, audioEm->pos.x, audioEm->pos.y, audioEm->pos.z);}


    alGetSource3f(audioEm->audioSource, AL_DIRECTION, openALx, openALy, openALz);
    if (!(audioEm->direction.x == *openALx && audioEm->direction.y == *openALy && audioEm->direction.z == *openALz))
    {alSource3f(audioEm->audioSource, AL_DIRECTION, audioEm->direction.x, audioEm->direction.y, audioEm->direction.z);}
}



void AUDIO_EMITTER_PLAY(AudioEmitter audioEm) {alSourcePlay(audioEm->audioSource);}

void AUDIO_EMITTER_STOP(AudioEmitter audioEm) {alSourceStop(audioEm->audioSource);};

void AUDIO_EMITTER_PAUSE(AudioEmitter audioEm) {alSourcePause(audioEm->audioSource);};


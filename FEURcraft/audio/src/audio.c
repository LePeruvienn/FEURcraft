#include "audio.h"

#include <AL/al.h>
#include <stddef.h>
#include <stdlib.h>


AudioConfig AUDIO_INSTANTIATE()
{
    AudioConfig audioConf = malloc(sizeof(AudioConfigStruct));

    /* 1. Open the default playback device */
    audioConf->device = alcOpenDevice(NULL);
    if (!audioConf->device) {
        fprintf(stderr, "Failed to open audio device.\n");
        audioConf->error = 1;
    }



    /* 2. Create and set the audio context */
    audioConf->context = alcCreateContext(audioConf->device, NULL);
    if (!audioConf->context || !alcMakeContextCurrent(audioConf->context)) {
        fprintf(stderr, "Failed to set audio context.\n");
        if (audioConf->context) alcDestroyContext(audioConf->context);
        alcCloseDevice(audioConf->device);
        audioConf->error = 1;
    }

    return audioConf;
}


AudioSource AUDIO_SOURCE_CREATE(const char *filename)
{
    /*  Open the sound file */
    SF_INFO sfinfo = {0};
    SNDFILE *sndfile = sf_open(filename, SFM_READ, &sfinfo);

    if (!sndfile) {
        fprintf(stderr, "Failed to open sound file '%s': %s\n", filename, sf_strerror(NULL));
        return 0;
    }

    /* Map libsndfile format to OpenAL format */
    ALenum format;
    if (sfinfo.channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if (sfinfo.channels == 2) {
        format = AL_FORMAT_STEREO16;
    } else {
        fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return 0;
    }

    /* Calculate total samples and allocate buffer space */
    sf_count_t num_samples = sfinfo.frames * sfinfo.channels;
    short *pcm_data = (short *)malloc(num_samples * sizeof(short));

    if (!pcm_data) {
        fprintf(stderr, "Memory allocation error\n");
        sf_close(sndfile);
        return 0;
    }

    /* Read PCM frames as 16-bit signed integers */
    sf_count_t read_count = sf_read_short(sndfile, pcm_data, num_samples);
    if (read_count != num_samples) {
        fprintf(stderr, "Warning: Expected %ld samples, read %ld\n", (long)num_samples, (long)read_count);
    }

    sf_close(sndfile);

    /* Generate OpenAL buffer and send PCM bytes */
    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, pcm_data, (ALsizei)(read_count * sizeof(short)), sfinfo.samplerate);

    free(pcm_data);

    return buffer;
}


// AudioListener
// ----------------



AudioListener AUDIO_LISTENER_CREATE_WITH_POSITION_AND_ROTATION(Vec3 pos, Vec3 atVector, Vec3 upVector)
{
    AudioListener audioList = malloc(sizeof(AudioListenerStruct));

    audioList->gain = 1;
    audioList->pos = pos;
    audioList->atVector = atVector;
    audioList->upVector = upVector;

    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
    ALfloat listenerOri[] = {atVector.x, atVector.y, atVector.z, upVector.x, upVector.y, upVector.z};
    alListenerfv(AL_ORIENTATION, listenerOri);

    return audioList;
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
    AudioEmitter audioEm = malloc(sizeof(AudioEmitterStruct));
    audioEm->gain = 1;
    audioEm->pos = pos;
    audioEm->direction = VEC3(0.f, 0.f, 0.f);

    alGenSources(1, &audioEm->audioSource);
    alSourcei(audioEm->audioSource, AL_BUFFER, audioSource);
    alSource3f(audioEm->audioSource, AL_POSITION, pos.x, pos.y, pos.z);


    return audioEm;
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




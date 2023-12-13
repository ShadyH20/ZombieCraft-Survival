#include "Sound.h"

#include <iostream>
// sound lib
#include <bass.h>

bool Sound::audio_device = false;

Sound::Sound(const char * filename, bool loop)
{
	// init 
	if(!audio_device)
	{
		if(!BASS_Init(-1, 44100, 0, NULL,NULL))
		{
			printf("erorr loading sound file \n");
		}
		audio_device = true;
	}

	if (loop) {
		channel = BASS_StreamCreateFile(false,filename, 0,0, BASS_SAMPLE_LOOP);
	}
	else
	{
		channel = BASS_StreamCreateFile(false, filename, 0, 0, NULL);
	}

	if(!channel)
	{
		printf("can't play file \n");
	}
}

Sound::~Sound()
{
	BASS_Free();
}


void Sound::play()
{
	play(false);
}

void Sound::play(bool fromStart = false)
{
	BASS_ChannelPlay(channel, fromStart);
}

void Sound::pause()
{
	BASS_ChannelPause(channel);
}

void Sound::stop()
{
	BASS_ChannelStop(channel);
}

// set volume
void Sound::setVolume(float volume)
{
	BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, volume);
}

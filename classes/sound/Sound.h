#pragma once

class Sound
{
public:
	Sound(const char* filename, bool loop);

	~Sound();

	void play();
	void play(bool fromStart);
	void pause();
	void stop();
	void setVolume(float volume);

private:
	unsigned int channel;

	static bool audio_device;
};
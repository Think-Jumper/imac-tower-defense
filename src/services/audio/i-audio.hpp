#pragma once

enum AudioFiles {
	MUSIC_WAVE = 0
};

class IAudio {
public:
	virtual void playSound(int soundID) = 0;
	virtual void stopSound(int soundID) = 0;
	virtual void stopAllSounds() = 0;
};

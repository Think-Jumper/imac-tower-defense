#pragma once

#include <string>
#include "events/handlers/event-emitter.hpp"

class Progression {
public:
	Progression(EventEmitter& emitter);
	~Progression();

	void setIntroImgPath(std::string imgPath);
	std::string getIntoImgPath();

	void setIntroText(std::string text);
	std::string getIntoText();

	void setExitText(std::string text);
	std::string getExitText();

	void setMaxLife(int value);
	int getMaxLife();

	void setLife(int value);
	void reduceLifeBy(int value);
	int getLife();

	void setMaxMirrorNumber(int value);
	int getMaxMirrorNumber();

	void setMirrorNumber(int value);
	void reduceMirrorNumberBy1();
	void increaseMirrorNumberBy1();
	int getMirrorNumbers();

	void setMaxSlowNumber(int value);
	int getMaxSlowNumber();

	void setSlowNumber(int value);
	void reduceSlowNumberBy1();
	void increaseSlowNumberBy1();
	int getSlowNumbers();

	void setLevelNumber(int value);
	int getLevelNumber();

private:
	EventEmitter& m_emitter;

	std::string m_introImgPath;
	std::string m_introText;
	std::string m_exitText;
	int m_maxLife;
	int m_life;
	int m_maxSlowNumber;
	int m_slowNumber;
	int m_maxMirrorNumber;
	int m_mirrorNumber;
	int m_levelNumber;
};

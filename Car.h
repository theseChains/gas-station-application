#ifndef CAR_CLASS_H
#define CAR_CLASS_H

#include <SFML/Graphics.hpp>

#include "Config.h"

class Car
{
	// fix!!!
public:
	sf::Texture m_redCarTexture{};
	sf::Texture m_yellowCarTexture{};


public:
	Car();

	sf::Sprite m_carSprite{};

	void loadCars();
	bool isInFuelingPlace();
	void moveCarSprite();
	bool hasFinished();
	void switchCarColor();
};

#endif
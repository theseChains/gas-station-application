#ifndef CAR_CLASS_H
#define CAR_CLASS_H

#include <SFML/Graphics.hpp>

#include "Config.h"

class Car
{
private:
	sf::Texture m_redCarTexture{};
	sf::Texture m_yellowCarTexture{};
	sf::Sprite m_carSprite{};

public:
	Car();

	void loadCars();
	void moveCarSprite();
	void switchCarColor();
	void resetCarPosition();

	bool hasFinished();
	bool isInFuelingPlace();

	sf::Sprite getCarSprite() const;
};

#endif
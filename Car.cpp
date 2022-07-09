#include "Car.h"

Car::Car()
{}

void Car::loadCars()
{
	if (!m_redCarTexture.loadFromFile("media/carRed.png"))
	{
		std::cerr << "Couldn't load texture.\n";
	}

	if (!m_yellowCarTexture.loadFromFile("media/carYellow.png"))
	{
		std::cerr << "Couldn't load texture.\n";
	}
	// first car will be a red one
	m_carSprite.setTexture(m_redCarTexture);
	m_carSprite.setPosition(coords::carStartX, coords::carY);
	m_carSprite.setScale(1.7f, 1.7f);
}

void Car::moveCarSprite()
{
	m_carSprite.move(10.0f, 0.0f);
}

bool Car::isInFuelingPlace()
{
	return (m_carSprite.getPosition().x >= coords::carFuelingX);
}

bool Car::hasFinished()
{
	return (m_carSprite.getPosition().x >= coords::carFinishX);
}

void Car::switchCarColor(sf::Sprite& carSprite)
{
	if (carSprite.getTexture() == &m_yellowCarTexture)
	{
		carSprite.setTexture(m_redCarTexture);
	}
	else
	{
		carSprite.setTexture(m_yellowCarTexture);
	}
}
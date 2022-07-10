#ifndef STATE_CLASS_H
#define STATE_CLASS_H

#include <SFML/Graphics.hpp>

#include "ChangeButton.h"
#include "Car.h"
#include "GasButton.h"
#include "InsertButton.h"
#include "ReturnButton.h"
#include "Globals.h"

class State
{
private:
	InsertButton& m_insertButton;
	ChangeButton& m_changeButton;
	ReturnButton& m_returnButton;
	GasButton& m_petrol95Button;
	GasButton& m_petrol92Button;
	Car& m_car;
	sf::Sprite& m_gasStation;
	sf::Texture& m_gasStationTexture;
	sf::Texture& m_gasStationFuelingTexture;

public:
	State(InsertButton& insertButton, ChangeButton& changeButton, ReturnButton& returnButton,
		GasButton& petrol95Button, GasButton& petrol92Button, Car& car, sf::Sprite& gasStation,
		sf::Texture& gasStationTexture, sf::Texture& gasStationFuelingTexture);

	void registerStates();
	void processStates(sf::Event& event);
	void processNonEventState();
};

#endif
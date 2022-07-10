#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "GasButton.h"
#include "ChangeButton.h"
#include "ReturnButton.h"
#include "InsertButton.h"
#include "Globals.h"
#include "Config.h"
#include "Car.h"
#include "State.h"

class Application
{
private:
	sf::RenderWindow m_window{};

	InsertButton m_insertButton{};
	ReturnButton m_returnButton{};
	ChangeButton m_changeButton{};
	GasButton m_petrol95Button{};
	GasButton m_petrol92Button{};
	Car m_car{};

	// should be divided into buttons state, car state and gas station state but whatever
	State m_appState;

	sf::Texture m_gasStationTexture{};
	sf::Texture m_gasStationFuelingTexture{};
	sf::Sprite m_gasStation{};

	sf::Font m_font{};
	sf::Color m_backgroundColor{};

	void processEvents();
	void render();
	void loadGasStation();
	void loadMainScreenText();
	void createButtons();

public:
	Application();

	void run();
};

#endif
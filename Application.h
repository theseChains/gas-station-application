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

	State m_appState;

	sf::Font m_font{};
	sf::Texture m_texture{};
	sf::Texture m_gasStationFueling{};
	sf::Sprite m_gasStation{};
	sf::Color m_backgroundColor{};

	void processNonEventState();
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
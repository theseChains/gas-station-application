#include "Application.h"

#include <iostream>

Application::Application()
	: m_window{ sf::VideoMode(1300, 650), "Application" },
	m_gasStationTexture{},
	m_gasStationFuelingTexture{},
	m_gasStation{},
	m_font{},
	m_backgroundColor{ 255, 255, 204 },
	m_appState{ m_insertButton, m_changeButton, m_returnButton, m_petrol95Button, m_petrol92Button, m_car,
				m_gasStation, m_gasStationTexture, m_gasStationFuelingTexture }
{
	m_window.setFramerateLimit(60);
	Globals::gui.setTarget(m_window);

	loadGasStation();
	loadMainScreenText();
	createButtons();
	m_car.loadCars();
}

void Application::loadGasStation()
{
	if (!m_gasStationTexture.loadFromFile("media/gasStation.png"))
	{
		std::cerr << "Couldn't load texture.\n";
	}

	if (!m_gasStationFuelingTexture.loadFromFile("media/gasStationFueling.png"))
	{
		std::cerr << "Couldn't load texture.\n";
	}

	m_gasStation.setTexture(m_gasStationTexture);
	m_gasStation.setScale(sizes::gasStationScaleX, sizes::gasStationScaleY);
	m_gasStation.setPosition(coords::gasStationX, coords::gasStationY);
}

void Application::loadMainScreenText()
{
	if (!m_font.loadFromFile("media/font.ttf"))
	{
		std::cerr << "Couldn't load font.\n";
	}

	Globals::mainScreenText.setFont(m_font);
	Globals::mainScreenText.setPosition(coords::mainScreenTextX, coords::mainScreenTextY);
	Globals::mainScreenText.setCharacterSize(sizes::mainScreenTextSize);
	Globals::mainScreenText.setString(text::waitForPayment);
	Globals::mainScreenText.setFillColor(sf::Color::Black);
}

void Application::createButtons()
{
	m_insertButton.createButton();
	m_returnButton.createButton();
	m_changeButton.createButton();
	m_petrol95Button.createButton(GasType::ninetyFive);
	m_petrol92Button.createButton(GasType::ninetyTwo);
}

void Application::processEvents()
{
	sf::Event event{};
	// process user input once the car is in place
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		m_appState.registerStates();
		m_appState.processStates(event);

		Globals::gui.handleEvent(event);
	}

	m_appState.processNonEventState();
}

void Application::render()
{
	m_window.clear(m_backgroundColor);

	m_window.draw(m_car.m_carSprite);
	m_window.draw(m_gasStation);
	m_window.draw(Globals::mainScreenText);

	m_window.draw(m_petrol95Button.m_sliderValues);
	m_window.draw(m_petrol95Button.m_exchangeRate);
	m_window.draw(m_petrol92Button.m_sliderValues);
	m_window.draw(m_petrol92Button.m_exchangeRate);

	if (Globals::amountToReturn && !(m_petrol95Button.isFueling() || m_petrol92Button.isFueling()))
	{
		m_window.draw(m_returnButton.m_moneySprite);
	}

	Globals::gui.draw();
	m_window.display();
}

void Application::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		render();
	}
}
#include "Application.h"

#include <array>

// distribute window, gui and main screen text via Button class
Application::Application()
	: m_window{ sf::VideoMode(1300, 650), "Application" },
	m_texture{},
	m_gasStation{},
	m_font{},
	m_backgroundColor{ 255, 255, 204 }
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
	if (!m_texture.loadFromFile("media/gasStation.png"))
	{
		std::cerr << "Couldn't load texture.\n";
	}

	if (!m_gasStationFueling.loadFromFile("media/gasStationFueling.png"))
	{
		std::cerr << "Couldn't load texture.\n";
	}

	m_gasStation.setTexture(m_texture);
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

void Application::processNonEventState()
{
	// this should happen regardless if user has done something or not (regardless of events)
	if (m_petrol95Button.isFueling())
	{
		m_petrol95Button.showProgress();
	}
	if (m_petrol92Button.isFueling())
	{
		m_petrol92Button.showProgress();
	}

	// car logic
	if (m_car.isInFuelingPlace())
	{
		m_gasStation.setTexture(m_gasStationFueling);
	}

	if (m_petrol95Button.isFueled() || m_petrol92Button.isFueled())
	{
		m_gasStation.setTexture(m_texture);
	}

	// move the car if it hasn't reached its fueling place
	// move the car if it finished fueling and the user took the change
	if ((!m_car.isInFuelingPlace() || m_petrol95Button.isFueled() || m_petrol92Button.isFueled())
		&& !(Globals::amountToReturn))
	{
		m_car.moveCarSprite();
	}

	if (m_car.hasFinished())
	{
		m_car.switchCarColor(m_car.m_carSprite);
		m_car.m_carSprite.setPosition(coords::carStartX, coords::carY);

		m_petrol95Button.setIsFueled(false);
		m_petrol92Button.setIsFueled(false);
		m_petrol95Button.setNoChangeLeft(false);
		m_petrol92Button.setNoChangeLeft(false);

		Globals::mainScreenText.setString(text::waitForPayment);
	}
}

void Application::registerStates()
{
	if ((!Globals::amountToReturn) && (!Globals::gasSlider) && (!Globals::sum) && m_car.isInFuelingPlace()
		&& !(m_petrol95Button.isFueled() || m_petrol92Button.isFueled()))
	{
		m_insertButton.setActive(true);
	}
	else
	{
		m_insertButton.setActive(false);
	}
	// only do this when the sum is non-zero and there is no slider
	if (Globals::sum && (!Globals::gasSlider))
	{
		m_returnButton.setActive(true);
	}
	else
	{
		m_returnButton.setActive(false);
	}
	// only do this when the sum is non-zero
	if (Globals::sum)
	{
		m_petrol95Button.setActive(true);
		m_petrol92Button.setActive(true);
	}
	else
	{
		m_petrol95Button.setActive(false);
		m_petrol92Button.setActive(false);
	}
	// only do this when the change money is non-zero and the car isn't fueling
	if (Globals::amountToReturn && !(m_petrol95Button.isFueling() || m_petrol92Button.isFueling()))
	{
		// the change button is active here
		m_changeButton.setActive(true);
	}
	else
	{
		m_changeButton.setActive(false);
	}
	// where do i put this..
	if ((!Globals::amountToReturn) && (!Globals::sum) && (!InsertButton::m_tempSum)
		&& !(m_petrol95Button.noChangeLeft()) && !(m_petrol92Button.noChangeLeft()))
	{
		Globals::mainScreenText.setString(text::waitForPayment);
	}
}

void Application::processStates(sf::Event& event)
{
	if (m_insertButton.isActive())
	{
		m_insertButton.processInput(event);
	}
	if (m_returnButton.isActive())
	{
		m_returnButton.processInput(event);
	}
	if (m_petrol95Button.isActive())
	{
		m_petrol95Button.processInput(event, GasType::ninetyFive);
	}
	if (m_petrol92Button.isActive())
	{
		m_petrol92Button.processInput(event, GasType::ninetyTwo);
	}
	if (m_changeButton.isActive())
	{
		m_changeButton.processInput(event);
	}
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

		registerStates();
		processStates(event);

		Globals::gui.handleEvent(event);
	}

	processNonEventState();
}

void Application::render()
{
	m_window.clear(m_backgroundColor);

	m_window.draw(m_car.m_carSprite);
	m_window.draw(m_gasStation);
	m_window.draw(Globals::mainScreenText);

	if (Globals::gasSlider)
	{
		m_window.draw(m_petrol95Button.m_sliderValues);
		m_window.draw(m_petrol95Button.m_exchangeRate);
		m_window.draw(m_petrol92Button.m_sliderValues);
		m_window.draw(m_petrol92Button.m_exchangeRate);
	}

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
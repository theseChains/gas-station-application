#include "State.h"

State::State(InsertButton& insertButton, ChangeButton& changeButton, ReturnButton& returnButton,
	GasButton& petrol95Button, GasButton& petrol92Button, Car& car, sf::Sprite& gasStation,
	sf::Texture& gasStationTexture, sf::Texture& gasStationFuelingTexture)
	: m_insertButton{ insertButton },
	m_changeButton{ changeButton },
	m_returnButton{ returnButton },
	m_petrol95Button{ petrol95Button },
	m_petrol92Button{ petrol92Button },
	m_car{ car },
	m_gasStation{ gasStation },
	m_gasStationTexture{ gasStationTexture },
	m_gasStationFuelingTexture{ gasStationFuelingTexture }
{
}

void State::registerStates()
{
	if ((!Globals::amountToReturn) && (!Globals::gasSlider) && (!Globals::sum) && m_car.isInFuelingPlace()
		&& !(m_petrol95Button.isFueling() || m_petrol92Button.isFueling()))
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
	
	if ((!Globals::amountToReturn) && (!Globals::sum) && (!m_insertButton.getTempSum())
		&& !(m_petrol95Button.noChangeLeft()) && !(m_petrol92Button.noChangeLeft()))
	{
		Globals::mainScreenText.setString(text::waitForPayment);
	}
}

void State::processStates(sf::Event& event)
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

void State::processNonEventState()
{
	if (m_petrol95Button.isFueling())
	{
		m_petrol95Button.showProgress();
	}
	if (m_petrol92Button.isFueling())
	{
		m_petrol92Button.showProgress();
	}

	// car logic
	// move the car if it hasn't reached its fueling place
	// move the car if it finished fueling and the user took the change
	if ((!m_car.isInFuelingPlace() || m_petrol95Button.isFueled() || m_petrol92Button.isFueled())
		&& !(Globals::amountToReturn))
	{
		m_car.moveCarSprite();
	}

	if (m_car.hasFinished())
	{
		m_car.switchCarColor();
		m_car.resetCarPosition();

		m_petrol95Button.setIsFueled(false);
		m_petrol92Button.setIsFueled(false);
		m_petrol95Button.setNoChangeLeft(false);
		m_petrol92Button.setNoChangeLeft(false);

		Globals::mainScreenText.setString(text::waitForPayment);
	}

	if (m_car.isInFuelingPlace())
	{
		m_gasStation.setTexture(m_gasStationFuelingTexture);
	}

	if (m_petrol95Button.isFueled() || m_petrol92Button.isFueled())
	{
		m_gasStation.setTexture(m_gasStationTexture);
	}
}
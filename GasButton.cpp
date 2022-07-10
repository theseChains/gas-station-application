#include "GasButton.h"

#include <iostream>

int GasButton::m_tempSliderValue{};

GasButton::GasButton()
{}

void GasButton::createButton(GasType gas)
{
	if (gas == GasType::ninetyFive)
	{
		m_button = tgui::Button::create();
		m_button->setPosition(coords::petrol95ButtonX, coords::petrol95ButtonY);
		m_button->setSize(sizes::petrolButtonW, sizes::petrolButtonH);
		tgui::Theme petrol95Theme{ "media/themes/95thGasTheme.txt" };
		m_button->setRenderer(petrol95Theme.getRenderer("Button"));
	}
	else if (gas == GasType::ninetyTwo)
	{
		m_button = tgui::Button::create();
		m_button->setPosition(coords::petrol92ButtonX, coords::petrol92ButtonY);
		m_button->setSize(sizes::petrolButtonW, sizes::petrolButtonH);
		tgui::Theme petrol92Theme{ "media/themes/92ndGasTheme.txt" };
		m_button->setRenderer(petrol92Theme.getRenderer("Button"));
	}
	setupText();
	setupMoney();
	Globals::gui.add(m_button);
}

void GasButton::setupText()
{
	if (!m_font.loadFromFile("media/gasFont.ttf"))
	{
		std::cerr << "Couldn't load font\n.";
	}

	m_exchangeRate.setFont(m_font);
	m_exchangeRate.setPosition(225, 295);
	m_exchangeRate.setCharacterSize(15);
	m_exchangeRate.setFillColor(sf::Color::Black);

	m_sliderValues.setFont(m_font);
	m_sliderValues.setPosition(195, 258);
	m_sliderValues.setCharacterSize(13);
	m_sliderValues.setFillColor(sf::Color::Black);
}

void GasButton::processInput(sf::Event& event, GasType gas)
{
	// create the slider if it isnt there
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_button->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))) && (!Globals::gasSlider))
	{
		createCheckMarkButton();
		createCrossButton();
		createSlider();
		m_sliderValues.setString(L"1 л                         50 л");
		if (gas == GasType::ninetyFive)
		{
			Globals::mainScreenText.setString(text::sum + std::to_wstring(Globals::sum) + text::toPay
				+ std::to_wstring(static_cast<int>(Globals::gasSlider->getValue()) * cfg::gas95Price));
			handle95SliderInput(); // signal which function to call when the slider is there
			m_exchangeRate.setString(L"Курс 100 р/л");
		}
		else
		{
			Globals::mainScreenText.setString(text::sum + std::to_wstring(Globals::sum) + text::toPay
				+ std::to_wstring(static_cast<int>(Globals::gasSlider->getValue()) * cfg::gas92Price));
			handle92SliderInput(); // signal which function to call when the slider is there
			m_exchangeRate.setString(L" Курс 50 р/л");
		}
	}
	else if (Globals::gasSlider && m_checkMarkButton && m_crossButton)
	{
		// the slider is also being handled here since we created it and binded respective callback functions
		// handle frames when user presses on checkmark or cross button
		handleCheckMarkInput(event, gas);
		if (m_crossButton) // if it hasn't been deleted by the check mark handler
			handleCrossInput(event);
	}
}

// do this after m_progress flag was set to true in checkmark input handler
void GasButton::showProgress()
{
	if (static_cast<int>(m_textToShow) < m_tempSliderValue)
	{
		m_textToShow += 0.16f; // adds 9.6 litres per second (per 60 frames)
		Globals::mainScreenText.setString(text::progress + std::to_wstring(static_cast<int>(m_textToShow)) + L" л");
	}
	else
	{
		if (Globals::amountToReturn)
		{
			Globals::mainScreenText.setString(text::takeChange + L"\n Заправлено:\n     "
				+ std::to_wstring(static_cast<int>(m_textToShow)) + L" л");
		}
		else
		{
			Globals::mainScreenText.setString(text::waitForPayment + L"\n Заправлено:\n     "
				+ std::to_wstring(static_cast<int>(m_textToShow)) + L" л");
			m_noChange = true;
		}
		// finished fueling
		m_fueled = true;
		// fueling progress done
		m_progress = false;
		m_textToShow = 0;
	}
}

void GasButton::checkSumSufficiency(GasType gas)
{
	if (Globals::sum < 0)
	{
		Globals::mainScreenText.setString(text::notEnoughMoney + text::takeChange);
		if (gas == GasType::ninetyFive)
			Globals::amountToReturn = Globals::sum + static_cast<int>(Globals::gasSlider->getValue() * cfg::gas95Price);
		else
			Globals::amountToReturn = Globals::sum + static_cast<int>(Globals::gasSlider->getValue() * cfg::gas92Price);
	}
	else if (Globals::sum >= 0)
	{
		Globals::amountToReturn = Globals::sum;
		// start fueling
		m_progress = true;
	}
}

void GasButton::handleCheckMarkInput(sf::Event& event, GasType gas)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_checkMarkButton->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))))
	{
		if (gas == GasType::ninetyFive)
		{
			Globals::sum -= static_cast<int>(Globals::gasSlider->getValue() * cfg::gas95Price);
			checkSumSufficiency(gas);
		}
		else
		{
			Globals::sum -= static_cast<int>(Globals::gasSlider->getValue() * cfg::gas92Price);
			checkSumSufficiency(gas);
		}

		Globals::sum = 0;
		removeSlider();
		removeUtilButtons();

		m_exchangeRate.setString("");
		m_sliderValues.setString("");
	}
}

void GasButton::handleCrossInput(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_crossButton->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))))
	{
		Globals::mainScreenText.setString(text::sum + std::to_wstring(Globals::sum) + text::chooseGas);
		removeSlider();
		removeUtilButtons();

		m_exchangeRate.setString("");
		m_sliderValues.setString("");
	}
}

void GasButton::removeUtilButtons()
{
	Globals::gui.remove(m_crossButton);
	m_crossButton = nullptr;
	Globals::gui.remove(m_checkMarkButton);
	m_checkMarkButton = nullptr;
}

void slider95Callback()
{
	Globals::mainScreenText.setString(text::sum + std::to_wstring(Globals::sum) + text::toPay
		+ std::to_wstring(static_cast<int>(Globals::gasSlider->getValue()) * cfg::gas95Price));
	GasButton::m_tempSliderValue = static_cast<int>(Globals::gasSlider->getValue());
}

void slider92Callback()
{
	Globals::mainScreenText.setString(text::sum + std::to_wstring(Globals::sum) + text::toPay
		+ std::to_wstring(static_cast<int>(Globals::gasSlider->getValue()) * cfg::gas92Price));
	GasButton::m_tempSliderValue = static_cast<int>(Globals::gasSlider->getValue());
}

void GasButton::handle95SliderInput()
{
	Globals::gasSlider->onValueChange(&slider95Callback);
	// if the user doesn't change the slider value, register the set value too!
	GasButton::m_tempSliderValue = static_cast<int>(Globals::gasSlider->getValue());
}

void GasButton::handle92SliderInput()
{
	Globals::gasSlider->onValueChange(&slider92Callback);
	// if the user doesn't change the slider value, register the set value too!
	GasButton::m_tempSliderValue = static_cast<int>(Globals::gasSlider->getValue());
}

void GasButton::createCheckMarkButton()
{
	m_checkMarkButton = tgui::Button::create();
	tgui::Theme checkBoxTheme{ "media/themes/checkBoxButtonTheme.txt" }; // checkmark, not checkbox...
	m_checkMarkButton->setRenderer(checkBoxTheme.getRenderer("Button"));
	m_checkMarkButton->setPosition(coords::checkMarkButtonX, coords::checkMarkButtonY);
	m_checkMarkButton->setSize(sizes::utilButtonW, sizes::utilButtonH);
	Globals::gui.add(m_checkMarkButton);
}

void GasButton::createCrossButton()
{
	m_crossButton = tgui::Button::create();
	tgui::Theme crossTheme{ "media/themes/crossButtonTheme.txt" };
	m_crossButton->setRenderer(crossTheme.getRenderer("Button"));
	m_crossButton->setPosition(coords::crossButtonX, coords::crossButtonY);
	m_crossButton->setSize(sizes::utilButtonW, sizes::utilButtonH);
	Globals::gui.add(m_crossButton);
}

void GasButton::createSlider()
{
	Globals::gasSlider = tgui::Slider::create();
	tgui::Theme sliderTheme{ "media/themes/sliderButtonTheme.txt" };
	Globals::gasSlider->setRenderer(sliderTheme.getRenderer("Slider"));
	Globals::gasSlider->setSize(sizes::petrolSliderW, sizes::petrolSliderH);
	Globals::gasSlider->setPosition(coords::petrolSliderX, coords::petrolSliderY);
	Globals::gasSlider->setMinimum(1);
	Globals::gasSlider->setMaximum(50);
	Globals::gasSlider->setValue(1);
	Globals::gui.add(Globals::gasSlider);
}

void GasButton::removeSlider()
{
	Globals::gui.remove(Globals::gasSlider);
	Globals::gasSlider = nullptr;
}

bool GasButton::isFueled() const
{
	return m_fueled;
}

bool GasButton::noChangeLeft() const
{
	return m_noChange;
}

bool GasButton::isFueling() const
{
	return m_progress;
}

void GasButton::setFueling(bool statement)
{
	m_progress = statement;
}

void GasButton::setNoChangeLeft(bool statement)
{
	m_noChange = statement;
}

void GasButton::setIsFueled(bool statement)
{
	m_fueled = statement;
}

int GasButton::getTempSliderValue() const
{
	return m_tempSliderValue;
}

sf::Text GasButton::getExchangeRate() const
{
	return m_exchangeRate;
}

sf::Text GasButton::getSliderValues() const
{
	return m_sliderValues;
}
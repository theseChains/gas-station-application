#ifndef GAS_BUTTON_H
#define GAS_BUTTON_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Button.h"
#include "Globals.h"
#include "Config.h"

class GasButton : public Button
{
private:
	tgui::Button::Ptr m_checkMarkButton{};
	tgui::Button::Ptr m_crossButton{};
	sf::Font m_font{};

public:
	GasButton();

	// make getters for these
	sf::Text m_exchangeRate{}; // make these render only if ...
	sf::Text m_sliderValues{};
	sf::Clock m_clock{};
	sf::Time m_elapsed{};
	bool m_progress{};
	static float m_sliderProgressValue;
	float m_textToShow{};
	static int m_tempSliderValue;
	bool m_fueled{};
	bool m_noChange{};

	void createButton(GasType gas);
	void processInput(sf::Event& event, GasType gas);

	void createSlider();
	void createCheckMarkButton();
	void createCrossButton();
	void setupText();

	void handle95SliderInput();
	void handle92SliderInput();
	void handleCheckMarkInput(sf::Event& event, GasType gas);
	void handleCrossInput(sf::Event& event);
	void removeSlider();
	void removeUtilButtons();
	void checkSumSufficiency(GasType gas);
	void showProgress();
};

#endif
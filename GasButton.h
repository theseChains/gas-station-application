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
	bool m_progress{};
	bool m_fueled{};
	bool m_noChange{};
	float m_textToShow{};

public:
	GasButton();

	sf::Text m_exchangeRate{};
	sf::Text m_sliderValues{};

	static int m_tempSliderValue;

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

	bool isFueled() const;
	bool noChangeLeft() const;
	bool isFueling() const;

	void setFueling(bool statement);
	void setNoChangeLeft(bool statement);
	void setIsFueled(bool statement);
};

#endif
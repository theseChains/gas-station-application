#ifndef BUTTON_H
#define BUTTON_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

class Button
{
protected:
	tgui::Button::Ptr m_button{};

	void setupMoney();

public:
	Button();

	// make getters for these
	sf::Texture m_moneyTexture{};
	sf::Sprite m_moneySprite{};
};

#endif
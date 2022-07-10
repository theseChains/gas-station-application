#ifndef BUTTON_H
#define BUTTON_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

class Button
{
protected:
	tgui::Button::Ptr m_button{};
	// true if active, false if inactive
	bool m_state{};

	sf::Texture m_moneyTexture{};
	sf::Sprite m_moneySprite{};

	void setupMoney();

public:
	Button();

	void setActive(bool statement);
	bool isActive() const;

	sf::Sprite getMoneySprite() const;
};

#endif
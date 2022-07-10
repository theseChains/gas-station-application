#include "Button.h"

Button::Button()
{}

void Button::setupMoney()
{
	m_moneyTexture.loadFromFile("media/money.png");
	m_moneySprite.setTexture(m_moneyTexture);
	m_moneySprite.setPosition(247, 500);
}

void Button::setActive(bool statement)
{
	m_state = statement;
}

bool Button::isActive() const
{
	return m_state;
}

sf::Sprite Button::getMoneySprite() const
{
	return m_moneySprite;
}
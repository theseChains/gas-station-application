#include "Button.h"

Button::Button()
	: m_button{}
{}

void Button::setupMoney()
{
	m_moneyTexture.loadFromFile("media/money.png");
	m_moneySprite.setTexture(m_moneyTexture);
	m_moneySprite.setPosition(247, 500);
}
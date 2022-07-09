#include "ReturnButton.h"

ReturnButton::ReturnButton()
{}

void ReturnButton::createButton()
{
	m_button = tgui::Button::create();
	m_button->setPosition(coords::returnButtonX, coords::returnButtonY);
	m_button->setSize(sizes::returnButtonW, sizes::returnButtonH);
	tgui::Theme returnTheme{ "media/themes/returnTheme.txt" };
	m_button->setRenderer(returnTheme.getRenderer("Button"));
	Globals::gui.add(m_button);

	setupMoney();
}

void ReturnButton::processInput(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_button->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))))
	{
		Globals::amountToReturn = Globals::sum;
		Globals::sum = 0;
		Globals::mainScreenText.setString(text::takeChange);
	}
}
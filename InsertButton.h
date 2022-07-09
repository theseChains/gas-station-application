#ifndef INSERT_BUTTON_H
#define INSERT_BUTTON_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Globals.h"
#include "Button.h"
#include "Config.h"

class InsertButton : public Button
{
private:
	static tgui::ListBox::Ptr m_listBox; // should be put in Globals but whatever
	tgui::Button::Ptr m_checkmark{};
	tgui::Theme m_checkmarkTheme{};
	tgui::Theme m_checkmarkLitTheme{};

public:
	InsertButton();

	void createButton();
	void processInput(sf::Event& event);

	void createCheckmarkButton();
	void createListBox();
	static void removeListBox();
	void handleInput();

	static int m_tempSum;
};

#endif
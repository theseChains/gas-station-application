#ifndef CHANGE_BUTTON_H
#define CHANGE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Button.h"
#include "Globals.h"
#include "Config.h"

class ChangeButton : public Button
{
public:
	ChangeButton();

	void createButton();
	void processInput(sf::Event& event);

	void createListBox();
	static void removeListBox();
	void handleInput();

	void calculateBills();
	static void nullifyBills();
};

#endif
#ifndef RETURN_BUTTON_H
#define RETURN_BUTTON_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Button.h"
#include "Globals.h"
#include "Config.h"

class ReturnButton : public Button
{
public:
	ReturnButton();

	void createButton();
	void processInput(sf::Event& event);
};

#endif
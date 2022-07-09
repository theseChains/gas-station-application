#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <array>

// a monostate class
// the sin of this project
class Globals
{
public:
	static int sum;
	static int amountToReturn;
	static sf::Text mainScreenText;
	static std::array<int, 5> bills;
	static tgui::GuiSFML gui;
	static tgui::ListBox::Ptr changeListBox;
	static tgui::Slider::Ptr gasSlider;
};

#endif
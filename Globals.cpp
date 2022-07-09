#include "Globals.h"

int Globals::sum{ 0 };
int Globals::amountToReturn{ 0 };
sf::Text Globals::mainScreenText{};
std::array<int, 5> Globals::bills{};
tgui::GuiSFML Globals::gui{};
tgui::ListBox::Ptr Globals::changeListBox{};
tgui::Slider::Ptr Globals::gasSlider{};
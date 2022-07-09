#include "ChangeButton.h"

ChangeButton::ChangeButton()
{}

void ChangeButton::createButton()
{
	m_button = tgui::Button::create();
	m_button->setPosition(coords::changeButtonX, coords::changeButtonY);
	m_button->setSize(sizes::changeButtonW, sizes::changeButtonH);
	m_button->setVisible(false);
	Globals::gui.add(m_button);
}

void ChangeButton::processInput(sf::Event& event)
{
	// if the window exists
	if (Globals::changeListBox)
	{
		// if a left click is outside of listBox remove it
		if (event.type == sf::Event::MouseButtonPressed
			&& !(Globals::changeListBox->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
				static_cast<float>(event.mouseButton.y)))))
		{
			ChangeButton::removeListBox();
		}

		// when a mouse is released, remove the listBox
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left
			&& Globals::changeListBox->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
				static_cast<float>(event.mouseButton.y))))
		{
			ChangeButton::removeListBox();
		}
	}
	// create window if it doesn't exist
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_button->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))))
	{
		calculateBills();
		createListBox();
		handleInput();
	}
}

void ChangeButton::calculateBills()
{
	// four types of bills: 5000, 1000, 500, 100 and 50
	int remainder{ 0 };
	Globals::bills[0] = Globals::amountToReturn / 5000;
	remainder = Globals::amountToReturn % 5000;
	Globals::bills[1] = remainder / 1000;
	remainder %= 1000;
	Globals::bills[2] = remainder / 500;
	remainder %= 500;
	Globals::bills[3] = remainder / 100;
	remainder %= 100;
	Globals::bills[4] = remainder / 50;
}

void ChangeButton::createListBox()
{
	Globals::changeListBox = tgui::ListBox::create();
	Globals::changeListBox->addItem(L"Забрать всё (" + std::to_wstring(Globals::amountToReturn) + L" p.)");

	// add those only if they exist
	if (Globals::bills[0] > 0)
		Globals::changeListBox->addItem(L"5000 р. x" + std::to_wstring(Globals::bills[0]));
	if (Globals::bills[1] > 0)
		Globals::changeListBox->addItem(L"1000 р. x" + std::to_wstring(Globals::bills[1]));
	if (Globals::bills[2] > 0)
		Globals::changeListBox->addItem(L"500 р. x" + std::to_wstring(Globals::bills[2]));
	if (Globals::bills[3] > 0)
		Globals::changeListBox->addItem(L"100 р. x" + std::to_wstring(Globals::bills[3]));
	if (Globals::bills[4] > 0)
		Globals::changeListBox->addItem(L"50 р. x" + std::to_wstring(Globals::bills[4]));

	tgui::Theme changeListBox{ "media/themes/listBoxTheme.txt" };
	Globals::changeListBox->setRenderer(changeListBox.getRenderer("ListBox"));
	Globals::changeListBox->setItemHeight(sizes::changeListBoxH);
	Globals::changeListBox->setPosition(coords::changeListBoxX, coords::changeListBoxY);
	Globals::changeListBox->setSize(sizes::changeListBoxW,
		Globals::changeListBox->getItemHeight() * Globals::changeListBox->getItemCount() + 5);
	Globals::gui.add(Globals::changeListBox);
}

void ChangeButton::nullifyBills()
{
	Globals::bills[0] = 0;
	Globals::bills[1] = 0;
	Globals::bills[2] = 0;
	Globals::bills[3] = 0;
	Globals::bills[4] = 0;
}

void changeListBoxCallback(tgui::String item)
{
	if (item == L"5000 р. x" + std::to_wstring(Globals::bills[0]))
	{
		Globals::amountToReturn -= 5000;
		--Globals::bills[0];
		ChangeButton::removeListBox();
	}
	else if (item == L"1000 р. x" + std::to_wstring(Globals::bills[1]))
	{
		Globals::amountToReturn -= 1000;
		--Globals::bills[1];
		ChangeButton::removeListBox();
	}
	else if (item == L"500 р. x" + std::to_wstring(Globals::bills[2]))
	{
		Globals::amountToReturn -= 500;
		--Globals::bills[2];
		ChangeButton::removeListBox();
	}
	else if (item == L"100 р. x" + std::to_wstring(Globals::bills[3]))
	{
		Globals::amountToReturn -= 100;
		--Globals::bills[3];
		ChangeButton::removeListBox();
	}
	else if (item == L"50 р. x" + std::to_wstring(Globals::bills[4]))
	{
		Globals::amountToReturn -= 50;
		--Globals::bills[4];
		ChangeButton::removeListBox();
	}
	else
	{
		Globals::amountToReturn = 0;
		ChangeButton::nullifyBills();
		ChangeButton::removeListBox();

	}
}

void ChangeButton::handleInput()
{
	Globals::changeListBox->onItemSelect(&changeListBoxCallback);
}

void ChangeButton::removeListBox()
{
	Globals::gui.remove(Globals::changeListBox);
	Globals::changeListBox = nullptr;
}
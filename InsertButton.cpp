#include "InsertButton.h"

tgui::ListBox::Ptr InsertButton::m_listBox{};
int InsertButton::m_tempSum{ 0 };

InsertButton::InsertButton()
{}

void InsertButton::createButton()
{
	m_button = tgui::Button::create();
	m_button->setPosition(coords::insertButtonX, coords::insertButtonY);
	m_button->setSize(sizes::insertButtonW, sizes::insertButtonH);
	m_button->setVisible(false);
	Globals::gui.add(m_button);
	createCheckmarkButton();
}

void InsertButton::createCheckmarkButton()
{
	m_checkmark = tgui::Button::create();
	m_checkmark->setPosition(coords::insertCheckmarkX, coords::insertCheckmarkY);
	m_checkmark->setSize(sizes::insertCheckmarkW, sizes::insertCheckmarkH);
	m_checkmarkTheme.load("media/themes/insertCheckmarkTheme.txt");
	m_checkmarkLitTheme.load("media/themes/insertCheckmarkLitTheme.txt");
	m_checkmark->setRenderer(m_checkmarkTheme.getRenderer("Button"));
	Globals::gui.add(m_checkmark);
}

void InsertButton::processInput(sf::Event& event)
{
	if (m_listBox)
	{
		// if a left click is outside of listBox remove it
		if (event.type == sf::Event::MouseButtonPressed
			&& !(m_listBox->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
				static_cast<float>(event.mouseButton.y)))))
		{
			removeListBox();
		}

		// when a mouse is released, remove the listBox
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left
			&& m_listBox->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
				static_cast<float>(event.mouseButton.y))))
		{
			removeListBox();
		}
	}
	// create window if it doesn't exist
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_button->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))))
	{
		createListBox();
		handleInput();
	}
	// process only if there is temp sum
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left
		&& m_checkmark->isMouseOnWidget(tgui::Vector2f(static_cast<float>(event.mouseButton.x),
			static_cast<float>(event.mouseButton.y))) && InsertButton::m_tempSum)
	{
		// this is to allow for other buttons to work only after the checkmark button was pressed
		Globals::sum += InsertButton::m_tempSum;
		InsertButton::m_tempSum = 0;
		Globals::mainScreenText.setString(text::sum + std::to_wstring(Globals::sum) + text::chooseGas);
		m_checkmark->setRenderer(m_checkmarkTheme.getRenderer("Button"));
	}
	if (InsertButton::m_tempSum)
	{
		m_checkmark->setRenderer(m_checkmarkLitTheme.getRenderer("Button"));
	}
	else
	{
		m_checkmark->setRenderer(m_checkmarkTheme.getRenderer("Button"));
	}
}

void InsertButton::createListBox()
{
	m_listBox = tgui::ListBox::create();

	m_listBox->addItem(L"5000 ð.");
	m_listBox->addItem(L"1000 ð.");
	m_listBox->addItem(L"500 ð.");
	m_listBox->addItem(L"100 ð.");
	m_listBox->addItem(L"50 ð.");

	tgui::Theme insertListBox{ "media/themes/listBoxTheme.txt" };
	m_listBox->setRenderer(insertListBox.getRenderer("ListBox"));

	m_listBox->setItemHeight(sizes::insertListBoxH);
	m_listBox->setPosition(coords::insertListBoxX, coords::insertListBoxY);
	m_listBox->setSize(sizes::insertListBoxW, m_listBox->getItemHeight() * m_listBox->getItemCount() + 5);

	Globals::gui.add(m_listBox);
}

void insertListBoxCallback(tgui::String item)
{
	if (item == L"5000 ð.")
	{
		InsertButton::m_tempSum += 5000;
		Globals::mainScreenText.setString(text::sum + std::to_wstring(InsertButton::m_tempSum));
		InsertButton::removeListBox();
	}
	else if (item == L"1000 ð.")
	{
		InsertButton::m_tempSum += 1000;
		Globals::mainScreenText.setString(text::sum + std::to_wstring(InsertButton::m_tempSum));
		InsertButton::removeListBox();
	}
	else if (item == L"500 ð.")
	{
		InsertButton::m_tempSum += 500;
		Globals::mainScreenText.setString(text::sum + std::to_wstring(InsertButton::m_tempSum));
		InsertButton::removeListBox();
	}
	else if (item == L"100 ð.")
	{
		InsertButton::m_tempSum += 100;
		Globals::mainScreenText.setString(text::sum + std::to_wstring(InsertButton::m_tempSum));
		InsertButton::removeListBox();
	}
	else if (item == L"50 ð.")
	{
		InsertButton::m_tempSum += 50;
		Globals::mainScreenText.setString(text::sum + std::to_wstring(InsertButton::m_tempSum));
		InsertButton::removeListBox();
	}
}

void InsertButton::handleInput()
{
	m_listBox->onItemSelect(&insertListBoxCallback);
}

void InsertButton::removeListBox()
{
	Globals::gui.remove(InsertButton::m_listBox);
	InsertButton::m_listBox = nullptr;
}

int InsertButton::getTempSum() const
{
	return m_tempSum;
}
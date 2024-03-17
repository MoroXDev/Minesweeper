#include "Menu.h"

void Menu::init()
{
	this->data.gameView.reset(sf::FloatRect(0, 0, this->data.fullhdWidth, this->data.fullhdHeight));
	this->initTextures();
	this->initSprites();
}

void Menu::initTextures()
{
	this->backgroundTexture->loadFromFile("Assets/Backgrounds/background.png");
	this->bombTexture->loadFromFile("Assets/Menu/Textures/bomb.png");
	this->pixelFont->loadFromFile("Assets/Menu/Fonts/pixelFont.ttf");
}

void Menu::initSprites()
{
	this->background->setTexture(*backgroundTexture);
	this->background->setOrigin(sf::Vector2f(this->background->getGlobalBounds().width / 2, this->background->getGlobalBounds().height / 2));
	this->background->setPosition(this->data.fullhdWidth / 2, this->data.fullhdHeight / 2);
	this->background->setScale(this->data.fullhdWidth / this->background->getGlobalBounds().width, this->data.fullhdHeight / this->background->getGlobalBounds().height);

	this->title->setFont(*this->pixelFont);
	this->title->setString("Minesweeper Game");
	this->title->setCharacterSize(60);
	this->title->setFillColor(sf::Color::White);
	this->title->setOutlineThickness(5); this->title->setOutlineColor(sf::Color::Black);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	this->title->setPosition(this->data.fullhdWidth / 2, this->data.fullhdHeight / 10);

	this->bomb->setTexture(*this->bombTexture);
	this->bomb->setOrigin(this->bomb->getGlobalBounds().width / 2, this->bomb->getGlobalBounds().height / 2);
	this->bomb->setPosition(this->title->getGlobalBounds().left + this->title->getGlobalBounds().width + this->bomb->getGlobalBounds().width / 2, this->title->getPosition().y);

	this->play->setText("PLAY", 35, *this->pixelFont, sf::Color::White, 3, sf::Color::Black);
}

void Menu::updateButtons()
{
	if (this->play->isPressed()) { this->states.push_back(std::make_unique<Gameplay>(this->data, this->states, 30, 10*10)); }
	else if (this->play->isActive()) { this->play->getShape().setFillColor(sf::Color(112, 255, 188)); }
	else if (this->play->isIdle()) { this->play->getShape().setFillColor(sf::Color::White); }
}

Menu::Menu(Data& data, std::vector<std::unique_ptr<State>>& states) : State(data, states)
{
	this->init();
}

Menu::~Menu()
{
	std::cout << "destruktor Menu\n";
	delete this->backgroundTexture;
	delete this->bombTexture;
	delete this->pixelFont;

	delete this->background;
	delete this->bomb;
	delete this->title;
	delete this->play;
}

void Menu::update()
{
	this->play->update(this->data.mousePosWindow, this->data.mouseButtonReleased);
	this->updateButtons();
	
}

void Menu::render()
{
	this->data.window->draw(*this->background);
	this->data.window->draw(*this->title);
	this->data.window->draw(*this->bomb);
	this->play->render(*this->data.window);
}

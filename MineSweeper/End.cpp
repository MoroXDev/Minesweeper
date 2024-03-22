#include "End.h"

void End::removeStates()
{
	if (this->states.size() != 1)
	{
		this->states.erase(this->states.begin());
	}
}

void End::init(bool win)
{
	this->data.gameView.reset(sf::FloatRect(0, 0, 1920, 1080));
	this->win = win;
	if (this->win == true)
	{
		this->backgroundTexture.loadFromFile("Assets/Backgrounds/winBackground.jpg");
	}
	else
	{
		this->backgroundTexture.loadFromFile("Assets/Backgrounds/gameoverBackground.jpg");
	}

	this->background.setTexture(this->backgroundTexture);
	this->background.setOrigin(this->background.getGlobalBounds().width / 2, this->background.getGlobalBounds().height / 2);
	this->background.scale(this->data.gameView.getSize().x / this->background.getGlobalBounds().width, this->data.gameView.getSize().y / this->background.getGlobalBounds().height);
	this->background.setPosition(this->data.fullhdWidth / 2, this->data.fullhdHeight / 2);
}

End::End(Data& data, std::vector<std::unique_ptr<State>>& states, bool win) : State(data, states)
{
	this->init(win);
}

End::~End()
{
}

void End::update()
{
	this->removeStates();
	std::cout << this->states.size() << "\n";
}

void End::render()
{
	this->data.window->draw(this->background);
}

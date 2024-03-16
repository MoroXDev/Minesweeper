#include "Game.h"

void Game::resetReleasedButtons()
{
	for (auto& it : this->data.mouseButtonReleased)
	{
		it.second = false;
	}
	for (auto& it : this->data.keyboardKeyReleased)
	{
		it.second = false;
	}
}

void Game::updateMouse()
{
	int MousePosX = sf::Mouse::getPosition(*this->data.window).x;
	int MousePosY = sf::Mouse::getPosition(*this->data.window).y;
	this->data.mousePosWindow = this->data.window->mapPixelToCoords(sf::Vector2i(MousePosX, MousePosY));
}

void Game::updateSFMLEvents()
{
	while (this->data.window->pollEvent(this->data.sfmlEvent))
	{
		switch (this->data.sfmlEvent.type)
		{
		case sf::Event::EventType::Closed: { this->data.window->close(); break; }
		case sf::Event::EventType::KeyPressed: 
		   {
			if (this->data.sfmlEvent.key.code == sf::Keyboard::Key::Escape) { this->data.window->close(); }
			break;
		   }
		   case sf::Event::EventType::MouseButtonReleased:
		   {
			   if (this->data.sfmlEvent.mouseButton.button == sf::Mouse::Left) { this->data.mouseButtonReleased.at("left") = true; }
			   if (this->data.sfmlEvent.mouseButton.button == sf::Mouse::Right) { this->data.mouseButtonReleased.at("right") = true; }
			   break;
		   }
		}
	}
}

void Game::update()
{
	this->data.window->setView(this->data.gameView);
	this->updateMouse();
	this->updateSFMLEvents();
	if (!this->states.empty())
	{
		this->states.back()->update();
	}
	this->resetReleasedButtons();
}

void Game::render()
{
	this->data.window->clear(sf::Color(67, 174, 232));
	if (!this->states.empty())
	{
		this->states.back()->render();
	}
	this->data.window->display();
}

void Game::initReleasedButtons()
{
	this->data.mouseButtonReleased.emplace("right", false);
	this->data.mouseButtonReleased.emplace("left", false);
}

void Game::initView()
{
	this->data.gameView.reset(sf::FloatRect(0, 0, this->data.fullhdWidth, this->data.fullhdWidth));
	this->data.gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void Game::initWindow()
{
	this->data.screenWidth = sf::VideoMode::getDesktopMode().width;
	this->data.screenHeight = sf::VideoMode::getDesktopMode().height;
	sf::ContextSettings context; context.antialiasingLevel = 8;
	this->data.window = std::make_unique<sf::RenderWindow>(sf::VideoMode(this->data.screenWidth * 0.75, this->data.screenHeight * 0.75), "Minesweeper", sf::Style::Default, context);
	this->data.window->setVerticalSyncEnabled(true);
}

void Game::initStates()
{
	this->states.push_back(std::make_unique<Menu>(this->data, this->states));
}

void Game::init()
{

	this->initWindow();
	this->initView();
	this->initReleasedButtons();
	this->initStates();
}

Game::Game()
{
	this->init();
}

Game::~Game()
{
	std::cout << "desturktor Game\n";
	if (!this->states.empty())
	{
		this->states.clear();
	}
}

void Game::run()
{
	while (this->data.window->isOpen())
	{
		this->update();
		this->render();
	}
}

#include "Gameplay.h"

void Gameplay::removeStates()
{
	while (this->states.size() != 1 && this->statesRemoved == false)
	{
		this->states.erase(this->states.begin());
	}
}

void Gameplay::setView()
{
	this->data.gameView.reset(sf::FloatRect(0, 0, this->data.fullhdWidth, this->data.fullhdHeight));
	this->data.gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void Gameplay::initSprites()
{
	this->background.setTexture(this->backgroundTexture);
	this->background.setOrigin(this->background.getGlobalBounds().width / 2, this->background.getGlobalBounds().height / 2);
	this->background.setPosition(this->data.fullhdWidth / 2, this->data.fullhdHeight / 2);
}

void Gameplay::initTextures()
{
	this->backgroundTexture.loadFromFile("Assets/Backgrounds/background.png");
}

void Gameplay::initGrid(unsigned int cellsMultiplier)
{
	float outlineThickness = 1080 * 100 / this->data.window->getSize().x / cellsMultiplier;
	if (outlineThickness < 1) { outlineThickness = 1; }

	sf::Vector2f firstCellPos; 
	firstCellPos.x = this->data.fullhdWidth / 4 + outlineThickness;
	firstCellPos.y = 0 + outlineThickness;
	sf::Vector2f cellPos = firstCellPos;

	for (int y = 0; y < cellsMultiplier; y++)
	{
		for (int x = 0; x < cellsMultiplier; x++)
		{
			//tutaj stworze shape'y
			sf::RectangleShape shape(sf::Vector2f(this->data.fullhdHeight / cellsMultiplier - outlineThickness * 2, this->data.fullhdHeight / cellsMultiplier - outlineThickness * 2));
			shape.setPosition(cellPos.x, cellPos.y);
			shape.setFillColor(sf::Color(150, 150, 150));
			shape.setOutlineThickness(outlineThickness);
			shape.setOutlineColor(sf::Color::Black);

			this->cells.push_back(Cell(shape, *this->data.window));

			if (cellPos.x < firstCellPos.x + shape.getGlobalBounds().width * (cellsMultiplier - 1))
			{
				cellPos.x += shape.getGlobalBounds().width;
			}
			else { cellPos.x = firstCellPos.x; cellPos.y += shape.getGlobalBounds().height; }
			
		}
	}
}

void Gameplay::initBombs(unsigned int bombsNumber)
{
	if (bombsNumber > this->cells.size())
	{
		bombsNumber = this->cells.size();
	}
	std::srand(std::time(NULL));

	unsigned int cellIndeks = 0;
	bool bombApplied = false;
    for (int i = 0; i < bombsNumber; i++)
	{	
		while (bombApplied == false)
		{
			cellIndeks = std::rand() % this->cells.size();
			if (this->cells.at(cellIndeks).getVariant() != 3)
			{
				cells.at(cellIndeks).setVariant(3);
				bombApplied = true;
			}
		}
		bombApplied = false;

	}
	for (int i = 0; i < cells.size(); i++)
	{
		std::cout << this->cells.at(i).getVariant();
	}

}

void Gameplay::initNumbers()
{
}

Gameplay::Gameplay(Data& data, std::vector<std::unique_ptr<State>>& states, unsigned int cellsMultiplier, unsigned int bombsNumber) : State(data, states)
{
	this->setView();
	this->initTextures();
	this->initSprites();
	this->initGrid(cellsMultiplier);
	this->initBombs(bombsNumber);
	this->initNumbers();
}

Gameplay::~Gameplay()
{
	std::cout << "desturktor Gameplay\n";
	this->cells.clear();
}

void Gameplay::update()
{
	this->removeStates();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { this->data.gameView.move(-3, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { this->data.gameView.move(3, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { this->data.gameView.move(0, -3); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { this->data.gameView.move(0, 3); }

	this->background.setPosition(this->data.gameView.getCenter());
}

void Gameplay::render()
{
	this->data.window->draw(this->background);
	if (!cells.empty())
	{
	  for (int i = 0; i < this->cells.size(); i++)
	  {
		  this->cells.at(i).render();
	  }
	}
}

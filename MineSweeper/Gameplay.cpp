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
	this->background.setPosition(this->data.gameView.getCenter());
}

void Gameplay::initTextures()
{
	this->backgroundTexture.loadFromFile("Assets/Backgrounds/background.png");
}

void Gameplay::initGrid()
{
	float outlineThickness = 1080 * 100 / this->data.window->getSize().x / cellsInRow;
	if (outlineThickness < 1) { outlineThickness = 1; }

	unsigned int indeks = 0;
	sf::Vector2u indeks2u = { 0, 0 };

	sf::Vector2f firstCellPos; 
	firstCellPos.x = this->data.fullhdWidth / 4 + outlineThickness;
	firstCellPos.y = 0 + outlineThickness;
	sf::Vector2f cellPos = firstCellPos;

	for (int y = 0; y < cellsInRow; y++)
	{
		for (int x = 0; x < cellsInRow; x++)
		{
			indeks = x + y * this->cellsInRow;
			//tutaj stworze shape'y
			sf::RectangleShape shape(sf::Vector2f(this->data.fullhdHeight / cellsInRow - outlineThickness * 2, this->data.fullhdHeight / cellsInRow - outlineThickness * 2));
			shape.setPosition(cellPos.x, cellPos.y);
			shape.setFillColor(sf::Color(120, 120, 120));
			shape.setOutlineThickness(outlineThickness);
			shape.setOutlineColor(sf::Color::Black);

			this->cells.push_back(Cell(shape, *this->data.window, cells, cellsInRow));
			this->cells.back().setIndeks(indeks, indeks2u);

			if (cellPos.x < firstCellPos.x + shape.getGlobalBounds().width * (cellsInRow - 1))
			{
				cellPos.x += shape.getGlobalBounds().width;
			}
			else { cellPos.x = firstCellPos.x; cellPos.y += shape.getGlobalBounds().height; }
			
		}
	}
}

void Gameplay::initBombs()
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

	for (auto& it : this->cells)
	{
		if (it.getVariant() == 3)
		{
			it.getShape().setFillColor(sf::Color::Red);
		}
	}
}

void Gameplay::initNumbers()
{
	int number = 0;
	for (int y = 0; y < this->cellsInRow; y++)
	{
		for (int x = 0; x < this->cellsInRow; x++)
		{
			if (this->cells.at(x + y * this->cellsInRow).getVariant() == 1)
			{
			    number = 0;
				if (x != 0) //jesli jest dostepna komorka na lewo
				{
					if (this->cells.at(x - 1 + y * this->cellsInRow).getVariant() == 3) //komorka na lewo
					{
						number++;
					}
				}
				if (x != this->cellsInRow - 1) //jesli jest dostepna komorka na prawo
				{
					if (this->cells.at(x + 1 + y * this->cellsInRow).getVariant() == 3) //komorka na prawo
					{
						number++;
					}
				}
				if (y != 0) //jesli jest dostepna komorka na gorze
				{
					if (this->cells.at(x + (y - 1) * this->cellsInRow).getVariant() == 3) //komorka na gorze
					{
						number++;
					}
					if (x != this->cellsInRow - 1) //jesli jest dostepna komorka na prawo po dostepie do komorki na gorze
					{
						if (this->cells.at(x + 1 + (y - 1) * this->cellsInRow).getVariant() == 3) //komorka na prawo
						{
							number++;
						}
					}
					if (x != 0) //jesli jest dostepna komorka na lewo po dostepie do komorki na gorze
					{
						if (this->cells.at(x - 1 + (y - 1) * this->cellsInRow).getVariant() == 3) //komorka na lewo
						{
							number++;
						}
					}
					
				}
				if (y < this->cellsInRow - 1) //jesli jest dostepna komorka na dole
				{
					if (this->cells.at(x + (y + 1) * this->cellsInRow).getVariant() == 3) //komorka na dole
					{
						number++;
					}
					if (x != this->cellsInRow - 1) //jesli jest dostepna komorka na prawo po dostepie do komorki na dole
					{
						if (this->cells.at(x + 1 + (y + 1) * this->cellsInRow).getVariant() == 3) //komorka na prawo
						{
							number++;
						}
					}
					if (x != 0) //jesli jest dostepna komorka na lewo po dostepie do komorki na dole
					{
						if (this->cells.at(x - 1 + (y + 1) * this->cellsInRow).getVariant() == 3) //komorka na lewo
						{
							number++;
						}
					}
						
				}
				
			this->cells.at(x + y * this->cellsInRow).setNumber(number);
			this->cells.at(x + y * this->cellsInRow).setVariant(2);
			}
		}
	}
}

Gameplay::Gameplay(Data& data, std::vector<std::unique_ptr<State>>& states, unsigned int cellsInRow, unsigned int bombsNumber) : State(data, states)
{
	this->cellsInRow = cellsInRow;
	this->bombsNumber = bombsNumber;
	this->setView();
	this->initTextures();
	this->initSprites();
	this->initGrid();
	this->initBombs();
	this->initNumbers();
	for (auto& it : cells)
	{
		it.show();
	}
}

Gameplay::~Gameplay()
{
	std::cout << "desturktor Gameplay\n";
	this->cells.clear();
}

void Gameplay::update()
{
	this->removeStates();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { for (auto& it : this->cells) { it.move(4, 0); } }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { for (auto& it : this->cells) { it.move(-4, 0); } }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { for (auto& it : this->cells) { it.move(0, 4); } }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { for (auto& it : this->cells) { it.move(0, -4); } }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { this->background.scale(1.01, 1.01); this->data.gameView.setSize(this->data.gameView.getSize().x * 1.01, this->data.gameView.getSize().y * 1.01); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { this->background.scale(0.99, 0.99); this->data.gameView.setSize(this->data.gameView.getSize().x * 0.99, this->data.gameView.getSize().y * 0.99); }

	for (int i = 0; i < this->cells.size(); i++)
	{
		this->cells.at(i).update(this->data.mousePosWindow, this->data.mouseButtonReleased);
		if (this->cells.at(i).checkExplosion() == true)
		{
			this->states.push_back(std::make_unique<End>(this->data, this->states, false));
		}
		if (this->cells.at(i).checkBlankCellClicked())
		{
			
		}
	}
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

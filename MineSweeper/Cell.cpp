#include "Cell.h"

Cell::Cell(sf::RectangleShape& shape, sf::RenderWindow& window , std::vector<Cell>& cells, unsigned int& cellsInRow) : window(window), cells(cells), cellsInRow(cellsInRow)
{
	this->shape.setSize(shape.getSize());
	this->shape.setOrigin(shape.getOrigin());
	this->shape.setPosition(shape.getPosition());
	this->shape.setFillColor(shape.getFillColor());
	this->shape.setOutlineColor(shape.getOutlineColor());
	this->shape.setOutlineThickness(shape.getOutlineThickness());
	this->shape.setScale(shape.getScale());
}

Cell::~Cell()
{
}

void Cell::setVariant(int variant)
{
	switch (variant)
	{
	case 1: { for (auto& it : this->variant) { it.second = false; } this->variant.at("isBlank") = true; break; }
	case 2: { for (auto& it : this->variant) { it.second = false; } this->variant.at("isNumber") = true; break; }
	case 3: { for (auto& it : this->variant) { it.second = false; } this->variant.at("isBomb") = true; break; }
	default:
		std::cout << "setVariant - variant poza zakresem"; throw;
		break;
	}
}

sf::RectangleShape& Cell::getShape()
{
	return this->shape;
}

void Cell::checkClick(sf::Vector2f& mousePosWindow, std::map<string, bool>& mouseButtonReleased)
{
	if (this->shape.getGlobalBounds().contains(mousePosWindow) && mouseButtonReleased.at("left") == true)
	{
		this->cellClicked = true;
		if (this->variant.at("isBomb") == true)
		{
			this->isBombExploded = true;
		}
		this->show();
	}
}

void Cell::update(sf::Vector2f& mousePosWindow, std::map<string, bool>& mouseButtonReleased)
{
	this->cellReset();
	this->checkClick(mousePosWindow, mouseButtonReleased);

}

void Cell::render()
{
	this->window.draw(this->shape);
	if (this->number != 0)
	{

	this->window.draw(this->text);
	}
}

void Cell::cellReset()
{
	this->cellClicked = false;
}

int Cell::getVariant()
{
	if (this->variant.at("isBlank") == true) { return 1; }
	else if (this->variant.at("isNumber") == true) { return 2; }
	else if (this->variant.at("isBomb") == true) { return 3; }
}

bool Cell::checkBlankCellClicked()
{
	if (this->wasBlankCellClicked == true)
	{
		return true;
	}
}

bool Cell::checkExplosion()
{
	if (this->isBombExploded == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cell::show()
{
	this->shape.setFillColor(sf::Color(200, 200, 200));
	if (this->number != 0)
	{
		this->font.loadFromFile("Assets/Fonts/pixelFont.ttf");
		this->text.setFont(this->font);
		this->text.setCharacterSize(this->shape.getGlobalBounds().height * 0.8);
		this->text.setString(std::to_string(this->number));
		this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
		sf::Color textColor = sf::Color::Magenta;

		switch (this->number)
		{
		   case 1: { textColor = sf::Color(255, 54, 54); break; } //red
		   case 2: { textColor = sf::Color(54, 165, 255); break; } //blue
		   case 3: { textColor = sf::Color(54, 255, 104); break; } //green
		   case 4: { textColor = sf::Color(118, 54, 255); break; } //purple
		   case 5: { textColor = sf::Color(255, 158, 54); break; } //orange
		   case 6: { textColor = sf::Color(255, 235, 54); break; } //yellow
		   case 7: { textColor = sf::Color(54, 255, 255); break; } //light blue
		   case 8: { textColor = sf::Color(252, 87, 255); break; } //pink
		   default: { std::cout << "Cell::show() - switch(number poza zakresem)\n"; break; }
		}

		this->text.setFillColor(textColor);
		sf::Vector2f shapePos;
		shapePos.x = this->shape.getPosition().x + this->shape.getGlobalBounds().width * 0.4;
		shapePos.y = this->shape.getPosition().y + this->shape.getGlobalBounds().height * 0.4;
		this->text.setPosition(shapePos);
	}
	else if (this->variant.at("isBomb") == true)
	{

		this->shape.setFillColor(sf::Color::Red);
	}
	else 
	{
		this->shape.setFillColor(sf::Color::White);
	}
	this->showOtherCells();
}
void Cell::move(float x, float y)
{
	if (this->number != 0)
	{
		this->text.move(x, y);
	}
	this->shape.move(x, y);
}
void Cell::setIndeks(unsigned int indeks, sf::Vector2u indeks2u)
{
	this->indeks = indeks;
	this->indeks2u = indeks2u;
}
void Cell::showOtherCells()
{
	std::cout << "showOtherCells\n";
	if (variant.at("isBlank") == true)
	{
			if (indeks2u.x != 0) //jesli jest dostepna komorka na lewo
			{

				if (cells.at(indeks2u.x - 1 + indeks2u.y * cellsInRow).getVariant() == 1) //komorka na lewo
				{
					cells.at(indeks2u.x - 1 + indeks2u.y * cellsInRow).showOtherCells();
					cells.at(indeks2u.x - 1 + indeks2u.y * cellsInRow).show();

				}
				else if (cells.at(indeks2u.x - 1 + indeks2u.y * cellsInRow).getVariant() == 2) //komorka na lewo
				{
					cells.at(indeks2u.x - 1 + indeks2u.y * cellsInRow).show();
				}

			}
			if (indeks2u.x != cellsInRow - 1) //jesli jest dostepna komorka na prawo
			{

				if (cells.at(indeks2u.x + 1 + indeks2u.y * cellsInRow).getVariant() == 1) //komorka na prawo
				{
					cells.at(indeks2u.x + 1 + indeks2u.y * cellsInRow).showOtherCells();
					cells.at(indeks2u.x + 1 + indeks2u.y * cellsInRow).show();
				}
				else if (cells.at(indeks2u.x + 1 + indeks2u.y * cellsInRow).getVariant() == 2) //komorka na prawo
				{
					cells.at(indeks2u.x + 1 + indeks2u.y * cellsInRow).show();
				}

			}
			if (indeks2u.y != 0) //jesli jest dostepna komorka na gorze
			{

				if (cells.at(indeks2u.x + (indeks2u.y - 1) * cellsInRow).getVariant() == 1) //komorka na gorze
				{
					cells.at(indeks2u.x + (indeks2u.y - 1) * cellsInRow).showOtherCells();
					cells.at(indeks2u.x + (indeks2u.y - 1) * cellsInRow).show();
				}
				else if (cells.at(indeks2u.x + (indeks2u.y - 1) * cellsInRow).getVariant() == 2) //komorka na gorze
				{
					cells.at(indeks2u.x + (indeks2u.y - 1) * cellsInRow).show();
				}

				if (indeks2u.x != cellsInRow - 1) //jesli jest dostepna komorka na prawo po dostepie do komorki na gorze
				{

					if (cells.at(indeks2u.x + 1 + (indeks2u.y - 1) * cellsInRow).getVariant() == 1) //komorka na prawo
					{
						cells.at(indeks2u.x + 1 + (indeks2u.y - 1) * cellsInRow).showOtherCells();
						cells.at(indeks2u.x + 1 + (indeks2u.y - 1) * cellsInRow).show();
					}
					else if (cells.at(indeks2u.x + 1 + (indeks2u.y - 1) * cellsInRow).getVariant() == 2) //komorka na prawo
					{
						cells.at(indeks2u.x + 1 + (indeks2u.y - 1) * cellsInRow).show();
					}

				}

				if (indeks2u.x != 0) //jesli jest dostepna komorka na lewo po dostepie do komorki na gorze
				{
					if (cells.at(indeks2u.x - 1 + (indeks2u.y - 1) * cellsInRow).getVariant() == 1) //komorka na lewo
					{
						cells.at(indeks2u.x - 1 + (indeks2u.y - 1) * cellsInRow).showOtherCells();
						cells.at(indeks2u.x - 1 + (indeks2u.y - 1) * cellsInRow).show();
					}
					else if (cells.at(indeks2u.x - 1 + (indeks2u.y - 1) * cellsInRow).getVariant() == 2) //komorka na lewo
					{
						cells.at(indeks2u.x - 1 + (indeks2u.y - 1) * cellsInRow).show();
					}
				}
			}
			if (indeks2u.y < cellsInRow - 1) //jesli jest dostepna komorka na dole
			{

				if (cells.at(indeks2u.x + (indeks2u.y + 1) * cellsInRow).getVariant() == 1) //komorka na dole
				{
					cells.at(indeks2u.x + (indeks2u.y + 1) * cellsInRow).showOtherCells();
					cells.at(indeks2u.x + (indeks2u.y + 1) * cellsInRow).show();
				}
				else if (cells.at(indeks2u.x + (indeks2u.y + 1) * cellsInRow).getVariant() == 2) //komorka na dole
				{
					cells.at(indeks2u.x + (indeks2u.y + 1) * cellsInRow).show();
				}

				if (indeks2u.x != cellsInRow - 1) //jesli jest dostepna komorka na prawo po dostepie do komorki na dole
				{

					if (cells.at(indeks2u.x + 1 + (indeks2u.y + 1) * cellsInRow).getVariant() == 1) //komorka na prawo
					{
						cells.at(indeks2u.x + 1 + (indeks2u.y + 1) * cellsInRow).showOtherCells();
						cells.at(indeks2u.x + 1 + (indeks2u.y + 1) * cellsInRow).show();
					}
					else if (cells.at(indeks2u.x + 1 + (indeks2u.y + 1) * cellsInRow).getVariant() == 2) //komorka na prawo
					{
						cells.at(indeks2u.x + 1 + (indeks2u.y + 1) * cellsInRow).show();
					}

				}
				if (indeks2u.x != 0) //jesli jest dostepna komorka na lewo po dostepie do komorki na dole
				{

					if (cells.at(indeks2u.x - 1 + (indeks2u.y + 1) * cellsInRow).getVariant() == 1) //komorka na lewo
					{
						cells.at(indeks2u.x - 1 + (indeks2u.y + 1) * cellsInRow).showOtherCells();
						cells.at(indeks2u.x - 1 + (indeks2u.y + 1) * cellsInRow).show();
					}
					else if (cells.at(indeks2u.x - 1 + (indeks2u.y + 1) * cellsInRow).getVariant() == 2) //komorka na lewo
					{
						cells.at(indeks2u.x - 1 + (indeks2u.y + 1) * cellsInRow).show();
					}

				}
			}
	}
}
void Cell::setNumber(int number)
{
	this->number = number;
}

/*sf::Text& Cell::getText()
{
	if (this->text != nullptr)
	{
	return *this->text;
	}
}*/
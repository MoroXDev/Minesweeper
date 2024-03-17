#include "Cell.h"

Cell::Cell(sf::RectangleShape& shape, sf::RenderWindow& window) : window(window)
{
	this->shape.setSize(shape.getSize());
	this->shape.setOrigin(shape.getOrigin());
	this->shape.setPosition(shape.getPosition());
	this->shape.setFillColor(shape.getFillColor());
	this->shape.setOutlineColor(shape.getOutlineColor());
	this->shape.setOutlineThickness(shape.getOutlineThickness());
	this->shape.setScale(shape.getScale());
	std::cout << "wieksze gowno\n";
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

void Cell::render()
{
	this->window.draw(this->shape);
}

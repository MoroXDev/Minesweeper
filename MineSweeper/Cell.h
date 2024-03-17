#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <iostream>
using std::string;
class Cell
{
private:
	std::map<string, bool> variant = { {"isBlank", false}, {"isNumber", false}, {"isBomb", false} };
	sf::RectangleShape shape;

	sf::RenderWindow& window;
public:
	Cell(sf::RectangleShape& shape, sf::RenderWindow& window );
	~Cell();
	void setVariant(int variant);
	void render();
	sf::RectangleShape& getShape();
};
#endif

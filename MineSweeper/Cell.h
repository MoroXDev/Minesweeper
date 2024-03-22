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
	bool cellClicked = false;
	bool isBombExploded = false;
	bool wasBlankCellClicked = false;
	int number = 0;
	unsigned int indeks = 0;
	sf::Vector2u indeks2u = { 0, 0 };
	std::map<string, bool> variant = { {"isBlank", true}, {"isNumber", false}, {"isBomb", false} };
	sf::RectangleShape shape;
    sf::RenderWindow& window;
	sf::Text text;
	sf::Font font;
	std::vector<Cell>& cells;
	unsigned int& cellsInRow;

	void cellReset();
public:
	Cell(sf::RectangleShape& shape, sf::RenderWindow& window, std::vector<Cell>& cells, unsigned int& cellsInRow);
	~Cell();
	void setVariant(int variant);
	void checkClick(sf::Vector2f& mousePosWindow, std::map<string, bool>& mouseButtonReleased);
	bool checkBlankCellClicked();
	int getVariant();
	void update(sf::Vector2f& mousePosWindow, std::map<string, bool>& mouseButtonReleased);
	void render();
	bool checkExplosion();
	void show();
	void showOtherCells();
	void setNumber(int number);
	void move(float x, float y);
	void setIndeks(unsigned int indeks, sf::Vector2u indeks2u);
	sf::RectangleShape& getShape();
	//sf::Text& getText;
};
#endif

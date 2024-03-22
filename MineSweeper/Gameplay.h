#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "End.h"
class Gameplay : public State
{
private:
	std::vector<Cell> cells;
	unsigned int cellsInRow;
	unsigned int bombsNumber;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	bool statesRemoved = false;

	void removeStates();
	void setView();

	void initSprites();
	void initTextures();
	void initGrid();
	void initBombs();
	void initNumbers();
public:
	Gameplay(Data& data, std::vector<std::unique_ptr<State>>& states, unsigned int cellsInRow, unsigned int bombsNumber);
	~Gameplay();
	void update();
	void render();
};
#endif

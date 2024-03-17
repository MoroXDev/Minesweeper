#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "State.h"
#include "Cell.h"

class Gameplay : public State
{
private:
	std::vector<Cell> cells;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	bool statesRemoved = false;

	void removeStates();
	void setView();

	void initSprites();
	void initTextures();
	void initGrid(unsigned int cellsMultiplier);
	void initBombs(unsigned int bombsNumber);
	void initNumbers();
public:
	Gameplay(Data& data, std::vector<std::unique_ptr<State>>& states, unsigned int cellsMultiplier, unsigned int bombsNumber);
	~Gameplay();
	void update();
	void render();
};
#endif

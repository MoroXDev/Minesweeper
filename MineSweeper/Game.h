#ifndef GAME_H
#define GAME_H
#include "Menu.h"
class Game
{
private:
	Data data;
	std::vector<std::unique_ptr<State>> states;

	void initReleasedButtons();
	void initView();
	void initWindow();
	void initStates();
	void init();

	void resetReleasedButtons();
	void updateMouse();
	void updateSFMLEvents();
	void update();
	void render();
public:
	Game();
	~Game();
	void run();

};
#endif

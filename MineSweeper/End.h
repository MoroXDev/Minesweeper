#ifndef END_H
#define END_H
#include "State.h"
#include "Cell.h"
class End : public State
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	bool win = false;

	void removeStates();
	void init(bool win);
public:
	End(Data& data, std::vector<std::unique_ptr<State>>& states, bool win);
	~End();
	void update();
	void render();



};
#endif END_H

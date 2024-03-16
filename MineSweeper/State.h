#ifndef STATE_H
#define STATE_H	
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
using std::string;

struct Data
{
unsigned int fullhdWidth = 1920;
unsigned int fullhdHeight = 1080;
unsigned int screenWidth = 960;
unsigned int screenHeight = 540;
std::unique_ptr<sf::RenderWindow> window;
sf::View gameView;
sf::Event sfmlEvent;
sf::Vector2f mousePosWindow = {0.f, 0.f};
std::map<string, bool> mouseButtonReleased;
std::map<string, bool> keyboardKeyReleased;
};

class State
{
private:
	
protected:
	Data& data;
	std::vector<std::unique_ptr<State>>& states;

public:
	State(Data& data, std::vector<std::unique_ptr<State>>& states);
	virtual ~State();
	virtual void update() = 0;
	virtual void render() = 0;
};
#endif

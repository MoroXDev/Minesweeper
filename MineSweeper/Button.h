#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using std::string;
class Button
{
	enum State
	{
		ACTIVE = 0,
		IDLE,
		PRESSED
	};
private:
	State buttonState = IDLE;
	sf::RectangleShape* shape = new sf::RectangleShape;
	sf::Text* text;
public:
	Button(sf::FloatRect floatrect, sf::Color color, float outlineThickness, sf::Color outlineColor);
	~Button();
	void setText(string string, unsigned int characterSize, sf::Font& font, sf::Color color, float outlineThickness, sf::Color outlineColor);
	void setShape(sf::FloatRect floatrect, sf::Color color, float outlineThickness, sf::Color outlineColor);
	bool isPressed();
	bool isActive();
	bool isIdle();
	sf::RectangleShape& getShape();
	sf::Text& getText();

	void update(sf::Vector2f& mousePosWindow, std::map<string, bool>& mouseButtonReleased);
	void render(sf::RenderWindow& window);
};
#endif

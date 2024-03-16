#include "Button.h"

void Button::setShape(sf::FloatRect floatrect, sf::Color color, float outlineThickness, sf::Color outlineColor)
{
	this->shape->setSize(sf::Vector2f(floatrect.width, floatrect.height));
	this->shape->setOrigin(this->shape->getGlobalBounds().width / 2, this->shape->getGlobalBounds().height / 2);
	this->shape->setFillColor(color);
	this->shape->setOutlineThickness(outlineThickness);
	this->shape->setOutlineColor(outlineColor);
	this->shape->setPosition(floatrect.left, floatrect.top);

}

Button::Button(sf::FloatRect floatrect, sf::Color color, float outlineThickness, sf::Color outlineColor)
{
	this->setShape(floatrect, color, outlineThickness, outlineColor);
}

Button::~Button()
{
	if (this->text != nullptr) { delete this->text; }
	delete this->shape;
}

void Button::setText(string string, unsigned int characterSize, sf::Font& font, sf::Color color, float outlineThickness, sf::Color outlineColor)
{
	if (this->text == nullptr) { this->text = new sf::Text; }
	this->text->setString(string);
	this->text->setCharacterSize(characterSize);
	this->text->setFont(font);
	this->text->setFillColor(color);
	this->text->setOutlineThickness(outlineThickness);
	this->text->setOutlineColor(outlineColor);
	this->text->setOrigin(this->text->getGlobalBounds().width / 2, this->text->getGlobalBounds().height / 2);
	this->text->setPosition(this->shape->getPosition().x, this->shape->getPosition().y);
}

bool Button::isPressed()
{
	if (buttonState == PRESSED)
	{
	return true;
	}
	else { return false; }
}

bool Button::isActive()
{
	if (buttonState == ACTIVE)
	{
		return true;
	}
	else { return false; }
}

bool Button::isIdle()
{
	if (buttonState == IDLE)
	{
		return true;
	}
	else { return false; }
}

sf::RectangleShape& Button::getShape()
{
	return *this->shape;
}

void Button::update(sf::Vector2f& mousePosWindow, std::map<string, bool>& mouseButtonReleased)
{
	if (shape->getGlobalBounds().contains(mousePosWindow) && mouseButtonReleased.at("left") == true) { this->buttonState = PRESSED; }
	else if (shape->getGlobalBounds().contains(mousePosWindow)) { this->buttonState = ACTIVE; }
	else { this->buttonState = IDLE; }

}

sf::Text& Button::getText()
{
	return *this->text;
}

void Button::render(sf::RenderWindow& window)
{
	window.draw(*this->shape);
	if (this->text != nullptr) { window.draw(*this->text); }
}

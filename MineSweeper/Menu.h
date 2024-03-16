#ifndef MENU_H
#define MENU_H
#include "Gameplay.h"
#include "Button.h"
class Menu : public State
{
private:
	sf::Texture* backgroundTexture = new sf::Texture;
	sf::Texture* bombTexture = new sf::Texture;
	sf::Font* pixelFont = new sf::Font;

	sf::Sprite* background = new sf::Sprite;
	sf::Sprite* bomb = new sf::Sprite;
	sf::Text* title = new sf::Text;

	Button* play = new Button(sf::FloatRect(this->data.fullhdWidth / 2, this->data.fullhdHeight / 3, 300, 100), sf::Color::White, 5, sf::Color::Black);

	void init();
	void initTextures();
	void initSprites();

	void updateButtons();
public:
	Menu(Data& data, std::vector<std::unique_ptr<State>>& states);
	~Menu();
	void update();
	void render();
};
#endif

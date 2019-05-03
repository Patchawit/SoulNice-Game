#include "Loading_screen.h"



Loading_screen::Loading_screen(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)
{

	this->speed = speed;
	faceRight = true;

	screen.setSize(sf::Vector2f(182.0f, 279.0f)); // กว้าง*ยาว
	screen.setOrigin(screen.getSize() / 2.0f);
	screen.setScale(1, 1);



	screen.setTexture(texture);
}


Loading_screen::~Loading_screen()
{
}

void Loading_screen::Update(float deltaTime,sf::Vector2f playerpos)
{
	screen.setPosition(playerpos);
	animation.Update(0, deltaTime, faceRight);
	screen.setTextureRect(animation.uvRect);
}

void Loading_screen::Draw(sf::RenderWindow& window)
{
	//window.draw(checkbox);
	window.draw(screen);
}
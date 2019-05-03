#include "Item.h"



Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime):
	animation(texture, imageCount, switchTime)
{
	body.setTexture(texture);
	body.setSize(sf::Vector2f(300.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setScale(0.7,0.7);
	body.setTextureRect(animation.uvRect);
}


Item::~Item()
{
}

void Item::Update(float deltaTime) {

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}
void Item::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Item::Set(sf::Vector2f playerpos) {
	body.setPosition(playerpos);
}
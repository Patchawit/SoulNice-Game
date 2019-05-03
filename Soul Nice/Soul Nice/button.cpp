#include "button.h"



button::button(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int num):
	animation(texture, imageCount, switchTime)
{

	body.setSize(sf::Vector2f(244.0f, 124.0f)); // กว้าง*ยาว
	body.setOrigin(body.getSize() / 2.0f);
	body.setScale(0.7, 0.7);
	body.setTexture(texture);
	if (num == 1) {
		body.setPosition(250.0f,570.0f);
	}
	if (num == 2) {
		body.setPosition(460.0f, 570.0f);
	}
	if (num == 3) {
		body.setPosition(670.0f, 570.0f);
	}
	if (num == 4) {
		body.setPosition(414.0f, 480.0f);
	}
	if (num == 5) {
		body.setPosition(782.0f, 480.0f);
	}
	if (num == 6) {
		body.setScale(0.4, 0.4);
		body.setPosition(1140.0f, 35.0f);
	}
	body.setTextureRect(animation.uvRect);
}


button::~button()
{
}

void button::Update(float deltaTime, sf::Vector2f mousepos) {
	if (body.getPosition().x - mousepos.x < 85.4f && mousepos.x - body.getPosition().x < 85.4f && body.getPosition().y - mousepos.y < 43.4f && mousepos.y - body.getPosition().y < 43.4f) {
		row = 1; 
	}
	else row = 0;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}
void button::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void button::set(sf::Vector2f pos) {
	body.setPosition(pos);
}
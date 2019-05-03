#include "Exam.h"



Exam::Exam(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int num):
	animation(texture, imageCount, switchTime)
{
	 // กว้าง*ยาว
	body.setTexture(texture);
	if (num == 1) {
		body.setSize(sf::Vector2f(91.0f, 93.0f));
		body.setScale(3, 3);
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(404.0f, 266.0f);
	}
	if (num == 2) {
		body.setSize(sf::Vector2f(91.0f, 93.0f));
	
		body.setScale(3, 3);
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(772.0f, 266.0f);
	}
	if (num == 3) {

		body.setSize(sf::Vector2f(50.0f, 50.0f));
		body.setScale(1.2, 1.2);
		body.setOrigin(body.getSize() / 2.0f);
	}
	body.setTextureRect(animation.uvRect);
}


Exam::~Exam()
{
}

void Exam::Update(float deltaTime) {
	
	animation.Update(0, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}
void Exam::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Exam::Set(sf::Vector2f playerpos) {
	body.setPosition(playerpos);
}

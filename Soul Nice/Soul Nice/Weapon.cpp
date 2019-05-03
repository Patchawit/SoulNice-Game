#include "Weapon.h"
#include<math.h>

using namespace sf;

Vector2f aimDir;
Vector2f aimDirNorm;

Weapon::Weapon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int num) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(211.0f, 143.0f)); // กว้าง*ยาว
	if (num == 2) {
		body.setScale(1.6, 1.6);
	}
	else if (num == 1) {
		body.setScale(1.2, 1.2);
	}
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(972.5f, 834.5f);
	body.setTexture(texture);

}


Weapon::~Weapon()
{
}

void Weapon::Update(float deltaTime, sf::Vector2f mousepos, sf::Vector2f playerpos)
{	
	if (Mouse::isButtonPressed(Mouse::Left)) {
		row = 1; 
	}
	else { row = 0; }
	body.setPosition(playerpos.x,playerpos.y+16);

	aimDir = mousepos - playerpos;
	aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	float PI = 3.14159265f;
	float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;

	

	if (mousepos.x > playerpos.x) {
		faceRight = true;
		body.setRotation(deg);
	}
	else {
		faceRight = false;
		body.setRotation(deg+180);
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Weapon::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	//window.draw(bullet);
}
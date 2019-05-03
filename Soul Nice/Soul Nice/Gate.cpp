#include "Gate.h"



Gate::Gate(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	faceRight = true;

	body.setSize(sf::Vector2f(182.0f, 279.0f)); // กว้าง*ยาว
	body.setOrigin(body.getSize() / 2.0f);
	body.setScale(1.3, 1.3);
	body.setTexture(texture);
	checkbox.setSize(sf::Vector2f(182.0f, 279.0f)); // กว้าง*ยาว
	checkbox.setOrigin(checkbox.getSize() / 2.0f);
	checkbox.setScale(1.3, 1.3);

}


Gate::~Gate()
{
}

void Gate::Update(float deltaTime, int map_cout)
{
	if (map_cout == 1) {
		body.setPosition(5005.0f, 1096.0f);
	}
	else if (map_cout == 2) {
		body.setPosition(4163.5f, 3167.5f);
	}
	else if (map_cout == 3) {
		body.setPosition(3338.0f, 1505.0f);
	}
	else if (map_cout == 4) {
		body.setPosition(4737.0f, 2940.0f);
	}
	else if (map_cout == 5)
	{
		body.setPosition(4659.0f,2825.0f);
	}
	else if (map_cout == 6)
	{
		body.setPosition(2965.0f, 2765.0f);
	}

	animation.Update(0, deltaTime, faceRight);
	checkbox.setPosition(body.getPosition());
	body.setTextureRect(animation.uvRect);
}

void Gate::Draw(sf::RenderWindow& window)
{
	//window.draw(checkbox);
	window.draw(body);
}
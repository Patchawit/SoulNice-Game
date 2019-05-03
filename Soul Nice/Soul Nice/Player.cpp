#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(91.0f, 93.0f)); // กว้าง*ยาว
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(972.5f, 834.5f);
	body.setTexture(texture);
	hitbox.setSize(sf::Vector2f(91.0f, 93.0f)); // กว้าง*ยาว
	hitbox.setOrigin(hitbox.getSize() / 2.0f);
}


Player::~Player()
{
}

void Player::Update(float deltaTime, sf::Vector2f mousepos, sf::Vector2f gatepos)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (immuneDelay.getElapsedTime().asSeconds() > 10)
	{
		immune = false; rearmor = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= speed * deltaTime + 0.5f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += speed * deltaTime + 0.5f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime + 0.5f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime + 0.5f;

	if (mousepos.x > body.getPosition().x) {
		faceRight = true;
	}
	else
		faceRight = false;
	
	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		row = 0;
	}
	else 
	{
		row = 1;

			
	}
	

	animation.Update(row, deltaTime, faceRight);
	hitbox.setPosition(body.getPosition());
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	//window.draw(hitbox);
	window.draw(body);
}


void Player::Set(sf::Vector2f playerpos) {
	body.setPosition(playerpos);
}
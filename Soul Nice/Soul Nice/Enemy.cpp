#include "Enemy.h"



Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,int type):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	type_enemy = type;
	canfight = true;
	scr = 0;
	if (type == 1) 
	{
		body.setSize(sf::Vector2f(182.0f, 181.0f)); // กว้าง*ยาว
		hitbox.setSize(sf::Vector2f(100.0f, 100.0f)); // กว้าง*ยาว
		hitbox.setOrigin(hitbox.getSize() / 2.0f);
	}
	else if (type == 2)
	{
		body.setSize(sf::Vector2f(232.0f, 219.0f)); // กว้าง*ยาว
		body.setScale(0.5, 0.5);
		hitbox.setSize(sf::Vector2f(50.0f, 50.0f)); // กว้าง*ยาว
		hitbox.setOrigin(hitbox.getSize() / 2.0f);
	}
	else if (type == 3)
	{
		body.setSize(sf::Vector2f(309.0f, 309.0f)); // กว้าง*ยาว
		body.setScale(1.2, 1.2);
		hitbox.setSize(sf::Vector2f(250.0f, 250.0f)); // กว้าง*ยาว
		hitbox.setOrigin(hitbox.getSize() / 2.0f);
		
	}
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setTextureRect(animation.uvRect);

	
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, int action, sf::Vector2f playerpos,int hp)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (delayTime.getElapsedTime().asSeconds() > 2)
	{
		delay = false;
		if (type_enemy == 1) {
			canfight = true;
		}
	}
		bool canlive;
	if (hp > 0) {
		canlive = true;
	}
	
	else 
	{
		canlive = false; 
	}

	if (type_enemy == 1 && canlive == true) 
	{
		if (canfight) 
		{
			if (playerpos.x - body.getPosition().x < 0.0f)
				movement.x -= speed * deltaTime ;
			if (playerpos.x - body.getPosition().x > 0.0f)
				movement.x += speed * deltaTime ;
			if (playerpos.y - body.getPosition().y > 0.0f)
				movement.y += speed * deltaTime ;
			if (playerpos.y - body.getPosition().y < 0.0f)
				movement.y -= speed * deltaTime ;
		}
		else
		{
			if (playerpos.x - body.getPosition().x < 0.0f)
				movement.x += speed * deltaTime;
			if (playerpos.x - body.getPosition().x > 0.0f)
				movement.x -= speed * deltaTime;
			if (playerpos.y - body.getPosition().y > 0.0f)
				movement.y -= speed * deltaTime;
			if (playerpos.y - body.getPosition().y < 0.0f)
				movement.y += speed * deltaTime;
		}

		if (movement.x <= 0.0f) {
			faceRight = false;
		}
		else
			faceRight = true;
		if (movement.x == 0 && movement.y == 0) 
		{
			row = 0;
		}
		if (row == 2) 
		{
			atkbox.setSize(sf::Vector2f(182.0f, 181.0f)); // กว้าง*ยาว
			atkbox.setOrigin(atkbox.getSize() / 2.0f);
			
		}
		if (canfight) {
			if (faceRight) {
				atkbox.setPosition(body.getPosition().x + 91.0f, body.getPosition().y);
			}
			else
				atkbox.setPosition(body.getPosition().x - 91.0f, body.getPosition().y);
		}
		else
		{
			atkbox.setPosition(body.getPosition());
		}

	}
	else if ((type_enemy == 2 || type_enemy == 3) && canlive == true)
	{
		if (canfight == true) 
		{
			if (playerpos.x - body.getPosition().x < 0.0f)
				movement.x -= speed * deltaTime;
			if (playerpos.x - body.getPosition().x > 0.0f)
				movement.x += speed * deltaTime;
			if (playerpos.y - body.getPosition().y > 0.0f)
				movement.y += speed * deltaTime;
			if (playerpos.y - body.getPosition().y < 0.0f)
				movement.y -= speed * deltaTime;

			if (playerpos.x - body.getPosition().x < 0.0f && playerpos.x - body.getPosition().x > -250.0f)
				movement.x -= speed * deltaTime + 0.2f;
			if (playerpos.x - body.getPosition().x > 0.0f && playerpos.x - body.getPosition().x < 250.0f)
				movement.x += speed * deltaTime + 0.2f;
			if (playerpos.y - body.getPosition().y > 0.0f && playerpos.y - body.getPosition().y < 250.0f)
				movement.y += speed * deltaTime + 0.2f;
			if (playerpos.y - body.getPosition().y < 0.0f && playerpos.y - body.getPosition().y > -250.0f)
				movement.y -= speed * deltaTime + 0.2f;
		}
		else if(canfight == false)
		{
			if (playerpos.x - body.getPosition().x < 0.0f)
				movement.x += speed * deltaTime;
			if (playerpos.x - body.getPosition().x > 0.0f)
				movement.x -= speed * deltaTime;
			if (playerpos.y - body.getPosition().y > 0.0f)
				movement.y -= speed * deltaTime;
			if (playerpos.y - body.getPosition().y < 0.0f)
				movement.y += speed * deltaTime;

			if (playerpos.x - body.getPosition().x < 0.0f && playerpos.x - body.getPosition().x > -250.0f)
				movement.x += speed * deltaTime + 0.2f;
			if (playerpos.x - body.getPosition().x > 0.0f && playerpos.x - body.getPosition().x < 250.0f)
				movement.x -= speed * deltaTime + 0.2f;
			if (playerpos.y - body.getPosition().y > 0.0f && playerpos.y - body.getPosition().y < 250.0f)
				movement.y -= speed * deltaTime + 0.2f;
			if (playerpos.y - body.getPosition().y < 0.0f && playerpos.y - body.getPosition().y > -250.0f)
				movement.y += speed * deltaTime + 0.2f;
		}
		
		if (movement.x <= 0.0f) {
			faceRight = false;
		}
		else
			faceRight = true;
		if (movement.x == 0 && movement.y == 0) {
			row = 0;
		}
		else if (playerpos.x - body.getPosition().x > -250.0f && playerpos.x - body.getPosition().x < 250.0f && playerpos.y - body.getPosition().y < 250.0f&& playerpos.y - body.getPosition().y > -250.0f)
		{
			row = 2;
		}
		else
		{
			row = 1;
		}

	}
	
	else if (canlive == false) 
	{

		row = 3;
	}


	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect); body.setPosition(hitbox.getPosition());
	hitbox.move(movement);
	
}

void Enemy::Draw(sf::RenderWindow& window)
{
	
	
	window.draw(body);
	
}


void Enemy::Set(sf::Vector2f playerpos) {
	hitbox.setPosition(playerpos);
	body.setPosition(playerpos);
}

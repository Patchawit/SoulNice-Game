#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Weapon
{
public:
	Weapon(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,int num);
	~Weapon();

	void Update(float deltaTime, sf::Vector2f mousepos, sf::Vector2f playerpos);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};
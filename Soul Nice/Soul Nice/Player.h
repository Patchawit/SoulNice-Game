#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"
using namespace sf;

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed);
	~Player();

	void Update(float deltaTime, sf::Vector2f mousepos, sf::Vector2f gatepos);
	void Draw(sf::RenderWindow& window);
	void Set(sf::Vector2f playerpos);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


	sf::RectangleShape body , hitbox;
	Animation animation;
	Clock immuneDelay;
	unsigned int row;
	float speed;
	bool faceRight , rearmor = false;
	bool immune = false;
};
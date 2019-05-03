#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

using namespace sf;

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,int type);
	~Enemy();

	void Update(float deltaTime, int action, sf::Vector2f playerpos,int hp);
	void Draw(sf::RenderWindow& window);
	void Set(sf::Vector2f playerpos);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	Collider GetAtkbox() { return Collider(atkbox); }
	Collider GetHitbox() { return Collider(hitbox); }

	sf::RectangleShape body, hitbox, atkbox;
	Animation animation;
	Clock delayTime;
	unsigned int row;
	float speed;
	int type_enemy , scr;
	bool faceRight, canfight;
	bool delay = false;
};


#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Gate
{
public:
	Gate(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed);
	~Gate();

	void Update(float deltaTime, int map_cout);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


private:
	sf::RectangleShape body,checkbox;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};


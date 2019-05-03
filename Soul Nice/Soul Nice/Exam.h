#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Exam
{
public:
	Exam(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int num);
	~Exam();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void Set(sf::Vector2f playerpos);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	Animation animation;

	sf::RectangleShape body, checkbox;
	
	unsigned int row;
	float speed;
	bool faceRight,shot = true;
};


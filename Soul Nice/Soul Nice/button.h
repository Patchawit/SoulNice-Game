#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class button
{
public:
	button(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, int num);
	~button();
	
	void Update(float deltaTime, sf::Vector2f mousepos);
	void Draw(sf::RenderWindow& window);
	void set(sf::Vector2f pos);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


private:
	sf::RectangleShape body, checkbox;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};


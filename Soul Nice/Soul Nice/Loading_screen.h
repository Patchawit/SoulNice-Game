#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Loading_screen
{
public:
	Loading_screen(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Loading_screen();

	void Update(float deltaTime, sf::Vector2f playerpos);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return screen.getPosition(); }
	Collider GetCollider() { return Collider(screen); }

private:
	sf::RectangleShape screen;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
};



#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<vector>
#include"Animation.h"
#include"Player.h"
#include"Platform.h"
#include"Gate.h"
#include"Weapon.h"
#include"Enemy.h"
#include"button.h"
#include"Exam.h"
#include<string>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include"Item.h"

using namespace sf;
using namespace std;

static const float VIEW_HEIGHT = 1200.0f;
static const float VIEW_WIDTH = 675.0f;

float hp = 202.0f;
float armor = 202.0f;
float score = 202.0f;



Vector2f mpos; Vector2f position;

ofstream save;
ifstream load;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_WIDTH);
}

void map_object(vector<Platform>&, vector <Platform>&, vector<Platform>&, vector<Platform>&, vector<Platform>&, vector<Platform>& , vector<Platform>& );

class Bullet
	{
	public:
		RectangleShape shape;
		Texture bullettex;
		Vector2f currVelocity;
		float maxSpeed;
		Bullet(float radius = 5.f)
			: currVelocity(0.f, 0.f), maxSpeed(1.f)
		{
			bullettex.loadFromFile("sheet/bullet.png");
			this->shape.setTexture(&bullettex);
			this->shape.setSize(Vector2f(30.0f,30.0f));
			this->shape.setOrigin(shape.getSize() / 2.0f);
			
		}
		sf::Vector2f GetPosition() { return shape.getPosition(); }
		Collider GetCollider() { return Collider(shape); }
	};

int main()
{
	vector<pair<int, string>> scoreboard;

	int mode = 0;
	int map_cout = 1;
	int shoottimer = 300;
	int charac = 0;
	int row = 0;
	int Score = 0;
	Text scores , score_over , nametext;
	Font font;
	font.loadFromFile("sheet/Minecraftia-Regular.ttf");
	scores.setFont(font);
	scores.setCharacterSize(24);
	scores.setOutlineThickness(1);
	scores.setOutlineColor(Color::Black);
	scores.setFillColor(Color::White);

	score_over.setFont(font);
	score_over.setCharacterSize(40);
	score_over.setOutlineThickness(1);
	score_over.setOutlineColor(Color::Black);
	score_over.setFillColor(Color::White);
	score_over.setString("SCORE = ");

	nametext.setFont(font);
	nametext.setCharacterSize(40);
	nametext.setOutlineThickness(1);
	nametext.setOutlineColor(Color::Black);
	nametext.setFillColor(Color::White);
	nametext.setString("NAME : ");

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1200, 675), "SOUL!XD", sf::Style::Close | sf::Style::Resize); //hide cursor

	Image icon;
	icon.loadFromFile("sheet/icon.jpeg");
	window.setIcon(225, 225, icon.getPixelsPtr());

	Bullet b1;
		std::vector<Bullet> bullets;
	
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH));

	vector<Platform> map1, map2, map3, map4, map5, map6, boss;

	map_object(map1, map2, map3, map4, map5, map6, boss);



	//HPBAR
	Texture hptex;
	hptex.loadFromFile("sheet/hp.png");
	RectangleShape HP(Vector2f(hp, 24.0f));
	HP.setTexture(&hptex);

	//ARMORBAR
	Texture armortex;
	armortex.loadFromFile("sheet/armor.png");
	RectangleShape ARMOR;
	ARMOR.setTexture(&armortex);

	//SCOREBAR
	Texture scoretex;
	scoretex.loadFromFile("sheet/score.png");
	RectangleShape SCORE;
	SCORE.setTexture(&scoretex);

	//CURSOR
	Texture mousecursor;
	mousecursor.loadFromFile("sheet/cursor.png");
	Sprite msprite;
	Vector2f origin;
	origin = window.mapPixelToCoords(Mouse::getPosition(window));
	msprite.setTexture(mousecursor);
	msprite.setScale(2.5, 2.5);

	//////////////////////////////////////menu//////////////////////////////////

	//MUSIC
	Music menumusic;
	menumusic.openFromFile("sheet/sound/Soul Knight OST - Forests.ogg");

	Music gameovermusic,winner;
	gameovermusic.openFromFile("sheet/sound/PacMan Game Over.ogg");
	winner.openFromFile("sheet/sound/winner.ogg");

	Sound shoteff , buttoneff ,selecteff,itemeff;
	SoundBuffer shoteffect, buttoneffect, select_char, itemeffect;
	shoteffect.loadFromFile("sheet/sound/Shotsound.ogg");
	buttoneffect.loadFromFile("sheet/sound/Click.ogg");
	select_char.loadFromFile("sheet/sound/select_char.ogg");
	itemeffect.loadFromFile("sheet/sound/item.ogg");
	buttoneff.setBuffer(buttoneffect);
	selecteff.setBuffer(select_char);
	itemeff.setBuffer(itemeffect);

	Texture menutex;
	menutex.loadFromFile("sheet/Menu.png");
	Sprite menu;
	menu.setTexture(menutex);

	Texture overtex;
	Sprite over;

	Texture newtex;
	newtex.loadFromFile("sheet/NEW GAME-sheet.png");
	button newgame(&newtex, Vector2u(1, 2), 0.1f, 1);

	Texture stex;
	stex.loadFromFile("sheet/SCOREMENU-sheet.png");
	button scoremenu(&stex, Vector2u(1, 2), 0.1f, 2);

	Texture Exittex;
	Exittex.loadFromFile("sheet/EXIT-sheet.png");
	button exit(&Exittex, Vector2u(1, 2), 0.1f, 6);

	Texture hstex;
	hstex.loadFromFile("sheet/highscore.png");
	Sprite highscore;
	highscore.setTexture(hstex);

	//////////////////////////////select//////////////////////////////////////
	Texture selecttex;
	selecttex.loadFromFile("sheet/select.png");
	Sprite select;
	select.setTexture(selecttex);

	Texture buttontex;
	buttontex.loadFromFile("sheet/SELECT-sheet.png");
	button button1(&buttontex, Vector2u(1, 2), 0.1f, 4);

	button button2(&buttontex, Vector2u(1, 2), 0.1f, 5);

	button buttonre(&buttontex, Vector2u(1, 2), 0.1f, 5);

	Texture asstex;
	asstex.loadFromFile("sheet/assassin v.3.png");
	Exam ass(&asstex, Vector2u(4, 2), 0.1f, 2);

	Texture kintex;
	kintex.loadFromFile("sheet/knightv.3.png");
	Exam kin(&kintex, Vector2u(4, 2), 0.1f, 1);

	////////////////////GAME///////////////////////
	Texture shottex; //กระสุนระเบิด
	shottex.loadFromFile("sheet/shot.png");
	Exam shot(&shottex, Vector2u(5, 1), 0.0041f, 3);

	Texture hpitemtex;
	hpitemtex.loadFromFile("sheet/item.png");
	Item hpitem(&hpitemtex, Vector2u(1, 3), 0.1);
	if (map_cout == 1) {
		hpitem.Set(Vector2f(3000.0f, 3152.0f)); hpitem.row = 0;
	}

	sf::Texture bg;
	if (map_cout == 1) {
		bg.loadFromFile("sheet/map 1-1.png");
	}
	sf::Sprite sprite;

	Texture text_gate,text_potiontex;
	text_gate.loadFromFile("sheet/textportal.png");
	text_potiontex.loadFromFile("sheet/textpotion.png");
	Sprite text_portal ,text_potion;
	text_portal.setTexture(text_gate);
	text_portal.setScale(0.2, 0.2);
	text_potion.setTexture(text_potiontex);
	text_potion.setScale(0.2, 0.2);

	Texture gatetexture;
	gatetexture.loadFromFile("sheet/portal v2.png");
	gatetexture.setSmooth(true);
	Gate gate(&gatetexture, Vector2u(8, 1), 0.12f, 100.0f);

	sf::Texture EnemyTexture,Boartex,MinerTexture,Apetex,boss2tex,boss1tex;
	EnemyTexture.loadFromFile("sheet/GiantGoblin.png");
	Boartex.loadFromFile("sheet/Boar.png");
	MinerTexture.loadFromFile("sheet/miner.png");
	Apetex.loadFromFile("sheet/ape.png");
	boss1tex.loadFromFile("sheet/ChristmasTreant.png");
	boss2tex.loadFromFile("sheet/GHOST.png");
	Enemy enemy(&EnemyTexture, sf::Vector2u(4, 4), 0.1f, 100.0f,1);
	Enemy boar(&Boartex, sf::Vector2u(4, 4), 0.1f, 100.0f, 2);
	Enemy miner(&MinerTexture, sf::Vector2u(4, 4), 0.1f, 100.0f, 1);
	Enemy ape(&Apetex, sf::Vector2u(4, 4), 0.1f, 100.0f, 2);
	Enemy boss1(&boss1tex, sf::Vector2u(4, 4), 0.1f, 200.0f, 3);
	Enemy boss2(&boss2tex, sf::Vector2u(4, 4), 0.1f, 250.0f, 3);

	vector<Enemy> enemies , enemies_boar , enemies2, enemies_boar2 , miners1 , miners2 , apes1 , apes2;
	int hpgoblin1[4] = { 10,10,10,10 };
	int hpboar1[8] = { 5,5,5,5,5,5,5,5 };
	int hpgoblin2[3] = { 10,10,10 };
	int hpboar2[8] = { 5,5,5,5,5,5,5,5 };

	int hpminer1[4] = { 10,10,10,10 };
	int hpape1[8] = { 5,5,5,5,5,5,5,5 };
	int hpminer2[4] = { 10,10,10,10 };
	int hpape2[8] = { 5,5,5,5,5,5,5,5 };

	int hpboss[2] = { 75,75 };
	///////////MAP 1///////////////////////
	for (int i = 0; i < 3; i++) 
	{
		enemies.push_back(enemy);
		Vector2f pos;
		pos.x = rand() % 900 + 2600;
		pos.y = rand() % 800 + 700;
		enemies[i].Set(pos);
		Enemy& enemyArray = enemies[i];
	}
	for (int i = 3; i < 4; i++) {
		enemies.push_back(enemy);
		Vector2f pos;
		pos.x = rand() % 500 + 4400;
		pos.y = rand() % 700 + 2600;
		enemies[i].Set(pos);
		Enemy& enemyArray = enemies[i];
	}
	for (int i = 0; i < 5; i++)
	{
		enemies_boar.push_back(boar);
		Vector2f pos;
		pos.x = rand() % 900 + 2600;
		pos.y = rand() % 800 + 700;
		enemies_boar[i].Set(pos);
		Enemy& boarArray = enemies_boar[i];
	}
	for (int i = 5; i < 8; i++) {
		enemies_boar.push_back(boar);
		Vector2f pos;
		pos.x = rand() % 500 + 4400;
		pos.y = rand() % 700 + 2600;
		enemies_boar[i].Set(pos);
		Enemy& boarArray = enemies_boar[i];
	}

	//////////////////MAP2////////////////////
	
	for (int i = 0; i < 3; i++)
	{
		enemies2.push_back(enemy);
		Vector2f pos;
		pos.x = rand() % 1653 + 1711;
		pos.y = rand() % 800 + 700;
		enemies2[i].Set(pos);
		Enemy& enemyArray2 = enemies2[i];
	}
	
	for (int i = 0; i < 5; i++)
	{
		enemies_boar2.push_back(boar);
		Vector2f pos;
		pos.x = rand() % 1653 + 1711;
		pos.y = rand() % 800 + 700;
		enemies_boar2[i].Set(pos);
		Enemy& boarArray2 = enemies_boar2[i];
	}
	for (int i = 5; i < 8; i++) {
		enemies_boar2.push_back(boar);
		Vector2f pos;
		pos.x = rand() % 696 + 649;
		pos.y = rand() % 300 + 3100;
		enemies_boar2[i].Set(pos);
		Enemy& boarArray2 = enemies_boar2[i];
	}

	/////////////////	MAP3	//////////////////

	boss1.Set(Vector2f(3340.0f, 1289.0f));

	/////////////////   MAP4   //////////////////

	for (int i = 0; i < 3; i++)
	{
		miners1.push_back(miner);
		Vector2f pos;
		pos.x = rand() % 800 + 4400;
		pos.y = rand() % 600 + 600;
		miners1[i].Set(pos);
		Enemy& enemyArray = miners1[i];
	}
	for (int i = 3; i < 4; i++) {
		miners1.push_back(miner);
		Vector2f pos;
		pos.x = rand() % 400 + 2600;
		pos.y = rand() % 1000 + 400;
		miners1[i].Set(pos);
		Enemy& enemyArray = miners1[i];
	}
	for (int i = 0; i < 5; i++)
	{
		apes1.push_back(ape);
		Vector2f pos;
		pos.x = rand() % 800 + 4400;
		pos.y = rand() % 600 + 600;
		apes1[i].Set(pos);
		Enemy& boarArray = apes1[i];
	}
	for (int i = 5; i < 8; i++) 
	{
		apes1.push_back(ape);
		Vector2f pos;
		pos.x = rand() % 400 + 2600;
		pos.y = rand() % 1000 + 400;
		apes1[i].Set(pos);
		Enemy& boarArray = apes1[i];
	}

	/////////////////   MAP5   //////////////////

	for (int i = 0; i < 3; i++)
	{
		miners2.push_back(miner);
		Vector2f pos;
		pos.x = rand() % 800 + 2600;
		pos.y = rand() % 600 + 600;
		miners2[i].Set(pos);
		Enemy& enemyArray = miners2[i];
	}
	for (int i = 3; i < 4; i++) {
		miners2.push_back(miner);
		Vector2f pos;
		pos.x = rand() % 400 + 4800;
		pos.y = rand() % 1000 + 400;
		miners2[i].Set(pos);
		Enemy& enemyArray = miners2[i];
	}
	for (int i = 0; i < 5; i++)
	{
		apes2.push_back(ape);
		Vector2f pos;
		pos.x = rand() % 800 + 2600;
		pos.y = rand() % 600 + 600;
		apes2[i].Set(pos);
		Enemy& boarArray = apes2[i];
	}
	for (int i = 5; i < 8; i++)
	{
		apes2.push_back(ape);
		Vector2f pos;
		pos.x = rand() % 400 + 4800;
		pos.y = rand() % 1000 + 400;
		apes2[i].Set(pos);
		Enemy& boarArray = apes2[i];
	}

	////////////////MAP 6 ////////////////

	boss2.Set(Vector2f(3000.0f,2864.0f));

	/////////////////////////////////////
	Texture stat_bar;
	if (!stat_bar.loadFromFile("sheet/statbar v.png")) 
	{
		std::cout << "Load Failed" << std::endl;
		system("pause");
	}
	Sprite stat;
	stat.setTexture(stat_bar);

	Platform gate_check(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(750.0f, 840.0f));
	
	Vector2f playerCenter;
	Vector2f mousePosWindow;
	Vector2f aimDir;
	Vector2f aimDirNorm;
	Vector2f playeroriginpos(972.5f, 834.5f);

	float deltaTime = 0.0f;
	sf::Clock clock ,debounce;

		menumusic.play();
	/////////////////////MENU////////////////////
	menu:
		//SCORE_TEXT
		load.open("score.txt");
		while (!load.eof()) {
			string tempName;
			int tempScore;
			load >> tempName >> tempScore;
			scoreboard.push_back({ tempScore,tempName });
		}
		sort(scoreboard.begin(), scoreboard.end(), greater<pair<int, string>>());

		string enterName;
		Text Name; Name.setFont(font);
		Name.setCharacterSize(48);
	while (window.isOpen() && mode == 0 )
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event button;
		while (window.pollEvent(button))
		{
			switch (button.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		mousePosWindow = window.mapPixelToCoords((Mouse::getPosition(window)));
		newgame.Update(deltaTime, mousePosWindow);
		scoremenu.Update(deltaTime, mousePosWindow);
		exit.Update(deltaTime, mousePosWindow);
		
		if (Mouse::isButtonPressed(Mouse::Left) && debounce.getElapsedTime().asSeconds() > 0.1)
		{

			if (newgame.GetPosition().x - mousePosWindow.x < 85.4f && mousePosWindow.x - newgame.GetPosition().x < 85.4f && newgame.GetPosition().y - mousePosWindow.y < 43.4f && mousePosWindow.y - newgame.GetPosition().y < 43.4f) 
			{
				buttoneff.play(); shoottimer = 0; menumusic.openFromFile("sheet/sound/Soul Knight OST - Living Room.ogg"); menumusic.play(); mode = 1;
			}
			else if (scoremenu.GetPosition().x - mousePosWindow.x < 85.4f && mousePosWindow.x - scoremenu.GetPosition().x < 85.4f && scoremenu.GetPosition().y - mousePosWindow.y < 43.4f && mousePosWindow.y - scoremenu.GetPosition().y < 43.4f)
			{
				buttoneff.play(); menumusic.openFromFile("sheet/sound/Soul Knight OST - Living Room.ogg"); menumusic.play(); mode = 4;
			}
			else if (exit.GetPosition().x - mousePosWindow.x < 48.8f && mousePosWindow.x - exit.GetPosition().x < 48.8f && exit.GetPosition().y - mousePosWindow.y < 24.8f && mousePosWindow.y - exit.GetPosition().y < 24.8f)
			{
				buttoneff.play(); window.close();
			}
			
		}
		
		window.clear();
		window.draw(menu);
		newgame.Draw(window);
		scoremenu.Draw(window);
		exit.Draw(window);
		window.display();
	}

	///////////////////////////////select_char///////////////////////////////////
	while (window.isOpen() && mode == 1)
	{
		sf::Event but;
		deltaTime = clock.restart().asSeconds();
		nametext.setPosition(1200 / 2 - 200, 675 / 2 + 250);
		while (window.pollEvent(but))
		{
			switch (but.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}

			if (but.type == Event::TextEntered)
			{
				if (but.text.unicode == 8) // BACK SPACE
				{
					if (enterName.size() != 0) enterName.pop_back();
					Name.setString(enterName);
					//Name.setOrigin(Name.getLocalBounds().left + Name.getLocalBounds().width / 2, Name.getLocalBounds().top + Name.getLocalBounds().height / 2);
					Name.setPosition(1200 / 2 - 50, 675 / 2+ 248);
				}
				else if (but.text.unicode == 13 and enterName.size() != 0) // RETURN
				{
					window.clear(Color::White);
					break;
				}
				else if (but.text.unicode < 128 and but.text.unicode != 32 and but.text.unicode != 8 and enterName.size() < 15)
				{
					enterName.push_back((char)but.text.unicode);
					Name.setString(enterName);
					//Name.setOrigin(Name.getLocalBounds().left + Name.getLocalBounds().width / 2, Name.getLocalBounds().top + Name.getLocalBounds().height / 2);
					Name.setPosition(1200 / 2 - 50, 675 / 2 +248);
				}
			}
		}

		mousePosWindow = window.mapPixelToCoords((Mouse::getPosition(window)));
		button1.Update(deltaTime, mousePosWindow);
		button2.Update(deltaTime, mousePosWindow);
		kin.Update(deltaTime);
		ass.Update(deltaTime);
		exit.Update(deltaTime, mousePosWindow);

		if (Mouse::isButtonPressed(Mouse::Left) && debounce.getElapsedTime().asSeconds() > 0.5)
		{
			if (enterName.size() != 0)
			{
				if (button1.GetPosition().x - mousePosWindow.x < 85.4f && mousePosWindow.x - button1.GetPosition().x < 85.4f && button1.GetPosition().y - mousePosWindow.y < 43.4f && mousePosWindow.y - button1.GetPosition().y < 43.4f) 
				{
					selecteff.play();menumusic.openFromFile("sheet/sound/Soul Knight OST - Forests.ogg"); menumusic.play();
					charac = 1; hp = 202.0f; armor = 202.0f;
					mode = 2;
				}
				if (button2.GetPosition().x - mousePosWindow.x < 85.4f && mousePosWindow.x - button2.GetPosition().x < 85.4f && button2.GetPosition().y - mousePosWindow.y < 43.4f && mousePosWindow.y - button2.GetPosition().y < 43.4f)
				{

					selecteff.play(); menumusic.openFromFile("sheet/sound/Soul Knight OST - Forests.ogg"); menumusic.play(); Sleep(500);
					charac = 2; hp = 202.0f; armor = 202.0f;
					mode = 2;
				}
			}

			if (exit.GetPosition().x - mousePosWindow.x < 48.8f && mousePosWindow.x - exit.GetPosition().x < 48.8f && exit.GetPosition().y - mousePosWindow.y < 24.8f && mousePosWindow.y - exit.GetPosition().y < 24.8f)
			{
				buttoneff.play();
				window.close();
			}
			debounce.restart().asSeconds();
		}
		
		
		window.clear();

		window.draw(select);
		ass.Draw(window);
		kin.Draw(window);
		button1.Draw(window);
		button2.Draw(window);
		window.draw(nametext);
		window.draw(Name);
		exit.Draw(window);

		window.display();
	}

	//////////////////////////////////GAME///////////////////////////////////////
	sf::Texture PlayerTexture;Texture revolvertexture;
		if (charac == 1) 
		{
			revolvertexture.loadFromFile("sheet/Revolver2.png");
			PlayerTexture.loadFromFile("sheet/knightv.3.png");	shoteff.setBuffer(shoteffect);
		}
		else if (charac == 2) 
		{
			revolvertexture.loadFromFile("sheet/Revolver.png");
			PlayerTexture.loadFromFile("sheet/assassin v.3.png");	shoteff.setBuffer(shoteffect);
		}
		Player player(&PlayerTexture, sf::Vector2u(4, 2), 0.1f, 150.0f);
		Weapon revolver(&revolvertexture, Vector2u(4, 2), 0.1f, 100.0f,charac);

	while (window.isOpen() && mode == 2)
	{

		ostringstream sc;
		sc << Score;
		scores.setString(sc.str());
		window.setMouseCursorVisible(false);
		deltaTime = clock.restart().asSeconds();
		position = player.GetPosition();
		
		text_portal.setPosition(gate.GetPosition().x-100.0f, gate.GetPosition().y-200.0f);
		text_potion.setPosition(hpitem.GetPosition().x - 90.0f , hpitem.GetPosition().y - 150.0f);
		////////////////////////MAP////////////////////////
		sprite.setTexture(bg);
		//////////////////////////////////////////////////

		sf::Event button;
		while (window.pollEvent(button))
		{ 
			switch (button.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
				
		playerCenter = player.GetPosition();
		mousePosWindow = window.mapPixelToCoords((Mouse::getPosition(window)));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		
		float PI = 3.14159265f;
		float deg = atan2(aimDirNorm.y, aimDirNorm.x) * 180 / PI;
		
		mpos = window.mapPixelToCoords(Mouse::getPosition(window));

		///////////////UPDATE/////////////////////
		player.Update(deltaTime,mpos,gate.GetPosition());
		gate.Update(deltaTime, map_cout);
		revolver.Update(deltaTime, mousePosWindow, player.GetPosition());
		hpitem.Update(deltaTime);
		//////////////////////////////////////////

		view.setCenter(player.GetPosition());
		msprite.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)).x-25.0f, window.mapPixelToCoords(Mouse::getPosition(window)).y - 25.0f);
		stat.setPosition(player.GetPosition().x - 570.0f, player.GetPosition().y - 327.5f);
		//SETHP
		HP.setPosition(player.GetPosition().x - 516.0f, player.GetPosition().y - 311.5f);
		HP.setSize(Vector2f(hp, 24.0f));
		//SETARMOR
		ARMOR.setPosition(player.GetPosition().x - 516.0f, player.GetPosition().y - 276.5f);
		ARMOR.setSize(Vector2f(armor, 24.0f));
		if (armor < 202.0f and !player.immune){
			player.immune = true;
			player.immuneDelay.restart().asSeconds();
			if (player.rearmor) {
				armor = 202.0f;
			}
		}
		//SETSCORE
		SCORE.setPosition(player.GetPosition().x - 516.0f, player.GetPosition().y - 241.5f);
		SCORE.setSize(Vector2f(score, 24.0f));
		scores.setPosition(SCORE.getPosition().x + 101.0f, SCORE.getPosition().y + 14);
		scores.setOrigin(scores.getLocalBounds().left + scores.getLocalBounds().width / 2, scores.getLocalBounds().top + scores.getLocalBounds().height / 2);
		
		//SHOOT
		if (shoottimer < 300) 
		{
			shoottimer++;
		}
		if (Mouse::isButtonPressed(Mouse::Left) && shoottimer >= 300 && debounce.getElapsedTime().asSeconds() > 0.1)
		{
			
				shoteff.play();
				b1.shape.setPosition(revolver.GetPosition().x,revolver.GetPosition().y-12);
				b1.currVelocity = aimDirNorm * b1.maxSpeed;
				b1.shape.setRotation(deg);
				bullets.push_back(Bullet(b1));
				shot.shot = true;
				shoottimer = 0;
				debounce.restart().asSeconds();
			
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].shape.move(bullets[i].currVelocity);
		}

		window.clear();
		window.setView(view);
		//draw
		
		window.draw(sprite);
		if (map_cout != 3 && map_cout != 6) {
			gate.Draw(window);
		}
		if (map_cout == 3 && hpboss[0] <= 0)
		{
			gate.Draw(window);
		}
		if (map_cout == 6 && hpboss[1] <= 0)
		{
			gate.Draw(window);
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i].shape);
		}
		
		hpitem.Draw(window);
		player.Draw(window);
	
		//////////////////////////MAP 1///////////////////////////////

		if (map_cout == 1) 
		{
			if (hpitem.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
				window.draw(text_potion);
				if (hpitem.row == 0)
				{
					hpitem.row = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && hpitem.row == 1) {
					itemeff.play(); hp = 202.0f; hpitem.row = 2;
				}
			}
			if (hp < 20.2f) 
			{
				view.setCenter(Vector2f(600.0f, 337.5f));
				over.setPosition(Vector2f(0.0f,0.0f)); 
				buttonre.set(Vector2f(600.0f,595.5));
				if (charac == 2) 
				{
				overtex.loadFromFile("sheet/gameover1ass.png");
				}
				else if (charac == 1) 
				{
					overtex.loadFromFile("sheet/gameover1kn.png");
				}
				save.open("score.txt", ios::app);
				save << "\n" << enterName << " " << Score;
				save.close(); gameovermusic.play(); menumusic.stop();
				mode = 3; 
			}
			for (int i = 0; i < 3; i++) //room1
			{
				if (player.GetPosition().x > 2190.0f && player.GetPosition().x < 3847.0f && player.GetPosition().y < 1758.0f) 
				{
					enemies[i].Update(deltaTime, enemies[i].row, player.GetPosition(),hpgoblin1[i]);
				}
				enemies[i].Draw(window);
			}
			for (int i = 0; i < 5; i++)
			{
				if (player.GetPosition().x > 2190.0f && player.GetPosition().x < 3847.0f && player.GetPosition().y < 1758.0f)
				{
					enemies_boar[i].Update(deltaTime, row, player.GetPosition(), hpboar1[i]);
				}
				enemies_boar[i].Draw(window);
			}

			for (int i = 3; i < 4; i++) //room2
			{
				if (player.GetPosition().x > 4274.0f && player.GetPosition().x < 5021.0f && player.GetPosition().y > 2466.0f) 
				{
					enemies[i].Update(deltaTime, enemies[i].row, player.GetPosition(), hpgoblin1[i]);
				}
				enemies[i].Draw(window);
			}
			for (int i = 5; i < 8; i++)
			{
				if (player.GetPosition().x > 4274.0f && player.GetPosition().x < 5021.0f && player.GetPosition().y > 2466.0f)
				{
					enemies_boar[i].Update(deltaTime, row, player.GetPosition(), hpboar1[i]);
				}
				enemies_boar[i].Draw(window);
			}

			for (Platform& platform : map1) 
			{
				platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, true);
				for (int i = 0; i < 4; i++) 
				{
					platform.GetCollider().CheckCollision(enemies[i].GetCollider(), 1.0f, true);
					for (int k = 0; k < 4; k++)
					{
						if (i != k) 
						{
							enemies[k].GetHitbox().CheckCollision(enemies[i].GetHitbox(), 1.0f, true);
						}
					}
					if (enemies[i].GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) 
					{
						enemies[i].row = 2;
						if (enemies[i].row == 2)
						{
							if (enemies[i].GetAtkbox().CheckCollision(player.GetCollider(), 1.0, false) and !enemies[i].delay and enemies[i].canfight == true)
							{
								if (armor <= 20.2f)
								{
									armor = 0;
									hp -= 20.2f;
								}
							else armor -= 20.2f;
							enemies[i].delay = true;
							enemies[i].canfight = false;
							enemies[i].delayTime.restart().asSeconds();
							
						
							}
						}
						
					}
					else 
					{
						enemies[i].row = 1;
					}
				}
				
				for (int k = 0; k < 8; k++)
				{
					platform.GetCollider().CheckCollision(enemies_boar[k].GetCollider(), 1.0f, true);
					for (int i = 0; i < 8; i++)
					{
						if (i != k)
						{
							enemies_boar[i].GetHitbox().CheckCollision(enemies_boar[k].GetHitbox(), 1.0f, true);
						}
					}
					if (platform.GetCollider().CheckCollision(enemies_boar[k].GetHitbox(), 1.0f, false))
					{
						enemies_boar[k].canfight = true;
					}
					if (enemies_boar[k].GetHitbox().CheckCollision(player.GetCollider(), 1.0f, false) and !enemies_boar[k].delay and enemies_boar[k].row != 3)
					{
						if (armor <= 20.2f)
						{
							armor = 0;
							hp -= 20.2f;
						}
						else armor -= 20.2f; 
						enemies_boar[k].delay = true;
						enemies_boar[k].delayTime.restart().asSeconds();
						enemies_boar[k].canfight = false;
					}
				}
				
				for (size_t i = 0; i < bullets.size(); i++) 
				{
					for (int k = 0; k < 8; k++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							enemies_boar[k].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true) )
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpboar1[k] -= 1;
								if (hpboar1[k] == 0)
								{
									Score += 200;hpboar1[k] -= 1;
								}
								break;
							}
						}
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int j = 0; j < 4; j++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							enemies[j].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpgoblin1[j] -= 1;
								if (hpgoblin1[j] == 0)
								{
									Score += 500; hpgoblin1[j] -= 1;
								}
								break;
							}
						}
					}
				}
				
			}
		}					
		//////////////////////////MAP 2///////////////////////////////

		else if (map_cout == 2) 
		{
			if (hpitem.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
				window.draw(text_potion);
				if (hpitem.row == 0)
				{
					hpitem.row = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && hpitem.row == 1) {
					itemeff.play(); hp = 202.0f; hpitem.row = 2;
				}
			}
			if (hp < 20.2f)
			{
				view.setCenter(Vector2f(600.0f, 337.5f));
				over.setPosition(Vector2f(0.0f, 0.0f));
				buttonre.set(Vector2f(600.0f, 595.5));
				if (charac == 2)
				{
					overtex.loadFromFile("sheet/gameover2ass.png");
				}
				else if (charac == 1)
				{
					overtex.loadFromFile("sheet/gameover2kn.png");
				}
				save.open("score.txt", ios::app);
				save << "\n" << enterName << " " << Score;
				save.close(); gameovermusic.play(); menumusic.stop();
				mode = 3; 
			}
			for (int i = 0; i < 3; i++) //room1
			{
				if (player.GetPosition().x > 1711.0f && player.GetPosition().x < 3364.0f && player.GetPosition().y < 1820.0f)
				{
					enemies2[i].Update(deltaTime, enemies2[i].row, player.GetPosition(), hpgoblin2[i]);
				}
				enemies2[i].Draw(window);
			}
			for (int i = 0; i < 5; i++)
			{
				if (player.GetPosition().x > 1711.0f && player.GetPosition().x < 3364.0f && player.GetPosition().y < 1820.0f)
				{
					enemies_boar2[i].Update(deltaTime, row, player.GetPosition(), hpboar2[i]);
				}
				enemies_boar2[i].Draw(window);
			}

			for (int i = 5; i < 8; i++)//room2
			{
				if (player.GetPosition().x > 649.0f && player.GetPosition().x < 1396.0f && player.GetPosition().y > 2840.0f)
				{
					enemies_boar2[i].Update(deltaTime, row, player.GetPosition(), hpboar2[i]);
				}
				enemies_boar2[i].Draw(window);
			}

			for (Platform& platform : map2)
			{
				platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, true);
				for (int i = 0; i < 3; i++)
				{
					platform.GetCollider().CheckCollision(enemies2[i].GetCollider(), 1.0f, true);
					for (int k = 0; k < 3; k++)
					{
						if (i != k)
						{
							enemies2[k].GetHitbox().CheckCollision(enemies2[i].GetHitbox(), 1.0f, true);
						}
					}
					if (enemies2[i].GetCollider().CheckCollision(player.GetCollider(), 1.0f, false))
					{
						enemies2[i].row = 2;
						if (enemies2[i].row == 2)
						{
							if (enemies2[i].GetAtkbox().CheckCollision(player.GetCollider(), 1.0, false) and !enemies2[i].delay and enemies2[i].canfight == true)
							{
								if (armor <= 20.2f)
								{
									armor = 0;
									hp -= 20.2f;
								}
								else armor -= 20.2f;
								enemies2[i].delay = true;
								enemies2[i].canfight = false;
								enemies2[i].delayTime.restart().asSeconds();


							}
						}
					}
					else
					{
						enemies2[i].row = 1;
					}
				}

				for (int k = 0; k < 8; k++)
				{
					platform.GetCollider().CheckCollision(enemies_boar2[k].GetCollider(), 1.0f, true);
					for (int i = 0; i < 8; i++)
					{
						if (i != k)
						{
							enemies_boar2[i].GetHitbox().CheckCollision(enemies_boar2[k].GetHitbox(), 1.0f, true);
						}
					}
					if (platform.GetCollider().CheckCollision(enemies_boar2[k].GetHitbox(), 1.0f, false))
					{
						enemies_boar2[k].canfight = true;
					}
					if (enemies_boar2[k].GetHitbox().CheckCollision(player.GetCollider(), 1.0f, false) and !enemies_boar2[k].delay and enemies_boar2[k].canfight == true)
					{
						if (armor <= 20.2f)
						{
							armor = 0;
							hp -= 20.2f;
						}
						else armor -= 20.2f;
						enemies_boar2[k].delay = true;
						enemies_boar2[k].delayTime.restart().asSeconds();
						enemies_boar2[k].canfight = false;
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int k = 0; k < 8; k++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							enemies_boar2[k].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpboar2[k] -= 1;
								if (hpboar2[k] == 0)
								{
									Score += 200; hpboar2[k] -= 1;
								}
								break;
							}
						}
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int j = 0; j < 3; j++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							enemies2[j].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpgoblin2[j] -= 1;
								if (hpgoblin2[j] == 0)
								{
									Score += 500; hpgoblin2[j] -= 1;
								}
								break;
							}
						}
					}
				}

			}
		}
		//////////////////////////MAP 3///////////////////////////////

		else if (map_cout == 3) 
		{
			if (hpitem.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
				window.draw(text_potion);
				if (hpitem.row == 0)
				{
					hpitem.row = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && hpitem.row == 1) {
					itemeff.play(); hp = 202.0f; hpitem.row = 2;
				}
			}
			if (hp < 20.2f)
			{
				view.setCenter(Vector2f(600.0f, 337.5f));
				over.setPosition(Vector2f(0.0f, 0.0f));
				buttonre.set(Vector2f(600.0f, 595.5));
				if (charac == 2)
				{
					overtex.loadFromFile("sheet/gameover3ass.png");
				}
				else if (charac == 1)
				{
					overtex.loadFromFile("sheet/gameover3kn.png");
				}
				save.open("score.txt", ios::app);
				save << "\n" << enterName << " " << Score;
				save.close(); gameovermusic.play(); menumusic.stop();
				mode = 3;
			}

			if (player.GetPosition().x > 2498.0f && player.GetPosition().x < 4170.0f && player.GetPosition().y < 2130.0f)
			{
				boss1.Update(deltaTime, row, player.GetPosition(), hpboss[0]);
			}
			boss1.Draw(window);

			for (Platform& platform : map3) 
			{
				platform.GetCollider().CheckCollision(boss1.GetCollider(), 1.0f, true);
				platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, true);
				if (platform.GetCollider().CheckCollision(boss1.GetHitbox(), 1.0f, false))
				{
					boss1.canfight = true;
				}
				if (boss1.GetHitbox().CheckCollision(player.GetCollider(), 1.0f, false) and !boss1.delay and boss1.canfight == true)
				{
					if (armor <= 20.2f)
					{
						armor = 0;
						hp -= 40.4f;
					}
					else armor -= 101.0f;
					boss1.delay = true;
					boss1.delayTime.restart().asSeconds();
					boss1.canfight = false;
				}
				for (size_t i = 0; i < bullets.size(); i++)
				{
					if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
						boss1.GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
					{
						if (shot.shot)
						{
							shot.animation.currentImage.x = 0; shot.shot = false;
						}
						shot.Set(bullets[i].GetPosition());
						shot.Update(deltaTime);
						shot.Draw(window);
						if (shot.animation.currentImage.x == 3)
						{
							bullets.erase(bullets.begin() + i); hpboss[0] -= 1;
							if (hpboss[0] == 0)
							{
								Score += 2000; hpboss[0] -= 1;
							}
							break;
						}
					}
				}
			}
			for (Platform& platform : boss)
			{
				if (platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
					menumusic.openFromFile("sheet/sound/Soul Knight OST - Floor 1 Boss.ogg"); menumusic.play();
				}
				
			}
		}

		//////////////////////////MAP 4///////////////////////////////
		else if (map_cout == 4) 
		{
			if (hpitem.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
				window.draw(text_potion);
				if (hpitem.row == 0)
				{
					hpitem.row = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && hpitem.row == 1) {
					itemeff.play(); hp = 202.0f; hpitem.row = 2;
				}
			}
			if (hp < 20.2f)
			{
				view.setCenter(Vector2f(600.0f, 337.5f));
				over.setPosition(Vector2f(0.0f, 0.0f));
				buttonre.set(Vector2f(600.0f, 595.5));
				if (charac == 2)
				{
					overtex.loadFromFile("sheet/gameover4ass.png");
				}
				else if (charac == 1)
				{
					overtex.loadFromFile("sheet/gameover4kn.png");
				}
				save.open("score.txt", ios::app);
				save << "\n" << enterName << " " << Score;
				save.close(); gameovermusic.play(); menumusic.stop();
				mode = 3; 
			}

			for (int i = 0; i < 3; i++) //room1
			{
				if (player.GetPosition().x > 4080.0f && player.GetPosition().x < 5350.0f && player.GetPosition().y < 1341.0f)
				{
					miners1[i].Update(deltaTime, miners1[i].row, player.GetPosition(), hpminer1[i]);
				}
				miners1[i].Draw(window);
			}
			for (int i = 0; i < 5; i++)
			{
				if (player.GetPosition().x > 4080.0f && player.GetPosition().x < 5350.0f && player.GetPosition().y < 1341.0f)
				{
					apes1[i].Update(deltaTime, row, player.GetPosition(), hpape1[i]);
				}
				apes1[i].Draw(window);
			}

			for (int i = 3; i < 4; i++) //room2
			{
				if (player.GetPosition().x > 2306.0f && player.GetPosition().x < 3140.0f && player.GetPosition().y < 1414.0f)
				{
					miners1[i].Update(deltaTime, miners1[i].row, player.GetPosition(), hpminer1[i]);
				}
				miners1[i].Draw(window);
			}
			for (int i = 5; i < 8; i++)
			{
				if (player.GetPosition().x > 2306.0f && player.GetPosition().x < 3140.0f && player.GetPosition().y < 1414.0f)
				{
					apes1[i].Update(deltaTime, row, player.GetPosition(), hpape1[i]);
				}
				apes1[i].Draw(window);
			}

			for (Platform& platform : map4) 
			{
				platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, true);
				for (int i = 0; i < 4; i++)
				{
					platform.GetCollider().CheckCollision(miners1[i].GetCollider(), 1.0f, true);
					for (int k = 0; k < 4; k++)
					{
						if (i != k)
						{
							miners1[k].GetHitbox().CheckCollision(miners1[i].GetHitbox(), 1.0f, true);
						}
					}
					if (miners1[i].GetCollider().CheckCollision(player.GetCollider(), 1.0f, false))
					{
						miners1[i].row = 2;
						if (miners1[i].row == 2)
						{
							if (miners1[i].GetAtkbox().CheckCollision(player.GetCollider(), 1.0, false) and !miners1[i].delay and miners1[i].canfight == true)
							{
								if (armor <= 20.2f)
								{
									armor = 0;
									hp -= 20.2f;
								}
								else armor -= 20.2f;
								miners1[i].delay = true;
								miners1[i].canfight = false;
								miners1[i].delayTime.restart().asSeconds();


							}
						}
					}
					else
					{
						miners1[i].row = 1;
					}
				}

				for (int k = 0; k < 8; k++)
				{
					platform.GetCollider().CheckCollision(apes1[k].GetCollider(), 1.0f, true);
					for (int i = 0; i < 8; i++)
					{
						if (i != k)
						{
							apes1[i].GetHitbox().CheckCollision(apes1[k].GetHitbox(), 1.0f, true);
						}
					}
					if (platform.GetCollider().CheckCollision(apes1[k].GetHitbox(), 1.0f, false))
					{
						apes1[k].canfight = true;
					}
					if (apes1[k].GetHitbox().CheckCollision(player.GetCollider(), 1.0f, false) and !apes1[k].delay and apes1[k].canfight == true)
					{
						if (armor <= 20.2f)
						{
							armor = 0;
							hp -= 20.2f;
						}
						else armor -= 20.2f;
						apes1[k].delay = true;
						apes1[k].delayTime.restart().asSeconds();
						apes1[k].canfight = false;
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int k = 0; k < 8; k++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							apes1[k].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpape1[k] -= 1;
								if (hpape1[k] == 0)
								{
									Score += 200; hpape1[k] -= 1;
								}
								break;
							}
						}
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int j = 0; j < 4; j++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							miners1[j].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpminer1[j] -= 1;
								if (hpminer1[j] == 0)
								{
									Score += 500; hpminer1[j] -= 1;
								}
								break;
							}
						}
					}
				}
			}
		}
		//////////////////// MAP 5 /////////////////////
		else if (map_cout == 5)
		{
			if (hpitem.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
				window.draw(text_potion);
				if (hpitem.row == 0)
				{
					hpitem.row = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && hpitem.row == 1) {
					itemeff.play(); hp = 202.0f; hpitem.row = 2;
				}
			}
			if (hp < 20.2f)
			{
				view.setCenter(Vector2f(600.0f, 337.5f));
				over.setPosition(Vector2f(0.0f, 0.0f));
				buttonre.set(Vector2f(600.0f, 595.5));
				if (charac == 2)
				{
					overtex.loadFromFile("sheet/gameover5ass.png");
				}
				else if (charac == 1)
				{
					overtex.loadFromFile("sheet/gameover5kn.png");
				}
				save.open("score.txt", ios::app);
				save << "\n" << enterName << " " << Score;
				save.close(); menumusic.stop(); gameovermusic.play();
				mode = 3; 
			}
			for (int i = 0; i < 3; i++) //room1
			{
				if (player.GetPosition().x > 2350.0f && player.GetPosition().x < 3580.0f && player.GetPosition().y < 1310.0f)
				{
					miners2[i].Update(deltaTime, miners2[i].row, player.GetPosition(), hpminer2[i]);
				}
				miners2[i].Draw(window);
			}
			for (int i = 0; i < 5; i++)
			{
				if (player.GetPosition().x > 2350.0f && player.GetPosition().x < 3580.0f && player.GetPosition().y < 1310.0f)
				{
					apes2[i].Update(deltaTime, row, player.GetPosition(), hpape2[i]);
				}
				apes2[i].Draw(window);
			}

			for (int i = 3; i < 4; i++) //room2
			{
				if (player.GetPosition().x > 4470.0f && player.GetPosition().x < 5250.0f && player.GetPosition().y < 1417.0f)
				{
					miners2[i].Update(deltaTime, miners2[i].row, player.GetPosition(), hpminer2[i]);
				}
				miners2[i].Draw(window);
			}
			for (int i = 5; i < 8; i++)
			{
				if (player.GetPosition().x > 4470.0f && player.GetPosition().x < 5250.0f && player.GetPosition().y < 1417.0f)
				{
					apes2[i].Update(deltaTime, row, player.GetPosition(), hpape2[i]);
				}
				apes2[i].Draw(window);
			}

			for (Platform& platform : map5)
			{
				platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, true);
				for (int i = 0; i < 4; i++)
				{
					platform.GetCollider().CheckCollision(miners2[i].GetCollider(), 1.0f, true);
					for (int k = 0; k < 4; k++)
					{
						if (i != k)
						{
							miners2[k].GetHitbox().CheckCollision(miners2[i].GetHitbox(), 1.0f, true);
						}
					}
					if (miners2[i].GetCollider().CheckCollision(player.GetCollider(), 1.0f, false))
					{
						miners2[i].row = 2;
						if (miners2[i].row == 2)
						{
							if (miners2[i].GetAtkbox().CheckCollision(player.GetCollider(), 1.0, false) and !miners2[i].delay and miners2[i].canfight == true)
							{
								if (armor <= 20.2f)
								{
									armor = 0;
									hp -= 20.2f;
								}
								else armor -= 20.2f;
								miners2[i].delay = true;
								miners2[i].canfight = false;
								miners2[i].delayTime.restart().asSeconds();


							}
						}
					}
					else
					{
						miners2[i].row = 1;
					}
				}

				for (int k = 0; k < 8; k++)
				{
					platform.GetCollider().CheckCollision(apes2[k].GetCollider(), 1.0f, true);
					for (int i = 0; i < 8; i++)
					{
						if (i != k)
						{
							apes2[i].GetHitbox().CheckCollision(apes2[k].GetHitbox(), 1.0f, true);
						}
					}
					if (platform.GetCollider().CheckCollision(apes2[k].GetHitbox(), 1.0f, false))
					{
						apes2[k].canfight = true;
					}
					if (apes2[k].GetHitbox().CheckCollision(player.GetCollider(), 1.0f, false) and !apes2[k].delay and apes2[k].canfight == true)
					{
						if (armor <= 20.2f)
						{
							armor = 0;
							hp -= 20.2f;
						}
						else armor -= 20.2f;
						apes2[k].delay = true;
						apes2[k].delayTime.restart().asSeconds();
						apes2[k].canfight = false;
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int k = 0; k < 8; k++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							apes2[k].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpape2[k] -= 1;
								if (hpape2[k] == 0)
								{
									Score += 200; hpape2[k] -= 1;
								}
								break;
							}
						}
					}
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (int j = 0; j < 4; j++) {
						if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
							miners2[j].GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
						{
							if (shot.shot)
							{
								shot.animation.currentImage.x = 0; shot.shot = false;
							}
							shot.Set(bullets[i].GetPosition());
							shot.Update(deltaTime);
							shot.Draw(window);
							if (shot.animation.currentImage.x == 3)
							{
								bullets.erase(bullets.begin() + i); hpminer2[j] -= 1;
								if (hpminer2[j] == 0)
								{
									Score += 500; hpminer2[j] -= 1;
								}
								break;
							}
						}
					}
				}
			}
		}
		/////////////////// MAP 6 //////////////////////////
		else if (map_cout == 6)
		{
			if (hpitem.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
				window.draw(text_potion);
				if (hpitem.row == 0)
				{
					hpitem.row = 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && hpitem.row == 1) {
					itemeff.play(); hp = 202.0f; hpitem.row = 2;
				}
			}
			if (hp < 20.2f)
			{
				view.setCenter(Vector2f(600.0f, 337.5f));
				over.setPosition(Vector2f(0.0f, 0.0f));
				buttonre.set(Vector2f(600.0f, 595.5));
				if (charac == 2)
				{
					overtex.loadFromFile("sheet/gameover6ass.png");
				}
				else if (charac == 1)
				{
					overtex.loadFromFile("sheet/gameover6kn.png");
				}
				save.open("score.txt", ios::app);
				save << "\n" << enterName << " " << Score;
				save.close(); gameovermusic.play(); menumusic.stop();
				mode = 3;
			}

			if (player.GetPosition().y > 2300.0f)
			{
				boss2.Update(deltaTime, row, player.GetPosition(), hpboss[1]);
			}
			boss2.Draw(window);

			for (Platform& platform : map6)
			{
				platform.GetCollider().CheckCollision(boss2.GetCollider(), 1.0f, true);
				platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, true);
				if (platform.GetCollider().CheckCollision(boss2.GetHitbox(), 1.0f, false))
				{
					boss2.canfight = true;
				}
				if (boss2.GetHitbox().CheckCollision(player.GetCollider(), 1.0f, false) and !boss2.delay and boss2.canfight == true)
				{
					if (armor <= 20.2f)
					{
						armor = 0;
						hp -= 40.4f;
					}
					else armor -= 101.0f;
					boss2.delay = true;
					boss2.delayTime.restart().asSeconds();
					boss2.canfight = false;
				}
				for (size_t i = 0; i < bullets.size(); i++)
				{
					if (platform.GetCollider().CheckCollision(bullets[i].GetCollider(), 1.0f, true) ||
						boss2.GetHitbox().CheckCollision(bullets[i].GetCollider(), 1.0f, true))
					{
						if (shot.shot)
						{
							shot.animation.currentImage.x = 0; shot.shot = false;
						}
						shot.Set(bullets[i].GetPosition());
						shot.Update(deltaTime);
						shot.Draw(window);
						if (shot.animation.currentImage.x == 3)
						{
							bullets.erase(bullets.begin() + i); hpboss[1] -= 1;
							if (hpboss[1] == 0)
							{
								Score += 1000; hpboss[1] -= 1;
							}
							break;
						}
					}
				}
			}
			for (Platform& platform : boss)
			{
				
				if (platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f, false)) {
					menumusic.openFromFile("sheet/sound/Soul Knight OST - Final Boss.ogg"); menumusic.play();
				}

			}
		}
		///////////////////////////////////////////////////
		revolver.Draw(window);
		if (map_cout != 3 && map_cout != 6)
		{
			if (gate.GetCollider().CheckCollision(player.GetCollider(), 0.0f, false))
			{
				window.draw(text_portal);
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					buttoneff.play();
					//loading.Draw(window);
					if (map_cout == 1)
					{
						map_cout = 2; hpitem.Set(Vector2f(2536.0f,3184.0f)); hpitem.row = 0;
						bg.loadFromFile("sheet/map 1-2.png"); menumusic.openFromFile("sheet/sound/Soul Knight OST - Forests.ogg"); menumusic.play();
						player.Set(playeroriginpos);
						
					}
					else if (map_cout == 2)
					{
						map_cout = 3; hpitem.Set(Vector2f(3296.0f, 3136.0f)); hpitem.row = 0;
						bg.loadFromFile("sheet/map 1-3 boss.png"); menumusic.openFromFile("sheet/sound/Soul Knight OST - Forests.ogg"); menumusic.play();
						player.Set(playeroriginpos);
					}
					
					else if (map_cout == 4)
					{
						map_cout = 5; hpitem.Set(Vector2f(3000.0f, 2816.0f)); hpitem.row = 0;
						bg.loadFromFile("sheet/map 2-2.png");
						menumusic.openFromFile("sheet/sound/Soul Knight OST - Glacier.ogg"); menumusic.play();
						playeroriginpos.x = 719.8;
						playeroriginpos.y = 923.9;
						player.Set(playeroriginpos);
					}
					else if (map_cout == 5)
					{
						map_cout = 6; hpitem.Set(Vector2f(3000.0f, 920.0f)); hpitem.row = 0;
						bg.loadFromFile("sheet/map 2-3.png");
						menumusic.openFromFile("sheet/sound/Soul Knight OST - Glacier.ogg"); menumusic.play();
						playeroriginpos.x = 719.8;
						playeroriginpos.y = 923.9;
						player.Set(playeroriginpos);
					}
				}
			}
		}
		if (map_cout == 3 && hpboss[0] <= 0)
		{
			if (gate.GetCollider().CheckCollision(player.GetCollider(), 0.0f, false))
			{
				
				window.draw(text_portal);
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					buttoneff.play();
					//loading.Draw(window);
					
					if (map_cout == 3)
					{
						map_cout = 4; hpitem.Set(Vector2f(4720.0f, 1920.0f)); hpitem.row = 0;
						bg.loadFromFile("sheet/map 2-1.png");
						menumusic.openFromFile("sheet/sound/Soul Knight OST - Glacier.ogg"); menumusic.play();
						playeroriginpos.x = 719.8;
						playeroriginpos.y = 923.9;
						player.Set(playeroriginpos);
					}
				}
			}
		}
		if (map_cout == 6 && hpboss[1] <= 0)
		{
			if (gate.GetCollider().CheckCollision(player.GetCollider(), 0.0f, false))
			{

				window.draw(text_portal);
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					buttoneff.play();
					if (map_cout == 6)
					{
						view.setCenter(Vector2f(600.0f, 337.5f));
						over.setPosition(Vector2f(0.0f, 0.0f));
						buttonre.set(Vector2f(600.0f, 595.5));
						if (charac == 2)
						{
							overtex.loadFromFile("sheet/WINNER6ass.png");
						}
						else if (charac == 1)
						{
							overtex.loadFromFile("sheet/WINNER6kn.png");
						}
						save.open("score.txt", ios::app);
						save << "\n" << enterName << " " << Score;
						save.close(); winner.play(); menumusic.stop();
						mode = 3;
					}
				}
			}
		}
		
		
		window.draw(stat);
		window.draw(HP);
		window.draw(ARMOR);
		window.draw(SCORE);
		window.draw(scores);
		window.draw(msprite);

		//window.draw(Bullet);

		window.display();
	}
	//////////////////////GAME OVER////////////////////////
	while (window.isOpen() && mode == 3)
	{
		window.setMouseCursorVisible(true);
		score_over.setPosition(Vector2f(400.0f,430.0f));
		scores.setPosition(score_over.getPosition().x + 350.0f , score_over.getPosition().y);
		scores.setCharacterSize(40);
		over.setTexture(overtex);
		deltaTime = clock.restart().asSeconds();
		sf::Event button;
		while (window.pollEvent(button))
		{
			switch (button.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		mousePosWindow = window.mapPixelToCoords((Mouse::getPosition(window)));
		buttonre.Update(deltaTime, mousePosWindow);

		if (Mouse::isButtonPressed(Mouse::Left) && debounce.getElapsedTime().asSeconds() > 0.5)
		{
			if (buttonre.GetPosition().x - mousePosWindow.x < 85.4f && mousePosWindow.x - buttonre.GetPosition().x < 85.4f && buttonre.GetPosition().y - mousePosWindow.y < 43.4f && mousePosWindow.y - buttonre.GetPosition().y < 43.4f)
			{
				buttoneff.play(); mode = 0; menumusic.openFromFile("sheet/sound/Soul Knight OST - Forests.ogg"); menumusic.play(); Score = 0;
				goto menu;
			}
			

		}
		window.setView(view);
		window.clear();
		window.draw(over);
		window.draw(score_over);
		window.draw(scores);
		buttonre.Draw(window);
		window.display();
	}

	/////////////////////////// HIGH SCORE ///////////////////////////
	while (window.isOpen() && mode == 4)
	{
		window.setMouseCursorVisible(true);

		buttonre.set(Vector2f(700.0f, 360.5));
		deltaTime = clock.restart().asSeconds();
		sf::Event button;
		while (window.pollEvent(button))
		{
			switch (button.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		mousePosWindow = window.mapPixelToCoords((Mouse::getPosition(window)));
		buttonre.Update(deltaTime, mousePosWindow);

		if (Mouse::isButtonPressed(Mouse::Left) && debounce.getElapsedTime().asSeconds() > 0.5)
		{
			if (buttonre.GetPosition().x - mousePosWindow.x < 85.4f && mousePosWindow.x - buttonre.GetPosition().x < 85.4f && buttonre.GetPosition().y - mousePosWindow.y < 43.4f && mousePosWindow.y - buttonre.GetPosition().y < 43.4f)
			{
				buttoneff.play(); mode = 0;
				goto menu;
			}


		}
		window.setView(view);
		view.setCenter(1200 / 2, 675 / 2);
		window.clear();
		window.draw(highscore);

		int cnt = 0;  //ประกาศตัวนับ
		for (vector<pair<int, string>>::iterator i = scoreboard.begin(); i != scoreboard.end(); ++i) {
			++cnt;
			if (cnt > 5) break;                       //เมื่อตัวนับเกิน 5 ให้จบการทำงาน
			                              //การตั้งค่า Font
			
			Text a, b;                                //ประกาศ Text
			a.setString(to_string(i->first));         //เนื่องจากค่าคะแนนเป็น integer จึงต้องทำการแปลงเป็น string ก่อนนำมาแสดงผล (first คือpair ตัวที่หนึ่ง =>int)
			a.setFont(font);                        //การตั้งค่า Font คะแนน
			a.setCharacterSize(40);                   //ตั้งค่าขนาด Font คะแนน
			a.setPosition(400, 120 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของคะแนน และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
			window.draw(a);                           //แสดงผลคะแนน
			b.setString(i->second);            // (second คือpair ตัวที่สอง =>string) 
			b.setFont(font);                        //การตั้งค่า Font ชื่อผู้เล่น
			b.setCharacterSize(40);                   //ตั้งค่าขนาด Font ชื่อผู้เล่น
			b.setPosition(100, 120 + (80 * cnt));      //ตั้งค่าตำแหน่งแสดงผลของชื่อผู้เล่น และเพิ่มค่าตำแหน่งให้ลงมาตัวละ 80 หน่วย
			window.draw(b);                           //แสดงผลชื่อผู้เล่น
		}
		buttonre.Draw(window);
		window.display();
	}

	
}





void map_object(vector<Platform>& map1, vector <Platform>& map2, vector <Platform>& map3, vector <Platform>& map4, vector <Platform>& map5, vector <Platform>& map6, vector <Platform>& boss) {
/////////////////////////ROOMBOSS////////////////////////////////////////////

	boss.push_back(Platform(nullptr, sf::Vector2f(270.0f, 50.0f), sf::Vector2f(3338.0f, 2139.0f)));
	boss.push_back(Platform(nullptr, sf::Vector2f(242.0f, 30.0f), sf::Vector2f(2967.0f, 2339.0f)));

/////////////////////////////////////////////////MAP1-1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	map1.push_back(Platform(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(575.0f, 840.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(972.5f, 460.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 142.0f), sf::Vector2f(1373.0f, 565.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 243.0f), sf::Vector2f(1373.0f, 1080.5f)));//roomstart
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(972.5f, 1145.0f)));

	map1.push_back(Platform(nullptr, sf::Vector2f(690.0f, 40.0f), sf::Vector2f(1795.0f, 979.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(690.0f, 40.0f), sf::Vector2f(1795.0f, 616.0f)));//ทางเดินแนวนอน

	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 142.0f), sf::Vector2f(2167.0f, 565.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(1653.0f, 40.0f), sf::Vector2f(3020.5f, 460.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 849.0f), sf::Vector2f(2167.0f, 1383.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(639.0f, 40.0f), sf::Vector2f(2513.5f, 1748.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(636.0f, 40.0f), sf::Vector2f(3529.0f, 1748.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 441.0f), sf::Vector2f(3874.0f, 690.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 579.0f), sf::Vector2f(3874.0f, 1518.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(690.0f, 40.0f), sf::Vector2f(4245.0f, 891.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(690.0f, 40.0f), sf::Vector2f(4245.0f, 1249.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 169.0f), sf::Vector2f(4617.0f, 826.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 249.0f), sf::Vector2f(4617.0f, 1353.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(5017.5f, 727.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(5017.5f, 1418.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 736.0f), sf::Vector2f(5418.0f, 1110.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1042.0f), sf::Vector2f(2860.0f, 2249.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1042.0f), sf::Vector2f(3184.0f, 2249.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 736.0f), sf::Vector2f(2648.0f, 3134.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(158.0f, 40.0f), sf::Vector2f(2754.0f, 2750.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(3316.5f, 2750.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(3048.5f, 3442.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 249.0f), sf::Vector2f(3449.0f, 3377.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 165.0f), sf::Vector2f(3449.0f, 2848.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(744.0f, 40.0f), sf::Vector2f(3848.0f, 2911.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(744.0f, 40.0f), sf::Vector2f(3848.0f, 3273.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 249.0f), sf::Vector2f(4247.0f, 3377.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 548.0f), sf::Vector2f(4247.0f, 2657.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1119.0f), sf::Vector2f(5048.0f, 2942.5f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(4647.5f, 2367.0f)));
	map1.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(4647.5f, 3442.0f)));

	/////////////////////////map 1-2////////////////////////////////////////////////

	map2.push_back(Platform(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(575.0f, 840.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(972.5f, 460.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 736.0f), sf::Vector2f(1369.0f, 840.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(700.5f, 1145.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(158.0f, 40.0f), sf::Vector2f(1263.0f, 1145.0f)));//room start

	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1687.0f), sf::Vector2f(833.0f, 1968.5f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1687.0f), sf::Vector2f(1157.0f, 1968.5f)));

	map2.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(700.5f, 2792.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(1289.5f, 2792.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(629.0f, 3174.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(1022.5f, 3482.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 250.0f), sf::Vector2f(1423.0f, 3417.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 162.0f), sf::Vector2f(1423.0f, 2887.0f)));

	map2.push_back(Platform(nullptr, sf::Vector2f(688.0f, 40.0f), sf::Vector2f(1794.0f, 2948.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(688.0f, 40.0f), sf::Vector2f(1794.0f, 3312.0f)));

	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 250.0f), sf::Vector2f(2165.0f, 3417.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 162.0f), sf::Vector2f(2165.0f, 2887.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(2565.5f, 3482.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 250.0f), sf::Vector2f(2966.0f, 3417.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 162.0f), sf::Vector2f(2966.0f, 2887.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(2245.5f, 2792.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(2833.5f, 2792.0f)));

	map2.push_back(Platform(nullptr, sf::Vector2f(743.0f, 40.0f), sf::Vector2f(3364.5f, 2948.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(743.0f, 40.0f), sf::Vector2f(3364.5f, 3312.0f)));

	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 250.0f), sf::Vector2f(3763.0f, 3417.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 162.0f), sf::Vector2f(3763.0f, 2887.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(4163.5f, 3482.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(4163.5f, 2792.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(4557.0f, 3174.0f)));

	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1072.0f), sf::Vector2f(2377.0f, 2276.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1072.0f), sf::Vector2f(2701.0f, 2276.0f)));


	map2.push_back(Platform(nullptr, sf::Vector2f(1653.0f, 40.0f), sf::Vector2f(2537.5f, 466.0f)));//ห้องใหญ่
	map2.push_back(Platform(nullptr, sf::Vector2f(639.0f, 40.0f), sf::Vector2f(2030.5f, 1760.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(636.0f, 40.0f), sf::Vector2f(3046.0f, 1760.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1338.0f), sf::Vector2f(1684.0f, 1151.0f)));
	map2.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1338.0f), sf::Vector2f(3391.0f, 1151.0f)));

	//////////////////////////Boss 1///////////////////////////////////////

	map3.push_back(Platform(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(575.0f, 840.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(972.5f, 460.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 736.0f), sf::Vector2f(1369.0f, 840.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(700.5f, 1145.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(158.0f, 40.0f), sf::Vector2f(1263.0f, 1145.0f)));//room start

	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1687.0f), sf::Vector2f(833.0f, 1968.5f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1687.0f), sf::Vector2f(1157.0f, 1968.5f)));

	map3.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(700.5f, 2792.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(1289.5f, 2792.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(40.0f, 736.0f), sf::Vector2f(629.0f, 3174.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(1022.5f, 3482.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 250.0f), sf::Vector2f(1423.0f, 3417.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 162.0f), sf::Vector2f(1423.0f, 2887.0f)));

	map3.push_back(Platform(nullptr, sf::Vector2f(1434.0f, 40.0f), sf::Vector2f(2167.0f, 2948.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(1434.0f, 40.0f), sf::Vector2f(2167.0f, 3312.0f)));

	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 250.0f), sf::Vector2f(2911.0f, 3417.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 162.0f), sf::Vector2f(2911.0f, 2887.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(747.0f, 40.0f), sf::Vector2f(3311.5f, 3482.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 736.0f), sf::Vector2f(3712.0f, 3174.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(3044.5f, 2792.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(211.0f, 40.0f), sf::Vector2f(3632.5f, 2792.0f)));

	
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 728.0f), sf::Vector2f(3177.0f, 2448.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 728.0f), sf::Vector2f(3500.0f, 2448.0f)));


	map3.push_back(Platform(nullptr, sf::Vector2f(1653.0f, 40.0f), sf::Vector2f(3336.5f, 810.0f)));//ห้องใหญ่
	map3.push_back(Platform(nullptr, sf::Vector2f(639.0f, 40.0f), sf::Vector2f(2829.5f, 2104.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(636.0f, 40.0f), sf::Vector2f(3845.0f, 2104.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1338.0f), sf::Vector2f(2483.0f, 1494.0f)));
	map3.push_back(Platform(nullptr, sf::Vector2f(54.0f, 1338.0f), sf::Vector2f(4190.0f, 1494.0f)));

	///////////////////////////map 2-1///////////////////////////////////////
	map4.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(720.5f, 562.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(720.5f, 1195.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 588.0f), sf::Vector2f(426.0f, 881.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 142.0f), sf::Vector2f(1015.0f, 658.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 194.0f), sf::Vector2f(1015.0f, 1125.0f)));

	map4.push_back(Platform(nullptr, sf::Vector2f(1267.0f, 40.0f), sf::Vector2f(1672.5f, 709.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(1267.0f, 40.0f), sf::Vector2f(1672.5f, 1048.0f)));

	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 436.0f), sf::Vector2f(2331.0f, 1246.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 390.0f), sf::Vector2f(2331.0f, 534.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(735.0f, 40.0f), sf::Vector2f(2724.5f, 313.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(735.0f, 40.0f), sf::Vector2f(2724.5f, 1437.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 100.0f), sf::Vector2f(2380.0f, 1370.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(2452.0f, 1395.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(244.0f, 5.0f), sf::Vector2f(2724.0f, 575.5f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 185.0f), sf::Vector2f(2871.0f, 485.5f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 350.0f), sf::Vector2f(2577.0f, 748.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(244.0f, 5.0f), sf::Vector2f(2724.0f, 1165.5f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 350.0f), sf::Vector2f(2871.0f, 993.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 185.0f), sf::Vector2f(2577.0f, 1255.5f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 436.0f), sf::Vector2f(3116.0f, 1242.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 390.0f), sf::Vector2f(3116.0f, 534.0f)));

	map4.push_back(Platform(nullptr, sf::Vector2f(932.0f, 40.0f), sf::Vector2f(3607.0f, 709.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(932.0f, 40.0f), sf::Vector2f(3607.0f, 1044.0f)));

	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 246.0f), sf::Vector2f(4097.0f, 606.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 292.0f), sf::Vector2f(4097.0f, 1170.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 836.0f), sf::Vector2f(5375.0f, 898.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(1228.0f, 40.0f), sf::Vector2f(4736.0f, 460.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(440.0f, 40.0f), sf::Vector2f(4343.0f, 1289.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(440.0f, 40.0f), sf::Vector2f(5127.0f, 1289.0f)));

	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 1221.0f), sf::Vector2f(4588.0f, 1880.5f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 1221.0f), sf::Vector2f(4882.0f, 1880.5f)));

	map4.push_back(Platform(nullptr, sf::Vector2f(196.0f, 40.0f), sf::Vector2f(4465.0f, 2471.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(196.0f, 40.0f), sf::Vector2f(5004.0f, 2471.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 830.0f), sf::Vector2f(4344.0f, 2911.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(50.0f, 830.0f), sf::Vector2f(5127.0f, 2911.0f)));
	map4.push_back(Platform(nullptr, sf::Vector2f(734.0f, 40.0f), sf::Vector2f(4735.0f, 3301.0f)));

	//////////////////// map 2-2 /////////////////////////
	map5.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(720.5f, 562.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(720.5f, 1195.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 588.0f), sf::Vector2f(426.0f, 881.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 142.0f), sf::Vector2f(1015.0f, 658.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 194.0f), sf::Vector2f(1015.0f, 1125.0f)));

	map5.push_back(Platform(nullptr, sf::Vector2f(1267.0f, 40.0f), sf::Vector2f(1672.5f, 709.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(1267.0f, 40.0f), sf::Vector2f(1672.5f, 1048.0f)));

	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 246.0f), sf::Vector2f(2330.0f, 606.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 292.0f), sf::Vector2f(2330.0f, 1174.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 246.0f), sf::Vector2f(3608.0f, 606.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 292.0f), sf::Vector2f(3608.0f, 1174.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(1228.0f, 40.0f), sf::Vector2f(2969.0f, 460.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(440.0f, 40.0f), sf::Vector2f(2576.0f, 1293.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(440.0f, 40.0f), sf::Vector2f(3360.0f, 1293.0f)));

	map5.push_back(Platform(nullptr, sf::Vector2f(826.0f, 40.0f), sf::Vector2f(4046.0f, 709.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(826.0f, 40.0f), sf::Vector2f(4046.0f, 1048.0f)));

	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 436.0f), sf::Vector2f(4484.0f, 1246.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 390.0f), sf::Vector2f(4484.0f, 534.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(735.0f, 40.0f), sf::Vector2f(4877.5f, 313.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(735.0f, 40.0f), sf::Vector2f(4877.5f, 1437.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 100.0f), sf::Vector2f(4533.0f, 1370.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(4605.0f, 1395.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(244.0f, 5.0f), sf::Vector2f(4877.0f, 575.5f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 185.0f), sf::Vector2f(5024.0f, 485.5f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 350.0f), sf::Vector2f(4730.0f, 748.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(244.0f, 5.0f), sf::Vector2f(4877.0f, 1165.5f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 350.0f), sf::Vector2f(5024.0f, 993.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 185.0f), sf::Vector2f(4730.0f, 1255.5f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 836.0f), sf::Vector2f(5269.0f, 1042.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 390.0f), sf::Vector2f(5269.0f, 534.0f)));

	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 977.0f), sf::Vector2f(2820.0f, 1761.5f))); // 2845
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 977.0f), sf::Vector2f(3115.0f, 1761.5f))); // 3090

	map5.push_back(Platform(nullptr, sf::Vector2f(389.0f, 40.0f), sf::Vector2f(2650.5f, 2230.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(389.0f, 40.0f), sf::Vector2f(3284.5f, 2230.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 1150.0f), sf::Vector2f(2431.0f, 2825.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 465.0f), sf::Vector2f(3504.0f, 3167.5f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 382.0f), sf::Vector2f(3504.0f, 2445.0f)));//2456
	map5.push_back(Platform(nullptr, sf::Vector2f(1024.0f, 40.0f), sf::Vector2f(2968.0f, 3345.0f)));


	map5.push_back(Platform(nullptr, sf::Vector2f(826.0f, 40.0f), sf::Vector2f(3941.0f, 2616.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(826.0f, 40.0f), sf::Vector2f(3941.0f, 2955.0f)));//4354

	map5.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(4671.5f, 2509.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(4671.5f, 3101.0f)));//4402
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 588.0f), sf::Vector2f(4964.0f, 2790.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 142.0f), sf::Vector2f(4379.0f, 2565.0f)));
	map5.push_back(Platform(nullptr, sf::Vector2f(50.0f, 194.0f), sf::Vector2f(4379.0f, 3032.0f)));

	/////////////////////////////// MAP 2-3 //////////////////////////////////////
	map6.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(720.5f, 562.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(539.0f, 40.0f), sf::Vector2f(720.5f, 1195.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 588.0f), sf::Vector2f(426.0f, 881.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 142.0f), sf::Vector2f(1015.0f, 658.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 194.0f), sf::Vector2f(1015.0f, 1125.0f)));

	map6.push_back(Platform(nullptr, sf::Vector2f(1267.0f, 40.0f), sf::Vector2f(1672.5f, 709.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(1267.0f, 40.0f), sf::Vector2f(1672.5f, 1048.0f)));

	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 246.0f), sf::Vector2f(2330.0f, 606.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 292.0f), sf::Vector2f(2330.0f, 1174.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 246.0f), sf::Vector2f(3608.0f, 606.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 292.0f), sf::Vector2f(3608.0f, 1174.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(1228.0f, 40.0f), sf::Vector2f(2969.0f, 460.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(440.0f, 40.0f), sf::Vector2f(2576.0f, 1293.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(440.0f, 40.0f), sf::Vector2f(3360.0f, 1293.0f)));

	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 977.0f), sf::Vector2f(2820.0f, 1761.5f))); // 2845
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 977.0f), sf::Vector2f(3115.0f, 1761.5f))); // 3090

	map6.push_back(Platform(nullptr, sf::Vector2f(389.0f, 40.0f), sf::Vector2f(2650.5f, 2230.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(389.0f, 40.0f), sf::Vector2f(3284.5f, 2230.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 1150.0f), sf::Vector2f(2431.0f, 2825.0f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 465.0f), sf::Vector2f(3504.0f, 3167.5f)));
	map6.push_back(Platform(nullptr, sf::Vector2f(50.0f, 382.0f), sf::Vector2f(3504.0f, 2445.0f)));//2456
	map6.push_back(Platform(nullptr, sf::Vector2f(1024.0f, 40.0f), sf::Vector2f(2968.0f, 3345.0f)));
}
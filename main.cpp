
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>
#include "Blub.h"
#define PI 3.14159265
using namespace std;

int main()
{
	int i;
	sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::None);
	sf::Time mainLoopClockTime;
	sf::Clock mainLoopClock;
	sf::CircleShape shape(5.f);
	shape.setFillColor(sf::Color::Green);

	Blub blubban = Blub(90.0, 30, 500, 500);
	Blub blubban2 = Blub(70.0, 20, 500, 500);
	sf::ConvexShape blubbanShape;
	sf::ConvexShape blubbanWannabe;
	blubbanShape.setPointCount(blubban.precision);
	blubbanShape.setFillColor(sf::Color(0, 255, 255, 255));
	blubbanWannabe.setPointCount(blubban2.precision);
	blubbanWannabe.setFillColor(sf::Color(0, 200, 200, 255));

	sf::Event event;
	bool wDown = false;
	bool aDown = false;
	bool sDown = false;
	bool dDown = false;

	for (i = 0; i < blubban2.precision; i++)
	{
		blubbanWannabe.setPoint(i, sf::Vector2f(blubban2.sideJoints[i].pos[0], blubban2.sideJoints[i].pos[1]));
	}

	mainLoopClock.restart();
	while (window.isOpen())
	{
		mainLoopClockTime = mainLoopClock.getElapsedTime();
		mainLoopClock.restart(); 

		

		
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed|| event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					wDown = false;
					blubban.moveCommand(0, 1000);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					aDown = false;
					blubban.moveCommand(1000, 0);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					sDown = false;
					blubban.moveCommand(0, -1000);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					dDown = false;
					blubban.moveCommand(-1000, 0);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W && !wDown)
				{
					wDown = true;
					blubban.moveCommand(0, -1000);
				}
				if (event.key.code == sf::Keyboard::A && !aDown)
				{
					aDown = true;
					blubban.moveCommand( -1000, 0);
				}
				if (event.key.code == sf::Keyboard::S && !sDown)
				{
					sDown = true;
					blubban.moveCommand(0, 1000);
				}
				if (event.key.code == sf::Keyboard::D && !dDown)
				{
					dDown = true;
					blubban.moveCommand(1000, 0);
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					Blub blubban3 = Blub(blubban, blubban2, 40);
					blubbanShape.setPointCount(blubban3.precision);
					blubban = blubban3;
					blubbanWannabe.setPointCount(0);
				}
			}
			


			//-----------------------------------------------------------
			
		}

		blubban.move(mainLoopClockTime.asMicroseconds());
		shape.setPosition(blubban.centerJoint.pos[0], blubban.centerJoint.pos[1]);
		for (i = 0; i < blubban.precision; i++)
		{
			blubbanShape.setPoint(i, sf::Vector2f(blubban.sideJoints[i].pos[0], blubban.sideJoints[i].pos[1]));
		}
		
		


		window.clear();
		window.draw(blubbanShape);
		window.draw(blubbanWannabe);
		window.draw(shape);
		window.display();
	}

	return 0;
}
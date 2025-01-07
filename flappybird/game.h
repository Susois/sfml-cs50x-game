#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<ctime>
#include<cstdlib>

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>

class game
{ 
private:

public:
	game();
	virtual ~game();

	//functions
	void updatesfmlevents();
	void update();
	void render();
	void run();


};
#endif 
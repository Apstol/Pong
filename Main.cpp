#include <stdexcept>
#include <iostream>

#include "Game.hpp"

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (const std::exception& exception)
	{
		std::cout << "ERROR: " << exception.what() << std::endl;
	}	
}

#include "Game.h"

Game::Game()
{
	while (!GameOver());
	cout << "Game Over!\n";
}
bool Game::GameOver()
{
	steady_clock::time_point t1 = steady_clock::now();
	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
	while (time_span.count() <= .101) //Delay
	{
		t2 = steady_clock::now();
		time_span = duration_cast<duration<double> >(t2 - t1);
	}
	if (_kbhit()) //Checking whether a button was hit or not
	{
		char c = _getch();
		c = _getch();
		return B.Move(c);
	}
	return B.Move(0); //otherwise move the same latest move
		
}



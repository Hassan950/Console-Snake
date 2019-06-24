#include "Board.h"
Board::Board()
{
	Score = 0;
	Food = { 0, 0 };
	cnsl = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < Width; i++)
	{
		B[0][i] = 1;
		B[Height - 1][i] = 1;
	}
	for (int i = 0; i < Height; i++)
	{
		B[i][0] = 1;
		B[i][Width - 1] = 1;
	}
	s.head = { Height / 2, Width / 2 };
	s.ntail = 0;
	last = 0;
	GenerateFood();
	Print();
}
void Board::GenerateFood()
{
	srand(time(NULL));
	int x, y;

	//food can neither be on snake's body nor the wall
	do
	{
		x = 0, y = 0;
		while (x <= 0 || x >= Width - 1) x = rand() % Width;
		while (y <= 0 || y >= Height - 1) y = rand() % Height;
	} while (B[y][x] != 0);
	B[y][x] = 4;
	Food = { y, x };
}
void Board::Clear()
{
	for (int i = 1; i < Height - 1; i++)
	{
		for (int j = 1; j < Width - 1; j++)
		{
			B[i][j] = 0;
		}
	}
	B[Food.first][Food.second] = FOOD;
}
void Board::Print()
{
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			switch (B[i][j])
			{
			case WALL:
				cout << '#';
				break;
			case SNK:
				cout << 'o';
				break;
			case EMP:
				cout << ' ';
				break;
			case HEAD:
				cout << 'O';
				break;
			case FOOD:
				cout << '$';
				break;
			}
		}
		cout << endl;
	}
}

void Board::Update()
{
	//seting console cursor to the beginning to overwrite the old board
	SetConsoleCursorPosition(cnsl, { 0, 0 });

	//printing
	Print();
	cout << "Score : " << Score << endl;
}
bool Board::Move(int Key)
{
	//Checking if input is an arrow key
	//Checking if snake is capable of moving in the input direction or not
	//if not move the same latest move
	if (((Key != LEFT && Key != UP && Key != RIGHT && Key != DOWN) || 
		((Key == UP && last == DOWN) || (Key == DOWN && last == UP) || (Key == RIGHT && last == LEFT) || (Key == LEFT && last == RIGHT))))
	{
		Key = last;
	}
	
	//moving
	switch (Key)
	{
	case UP:
		s.history.push_back(s.head);
		s.head = { s.head.first + -1, s.head.second + 0 };
		break;
	case DOWN:
		s.history.push_back(s.head);
		s.head = { s.head.first + 1, s.head.second + 0 };
		break;
	case LEFT:
		s.history.push_back(s.head);
		s.head = { s.head.first + 0, s.head.second + -1 };
		break;
	case RIGHT:
		s.history.push_back(s.head);
		s.head = { s.head.first + 0, s.head.second + 1 };
		break;
	default:
		break;
	}

	//storing the new move
	last = Key;

	//if snake has found the food increase score and tail length
	if (B[s.head.first][s.head.second] == FOOD) s.ntail++, Score += 10;

	//if snake has gone into a wall or its body game over
	if (B[s.head.first][s.head.second] == SNK || B[s.head.first][s.head.second] == WALL) 
		return true; //game over
	
	//clearing the board to print a new one
	Clear();

	//Determine the new head location
	B[s.head.first][s.head.second] = HEAD;

	//Determining the tails location (if any)
	for (int i = (int)s.history.size() - 1; i >= (int)s.history.size() - s.ntail; i--) 
		B[s.history[i].first][s.history[i].second] = SNK;

	//if food is already eaten Generate a new one
	if (B[Food.first][Food.second] != FOOD) 
		GenerateFood();

	//now update to print
	Update();

	//game is still not over
	return false;
}

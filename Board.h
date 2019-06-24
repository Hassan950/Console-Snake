#pragma once
#include <iostream>
#include <time.h>
#include <chrono>
#include <Windows.h>
#include "Defs.h"
using namespace std;
using namespace std::chrono;
class Board
{
	int B[Height][Width];
	HANDLE cnsl;
	pair<int, int> Food;
	int last;
	Snake s;
	int Score;
public:
	Board();
	void GenerateFood();
	void Print();
	void Update();
	bool Move(int Key);
	void Clear();
};


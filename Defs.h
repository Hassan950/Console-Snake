#pragma once
#include <algorithm>
#include <vector>
#include <conio.h>
#include <iomanip> 
using namespace std;
#define Width 20
#define Height 20
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

struct Snake
{
	pair<int, int> head;
	int ntail;
	vector<pair<int, int> >history;
};
enum Element
{
	EMP,
	WALL,
	SNK,
	HEAD,
	FOOD,
	Ecnt
};

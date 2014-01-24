#pragma once
#include <string>

class map
{
public:
	map(void);
	~map(void);

	char map_array[50*10][50*10];
	void game_map();
	void parser();
};


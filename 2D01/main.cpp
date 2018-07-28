#include <iostream>
#include <string>
using namespace std;

char getInput(char c)
{
	printf("w:up, s:down, d:right, a:left\n>>");
	cin >> c;
	return c;
}

int findPlayerPosition(string map, int w, int h)
{
	for (int i = 0; i < w*h; i++)
	{
		if (map[i] == 'P')
		{
			return i;
		}
	}
}

int fingGoalPosition(string map, int w, int h)
{
	for (int i = 0; i < w*h; i++)
	{
		if (map[i] == '.')
		{
			return i;
		}
	}
}

int nextPosition(char c, int p, int w)
{
	int nextP = p;

	if (c == 'w') nextP = p - w;
	else if (c == 's') nextP = p + w;
	else if (c == 'd') nextP = p + 1;
	else if (c == 'a') nextP = p - 1;

	return nextP;
}

int nextNextPosition(char c, int p, int w)
{
	int nextNextP = p;

	if (c == 'w') nextNextP = p - w * 2;
	else if (c == 's') nextNextP = p + w * 2;
	else if (c == 'd') nextNextP = p + 2;
	else if (c == 'a') nextNextP = p - 2;

	return nextNextP;
}

string updateGame(string map, int g, int w, int h, char c)
{
	int p = findPlayerPosition(map, w, h);
	int nextP = nextPosition(c, p, w);
	int nextNextP = nextNextPosition(c, p, w);

	if (map[nextP] == 'o' && map[nextNextP] != '#')
	{
		if (map[nextNextP] == '.') cout << "\n\n!!!!!!\n!GOAL!\n!!!!!!\n\n" << endl;
		map[nextNextP] = 'o';
		map[nextP] = 'P';
		map[p] = ' ';
	}
	else if (map[nextP] != '#' && map[nextP] != 'o')
	{
		map[nextP] = 'P';
		map[p] = ' ';
	}
	//draw goal position
	if (map[g] == ' ') map[g] = '.';

	return map;
}

void draw(string map, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			cout << map[i*w + j];
		}
		cout << endl;
	}
}

int main()
{
	char c = ' ';
	const int w = 10;
	const int h = 9;
	string map = 
		"##########"
		"#  .     #"
		"# #o## P #"
		"# #  # # #"
		"# ## # # #"
		"# #  # # #"
		"#   # ## #"
		"# # #    #"
		"##########";
	int g = fingGoalPosition(map, w, h);

	draw(map, w, h);

	while (c != 'q')
	{
		c = getInput(c);
		map = updateGame(map, g, w, h, c);
		draw(map, w, h);
	}

	return 0;
}
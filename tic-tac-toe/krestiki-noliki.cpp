#include "pch.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <tuple>
#include <string>

using namespace std;
class Game
{
public:
	int checknum(int num)
	{
		if ((num >= 2) && (num < 20))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	void Massiv(char **mass, int row1, int col1, int num1)
	{
		col = col1;
		row = row1;
		num = num1;
		massiv = new char*[col];
		for (int i = 0; i < col; i++)
		{
			massiv[i] = new char[row];
		}
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				massiv[i][j] = mass[i][j];
			}
		}
		playermass = new string*[num];
		for (int i = 0; i < num; i++)
		{
			playermass[i] = new string[num];
		}
		Aimass = new string*[num];
		for (int i = 0; i < num; i++)
		{
			Aimass[i] = new string[num];
		}
	}
	void Delete()
	{
		for (int i = 0; i < col; i++)
		{
			delete[] massiv[i];
		}
		for (int i = 0; i < num; i++)
		{
			delete[] Aimass[i];
		}
		for (int i = 0; i < num; i++)
		{
			delete[] playermass[i];
		}
	}
	void RealTime()
	{
		//system("cls");
		for (int i = 1; i <= col; i++)
		{
			for (int j = 1; j <= row; j++)
			{
				cout << "|" << "-" << i - 1 << j - 1 << "-" << "|";
			}
			cout << endl;
		}
		cout << endl << endl;
		cout << "Realtime situation" << endl;
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				cout << "|" << "-" << massiv[i][j] << "-" << "|";
			}
			cout << endl;
		}
	}
	char victorycheck()
		{
		for (int i = 0; i < col - num + 1; i++) {
			for (int j = 0; j < row - num + 1; j++) {
				if (checkdiaog('X', i, j) || checkLine('X', i, j))
				{
					return 'X';
				}
				if (checkdiaog('0', i, j) || checkLine('0', i, j))
				{
					return '0';
				}
			}
		}
			int k = 0;
			for (int i = 0; i < col; i++)
			{
				for (int j = 0; j < row; j++)
				{
					if (massiv[i][j] != '.')
					{
						if (k == col * row)
						{
							return '1';
						}
						k++;
					}
				}
			}
			return '2';
		}
	bool checkdiaog(char sym, int offsetX, int offsetY)
		{
			bool toright = true;
			bool toleft = true;
			for (int i = 0; i < num; i++)
			{
				toright = toright & (massiv[i + offsetX][i + offsetY] == sym);
				toleft = toleft & (massiv[num - i - 1 + offsetX][i + offsetY] == sym);
			}
			if ((toright) || (toleft))
			{
				return true;
			}
			return false;
		}
	bool checkLine(char sym, int offsetX, int offsetY)
		{
			bool colum;
			bool rows;
			for (int i = offsetX; i < num + offsetX; i++)
			{
				colum = true;
				rows = true;
				for (int j = offsetY; j < num + offsetY; j++)
				{
					colum = colum & (massiv[j][i] == sym);
					rows = rows & (massiv[i][j] == sym);
				}
				if ((colum) || (rows))
				{
					return true;
				}
			}
			return false;
		}
	std::tuple<int, int, int> max(int alpha, int beta)
		{
			int maxv = -2;
			int px = 0;
			int py = 0;
			int minx;
			int miny;
			int m;
			char result = victorycheck();
			if (result == 'X')
			{
				return std::make_tuple(-1, 0, 0);
			}
			else if (result == '0')
			{
				return std::make_tuple(1, 0, 0);
			}
			else if (result == '1')
			{
				return std::make_tuple(0, 0, 0);
			}
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (massiv[i][j] == '.')
					{
						massiv[i][j] = '0';
						std::tie(m, minx, miny) = min(alpha, beta);
						cout << "m:  " << m << ">" << "Score maxv: " << maxv << ", cordin = " << i << j << endl;
						if (m > maxv)//вот тут
						{
							maxv = m;
							px = i;
							py = j;
							RealTime();
						}
						massiv[i][j] = '.';
						if (maxv >= beta)
						{
							return std::make_tuple(maxv, px, py);
						}
						if (maxv > alpha)
						{
							alpha = maxv;
						}
					}
				}
			}
			return std::make_tuple(maxv, px, py);
		}
	std::tuple<int, int, int> min(int alpha, int beta)
		{
			int minv = 2;
			int qx = 0;
			int qy = 0;
			int maxx;
			int maxy;
			int m;
			char result = victorycheck();
			if (result == 'X')
			{
				return std::make_tuple(-1, 0, 0);
			}
			else if (result == '0')
			{
				return std::make_tuple(1, 0, 0);
			}
			else if (result == '1')
			{
				return std::make_tuple(0, 0, 0);
			}
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (massiv[i][j] == '.')
					{
						massiv[i][j] = 'X';
						std::tie(m, maxx, maxy) = max(alpha, beta);
						if (m < minv)
						{
							minv = m;
							qx = i;
							qy = j;
						}
						massiv[i][j] = '.';
						if (minv <= alpha)
						{
							return std::make_tuple(minv, qx, qy);
						}
						if (minv < beta)
						{
							beta = minv;
						}
					}
				}
			}
			return std::make_tuple(minv, qx, qy);
		}
	int Player1(string kordin, int kor1, int kor2)
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if ((kordin == playermass[i][j]) || (kordin == Aimass[i][j]))
				{
					return 1;
				}
				else
				{
					massiv[kor1][kor2] = 'X';
					playermass[i][j] = kordin;
					return 0;
				}
			}
		}
		return 2;
	}
	void Player2()
	{
		/*for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				if ((kordin == playermass[i][j]) || (kordin == Aimass[i][j]))
				{
					return 1;
				}
				else
				{
					massiv[kor1][kor2] = '0';
					Aimass[i][j] = kordin;
					return 0;
				}
			}
		}
		return 2;*/
			int m;
			int px = 0;
			int py = 0;
			std::tie(m, px, py) = max(-2, 2);
			massiv[px][py] = '0';
	}
	private:
		char **massiv;
		string **playermass;
		string **Aimass;
		int row;
		int col;
		int num;
	};
int main()
{
	Game game;
	int col;
	int row;
	int num;
	string kordin;
	int kor1;
	int kor2;
	std::cout << "Put the number of colums: ";
	std::cin >> col;
	std::cout << "Put number of rows: ";
	std::cin >> row;
	std::cout << "Please,put the number of symbols,which your need to win: ";
	std::cin >> num;
	char **mass = new char*[col];
	for (int i = 0; i < col; i++)
	{
		mass[i] = new char[row];
	}
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			mass[i][j] = '.';
		}
	}
	game.Massiv(mass, row, col, num);
	while (game.checknum(num) != 0)
	{
		if (game.checknum(num) == 1)
		{
			std::cout << "Your make a mistake,you must put the number between 2 and 19: ";
			std::cin >> num;
		}
	}
	game.RealTime();
	int step = 1;
	std::cin.ignore(std::numeric_limits<size_t>::max(), '\n');
	for (int i = 0; i < row*col; i++)
	{
		if (step % 2)
		{
			std::cout << endl << "You" << endl;
			std::cout << "Put your cordinates: ";
			getline(cin, kordin);
			if (kordin.length() == 2)
			{
				kor1 = stoi(kordin.substr(0, 1));
				kor2 = stoi(kordin.substr(1, 2));
			}
			else if (kordin.length() == 4)
			{
				kor1 = stoi(kordin.substr(0, 2));
				kor2 = stoi(kordin.substr(2, 4));
			}
			game.Player1(kordin, kor1, kor2);
			game.RealTime();
		}
		else
		{
			cout << endl << "Computer" << endl;
			game.Player2();
			game.RealTime();
		}
		if (step >= (num * 2) - 1)
		{
			char prov = game.victorycheck();
			if (prov == 'X')
			{
				cout << "You win the game" << endl;
				break;
			}
			else if (prov == '0')
			{
				cout << "Computer win the game" << endl;
				break;
			}
		}
		step++;
	}
	for (int i = 0; i < col; i++)
	{
		delete[] mass[i];
	}
	game.Delete();
	return 0;
}
#include <SFML/Graphics.hpp>
using namespace sf;

class Figure {
private:
	const int figures[7][4] =
	{
		1,3,5,7,
		2,4,5,7, 
		3,5,4,6, 
		3,5,4,7, 
		2,3,5,7, 
		3,5,7,6, 
		2,3,4,5, 
	};
	static const int M = 20;
	static const int N = 10;
	int colorNum = 1, n = rand() % 7;
public:
	struct Point
	{
		int x, y;
	} a[4], b[4];
	
	int field[M][N] = { 0 }; 
	double timer = 0, delay = 0.3;

	int getColor() { return colorNum; }
	int getHeight() { return M; }
	int getWeight() { return N; }

	bool check()
	{
		for (int i = 0; i < 4; i++)
			if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false;
			else if (field[a[i].y][a[i].x]) return false;
		return true;
	};
	void Move(int x) {
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += x; }
		if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
	}
	void Rotate() {
		Point p = a[1];
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!check()) { for (int i = 0; i < 4; i++) a[i] = b[i]; }
	}
	void Fall() {
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
			if (!check())
			{
				for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
				colorNum = 1 + rand() % 7;
				n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			timer = 0;
		}
	}
	void FirstAppear() {
		n = rand() % 7;
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}
	}
};
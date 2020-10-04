#include<stdio.h>
#include<Windows.h>
#include<conio.h>
void draw_ship(int, int);
void erase_ship(int, int);
void setcursor(bool);
void setcolor(int, int);
void move(int*, int*);
void shoot(int, int);
int main()
{
	setcursor(0);

	int x = 38, y = 20;
	move(&x, &y);
	return 0;
}

void draw_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(2, 4);
	printf(" <-0-> ");
}
void erase_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(1, 0);
	printf("       ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void shoot(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(2, 4);
	printf("*");
}
void move(int* x, int* y)
{
	int check = 5;
	char ch = 'null';
	draw_ship(*x, *y);
	do
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 'a' and *x > 0)
			{
				while (*x > 0)
				{
					if (_kbhit())
					{
						ch = _getch();
						if (ch == 's')
						{
							ch = 'null';
							break;
						}
					}
					erase_ship(*x, *y);
					draw_ship(-- * x, *y);
					Sleep(70);
				}
			}
			if (ch == 'd' and *x < 80)
			{
				while (*x < 80)
				{
					if (_kbhit())
					{
						ch = _getch();
						if (ch == 's')
						{
							ch = 'null';
							break;
						}
					}
					erase_ship(*x, *y);
					draw_ship(++ * x, *y);
					Sleep(70);
				}
			}
			if (ch == 'w' and *y > 0)
			{
				erase_ship(*x, *y);
				draw_ship(*x, -- * y);
			}
			if (ch == 's' and *y < 24)
			{
				erase_ship(*x, *y);
				draw_ship(*x, ++ * y);
			}
			if (ch == ' ' && check > 0)
			{
				int i = 0;
				int bullet_x[5];
				bullet_x[0] = *x + 3;
				int bullet_y[5];
				bullet_y[0] = *y - 1;
				while (bullet_y[i] > 0)
				{
					erase_ship(bullet_x[0], bullet_y[0]);
					shoot(bullet_x[0], --bullet_y[0]);
					if (_kbhit())
					{
						ch = _getch();
						if (ch == ' ')
						{
							bullet_x[i] = *x + 3;
							bullet_y[i] = *y - 1;
							erase_ship(bullet_x[i], bullet_y[i]);
							shoot(bullet_x[i], --bullet_y[i]);
							if (bullet_y[i] == 0)
							{
								erase_ship(bullet_x[i], 0);
							}
						}
					}
					Sleep(70);
					if (bullet_y == 0)
					{
						erase_ship(bullet_x[i], 0);
					}
				}
			}
			fflush(stdin);
		}
		Sleep(70);
	} while (ch != 'x');
}

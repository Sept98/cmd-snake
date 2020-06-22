#include<iostream>
#include<ctime>
#include<windows.h>
#include<deque>
#include<conio.h>
#include<ctime>
using namespace std;
#define LEFT 5
#define RIGHT 115
#define UP 1
#define DOWN 28
#define STD_OUTPUT_HANDLE ((DWORD)-11)

/*
方向定义：
1：上
2：下
3：左
4：右
*/

void cursor(int x, int y)//确定光标位置
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class snake
{
public:
	int direction;//记方向
	int score;//记得分
	void stage();//在屏幕输出舞台
	int score_add();//得分增加
	void score_show();//显示得分
	int operate_start();//开始操作项目选择
	void operate_end();//结束操作项目
	bool ended();//游戏失败判断标准
	deque<deque<int>> pos;//储存位置
	void generate();//产生蛇头
	int speed();//蛇头运动速度
	void show();//显示蛇身
	int item;//操作项目
	snake();//构造函数初始化item
};

class seed
{
public:
	seed();//构造函数
	int seed_x;
	int seed_y;
	void generator(snake&s);//生成食物
};

snake::snake()
{
	item = 49;
}

seed::seed()
{
	seed_x = 0;
	seed_y = 0;
}

void snake::show()
{
	for (int i = 0; i <= pos.size() - 1; i++)
	{
		cursor(pos[i][0], pos[i][1]);
		std::cout << "*";
	}
	cursor(0, 0);
}

void snake::score_show()
{
	cursor(50, 1);
	std::cout << "Your score is : " << score;
	cursor(5000, 5000);
}

int snake::speed()
{
	int velocity = 0;
	if (pos.size() >= 1 && pos.size() <= 5)
	{
		velocity = 500;
	}
	else if (pos.size() > 5 && pos.size() <= 10)
	{
		velocity = 400;
	}
	else if (pos.size() > 10 && pos.size() <= 16)
	{
		velocity = 300;
	}
	else if (pos.size() > 16 && pos.size() <= 20)
	{
		velocity = 200;
	}
	else if (pos.size() > 20 && pos.size() <= 30)
	{
		velocity = 150;
	}
	else
	{
		velocity = 120;
	}
	return velocity;
}

bool snake::ended()
{
	int decide = 1;
	for (int i = 1; i <= pos.size() - 1; i++)
	{
		if (pos[0][0] == pos[i][0] && pos[0][1] == pos[i][1])
		{
			decide = 0;
		}
	}

	if (pos[0][0] == LEFT || pos[0][0] == RIGHT - 1 || pos[0][1] == UP + 1 || pos[0][1] == DOWN)
	{
		decide = 0;
	}

	if (decide == 0)
	{
		return false;
	}
	else{ return true; }
}

void snake::generate()
{
	deque<int>n;
	cursor(52, 17);
	std::cout << "*";
	n.push_back(52);
	n.push_back(17);
	n.push_back(1);
	pos.push_back(n);
}

void seed::generator(snake&s)
{
	int judge = 0;
	srand(time(NULL));
	if (s.pos.size() > 1)
	{
		while (judge != 2)
		{
			seed_x = rand() % 110 + 5;
			seed_y = rand() % 27 + 4;
			for (int i = 0; i != s.pos.size() - 1; i++)
			{
				if ((s.pos[i][0] == seed_x&&s.pos[i][1] == seed_y) || (seed_x <= LEFT) || (seed_x >= RIGHT - 1) || (seed_y <= UP) || (seed_y >= DOWN))
				{
					judge = 1;
				}
				else
				{
					judge = 2;
				}
			}
		}
	}
	else
	{
		while (judge != 2)
		{
			seed_x = rand() % 110 + 4;
			seed_y = rand() % 27 + 1;
			if ((seed_x <= LEFT) || (seed_x >= RIGHT - 1) || (seed_y <= UP) || (seed_y >= DOWN))
			{judge = 1;}
			else{ judge = 2; }
		}
	}
	cursor(seed_x, seed_y);
	std::cout << "*";
	cursor(0, 0);
}

int snake::operate_start()
{
	char CHOOSE[] = "choose 1 & 2:";
	char START[] = "1.Start";
	char CLOSE[] = "2.Close";
	item = 0;
	while (item != 1 || item != 2)
	{
		system("cls"); stage();
		cursor(52, 11);
		cout << "↑(W)    ↓(S)    ←(A)    →(D)";
		cursor(52, 13);
		for (int i = 0; i <= 6; i++)
		{
			Sleep(100);
			std::cout << START[i];
		}
		cursor(52, 15);
		for (int i = 0; i <= 6; i++)
		{
			Sleep(100);
			std::cout << CLOSE[i];
		}
		cursor(52, 17);
		for (int i = 0; i <= 12; i++)
		{
			Sleep(100);
			std::cout << CHOOSE[i];
		}
		item = _getch();
		cursor(52, 19);
		if (item == 49){ system("cls"); stage(); break; }
		else if (item == 50){ break; exit(0); }
		else{ std::cout << "Please select 1 & 2"; }
		Sleep(2000);
	}
	return item;
}

void snake::operate_end()
{
	char CHOOSE[] = "Game over";
	system("cls");
	stage();
	cursor(46, 13);
	for (int i = 0; i <= 8; i++)
	{
		Sleep(100);
		std::cout << CHOOSE[i];
	}
	cursor(46, 14);
}

void snake::stage()
{
	for (int k = 0; k <= 44; k++)
	{
		std::cout << " ";
	}
	std::cout << "Welcome to Gluttonous Snake";
	for (int j = 1; j <= DOWN; j++)//j表示列
	{
		for (int i = 1; i <= RIGHT; i++)//i表示行
		{
			if (((i == LEFT + 1) && (j>UP)) || ((i == RIGHT) && (j>UP)) || ((j == UP + 1) && (i>LEFT)) || ((j == DOWN) && (i>LEFT)))
			{
				std::cout << "+";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
}

int snake::score_add()
{
	score += 100;
	return score;
}

void eat(seed&se, snake&s)
{
	if (se.seed_x == s.pos[0][0] && se.seed_y == s.pos[0][1])
	{
		s.score_add();
		se.generator(s);
	}
}

void move(seed&se, snake&s)
{
	int judge = 0;
	int de = 0;
	deque<int>ad;
	if (s.pos.size() >= 2)
	{
		de = s.pos[0][2];
	}
	char dir = ' ';
	int t = clock();
	while (clock() - t <= s.speed())
	{
		if (_kbhit())
		{
			dir = _getch();
			break;
		}
	}

	if ((dir == 'w'&& de != 2))
	{
		ad.push_back(s.pos[0][0]);
		ad.push_back(s.pos[0][1] - 1);
		ad.push_back(1);
		s.pos.push_front(ad);
		judge = 1;
	}
	else if ((dir == 's'&& de != 1))
	{
		ad.push_back(s.pos[0][0]);
		ad.push_back(s.pos[0][1] + 1);
		ad.push_back(2);
		s.pos.push_front(ad);
		judge = 1;
	}
	else if ((dir == 'a'&& de != 4))
	{
		ad.push_back(s.pos[0][0] - 1);
		ad.push_back(s.pos[0][1]);
		ad.push_back(3);
		s.pos.push_front(ad);
		judge = 1;
	}
	else if ((dir == 'd'&& de != 3))
	{
		ad.push_back(s.pos[0][0] + 1);
		ad.push_back(s.pos[0][1]);
		ad.push_back(4);
		s.pos.push_front(ad);
		judge = 1;
	}

	if (dir != 'w'&&dir != 's'&&dir != 'a'&&dir != 'd'&&s.pos.size()>=2)
	{

		if (s.pos[0][2] == 1)
		{
			ad.push_back(s.pos[0][0]);
			ad.push_back(s.pos[0][1] - 1);
			ad.push_back(1);
			s.pos.push_front(ad);
			judge = 1;
		}
		else if (s.pos[0][2] == 2)
		{
			ad.push_back(s.pos[0][0]);
			ad.push_back(s.pos[0][1] + 1);
			ad.push_back(2);
			s.pos.push_front(ad);
			judge = 1;
		}
		else if (s.pos[0][2] == 3)
		{
			ad.push_back(s.pos[0][0] - 1);
			ad.push_back(s.pos[0][1]);
			ad.push_back(3);
			s.pos.push_front(ad);
			judge = 1;
		}
		else if (s.pos[0][2] == 4)
		{
			ad.push_back(s.pos[0][0] + 1);
			ad.push_back(s.pos[0][1]);
			ad.push_back(4);
			s.pos.push_front(ad);
			judge = 1;
		}
	}

	if (judge == 1)
	{
		cursor(s.pos[0][0], s.pos[0][1]);
		std::cout << "*";
		if (se.seed_x != s.pos[0][0] || se.seed_y != s.pos[0][1])
		{
			cursor(s.pos[s.pos.size() - 1][0], s.pos[s.pos.size() - 1][1]);
			std::cout << " ";
			s.pos.pop_back();
		}
	}
}

void main()
{
	int decide = 0;
	snake viper;
	seed mi;
	if (viper.operate_start() == 49)
	{
		mi.generator(viper);
		viper.generate();
		cursor(5000, 5000);
		while (viper.ended())
		{
			move(mi, viper);
			eat(mi, viper);
			viper.score_show();
		}
		for (int ji = 0; ji <= 2; ji++)//失败
		{
			system("cls");
			viper.stage();
			for (int i = 0; i <= viper.pos.size() - 1; i++)
			{
				cursor(viper.pos[i][0], viper.pos[i][1]);
				std::cout << "*";
			}
			Sleep(100);
		}
		viper.operate_end();
	}
	else
	{
		exit(0);
	}
}
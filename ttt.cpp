
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
using namespace std;

//棋盘的三种状态
enum chess_grid_state { None, human, computer };

//胜利
const int win[8][3] = { {0,1,2},{3,4,5}, {6,7,8}, {0,3,6}, {1,4,7} , {2,5,8}, {0,4,8}, {2,4,6} };


class ttt {
public:
	ttt() {
		reset();
	};
	void play() {
		p = rand() % 2;//0是电脑先下棋，1是玩家先下棋
		while (1) {
			//判断出结果与否
			for (int i = 0; i < 8; i++) {
				if ((contents[win[i][0]] == computer || contents[win[i][0]] == human) && contents[win[i][0]] == contents[win[i][1]] && contents[win[i][1]] == contents[win[i][2]]) {
					if (contents[win[i][0]] == computer) {
						cout << endl;
						cout << "computer wins the game!" << endl;
					}
					else if (contents[win[i][0]] == human) {
						cout << endl;
						cout << "human wins the game!" << endl;
					}

					cout << "Want to play again?" << endl;
					char a;
					cin >> a;
					if (a == 'Y' || a == 'y') {
						reset();
						continue;
					}
					else {
						return;
					}
				}
			}
			if (chess_num == 9) {
				cout << "It is a draw!" << endl;
				cout << "Want to play again?" << endl;
				char a;
				cin >> a;
				if (a == 'Y' || a == 'y') {
					reset();
					continue;
				}
				else {
					return;
				}
			}

			if (p) {
				human_draw();
			}
			else {
				computer_draw();
			}
			p++;
			p = p % 2;

		}



	}
private:
	//初始化棋盘状态
	void reset() {
		for (int i = 0; i < 9; i++) {
			contents[i] = None;
		}
		chess_computer_num = 0;
		chess_num = 0;
		Draw_init();
	}
	//绘制初始棋盘
	void Draw_init() {
		cursor = { 0,0 };
		//清屏
		system("cls");
		//定义控制台屏幕初始坐标
		//设置控制台光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
		cout << "| 1 | 2 | 3 |" << endl;
		cout << "|---+---+---|" << endl;
		cout << "| 4 | 5 | 6 |" << endl;
		cout << "|---+---+---|" << endl;
		cout << "| 7 | 8 | 9 |" << endl;
		cout << "please enter 1~9" << " ";

	}
	void Draw() {
		cursor = { 0,0 };
		//清屏
		system("cls");
		//定义控制台屏幕初始坐标
		//设置控制台光标位置
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
		cout << "| 1 | 2 | 3 |" << endl;
		cout << "|---+---+---|" << endl;
		cout << "| 4 | 5 | 6 |" << endl;
		cout << "|---+---+---|" << endl;
		cout << "| 7 | 8 | 9 |" << endl;
		int index = 0;
		for (int y = 0; y < 5; y += 2) {
			for (int x = 2; x < 13; x += 4) {
				if (contents[index] == human) {
					cursor = { short(x),short(y) };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
					cout << "X";

				}
				else if (contents[index] == computer) {
					cursor = { short(x),short(y) };
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
					cout << "O";
				}
				index++;
			}
		}
		cursor = { 0,5 }; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
		cout << "please enter 1~9" << " ";
	}
	void human_draw() {
		chess_num++;
		int num;
		while (cin >> num) {
			if (num < 1 || num>9) {
				cout << " 输入不合法! ";
			}
			else {
				if (contents[num - 1] != None) {
					cout << " 该位置已被占用，请重新输入！ ";
				}
				else {
					contents[num - 1] = human;
					Draw();
					return;
				}
			}
			Draw();
		}
	}
	void computer_draw() {
		chess_num++;
		int index = 0;
		if (chess_computer_num == 0) {
			do {
				index = rand() % 9;
			} while (contents[index] != None);
			contents[index] = computer;
			Draw();
			chess_computer_num++;
			return;
		}
		//先在获胜条件中找到当前棋盘时候出现2/3的获胜条件
		for (int i = 0; i < 8; i++) {
			if ((contents[win[i][0]] == contents[win[i][1]] == computer && contents[win[i][2]] == None) || (contents[win[i][0]] == contents[win[i][2]] == computer && contents[win[i][1]] == None) || (contents[win[i][1]] == contents[win[i][2]] == computer && contents[win[i][0]] == None)) {
				if (contents[win[i][0]] == None) {
					contents[win[i][0]] = computer;
					Draw();
					return;
				}
				else if (contents[win[i][1]] == None) {
					contents[win[i][1]] = computer;
					Draw();
					return;
				}
				else if (contents[win[i][2]] == None) {
					contents[win[i][2]] = computer;
					Draw();
					return;
				}
			}
			else if ((contents[win[i][0]] == contents[win[i][1]] == human && contents[win[i][2]] == None) || (contents[win[i][0]] == contents[win[i][2]] == human && contents[win[i][1]] == None) || (contents[win[i][1]] == contents[win[i][2]] == human && contents[win[i][0]] == None)) {
				if (contents[win[i][0]] == None) {
					contents[win[i][0]] = computer;
					Draw();
					return;
				}
				else if (contents[win[i][1]] == None) {
					contents[win[i][1]] = computer;
					Draw();
					return;
				}
				else if (contents[win[i][2]] == None) {
					contents[win[i][2]] = computer;
					Draw();
					return;
				}
			}

		}
		do {
			index = rand() % 9;
		} while (contents[index] != None);
		contents[index] = computer;
		Draw();
	}



	COORD cursor = { 0,0 };	//光标位置
	int p;					//判断当前轮到human还是computer下棋的标志位
	int contents[9];		//棋格内容
	int chess_num = 0;		//棋盘上的棋子数
	int chess_computer_num = 0;
};
int main() {
	//随机初始化
	srand(GetTickCount());
	ttt t;
	t.play();
	return 0;
}


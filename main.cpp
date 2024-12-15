﻿#include <iostream>
#include <Windows.h>

using std::cout;

void gotoxy(int x, int y) { //функция для перемещения курсора в центр карты
	COORD pos = { x, y }; //получение координат курсора 
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE); //?
	SetConsoleCursorPosition(output, pos); //устанавливает курсор на заданное значение 
}

char map[] = //карта игры
"################\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"################\n";
const int WIDTH = 17; //ширина карты (x)
const int HEIGHT = 10; // высота карты (y)
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2); //максимальная длина змейки

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3; //плоскости движения змейки

int snake_dir = UP; //направление куда движется змея

bool isRunning = true; //проверка на запуск игры, если игра завершена = false

char snake = 'O'; //скин змейки

int snake_x[MAX_LEN_SNAKE] = { 0 }; //координата части змеи по x
int snake_y[MAX_LEN_SNAKE] = { 0 }; //координата части змеи по y

int snake_len = 1; //текущая длина змеи 

int main() {
	snake_x[0] = WIDTH / 2;
	snake_y[0] = HEIGHT / 2; //спавн головы змейки в центре поля

	while (isRunning) {
		for (int i = snake_len - 2; i >= 0; i--) { //значение i(счетчика) это предпоследняя часть змейки, это делается для того, что бы все двигалось равномерно, i-- для того что бы перейти к след части змейки и передвинуть ее
			snake_x[i + 1] = snake_x[i];
			snake_y[i + 1] = snake_y[i];
		}
		if (snake_dir == UP) {
			--snake_y[0];
		}
		if (snake_dir == DOWN) {
			++snake_y[0];
		}
		if (snake_dir == RIGHT) {
			++snake_y[0];
		}
		if (snake_dir == LEFT) {
			--snake_y[0];
		}
		

		gotoxy(0, 0);
		cout << "Current lenght: " << snake_len << std::endl;
		for (int i = 0; i < snake_len; i++) {
			map[snake_y[i] * WIDTH + snake_x[i]] = snake; //прорисовка змейки
		}
		cout << map; //отрисовка карты
		for (int i = 0; i < snake_len; i++) {
			map[snake_y[i] * WIDTH + snake_x[i]] = ' '; //очищение буфера от предыдущей змейки
		}
	}
}
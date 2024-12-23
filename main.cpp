#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>

using std::cout;

void gotoxy(int x, int y) { //функция для перемещения курсора в центр карты
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) }; //получение координат курсора 
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
const int MAX_LEN_SNAKE = WIDTH * HEIGHT - 1; //максимальная длина змейки (WIDTH - 3) * (HEIGHT - 2)

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3; //плоскости движения змейки

int snake_dir = 5; //направление куда движется змея

bool isRunning = true; //проверка на запуск игры, если игра завершена = false

char snake = 'O'; //скин змейки
char food = '*'; //скин еды

int food_x = 5;
int food_y = 5;

int snake_x[MAX_LEN_SNAKE] = { 0 };  //координата части змеи по x
int snake_y[MAX_LEN_SNAKE] = { 0 };  //координата части змеи по y

int snake_len = 1; //текущая длина змеи 

bool test() {
	for (int i = 0; i < snake_len; ++i)
		if (snake_x[i] == food_x && snake_y[i] == food_y)
			return true;
	return false;
}

void resp_food() {
	do {
		food_x = 1 + (rand() % (WIDTH - 3));
		food_y = 1 + (rand() % (HEIGHT - 2));
	} while (test());

}

void tracing() {
	if (snake_x[0] == food_x && snake_y[0] == food_y) {
		++snake_len;
		resp_food();
	}

	for (int i = snake_len - 1; i >= 0; i--) { //значение i(счетчика) это предпоследняя часть змейки, это делается для того, что бы все двигалось равномерно, i-- для того что бы перейти к след части змейки и передвинуть ее
		snake_x[i + 1] = snake_x[i];
		snake_y[i + 1] = snake_y[i];
	}
	gotoxy(0, 0);
	map[food_y * WIDTH + food_x] = food;
	for (int i = 0; i < snake_len; i++) {
		map[snake_y[i] * WIDTH + snake_x[i]] = snake; //прорисовка змейки 
	}
	cout << "for leave press 'x'\n";
	cout << map;
	for (int i = 0; i < snake_len; i++) {
		map[snake_y[i] * WIDTH + snake_x[i]] = ' '; //очищение буфера от предыдущей змейки
	}
	if (snake_len != 1) {
		cout << "Current lenght: " << snake_len - 1 << std::endl;
	}
	else {
		cout << "for play use WASD" << std::endl;
	} 

	if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 1) {
		cout << "Game Over!";
		isRunning = false;
	}
}
void moving() {
	if (snake_dir == UP) {
		--snake_y[0];
	}
	if (snake_dir == DOWN) {
		++snake_y[0];
	}
	if (snake_dir == RIGHT) {
		++snake_x[0];
	}
	if (snake_dir == LEFT) {
		--snake_x[0];
	}

	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (snake_dir != RIGHT){
				snake_dir = LEFT;
			}
			break;
		case 'd':
			if (snake_dir != LEFT){
				snake_dir = RIGHT;
			}
			break;
		case 'w':
			if (snake_dir != DOWN){
				snake_dir = UP;
			}
			break;
		case 's':
			if (snake_dir != UP){
				snake_dir = DOWN;
			}
			break;
		case 'x':
			cout << "U end game, goobye!";
			isRunning = false;
		}
	}
}
void game_logic() {

	if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH - 2 || snake_y[0] == HEIGHT - 1) {
		cout << "Game Over!";
		isRunning = false;
	}
	for (int i = 1; i < snake_len; i++) {
		if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
			isRunning = false;
			i = snake_len;
		}
	}
	if (snake_len == MAX_LEN_SNAKE){
		cout << "u win game, ggwp";
		isRunning = false;
	}
}


int main() { 

	srand(static_cast<unsigned int>(time(0)));
	snake_x[0] = WIDTH / 2;
	snake_y[0] = HEIGHT / 2; //спавн головы змейки в центре поля
	
	resp_food();

	while (isRunning) {
		tracing();
		Sleep(500);
		moving();
		game_logic();
	}
}

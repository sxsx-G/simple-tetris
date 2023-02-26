#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 32
#define MAX_TELEPHONE_LENGTH 12
#define COL 20 //游戏区列数
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //空格键
#define ESC 27 //Esc键

int choice_ar = 0;
int ROW = 30;//游戏区行数
//Overall values
int logged_in = 0;
int t = 0; //diffculty(15000)
int diff = 0;
char temp_user[MAX_USERNAME_LENGTH];

void sign_up();
void log_in();
void log_in_or_sign_up();
void delete_user();
void main_board();
void clear_screen();
void game();
void write_player_score(char* username, int score);
void read_and_print_data();//from playscore.txt
void back_to_mainboard();
void choose_diff();
void remove_duplicate_scores(const char* filename);
void startTimer(char* user);
void endTimer(char* user);
void print_txt_contents(const char* txt_name);
void merge_player_data(const char* input_file);
void clearFile(const char* filename);
void get_current_date(int* year, int* month, int* day);
void read_scores_for_year(int year);
void read_scores_for_day(int year, int month, int day);
void read_scores_for_month(int year, int month);
void ShowCursor_1();
void HideCursor();
void choose_square();
int square = 0;
//gamefunc
void jump_to(int x, int y);//光标跳转
void InitInterface();//初始化界面
void InitBlockInfo();//初始化方块信息
void color(int num);//颜色设置
void DrawBlock(int shape, int form, int x, int y);//画出方块
void print_space(int shape, int form, int x, int y);//空格覆盖
int bool_legal(int shape, int form, int x, int y);//合法性判断
int score_judge();//判断得分与结束
void start_game();//游戏主体逻辑函数
void read_max_grade();//从文件读取最高分
void write_max_grade();//更新最高分到文件
void show_face();
int max, grade; //全局变量

//main函数
int main()
{
	main_board();
	return 0;
}

void log_in_or_sign_up()
{
	int choice;
	printf("欢迎使用登录或注册系统!\n");
	printf("1. 注册\n");
	printf("2. 登录\n");
	printf("3. 删除账户\n");
	printf("请输入你的选择（阿拉伯数字）: ");
	scanf("%d", &choice);

	if (choice == 1)
	{
		// Call the sign_up function
		clear_screen();
		sign_up();
	}
	else if (choice == 2)
	{
		// Call the log_in function
		clear_screen();
		log_in();

	}
	else if (choice == 3)
	{
		clear_screen();
		delete_user();
	}

}

// 清空文件
void clearFile(const char* filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Error: failed to open file.\n");
		return;
	}
	fclose(fp);
}
void sign_up()
{
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
	// char telephone[MAX_TELEPHONE_LENGTH];

	 // Prompt the user for a username
	printf("创建一个用户名: ");
	scanf("%s", username);

	// Prompt the user for a password
	printf("创建一个密码： ");
	scanf("%s", password);

	// Prompt the user for a telephone number
   // printf("Enter a telephone number: ");
	//scanf("%s", telephone);

	// Open the "users.txt" file in append mode
	FILE* file = fopen("users.txt", "a");
	if (file == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	// Write the username, password, and telephone number to the file
	fprintf(file, "%s %s\n", username, password);//, telephone);

	// Close the file
	fclose(file);

	printf("注册成功!\n");
	Sleep(1000);
}
void log_in()
{
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
	char file_username[MAX_USERNAME_LENGTH];
	char file_password[MAX_PASSWORD_LENGTH];
	int found = 0;

	// Prompt the user for a username
	printf("请输入您的用户名: ");
	scanf("%s", username);


	// Prompt the user for a password
	printf("请输入您的密码: ");
	scanf("%s", password);

	// Open the "users.txt" file in read mode
	FILE* file = fopen("users.txt", "r");
	if (file == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	// Read the username and password from the file
	while (fscanf(file, "%s %s\n", file_username, file_password) != EOF)
	{
		// Compare the username and password entered by the user with the ones in the file
		if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
		{
			// If they match, set the found flag to 1
			found = 1;
			break;
		}
	}

	if (found)
	{
		printf("成功登录！\n");
		Sleep(1000);
		logged_in = 1;
		strcpy(temp_user, username);
	}
	else
	{
		printf("无效的用户名或密码!\n");
		Sleep(1000);
	}

	// Close the file
	fclose(file);
}
void delete_user()
{
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
	char file_username[MAX_USERNAME_LENGTH];
	char file_password[MAX_PASSWORD_LENGTH];
	int found = 0;

	// Prompt the user for a username
	printf("请输入您想删除的账户名: ");
	scanf("%s", username);

	// Prompt the user for a password
	printf("请输入密码: ");
	scanf("%s", password);

	// Open the "users.txt" file in read mode
	FILE* file = fopen("users.txt", "r");
	if (file == NULL)
	{
		printf("Error opening file!\n");
		Sleep(1000);
		exit(1);
	}

	// Create a temporary file
	FILE* temp_file = fopen("temp.txt", "w");
	if (temp_file == NULL)
	{
		printf("Error creating temporary file!\n");
		Sleep(1000);
		fclose(file);
		exit(1);
	}

	// Read the username and password from the file
	while (fscanf(file, "%s %s\n", file_username, file_password) != EOF)
	{
		// Compare the username and password entered by the user with the ones in the file
		if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
		{
			// If they match, set the found flag to 1
			found = 1;
		}
		else
		{
			// Otherwise, write the username and password from the file to the temporary file
			fprintf(temp_file, "%s %s\n", file_username, file_password);
		}
	}

	// Close both files
	fclose(file);
	fclose(temp_file);

	// If the user was found, delete the original file and rename the temporary file
	if (found)
	{
		if (remove("users.txt") != 0 || rename("temp.txt", "users.txt") != 0)
		{
			printf("Error deleting user!\n");
			exit(1);
		}

		printf("成功删除账户!\n");
		Sleep(1000);
	}
	else
	{
		printf("无效的用户名或密码！\n");
		Sleep(1000);
	}
}
void back_to_mainboard()
{

	printf("输入任何字符以返回:");
	int back = 0;
	scanf("%d", &back);
	if (back == 1)
	{
		clear_screen();
		main_board();
	}
	else {
		clear_screen();
		main_board();
	}
}
void choose_diff()
{
	//clear_screen();
	printf("难度 [1]简单 [2]普通 [3]困难\n");
	printf("请选择难度:");
	diff = 0;
	scanf("%d", &diff);
	printf("\n");
	printf("即将开始游戏，请做好准备！");
	Sleep(2000);
	clear_screen();
}

char MainBoardText[7][20] = {
	"[A]  开始游戏",
	"[B]  登出",
	"[C]  分数排行榜",
	"[D]  游玩时间排行榜",
	"[E]  退出游戏",
	"[F]  Menu6",
	"[Q]  Exit "
};

void displaymenu(int hilight)
{
	int i;
	clear_screen();
	printf("\033[1;31;40m■■■■■■■■■■■■\033[0m\n");
	printf("欢迎来到俄罗斯方块！\n");
	printf("\n");
	for (i = 0; i < 5; i++) {
		if (i == hilight - 1)
			printf("\033[1;31;40m<<\033[0m%s\033[1;31;40m>>\033[0m\n", MainBoardText[i]);
		else
			printf("  %s\n", MainBoardText[i]);
	}
	printf("\033[1;31;40m■■■■■■■■■■■■\033[0m\n");
	printf("进行选择:(使用方向键或 A B C D E)\n ");
}

void main_board() {
	char c = ' ';
	ShowCursor_1();
	int selection = 1;
	if (logged_in)
	{
		displaymenu(selection);
		for (;;) {
			if (_kbhit()) {
				if (GetAsyncKeyState(VK_UP)) {
					selection = (selection > 1) ? selection - 1 : selection;
					Sleep(300);
					system("cls");
					displaymenu(selection);
				}
				if (GetAsyncKeyState(VK_DOWN)) {
					selection = (selection < 7) ? selection + 1 : selection;
					Sleep(300);
					system("cls");
					displaymenu(selection);
				}
				c = _getch();
				if (c <= 'z' && c >= 'a')c = c - ('a' - 'A');
				if (c <= 'F' && c >= 'A') {
					selection = c - 'A' + 1;
					system("cls");
					displaymenu(selection);
					printf("当前选项 [%c]", c);
				}
				else if (c == '\r') {
					if (selection == 7)return;
					system("cls");
					displaymenu(selection);
					char c2 = 'A' + selection - 1;
					printf("当前选项 [%c]", c2);
					if (c2 == 'A')
					{
						// Start the game
						clear_screen();
						printf("Starting game...\n");
						choose_square();
						choose_diff();
						game();
					}
					else if (c2 == 'B')
					{
						//Log out the user
						clear_screen();
						logged_in = 0;
						printf("成功退出登录!\n");
						Sleep(1000);
						main_board();
					}
					else if (c2 == 'C')
					{
						//Show the ranking
						clear_screen();
						remove_duplicate_scores("playerscore.txt");
						printf("请输入你的选择（阿拉伯数字）:\n");
						printf("[1] 日排行榜\n");
						printf("[2] 月排行榜\n");
						printf("[3] 年排行榜\n");


						int choice_rank = 0;
						scanf("%d", &choice_rank);
						if (choice_rank == 1)
						{
							clear_screen();
							int cyear, cmonth, cday;
							printf("请输入你想查询的一天:(格式：年 月 日)");
							scanf("%d %d %d", &cyear, &cmonth, &cday);
							clear_screen();
							read_scores_for_day(cyear, cmonth, cday);
						}
						else if (choice_rank == 2)
						{
							clear_screen();
							int cyear, cmonth;
							printf("请输入你想查询的一个月:(格式：年 月)");
							scanf("%d %d", &cyear, &cmonth);
							clear_screen();
							read_scores_for_month(cyear, cmonth);
						}
						else if (choice_rank == 3)
						{
							clear_screen();
							int cyear;
							printf("请输入你想查询的一年:");
							scanf("%d", &cyear);
							clear_screen();
							read_scores_for_year(cyear);
							back_to_mainboard();
						}
					}
					else if (c2 == 'D')
					{
						clear_screen();
						//clearFile("PlaytimeRank.txt");
						merge_player_data("playtime.txt");
						Sleep(500);
						//print_txt_contents("playtime.txt");
						back_to_mainboard();
					}
					else if (c2 == 'E')
					{
						clear_screen();
						Sleep(100);
						exit(0);
					}
				}
			}
			else if (c == 'Q') return;

		}
	}
	else {
		// If the user is not logged in, show the "log in or sign up" option
		int choice;
		printf("欢迎来到俄罗斯方块游戏！\n");
		printf("你需要注册并登录\n");
		printf("输入任意数字并按下回车以确认: ");
		scanf("%d", &choice);

		if (choice == 1)
		{
			// Call the log_in_or_sign_up function
			clear_screen();
			log_in_or_sign_up();
			clear_screen();
			main_board();

		}
		else {
			clear_screen();
			log_in_or_sign_up();
			clear_screen();
			main_board();
		}

	}


}

#define MAX_NAME_LEN 100
#define MAX_LINE_LEN 1000

// 定义结构体，用于存储玩家的数据
typedef struct {
	char name[MAX_NAME_LEN];
	double score;
} PlayerData;

// 初始化玩家数据
void initPlayerData(PlayerData* player) {
	memset(player->name, 0, MAX_NAME_LEN);
	player->score = 0;
}

// 从文件中读取玩家数据
int readPlayerData(FILE* fp, PlayerData* player) {
	char line[MAX_LINE_LEN];
	if (fgets(line, MAX_LINE_LEN, fp) == NULL) {
		// 如果读到文件末尾，返回0
		return 0;
	}

	// 使用sscanf函数从字符串中读取数据
	sscanf(line, "%s %lf", player->name, &player->score);
	return 1;
}

// 保存玩家数据到文件
void savePlayerData(FILE* fp, PlayerData* player) {
	fprintf(fp, "%s %.2lf\n", player->name, player->score);
}

#define MAX_LINE_LENGTH 100

typedef struct player_data_t {
	char name[MAX_LINE_LENGTH];
	int score;
} player_data;

void merge_player_data(const char* input_file) {
	// 打开文件
	FILE* fp = fopen(input_file, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	// 分配动态内存并读入数据
	player_data* data = (player_data*)malloc(sizeof(player_data));
	int num_items = 0;
	while (fscanf(fp, "%s %d", data[num_items].name, &data[num_items].score) == 2) {
		num_items++;
		player_data* tmp = (player_data*)realloc(data, (num_items + 1) * sizeof(player_data));
		if (tmp == NULL) {
			// 如果分配内存失败，输出错误信息并退出程序
			printf("Error allocating memory\n");
			exit(1);
		}
		data = tmp;
	}


	fclose(fp);
	FILE* ffp = fopen(input_file, "w");
	if (ffp == NULL) {
		printf("Error opening file\n");
		exit(0);
	}

	// 关闭文件
	fclose(ffp);



	// 循环遍历所有数据，对每个玩家的数据进行合并
	for (int i = 0; i < num_items; i++) {
		for (int j = i + 1; j < num_items; j++) {
			if (strcmp(data[i].name, data[j].name) == 0) {
				// 如果发现两条数据的玩家名称相同，则将它们的分数相加
				data[i].score += data[j].score;
				// 然后将后面的数据往前移动一位，覆盖掉被合并的数据
				for (int k = j; k < num_items - 1; k++) {
					data[k] = data[k + 1];
				}
				num_items--;
				j--;
			}
		}
	}
	// 使用冒泡排序将数据按照分数从高到低排序
	for (int i = 0; i < num_items - 1; i++) {
		for (int j = 0; j < num_items - i - 1; j++) {
			if (data[j].score < data[j + 1].score) {
				player_data temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}
	FILE* fp3 = fopen(input_file, "w");
	for (int i = 0; i < num_items; i++) {
		fprintf(fp3, "%s %d\n", data[i].name, data[i].score);
	}
	fclose(fp3);

	// 将合并后的数据输出到屏幕
	for (int i = 0; i < num_items; i++) {
		printf("%s %d\n", data[i].name, data[i].score);
		Sleep(200);
	}

	// 释放动态内存
	free(data);
}

void print_txt_contents(const char* txt_name) {
	FILE* fp;
	char c;

	fp = fopen(txt_name, "r"); // 以只读方式打开文件
	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// 使用 fgetc 函数从文件中读取字符并打印
	c = fgetc(fp);
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(fp);
	}

	fclose(fp); // 关闭文件
}


void clear_screen()
{
	// Use the system function to execute the "clear" or "cls" command, depending on the operating system
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}


struct Player_T {
	char* name;
	time_t start_time;
	double elapsed_time;
};

struct Player_T players[10];
int num_players = 0;

void startTimer(char* user) {
	//printf("        Timer started for user %s\n", user);
	players[num_players].name = user;
	players[num_players].start_time = time(NULL);
	players[num_players].elapsed_time = 0;
	num_players++;
}

void endTimer(char* user) {
	int i;
	for (i = 0; i < num_players; i++) {
		if (strcmp(players[i].name, user) == 0) {
			time_t end_time = time(NULL);
			double elapsed_time = difftime(end_time, players[i].start_time);
			printf("Timer ended for user %s. Elapsed time: %f seconds\n", user, elapsed_time);

			// Open the file for appending
			FILE* fp = fopen("playtime.txt", "a");
			if (fp == NULL) {
				printf("Error opening file!\n");
				return;
			}

			// Write the new playtime for the player to the end of the file
			fprintf(fp, "%s %f\n", user, elapsed_time);

			// Close the file
			fclose(fp);
			break;
		}
	}
}

// Function to read data from the file "playerscore.txt"
// and print it to the screen
void read_and_print_data() {
	// Open the file for reading
	FILE* fp = fopen("playerscore.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// Read and print the data from the file
	char username[100];
	int score;
	int year, month, day;
	while (fscanf(fp, "%s %d %d %d %d", username, &score, &year, &month, &day) == 5) {
		printf("%s %d %d %d %d\n", username, score, year, month, day);
		Sleep(200);
	}

	// Close the file
	fclose(fp);
}

#define MAX_LINE_LEN 1000//数据行数

typedef struct {
	char username[MAX_USERNAME_LENGTH];
	int score;
	int year;
	int month;
	int day;
} Scoredate;

void remove_duplicate_scores(const char* filename) {
	// Open the file
	FILE* file = fopen(filename, "r+");
	if (file == NULL) {
		fprintf(stderr, "Error: Unable to open file.\n");
		return;
	}

	// Create an array for storing the read-in data
	Scoredate* scoress = (Scoredate*)malloc(MAX_LINE_LEN * sizeof(Scoredate));
	if (scoress == NULL) {
		fprintf(stderr, "Error: Unable to allocate memory.\n");
		return;
	}
	int num_scores = 0;

	// Read data from the file
	char line[MAX_LINE_LEN];
	while (fgets(line, MAX_LINE_LEN, file) != NULL) {
		// Extract the username and score from the line
		char username[MAX_USERNAME_LENGTH];
		int score;
		int year;
		int month;
		int day;
		sscanf(line, "%s %d %d %d %d", username, &score, &year, &month, &day);

		// Check if a record with the same username and date already exists
		int found = 0;
		for (int i = 0; i < num_scores; i++) {
			if (strcmp(username, scoress[i].username) == 0 && year == scoress[i].year && month == scoress[i].month && day == scoress[i].day) {
				found = 1;
				// If the score is higher, update the score
				if (score > scoress[i].score) {
					scoress[i].score = score;
				}
				break;
			}
		}

		// If the username and date were not found, add them to the array
		if (!found) {
			strcpy(scoress[num_scores].username, username);
			scoress[num_scores].score = score;
			scoress[num_scores].year = year;
			scoress[num_scores].month = month;
			scoress[num_scores].day = day;
			num_scores++;
		}
	}

	// Close the file
	fclose(file);

	// Open the file for writing
	file = fopen(filename, "w");
	if (file == NULL) {
		fprintf(stderr, "Error: Unable to open file.\n");
		return;
	}

	// Write the data from the array to the file
	for (int i = 0; i < num_scores; i++) {
		fprintf(file, "%s %d %d %d %d\n", scoress[i].username, scoress[i].score, scoress[i].year, scoress[i].month, scoress[i].day);
	}

	// Close the file
	fclose(file);

	// Free the allocated memory
	free(scoress);
}


struct Face
{
	int data[30][COL + 10];
	int color[30][COL + 10];
}face;
struct Face2
{
	int data[36][COL + 10];
	int color[36][COL + 10];
}face2;

struct Block
{
	int space[4][4];
}block[7][4];

void choose_square()
{
	clear_screen();
	printf("请选择游戏界面大小（[1]小 [2]大）：");
	scanf("%d", &square);
	if (square == 1)
	{
		clear_screen();
		system("mode con lines=30 cols=60");
		ROW = 30;
		show_face();
		Sleep(1000);

	}
	else if (square == 2)
	{
		clear_screen();
		system("mode con lines=36 cols=60");
		ROW = 36;
		show_face();
		Sleep(1000);

	}
}

void game()
{
#pragma warning (disable:4996) 
	max = 0, grade = 0; //初始化
	if (square == 1)
	{
		system("mode con lines=30 cols=60");
	}
	else if (square == 0)
	{
		system("mode con lines=40 cols=60");
	}
	HideCursor(); //隐藏光标
	read_max_grade(); //从文件读取最高分到max变量	
	InitInterface(); //初始化界面
	InitBlockInfo(); //初始化方块信息
	srand((unsigned int)time(NULL));
	start_game(); //开始游戏
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = 1;
	curInfo.bVisible = FALSE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curInfo);
}
void ShowCursor_1()
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = 1;
	curInfo.bVisible = TRUE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curInfo);
}
//光标跳转
void jump_to(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}
//初始化界面
void show_face()
{
	color(5); //颜色设置为白色
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL + 10; j++)
		{
			if (j == 0 || j == COL - 1 || j == COL + 9)
			{
				face.data[i][j] = 1; //标记该位置有方块
				jump_to(2 * j, i);
				printf("■");
			}
			else if (i == ROW - 1)
			{
				face.data[i][j] = 1; //标记该位置有方块
				printf("■");
			}
			else
				face.data[i][j] = 0; //标记该位置无方块
		}
	}
	for (int i = COL; i < COL + 10; i++)
	{
		face.data[8][i] = 1; //标记该位置有方块
		jump_to(2 * i, 8);
		printf("■");
	}
	jump_to(2 * COL, 1);
	printf("已选界面\n");

}
void InitInterface()
{
	if (square == 1)
	{
		color(5); //颜色设置为白色
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL + 10; j++)
			{
				if (j == 0 || j == COL - 1 || j == COL + 9)
				{
					face.data[i][j] = 1; //标记该位置有方块
					jump_to(2 * j, i);
					printf("■");
				}
				else if (i == ROW - 1)
				{
					face.data[i][j] = 1; //标记该位置有方块
					printf("■");
				}
				else
					face.data[i][j] = 0; //标记该位置无方块
			}
		}
		for (int i = COL; i < COL + 10; i++)
		{
			face.data[8][i] = 1; //标记该位置有方块
			jump_to(2 * i, 8);
			printf("■");
		}

		jump_to(2 * COL, 1);
		printf("NEXT BLOCK：");

		jump_to(2 * COL + 4, ROW - 19);
		printf("左移：←");

		jump_to(2 * COL + 4, ROW - 17);
		printf("右移：→");

		jump_to(2 * COL + 4, ROW - 15);
		printf("加速：↓");

		jump_to(2 * COL + 4, ROW - 13);
		printf("旋转：空格");

		jump_to(2 * COL + 4, ROW - 11);
		printf("暂停: S");

		jump_to(2 * COL + 4, ROW - 9);
		printf("退出: Esc");

		jump_to(2 * COL + 4, ROW - 7);
		printf("重新开始:R");

		jump_to(2 * COL + 4, ROW - 5);
		printf("历史最高分:%d", max);

		jump_to(2 * COL + 4, ROW - 3);
		printf("当前得分：%d", grade);
	}
	else {
		color(5); //颜色设置为白色
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL + 10; j++)
			{
				if (j == 0 || j == COL - 1 || j == COL + 9)
				{
					face2.data[i][j] = 1; //标记该位置有方块
					jump_to(2 * j, i);
					printf("■");
				}
				else if (i == ROW - 1)
				{
					face2.data[i][j] = 1; //标记该位置有方块
					printf("■");
				}
				else
					face2.data[i][j] = 0; //标记该位置无方块
			}
		}
		for (int i = COL; i < COL + 10; i++)
		{
			face2.data[8][i] = 1; //标记该位置有方块
			jump_to(2 * i, 8);
			printf("■");
		}

		jump_to(2 * COL, 1);
		printf("NEXT BLOCK：");

		jump_to(2 * COL + 4, ROW - 19);
		printf("左移：←");

		jump_to(2 * COL + 4, ROW - 17);
		printf("右移：→");

		jump_to(2 * COL + 4, ROW - 15);
		printf("加速：↓");

		jump_to(2 * COL + 4, ROW - 13);
		printf("旋转：空格");

		jump_to(2 * COL + 4, ROW - 11);
		printf("暂停: S");

		jump_to(2 * COL + 4, ROW - 9);
		printf("退出: Esc");

		jump_to(2 * COL + 4, ROW - 7);
		printf("重新开始:R");

		jump_to(2 * COL + 4, ROW - 5);
		printf("历史最高分:%d", max);

		jump_to(2 * COL + 4, ROW - 3);
		printf("当前得分：%d", grade);
	}

}
//初始化
void InitBlockInfo()
{
	//“T”形
	for (int i = 0; i <= 2; i++)
		block[0][0].space[1][i] = 1;
	block[0][0].space[2][1] = 1;

	//“L”形
	for (int i = 1; i <= 3; i++)
		block[1][0].space[i][1] = 1;
	block[1][0].space[3][2] = 1;

	//“J”形
	for (int i = 1; i <= 3; i++)
		block[2][0].space[i][2] = 1;
	block[2][0].space[3][1] = 1;

	for (int i = 0; i <= 1; i++)
	{
		//“Z”形
		block[3][0].space[1][i] = 1;
		block[3][0].space[2][i + 1] = 1;
		//“S”形
		block[4][0].space[1][i + 1] = 1;
		block[4][0].space[2][i] = 1;
		//“O”形
		block[5][0].space[1][i + 1] = 1;
		block[5][0].space[2][i + 1] = 1;
	}

	//“I”形
	for (int i = 0; i <= 3; i++)
		block[6][0].space[i][1] = 1;

	int temp[4][4];
	for (int shape = 0; shape < 7; shape++) //7种形状
	{
		for (int form = 0; form < 3; form++)
		{
			//获取形态
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = block[shape][form].space[i][j];
				}
			}
			//顺时针旋转
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					block[shape][form + 1].space[i][j] = temp[3 - j][i];
				}
			}
		}
	}
}
//颜色设置
void color(int c)
{
	switch (c)
	{
	case 0:
		c = 13; //“T”形方块设置为紫色
		break;
	case 1:
	case 2:
		c = 12;
		break;
	case 3:
	case 4:
		c = 10;
		break;
	case 5:
		c = 14;
		break;
	case 6:
		c = 11;
		break;
	default:
		c = 7;
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置

}
//画出方块
void DrawBlock(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				jump_to(2 * (x + j), y + i); //光标跳转到指定位置
				printf("■"); //输出方块
			}
		}
	}
}
//空格覆盖
void print_space(int shape, int form, int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[shape][form].space[i][j] == 1) //如果该位置有方块
			{
				jump_to(2 * (x + j), y + i); //光标跳转到指定位置
				printf("  "); //打印空格覆盖（两个空格）
			}
		}
	}
}
//合法性判断
int bool_legal(int shape, int form, int x, int y)
{
	if (square == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//如果方块落下的位置本来就已经有方块了，则不合法
				if ((block[shape][form].space[i][j] == 1) && (face.data[y + i][x + j] == 1))
					return 0; //不合法
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//如果方块落下的位置本来就已经有方块了，则不合法
				if ((block[shape][form].space[i][j] == 1) && (face2.data[y + i][x + j] == 1))
					return 0; //不合法
			}
		}

	}
	return 1; //合法
}
//判断得分与结束
int score_judge()
{
	if (square == 1)
	{
		//判断是否得分
		for (int i = ROW - 2; i > 4; i--)
		{
			int sum = 0; //记录第i行的方块个数
			for (int j = 1; j < COL - 1; j++)
			{
				sum += face.data[i][j];
			}
			if (sum == 0)
				break;
			if (sum == COL - 2)
			{
				grade += 10; //满一行加10分
				color(5);
				jump_to(2 * COL + 4, ROW - 3);
				printf("当前分数：%d", grade); //更新
				for (int j = 1; j < COL - 1; j++)
				{
					face.data[i][j] = 0;
					jump_to(2 * j, i);
					printf("  ");
				}
				//把被清除行上面的行整体向下挪一格
				for (int m = i; m > 1; m--)
				{
					sum = 0; //记录上一行的方块个数
					for (int n = 1; n < COL - 1; n++)
					{
						sum += face.data[m - 1][n];
						face.data[m][n] = face.data[m - 1][n];
						face.color[m][n] = face.color[m - 1][n];
						if (face.data[m][n] == 1)
						{
							jump_to(2 * n, m);
							color(face.color[m][n]);
							printf("■"); //打印
						}
						else
						{
							jump_to(2 * n, m);
							printf("  "); //打印空格
						}
					}
					if (sum == 0)
						return 1;
				}
			}
		}
		//判断
		for (int j = 1; j < COL - 1; j++)
		{
			if (face.data[1][j] == 1)
			{
				Sleep(1000);
				system("cls");
				color(7);
				write_player_score(temp_user, grade);
				jump_to(2 * (COL / 3), ROW / 2 - 3);
				if (grade > max)
				{
					printf("恭喜，您打破了历史记录:%d分", grade);
					write_max_grade();
				}
				else if (grade == max)
				{
					printf("您与历史最高分持平 :%d分", grade);
				}
				else
				{
					printf("您与最高分相差%d分", max - grade);
				}
				jump_to(2 * (COL / 3), ROW / 2);
				printf("GAME OVER");
				endTimer(temp_user);
				while (1)
				{
					char ch;
					jump_to(2 * (COL / 3), ROW / 2 + 3);
					printf("你想再玩一次吗?(y/n):");
					scanf("%c", &ch);
					if (ch == 'y' || ch == 'Y')
					{
						system("cls");
						game();
					}
					else if (ch == 'n' || ch == 'N')
					{
						jump_to(2 * (COL / 3), ROW / 2 + 5);
						main_board();
					}
					else
					{
						jump_to(2 * (COL / 3), ROW / 2 + 4);
						printf("Wrong Option!");
					}
				}
			}
		}
		return 0; //判断结束，无需再调用该函数进行判断
	}
	else {
		//判断是否得分
		for (int i = ROW - 2; i > 4; i--)
		{
			int sum = 0; //记录第i行的方块个数
			for (int j = 1; j < COL - 1; j++)
			{
				sum += face2.data[i][j];
			}
			if (sum == 0)
				break;
			if (sum == COL - 2)
			{
				grade += 10; //满一行加10分
				color(7);
				jump_to(2 * COL + 4, ROW - 3);
				printf("当前分数：%d", grade);
				for (int j = 1; j < COL - 1; j++)
				{
					face2.data[i][j] = 0;
					jump_to(2 * j, i);
					printf("  ");
				}

				for (int m = i; m > 1; m--)
				{
					sum = 0;
					for (int n = 1; n < COL - 1; n++)
					{
						sum += face2.data[m - 1][n];
						face2.data[m][n] = face2.data[m - 1][n];
						face2.color[m][n] = face2.color[m - 1][n];
						if (face2.data[m][n] == 1)
						{
							jump_to(2 * n, m);
							color(face2.color[m][n]);
							printf("■");
						}
						else
						{
							jump_to(2 * n, m);
							printf("  ");
						}
					}
					if (sum == 0)
						return 1;
				}
			}
		}
		//判断游戏是否结束
		for (int j = 1; j < COL - 1; j++)
		{
			if (face2.data[1][j] == 1)
			{
				Sleep(1000);
				system("cls");
				color(7);
				write_player_score(temp_user, grade);
				jump_to(2 * (COL / 3), ROW / 2 - 3);
				if (grade > max)
				{
					printf("恭喜，您打破了历史记录:%d分", grade);
					write_max_grade();
				}
				else if (grade == max)
				{
					printf("您与历史最高分持平 :%d分", grade);
				}
				else
				{
					printf("您与最高分相差%d分", max - grade);
				}
				jump_to(2 * (COL / 3), ROW / 2);
				printf("GAME OVER");
				while (1)
				{
					char ch;
					jump_to(2 * (COL / 3), ROW / 2 + 3);
					printf("你想再玩一次吗?(y/n):");
					scanf("%c", &ch);
					if (ch == 'y' || ch == 'Y')
					{
						system("cls");
						game();
					}
					else if (ch == 'n' || ch == 'N')
					{
						jump_to(2 * (COL / 3), ROW / 2 + 5);
						main_board();
					}
					else
					{
						jump_to(2 * (COL / 3), ROW / 2 + 4);
						printf("Wrong Option!");
					}
				}
			}
		}
		return 0; //判断结束，无需再调用该函数进行判断

	}

}
//游戏主体逻辑函数
void start_game()
{
	int shape = rand() % 7, form = rand() % 4; //随机获取方块的形状和形态
	startTimer(temp_user);
	while (1)
	{

		int nextShape = rand() % 7, nextForm = rand() % 4;
		int x = COL / 2 - 2, y = 0;
		color(nextShape);
		DrawBlock(nextShape, nextForm, COL + 3, 3);
		while (1)
		{
			color(shape); //颜色设置为当前正在下落的方块
			DrawBlock(shape, form, x, y); //将该方块显示在初始下落位置
			if (diff == 1)
			{
				t = 21000;
			}
			else if (diff == 2)
			{
				t = 15000;
			}
			else if (diff == 3)
			{
				t = 8500;
			}
			while (--t)
			{
				if (kbhit() != 0) //若键盘被敲击，则退出循环
					break;
			}
			if (t == 0) //键盘未被敲击
			{
				if (bool_legal(shape, form, x, y + 1) == 0)
				{

					if (square == 1)
					{
						for (int i = 0; i < 4; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								if (block[shape][form].space[i][j] == 1)
								{
									face.data[y + i][x + j] = 1; //将该位置标记为有方块
									face.color[y + i][x + j] = shape; //记录该方块的颜色数值
								}
							}
						}
					}
					else {
						for (int i = 0; i < 4; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								if (block[shape][form].space[i][j] == 1)
								{
									face2.data[y + i][x + j] = 1; //将该位置标记为有方块
									face2.color[y + i][x + j] = shape; //记录该方块的颜色数值
								}
							}
						}
					}
					while (score_judge()); //判断此次方块下落是否得分以及游戏是否结束
					break; //跳出当前死循环
				}
				else //未到底部
				{
					print_space(shape, form, x, y); //用空格覆盖当前方块所在位置
					y++;
				}
			}
			else //键盘被敲击
			{
				char ch = getch();
				switch (ch)
				{
				case DOWN:
					if (bool_legal(shape, form, x, y + 1) == 1) //判断方块向下移动一位后是否合法
					{

						print_space(shape, form, x, y);
						y++;
					}
					break;
				case LEFT:
					if (bool_legal(shape, form, x - 1, y) == 1)
					{

						print_space(shape, form, x, y);
						x--;
					}
					break;
				case RIGHT:
					if (bool_legal(shape, form, x + 1, y) == 1)
					{

						print_space(shape, form, x, y);
						x++;
					}
					break;
				case SPACE:
					if (bool_legal(shape, (form + 1) % 4, x, y + 1) == 1)
					{

						print_space(shape, form, x, y);
						y++;
						form = (form + 1) % 4;
					}
					break;
				case ESC:
					system("cls"); //清空屏幕
					color(7);
					jump_to(COL, ROW / 2);
					printf("  游戏结束  ");
					endTimer(temp_user);
					jump_to(COL, ROW / 2 + 2);
					ShowCursor_1();
					back_to_mainboard();
				case 's':
				case 'S':
					system("pause>nul");
					break;
				case 'r':
				case 'R':
					system("cls");
					endTimer(temp_user);
					choose_diff();
					game();
				}
			}
		}
		shape = nextShape, form = nextForm; //获取下一个方块的信息
		print_space(nextShape, nextForm, COL + 3, 3);
	}
}

void read_max_grade()
{
	FILE* pf = fopen("ranking.txt", "r"); //以只读方式打开文件
	if (pf == NULL) //打开文件失败
	{
		pf = fopen("ranking.txt", "w");
		fwrite(&grade, sizeof(int), 1, pf);
	}
	fseek(pf, 0, SEEK_SET);
	fread(&max, sizeof(int), 1, pf);

	fclose(pf);
	pf = NULL;
}
//更新最高分到文件
void write_max_grade()
{
	FILE* pf = fopen("ranking.txt", "w");
	if (pf == NULL)
	{
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf);
	fclose(pf);
	pf = NULL;
}

// Struct for storing a player's name and score
typedef struct {
	char username[20];
	int score;
} Player;


typedef struct {
	char username[MAX_USERNAME_LENGTH];
	int score;
	int year;
	int month;
	int day;
} Score;

// Comparison function for qsort
int cmp(const void* a, const void* b) {
	Score* score_a = (Score*)a;
	Score* score_b = (Score*)b;
	return score_b->score - score_a->score;
}

void read_scores_for_year(int year) {
	// Open the file for reading
	FILE* fp = fopen("playerscore.txt", "r");
	if (fp == NULL) {
		printf("错误!\n");
		return;
	}

	// Read the scores from the file and store them in an array
	Score* scores = NULL;
	int num_scores = 0;
	char line[MAX_LINE_LEN];
	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		char username[MAX_USERNAME_LENGTH];
		int score;
		int y;
		int m;
		int d;
		sscanf(line, "%s %d %d %d %d", username, &score, &y, &m, &d);
		if (y == year) {
			scores = (Score*)realloc(scores, (num_scores + 1) * sizeof(Score));
			if (scores == NULL) {
				fprintf(stderr, "Error(malloc).\n");
				exit(1);
			}
			strcpy(scores[num_scores].username, username);
			scores[num_scores].score = score;
			scores[num_scores].year = y;
			scores[num_scores].month = m;
			scores[num_scores].day = d;
			num_scores++;
		}
	}

	if (num_scores == 0) {
		printf("找不到 %d 的数据\n", year);
	}
	else {
		// 排序
		qsort(scores, num_scores, sizeof(Score), cmp);

		// 打印数据
		for (int i = 0; i < num_scores; i++) {
			printf("%s %d %d-%d-%d\n", scores[i].username, scores[i].score, scores[i].year, scores[i].month, scores[i].day);
			Sleep(200);
		}
	}
	fclose(fp);
	free(scores);
}
void read_scores_for_day(int year, int month, int day) {

	FILE* fp = fopen("playerscore.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!\n");
		return;
	}

	// 读取，排序
	Score* scores = NULL;
	int num_scores = 0;
	char line[MAX_LINE_LEN];
	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		char username[MAX_USERNAME_LENGTH];
		int score;
		int y;
		int m;
		int d;
		sscanf(line, "%s %d %d %d %d", username, &score, &y, &m, &d);
		if (y == year && m == month && d == day) {
			scores = (Score*)realloc(scores, (num_scores + 1) * sizeof(Score));
			if (scores == NULL) {
				fprintf(stderr, "Error: 错误.\n");
				exit(1);
			}
			strcpy(scores[num_scores].username, username);
			scores[num_scores].score = score;
			scores[num_scores].year = y;
			scores[num_scores].month = m;
			scores[num_scores].day = d;
			num_scores++;
		}
	}

	if (num_scores == 0) {
		printf("找不到 %d-%d-%d 的数据\n", year, month, day);
		back_to_mainboard();
	}
	else {
		//分数排序
		qsort(scores, num_scores, sizeof(Score), cmp);
		for (int i = 0; i < num_scores; i++) {
			printf("%s %d %d-%d-%d\n", scores[i].username, scores[i].score, scores[i].year, scores[i].month, scores[i].day);
			Sleep(200);
		}
		back_to_mainboard();
	}
	fclose(fp);
	free(scores);
}
void read_scores_for_month(int year, int month) {
	// Open the file for reading
	FILE* fp = fopen("playerscore.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!\n");
		return;
	}


	Score* scores = NULL;
	int num_scores = 0;
	char line[MAX_LINE_LEN];
	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		char username[MAX_USERNAME_LENGTH];
		int score;
		int y;
		int m;
		int d;
		sscanf(line, "%s %d %d %d %d", username, &score, &y, &m, &d);
		if (y == year && m == month) {
			scores = (Score*)realloc(scores, (num_scores + 1) * sizeof(Score));
			if (scores == NULL) {
				fprintf(stderr, "Error\n");
				exit(1);
			}
			strcpy(scores[num_scores].username, username);
			scores[num_scores].score = score;
			scores[num_scores].year = y;
			scores[num_scores].month = m;
			scores[num_scores].day = d;
			num_scores++;
		}
	}

	if (num_scores == 0) {
		printf("找不到%d-%d的数据\n", year, month);
		back_to_mainboard();
	}
	else {
		qsort(scores, num_scores, sizeof(Score), cmp);

		// Print the sorted scores to the screen
		for (int i = 0; i < num_scores; i++) {
			printf("%s %d %d-%d-%d\n", scores[i].username, scores[i].score, scores[i].year, scores[i].month, scores[i].day);
			Sleep(200);
		}
		back_to_mainboard();
	}
	fclose(fp);
	free(scores);
}

int year, month, day;
void get_current_date(int* year, int* month, int* day) {
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	*year = tm->tm_year + 1900;

	*month = tm->tm_mon + 1;

	*day = tm->tm_mday;
}

void write_player_score(char* username, int score) {
	time_t now = time(NULL);
	struct tm* local = localtime(&now);
	int year = local->tm_year + 1900;
	int month = local->tm_mon + 1;
	int day = local->tm_mday;
	FILE* fp = fopen("playerscore.txt", "a");
	fprintf(fp, "%s %d %d %d %d\n", username, score, year, month, day);
	fclose(fp);
}








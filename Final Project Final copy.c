/*
* Final project for the PHY2027 module
* Author: Toby Woodcock
* Date: 04/12/2021
*/

/*
 *Program that simulates Conway's game of life in the terminal using ascii characters. The program uses two 2d arrays of 1s & 0s to repeat the program a number of times given by the user.
 *The size and starting conditions can also be determined by the user, either by choosing from a selection of three pre-defined starting conditions or by creating their own starting array.
 *The program allows the user to repeat Conway's game of life any number of times with different starting conditions. The program uses as many aspects taught on the course as possible. 
 */




#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <signal.h>

typedef struct board_position { int N, ** board, i, j; }board_pos;//A structure that stores the size of the board, the current state of the board, and the current position on the board

typedef struct menu_data { int N, iterations, ext, condition[6][6]; }menu;//A structure that stores the size of the board, the number of iterations to be undertaken, the exit variable, and the starting array

menu Conway_menu();//The overall menu that allows the user to set up and choose the parameters of the Conway's game to simulate

menu pre_conditions();//A menu that allows the user to choose one of three predefined starting arrays

menu in_conditions();//A menu that allows the user to input their own starting conditions

void write_array(int array[6][6]);//A function that simply outputs the board condition given an array of 1s and 0s, used to display the starting arrays

void write_board(int N, int** array);//A function that outputs the board condition, given the current board and its size

int neighbours(board_pos* current);//A function that finds how many neighbours a given board position has

int rules(board_pos* current, int count);//A function that decides which rule applies to a given board position with a number of neighbours

int main() {
	int** board = NULL, i, j, run = 0, ** newboard = NULL, count;
	menu start_data;
	start_data.ext = 0;
	while (start_data.ext != 3) {//loop that repeats the program until the user chooses the exit option
		start_data = Conway_menu();
		if (start_data.ext == 3) {//if function that checks if the exit condition is met
			break;
		}
		board = (int**)calloc(start_data.N, sizeof(int*));//Memory is assigned to the original board state, and the new board state
		newboard = (int**)calloc(start_data.N, sizeof(int*));
		for (i = 0; i < start_data.N; ++i) {
			board[i] = (int*)calloc(start_data.N, sizeof(int));
			newboard[i] = (int*)calloc(start_data.N, sizeof(int));
		}
		int consize = sqrt(sizeof(start_data.condition) / (sizeof(int)));
		for (i = 0; i < consize; ++i) {
			for (j = 0; j < consize; ++j) {
				board[(int)(start_data.N / 2) - (int)(consize / 2) + i][(int)(start_data.N / 2) - (int)(consize / 2) + j] += start_data.condition[i][j];//the center of the board is found and the starting array placed there
			}
		}
		write_board(start_data.N, board);

		for (run = 0; run < start_data.iterations; ++run) {//the program is run for the number of iterations stated by the user
			printf("\n");
			for (i = 0; i < start_data.N; ++i) {
				for (j = 0; j < start_data.N; ++j) {
					board_pos cur = { .N = start_data.N,.board = board,.i = i,.j = j };//the current board state is found
					count = (int)neighbours(&cur);

					newboard[i][j] = rules(&cur, count);
				}
			}
			write_board(start_data.N, newboard);
			for (i = 0; i < start_data.N; ++i) {
				for (j = 0; j < start_data.N; ++j) {
					board[i][j] = newboard[i][j];//The newboard state becomes the old state before the process is repeated
				}
			}
		}
		write_board(start_data.N, newboard);
		free(board);//
		free(newboard);
	}
	return 0;
}

void write_board(int N, int** array) {
	system("cls");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			switch (array[i][j]) {
			case 1: printf("[]"); break;//two square brackets are used to indicates 'on' squares
			case 0: printf("  "); break;//two spaces are used to indicate 'off' squares
			}
			if (j == N - 1) {
				printf("\n");
			}
		}
	}
}

void write_array(int array[6][6]) {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			switch (array[i][j]) {
			case 1: printf("[]"); break;
			case 0: printf("  "); break;
			}
			if (j == 6 - 1) {
				printf("\n");
			}
		}
	}
}

menu pre_conditions() {
	menu array;
	int arraynum;

	int condition_array[][6][6] = { {//array of pre-defined starting arrays
		{0, 0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 0},
		{0, 0, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 1, 0},
		{0, 0, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0},
		{0, 1, 0, 1, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
	}
	};
	printf("Choose from one of the following starting conditions");
	for (int i = 0; i < sizeof(condition_array) / sizeof(condition_array[i]); i++) {//loop that loops through all the pre-defined starting conditions, printing them
		printf("\narray %d:\n", i + 1);
		write_array(condition_array[i]);

	}
	scanf_s("%d", &arraynum);
	for (int i = 0; i < sqrt(sizeof(condition_array[arraynum - 1]) / (sizeof(int))); ++i) {// Early on, I was having several issues passing a pointer to a 2d array back to main, I was able to solve these by imbedding the array in a structure
		for (int j = 0;j < sqrt(sizeof(condition_array[arraynum - 1]) / (sizeof(int))); ++j) {
			array.condition[i][j] = condition_array[arraynum - 1][i][j];
		}
	}
	return array;
}

menu in_conditions() {
	int custom_array[6][6] = { 0 }, num_pos, i_pos, j_pos;
	menu array;
	char tf=' ', h = ' ';
	printf("\nBy default your array will be 6 by 6 and will consist entirely of blank space.\n");

	while (h != 'y') {
		h = ' ';
		printf("\nHow many positions would you like to change? \t");
		scanf_s("%d", &num_pos);
		for (int i = 0; i < num_pos; ++i) {
			printf("\nfrom 1 to 6 what row number would you like to change?\t");
			scanf_s("%d", &i_pos);
			printf("\nfrom 1 to 6 what element would you like to change?\t");
			scanf_s("%d", &j_pos);
			if (custom_array[i_pos-1][j_pos-1] == 1) {
				printf("\nYou have already changed the %dth position of the %dth row, are you sure you'd like to change it back to blank? [y/n]\t", j_pos, i_pos);
				scanf_s(" %c", &tf);
				if (tf == 'y') { custom_array[i_pos-1][j_pos-1] = 0; }
			}
			else {
				custom_array[i_pos-1][j_pos-1] = 1;
			}
			printf("\nYour custom array:\n");
			write_array(custom_array);
		}
		while (h != 'y' && h != 'n') {
			printf("Are you happy with your array? [y/n]\t");
			scanf_s(" %c", &h);
		}
	}
	for (int i = 0; i < sqrt(sizeof(custom_array) / (sizeof(int))); ++i) {
		for (int j = 0; j < sqrt(sizeof(custom_array) / (sizeof(int))); ++j) {
			array.condition[i][j] = custom_array[i][j];
		}
	}
	return array;

}



menu Conway_menu() {
	menu cur_menu, f_conditions;
	cur_menu.ext = 0;
	cur_menu.N = 0;
	printf("MENU\n\n"
		"This program is designed to simulate Conway's game of life based off either a predefined array or a user inputed array\n"
		"1.Choose from a set of predefined arrays\n"
		"2.Input your own array\n"
		"3.Exit\n"
	);
	while (cur_menu.ext < 1 || cur_menu.ext>3) {
		printf("Enter an integer corresponding to one of the options:\t");
		scanf_s("%d", &cur_menu.ext);
	};
	switch (cur_menu.ext) {
	case 3:
		printf("The program will now stop");
		return cur_menu;
		break;
	default:
		while (cur_menu.N <= 6) {
			printf("Enter an integer greater than 6 to be the side length of the board:\t");
			scanf_s("%d", &cur_menu.N);
		}
		printf("Enter an integer to be the number of iterations:\t");
		scanf_s("%d", &cur_menu.iterations);
	};
	switch (cur_menu.ext)
	{
	case 1:
		f_conditions = pre_conditions();
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				cur_menu.condition[i][j] = f_conditions.condition[i][j];
			}
		}
		break;
	case 2:
		f_conditions = in_conditions();
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 6; ++j) {
				cur_menu.condition[i][j] = f_conditions.condition[i][j];
			}
		}
		break;
	}
	return cur_menu;
}

int neighbours(board_pos* current) {
	int k, m, count = 0;
	for (k = 0; k < 3; ++k) {//loop which looks at all 8 squares surrounding the current board position
		int i_k = current->i - 1 + k;
		for (m = 0; m < 3; ++m) {
			int j_m = current->j - 1 + m;
			if (i_k >= 0 && i_k < current->N && j_m >= 0 && j_m < current->N) {
				count += current->board[i_k][j_m];
			}
		}
	}
	count -= current->board[current->i][current->j];// subtraction of the current position to avoid counting it as a neighbour
	return count;
}

int rules(board_pos* current, int count) {
	int newtile;
	if (current->board[current->i][current->j] == 0 && count == 3) {
		newtile = 1;
	}
	else if (current->board[current->i][current->j] == 1 && (count == 2 || count == 3)) {
		newtile = 1;
	}
	else {
		newtile = 0;
	}
	return newtile;
}
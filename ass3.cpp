/**********************************************************************
Filename:		Ass3.cpp
Version:		1.0
Author:			Victor Fernandes
Student No:		040772243
Course Name/Number:	CST8233 - Numerical Computing
Lab Sect:		302
Assignment #:		3
Assignment name:	Bungee
Due Date:		December 6 2015
Submission Date:
Professor:		Andrew Tyler
Purpose:		To simulate a person performing a bungee
			jump using Euler's method.
*********************************************************************/
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#ifndef DRAG_CEIL
#define DRAG_CEIL 10.0
#endif

#ifndef DRAG_FLOOR
#define DRAG_FLOOR 1.0
#endif

#ifndef SAFE_SPD_TH
#define SAFE_SPD_TH 1.0
#endif

#ifndef FLOOR_TH
#define FLOOR_TH 0.0
#endif

#ifndef SAFE_HEIGHT
#define SAFE_HEIGHT 1.0
#endif

using namespace std;

void start();
void clear();
clock_t curr_time;

int main(void){

	char user_select; 
	
	while (1){
		clear();
		cout << "*** Bungee Jumping Simulator ***" << endl <<
			"1. Start simulation" << endl <<
			"2. Exit" << endl;
		fflush(stdin);
		cin >> user_select;
		switch (user_select){
		case '1':
			clear();
			start();
			break;
		case '2':
			return 0;
		default:
			break;
		}
	}
}

void start(){
	double drag = 10.0;
	double accel = 0.0;
	double speed = 0.0;
	double prev_speed = 0.0;
	double height = 400.0;
	double time_elapsed = 0.0;
	long long int prev_time = 0;
	
	while (1){
		curr_time = clock();
		time_elapsed = ((double)(curr_time - prev_time)) / CLOCKS_PER_SEC;

		accel = 9.8 - drag / 68 * (speed + 8.0 * pow(speed / 46, 2)) - 0.04 * (400 - height);
		speed = speed + accel * time_elapsed;
		height = height - ((speed + prev_speed) / 2) * time_elapsed;

		prev_time = curr_time;
		prev_speed = speed;

		cout << "------ PRESS 'X' TO QUIT ------" << endl <<
			"Q (+1.0 DRAG) --- W (+0.1 DRAG)" << endl <<
			"E (-0.1 DRAG) --- R (-1.0 DRAG)" << endl <<
			"Simulating bungee jump:" << endl <<
			"Wind Drag\t " << drag << endl <<
			"Time Elapsed\t " << (curr_time / (CLOCKS_PER_SEC * 60)) % 60 << "'" << (curr_time / CLOCKS_PER_SEC) % 60 << "\"" << endl <<
			"Speed\t\t " << speed << "m/s" << endl <<
			"Height\t\t " << height << "m" << endl;

		if (_kbhit()){
			switch (_getch()){
			case 'q': drag < DRAG_CEIL ? drag += 1.0 : drag; break;
			case 'w': drag < DRAG_CEIL ? drag += 0.1 : drag; break;
			case 'e': drag > DRAG_FLOOR ? drag -= 0.1: drag; break;
			case 'r': drag > DRAG_FLOOR ? drag -= 1.0: drag; break;
			case 'x': return;
			}
		}
		if (speed > SAFE_SPD_TH && height <= FLOOR_TH){
			cout << "Let the bodies hit the floor." << endl << 
				"Press any key to continue" << endl;
			fflush(stdin);
			_getch();

			return;
		}
		if (speed < SAFE_SPD_TH && height < SAFE_HEIGHT){
			cout << "You can get off now!" << endl << 
				"Press any key to continue"<< endl;
			fflush(stdin);
			_getch();
			return;
		}
		if (speed == 0.0 && (int) height == 155){
			cout << "How's it hangin? Just... hang on we'll get you out of there." << endl << 
				"Press any key to continue" << endl;
			fflush(stdin);
			_getch();
			return;
		}
		clear();
	}

}

void clear(){
	system("cls");
}


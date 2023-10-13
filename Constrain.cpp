#include <iostream>
#include <string>
#include "mylib.h"
#include "GlobalVariables.h"

using namespace std;

void TypeOnlyAWord(string& result, int& step, bool& Saved, int Limit_word_lenght, int distance) {
	int length = result.length();
	int cnt = length;
	gotoxy(X_Add + distance, Y_Add + step * 4); //vi tri con tro
	cout << result;
	int event; 

	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isalpha(char(event))) {
					if (cnt <= Limit_word_lenght) {
						char c = char(event);
						c = toupper(c);
						cout << c;
						result += c;
						cnt++;
					}
				}
				else if (event == ENTER) {
					return;
				}
				else if (event == ESC) {
					Saved = false;
					return;
				}
				else if (event == BACKSPACE && cnt > 0) {
					//Di chuyen con tro chuot len dang truoc 1 ki tu va de 1 khoang trang len ki tu muon xoa
					//sau do lai di chuyen con tro chuot len truoc 1 len nua
					cout << "\b" << " " << "\b";

					//Xoa ki tu trong chuoi result sau khi da bam BACKSPACE
					result.erase(result.length() - 1, 1);

					//Cap nhat do dai chuoi
					cnt--;
				}
			}
		}
	}
}

void TypeWordAndSpace(string& result, int& step, bool& Saved, int Limit_word_lenght, int distance) {
	int length = result.length();
	int cnt = length;
	gotoxy(X_Add + distance, Y_Add + step * 4);
	cout << result;
	int event;

	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isalpha(char(event))) {
					if (cnt <= Limit_word_lenght) {
						char c = char(event);
						cnt++;
						c = toupper(c);
						cout << c;
						result += c;
					}
				}
				else if (event == SPACE) {
					if (result[result.length() - 1] != ' ') {
						cout << char(event);
						result += char(event);
					}
				}
				else if (event == ENTER) {
					if (result != "" && result[result.length() - 1] == ' ') {
						result = result.substr(0, result.length() - 1);
					}
					return;
				}
				else if (event == BACKSPACE && cnt > 0) {
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					cnt--;
				}
				else if (event == ESC) {
					Saved = false;
					return;
				}
			}
		}
	}
}

void TypeOnlyNumber(int& result, int& step, bool& Saved, int Limit_number, int distance) {
	int cnt = 0;
	int number = result;
	gotoxy(X_Add + distance, Y_Add + step * 4);
	cout << result;
	int event;
	while (number != 0) {
		cnt++;
		number /= 10;
	}
	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isdigit(char(event))) {
					int num = event - 48;
					if ((result * 10 + num) <= Limit_number) {
						cout << num;
						result = result * 10 + num;
						cnt++;
					}
				}
				else if (event == BACKSPACE && cnt > 0) {
					cout << "\b" << " " << "\b";
					result /= 10;
					cnt--;
				}
				else if (event == ENTER) {
					return;
				}
				else if (event == ESC) {
					Saved = false;
					return;
				}
			}
		}
	}
}

void TypeWordAndNumber(string& result, int& step, bool& Saved, int Limit_word_lenght, int distance) {
	int length = result.length();
	int cnt = length;
	gotoxy(X_Add + distance, Y_Add + step * 4);
	cout << result;
	int event;

	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isalpha(char(event)) || isdigit(char(event))) {
					if (cnt <= Limit_word_lenght) {
						char c = char(event);
						c = toupper(c);
						cout << c;
						result += c;
						cnt++;
					}
				}
				else if (event == ENTER) {
					return;
				}
				else if (event == ESC) {
					Saved = false;
					return;
				}
				else if (event == BACKSPACE && cnt > 0) {
					//Di chuyen con tro chuot len dang truoc 1 ki tu va de 1 khoang trang len ki tu muon xoa
					//sau do lai di chuyen con tro chuot len truoc 1 len nua
					cout << "\b" << " " << "\b";

					//Xoa ki tu trong chuoi result sau khi da bam BACKSPACE
					result.erase(result.length() - 1, 1);

					//Cap nhat do dai chuoi
					cnt--;
				}
			}
		}
	}
}

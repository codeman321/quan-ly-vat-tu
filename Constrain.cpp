#include <iostream>
#include <string>
#include "mylib.h"
#include "GlobalVariables.h"

using namespace std;

void TypeOnlyAWord(string& result, int step, bool& Saved, int Limit_word_length, int distance) {
	int length = result.length();
	int cnt = length;
	gotoxy(X_Add + distance, Y_Add + (step - 1) * 4); //vi tri con tro
	cout << result;
	int event; 

	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isalpha(char(event))) {
					if (cnt <= Limit_word_length) {
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

void TypeWordAndSpace(string& result, int step, bool& Saved, int Limit_word_length, int distance) {
	int length = result.length();
	int cnt = length;
	gotoxy(X_Add + distance, Y_Add + (step - 1) * 4);
	cout << result;
	int event;

	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isalpha(char(event))) {
					if (cnt <= Limit_word_length) {
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
						cnt++;
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

void TypeOnlyNumber(int& result, int step, bool& Saved, int Limit_number, int distance) {
	int cnt = 0;
	int number = result;
	gotoxy(X_Add + distance, Y_Add + (step - 1) * 4);
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

void TypeWordAndNumber(string& result, int step, bool& Saved, int Limit_word_length, int distance) {
	int length = result.length();
	int cnt = length;
	gotoxy(X_Add + distance, Y_Add + (step - 1) * 4);
	cout << result;
	int event;

	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isalpha(char(event)) || isdigit(char(event))) {
					if (cnt <= Limit_word_length) {
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

void TypeDate(int& result, int& step, bool& Saved, int LimitReach, int distance, int min, int max) {
	int cnt = 0;
	int number = result;
	gotoxy(X_Add + distance, Y_Add + (step - 1) * 4);
	if (result != 0) {
		cout << result;
	}
	int num = result;
	/*Lay do dai day so dang nhap*/
	while (number != 0) {
		cnt++;
		number /= 10;
	}

	int signal;
	while (true) {
		while (_kbhit()) {
			signal = _getch();
			/*thao tac nhap so*/
			if (signal != 224 && signal != 0) {
				if (48 <= signal && signal <= 57) {
					int numb = signal - 48;
					/*vi nhu nhap 13 la gio thi khong hop le*/
					if (result > LimitReach) {
						continue;
					}

					if ((result * 10 + numb) < LimitReach) {
						cout << numb;
						result = result * 10 + (numb);
						cnt++;
					}
				}
				else if (signal == BACKSPACE && cnt > 0) {
					cout << "\b" << " " << "\b";
					cnt--;
					result /= 10;
				}
				else if (signal == ESC) {
					Saved = false;
					return;
				}
				else if (signal == ENTER) {
					if (result > LimitReach || result == 0 || min >= result || result >= max)
						continue;
					return;
				}
			}
		}
	}
}

void TypeDoubleNumber(double& result, int step, bool& Saved, double Limit_number, int distance) {
	int cnt = 0, temp = 0;
	double number = result;
	gotoxy(X_Add + distance, Y_Add + (step - 1) * 4);
	int event;
	bool decimalPointEntered = false;

	while (number != 0) {
		cnt++;
		number /= 10;
	}

	double decimalFactor = 1.0;  //Bien theo doi phan thap phan
	while (true) {
		while (_kbhit()) {
			event = _getch();
			if (event != 224 && event != 0) {
				if (isdigit(char(event))) {
					int num = event - 48;
					if (!decimalPointEntered) {
						if ((result * 10 + num) <= Limit_number) {
							cout << num;
							result = result * 10 + num;
							cnt++;
						}
					}
					else {
						//Xu ly phan thap phan
						decimalFactor *= 0.1;  //Cap nhat he so thap phan
						if ((result + num * decimalFactor) <= Limit_number) {
							cout << num;
							result += num * decimalFactor;
							cnt++;
						}
					}
				}
				else if (event == BACKSPACE && cnt >= 0) {
					cout << "\b" << " " << "\b";
					if (!decimalPointEntered) {
						result = result / 10;
					}
					else {
						decimalFactor *= 10.0; 
						result = int(result * decimalFactor) / decimalFactor;
					}
					cnt--;
					if (temp == cnt) { //Neu da xoa dau cham thi reset bien de sau nay nhap lai
						decimalPointEntered = false;
					}
				}
				else if (event == '.' && !decimalPointEntered) {
					cout << ".";
					temp = cnt;
					decimalPointEntered = true;
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


string StandardDate(int ngay, int thang, int nam) {
	string t_ngay = to_string(ngay);
	string t_thang = to_string(thang);
	string t_nam = to_string(nam);

	if (ngay <= 9) {
		t_ngay = "0" + t_ngay;
	}
	if (thang <= 9) {
		t_thang = "0" + t_thang;
	}

	return t_ngay + " / " + t_thang + " / " + t_nam;
}
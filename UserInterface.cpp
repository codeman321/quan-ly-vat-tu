#include <iomanip>
#include "UserInterface.h"
#include "GlobalVariables.h"
#include "ProcessionFile.h"
#include "dsNhanVien.h"
#include "dsVatTu.h"

int xKeyContentNV[5] = { 12, 30, 65, 100, 113 };
int xKeyContentVT[5] = { 12, 30, 65, 100, 113 };

string menu_func[Max_item] = { "Danh sach vat tu",
							   "Danh sach nhan vien",
							   "Lap hoa don nhap/xuat",
							   "In hoa don",
							   "Thong ke hoa don",
							   "In 10 vat tu co doanh thu cao nhat",
							   "Thong ke doanh thu trong 1 nam",
							   "Thoat" };

string ContentNV[4] = { "Ma nhan vien", "Ho", "Ten", "Phai" };
string ContentVT[4] = { "Ma vat tu", "Ten vat tu","Don vi tinh", "SL ton" };

void NormalLine() {
	SetColor(14);// yellow
	SetBGColor(0);// black
}
// dong dang chon
void HighlightLine() {
	SetColor(14);// yellow 
	SetBGColor(1);// dark blue        
}

//============= Start: Ve Menu ===========
void DrawTable() {
	gotoxy(X_display + 12, Y_display + 2);
	cout << "Pham Minh Duc - N22DCCN122";
	gotoxy(X_display + 12, Y_display + 4);
	cout << "Mai Hoang Long - N22DCCN049";
	gotoxy(X_display + 78, Y_display + 3);
	cout << "HOC VIEN CONG NGHE BUU CHINH VIEN THONG";

	//-------load file ve notepad-------
	ShowCur(0);
	string temp;
	ifstream file("topic.txt", ios::in);
	if (file.good()) {
		while (file.eof() == false) {
			getline(file, temp);
			cout << temp << endl;
		}
	}
	else {
		cout << "\n Liet ke file that bai" << endl;
	}

	for (int ix = 22; ix <= 167; ix++) {
		//ve dong ben tren so 1
		gotoxy(ix, Y_display);
		cout << char(177);

		//ve dong ben tren so 2
		gotoxy(ix, Y_display + 6);
		cout << char(177);

		//ve dong cuoi cung
		gotoxy(ix, Y_display + 42);
		cout << char(177);
	}

	for (int iy = 8; iy <= 49; iy++) {
		//ve cot dau tien
		gotoxy(X_display, iy);
		cout << char(177);

		//ve cot thu 2
		gotoxy(X_display + 50, iy);
		cout << char(177);

		//ve cot cuoi cung
		gotoxy(X_display + 145, iy);
		cout << char(177);
	}
}

int scrollMenu() {
	//------xuat menu-------
	ShowCur(0);
	NormalLine();
	system("cls");
	DrawTable(); //ve bang
	for (int i = 0; i < Max_item; i++) {
		gotoxy(X_display + 5, Y_display + 10 + (i * 4));
		cout << i + 1 << "/ " << menu_func[i];
	}
	//--------highlight dong dang chon--------
	int pick = 0;
	HighlightLine();
	gotoxy(X_display + 5, Y_display + 10);
	cout << pick + 1 << "/ " << menu_func[pick];
	//--------kiem tra nut len xuong
	char signal;
	while (true) {
		signal = _getch(); //kiem tra co nhap gi tu ban phim khong
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case KEY_UP:
			if (pick + 1 > 1) {
				NormalLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
				pick--;

				HighlightLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
			}
			else {
				NormalLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
				pick = Max_item - 1;

				HighlightLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
			}
			break;
		case KEY_DOWN:
			if (pick + 1 < Max_item) {
				NormalLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
				pick++;

				HighlightLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
			}
			else {
				NormalLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
				pick = 0;

				HighlightLine();
				gotoxy(X_display + 5, Y_display + 10 + pick * 4);
				cout << pick + 1 << "/ " << menu_func[pick];
			}
			break;
		case ENTER:
			NormalLine();
			return pick + 1; //luu lua chon de thuc hien chuc nang ham Menu
		}
	}
}

void Menu() {
	Introduction();
	system("cls");

	Vt_Node dsvt;
	CreateDsvt(dsvt);
	ReadVtFile(dsvt);

	dsNV dsnv;
	ReadNVFile(dsnv);

	int pick;
	int choice = 0;
	bool quit = false;

	while (!quit) {
		if (choice == 0)
			pick = scrollMenu();

		switch (pick) {
		case 1:
			system("color 0E");
			choice = PrintOrUpdate(0);
			if (choice == 0) {
				MenuManageVT(dsvt);
			}
			else if (choice == 1) {
				PrintListVT(dsvt);
			}
			choice = 0;
			break;
		case 2: 
			system("color 0E");
			choice = PrintOrUpdate(2);
			if (choice == 2) {
				MenuManageNV(dsnv);
			}
			else if (choice == 3) {
				PrintListNV(dsnv);
			}
			choice = 0;
			break;
		case 3:
			system("color 0E");
			break;
		case 4:
			system("color 0E");
			break;
		case 5:
			system("color 0E");
			break;
		case 6:
			system("color 0E");
			break;
		case 7:
			system("color 0E");
			break;
		case Max_item:
			system("color 0E");
			quit = true;
			system("cls");
			WriteNVToFile(dsnv);
			break;
		}
	}
}
//=========== End: Ve Menu ===========

//=========== Start: Bang xoa thong tin ==========
//----------Ve bang xoa thong tin ----------
void DrawRemoveTable() {
	for (int ix = X_RemoveConfirm; ix <= X_RemoveConfirm + 38; ix++) {
		//ve hang tren thu nhat
		gotoxy(ix, Y_RemoveConfirm - 2);
		cout << char(205);

		//ve hang tren thu hai
		gotoxy(ix, Y_RemoveConfirm + 2);
		cout << char(205);


		//ve hang duoi
		gotoxy(ix, Y_RemoveConfirm + 6);
		cout << char(205);
	}

	for (int iy = Y_RemoveConfirm - 2; iy <= Y_RemoveConfirm + 6; iy++) {
		//ve cot dau tien
		gotoxy(X_RemoveConfirm, iy);
		cout << char(186);

		//ve cot cuoi cung
		gotoxy(X_RemoveConfirm + 38, iy);
		cout << char(186);
	}

	for (int iy = Y_RemoveConfirm + 2; iy <= Y_RemoveConfirm + 6; iy++) {
		//ve cot ngan cach giua
		gotoxy(X_RemoveConfirm + 19, iy);
		cout << char(186);
	}

	//dieu chinh cac goc
	gotoxy(X_RemoveConfirm, Y_RemoveConfirm - 2);
	cout << char(201);
	gotoxy(X_RemoveConfirm, Y_RemoveConfirm + 6);
	cout << char(200);
	gotoxy(X_RemoveConfirm + 38, Y_RemoveConfirm - 2);
	cout << char(187);
	gotoxy(X_RemoveConfirm + 38, Y_RemoveConfirm + 6);
	cout << char(188);
	gotoxy(X_RemoveConfirm + 19, Y_RemoveConfirm + 2);
	cout << char(203);
	gotoxy(X_RemoveConfirm + 19, Y_RemoveConfirm + 6);
	cout << char(202);
}

//--------- Hoi nguoi dung co muon xoa khong ----------
int RemoveConfirm() {
	ShowCur(false);
	DrawRemoveTable();
	NormalLine();
	string remove[3] = { "Ban co chac chan muon xoa khong??", "Co", "Khong" };

	gotoxy(X_RemoveConfirm + 3, Y_RemoveConfirm);
	cout << remove[0];
	gotoxy(X_RemoveConfirm + 7, Y_RemoveConfirm + 4);
	cout << remove[1];
	gotoxy(X_RemoveConfirm + 27, Y_RemoveConfirm + 4);
	cout << remove[2];

	int pointer = 1;//chi so mang remove
	gotoxy(X_RemoveConfirm + 7, Y_RemoveConfirm + pointer * 2 + 2);
	HighlightLine();
	cout << remove[pointer];
	char event;
	while (true) {
		event = _getch();
		if (event == 224) {
			event = _getch();
		}
		switch (event) {
			case KEY_LEFT:
				if (pointer == 2) {
					NormalLine();
					gotoxy(X_RemoveConfirm + 27, Y_RemoveConfirm + 4);
					cout << remove[2];
					pointer--;

					HighlightLine();
					gotoxy(X_RemoveConfirm + 7, Y_RemoveConfirm + 4);
					cout << remove[1];
				}
				break;
			case KEY_RIGHT:
				if (pointer == 1) {
					NormalLine();
					gotoxy(X_RemoveConfirm + 7, Y_RemoveConfirm + 4);
					cout << remove[1];
					pointer++;

					HighlightLine();
					gotoxy(X_RemoveConfirm + 27, Y_RemoveConfirm + 4);
					cout << remove[2];
				}
				break;
			case ENTER:
				DeleteNotification();
				return pointer;
		}
	}
}

//---------- Xoa bang nhap thong tin ---------------
void RemoveFormComplete(int sl) {
	NormalLine();
	for (int i = X_InputForm - 2; i <= X_InputForm + 50; i++) {
		for (int j = Y_InputForm; j <= Y_InputForm + sl * 4; j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}
}

//---------- Xoa bang thong tin vua moi nhap --------
void RemoveForm(int sl) {
	NormalLine();
	for (int i = 0; i < sl; i++) {
		for (int j = 155; j <= 185; j++) {
			gotoxy(j, 7 + i * 4);
			cout << " ";
		}
	}
}
//========== End: Bang xoa thong tin ===========

//---------- Ve bang thong bao -----------
void Notification(string nd) {
	//SetColor(6);
	ShowCur(0);
	gotoxy(X_Notification + 20, Y_Notification);
	cout << "THONG BAO";
	gotoxy(X_Notification + 2, Y_Notification + 4);
	cout << nd;
	for (int ix = X_Notification; ix <= X_Notification + 50; ix++) {
		//ve hang tren thu nhat
		gotoxy(ix, Y_Notification - 2);
		cout << char(205);

		//ve hang tren thu hai
		gotoxy(ix, Y_Notification + 2);
		cout << char(205);


		//ve hang duoi
		gotoxy(ix, Y_Notification + 6);
		cout << char(205);
	}

	for (int iy = Y_Notification - 2; iy <= Y_Notification + 6; iy++) {
		//ve cot dau tien
		gotoxy(X_Notification, iy);
		cout << char(186);

		//ve cot cuoi cung
		gotoxy(X_Notification + 50, iy);
		cout << char(186);
	}

	//dieu chinh cac goc
	gotoxy(X_Notification, Y_Notification - 2);
	cout << char(201);
	gotoxy(X_Notification, Y_Notification + 6);
	cout << char(200);
	gotoxy(X_Notification + 50, Y_Notification - 2);
	cout << char(187);
	gotoxy(X_Notification + 50, Y_Notification + 6);
	cout << char(188);

	Sleep(1000);
	DeleteNotification();

	ShowCur(1);
}

//------------ xoa bang thong bao -----------
void DeleteNotification() {
	NormalLine();
	for (int i = 140; i <= 190; i++) {
		for (int j = 38; j <= 46; j++) {
			gotoxy(i, j);
			cout << " ";
		}
	}
}

//----------- Ve bang show thong tin ------------
void Display(string ct[], int sl, bool used) {
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < sl; i++) {
		gotoxy(xKeyContentNV[i] + 3, Y_Display);
		cout << ct[i];
	}

	//ve cac duong thang de phan chia cac cot
	for (int iy = Y_Display - 2; iy <= Y_Display + 45; iy++) {
		for (int i = 0; i < sl + 1; i++) {
			gotoxy(xKeyContentNV[i], iy);
			cout << char(219);
		}
	}

	//ve thanh ngang ben tren va duoi
	for (int ix = xKeyContentNV[0]; ix <= xKeyContentNV[sl]; ix++) {
		//ve thanh ngang ben tren so 1
		gotoxy(ix, Y_Display - 2);
		cout << char(219);

		// ve thanh ngang ben tren so 2
		gotoxy(ix, Y_Display + 2);
		cout << char(219);

		//ve thanh ngang ben duoi
		gotoxy(ix, Y_Display + 45);
		cout << char(219);
	}

	//nut huong dan
	if (used) {
		gotoxy(X_Instruction, Y_Instruction);
		cout << "Nhung phim chuc nang:";
		gotoxy(X_Instruction, Y_Instruction + 2);
		cout << "PAGE UP: Len || PAGE DOWN: Xuong";
		gotoxy(X_Instruction, Y_Instruction + 4);
		cout << "INSERT: Them thong tin || DELETE: Xoa thong tin";
		gotoxy(X_Instruction, Y_Instruction + 6);
		cout << "HOME: Chinh sua thong tin || ESC: Thoat bang tinh";
	}
}

//-------- in bang thong tin (only watch) -----------
void DisplayForWatch(string ct[], int num_row, int num_item) {
	//show key - the hien ra noi dung cua cac cot
	for (int i = 0; i < num_row; i++) {
		gotoxy(xKeyContentVT[i] + 3, Y_Display);
		cout << ct[i];
	}

	//ve cac duong thang de phan chia cac cot
	for (int iy = Y_Display - 2; iy <= Y_Display + 45; iy++) {
		for (int i = 0; i < num_row + 1; i++) {
			gotoxy(xKeyContentVT[i], iy);
			cout << char(219);
		}
	}

	//ve thanh ngang ben tren va duoi
	for (int ix = xKeyContentVT[0]; ix <= xKeyContentVT[num_row]; ix++) {
		//ve thanh ngang ben tren so 1
		gotoxy(ix, Y_Display - 2);
		cout << char(219);

		// ve thanh ngang ben tren so 2
		gotoxy(ix, Y_Display + 2);
		cout << char(219);

		//ve thanh ngang ben duoi
		gotoxy(ix, Y_Display + 45);
		cout << char(219);
	}
}

//-------- xoa nhung item vuot qua so luong xuat hien tren 1 bang --------
void RemoveExceedMember(int cnt, int sl) {
	if (cnt < NumberPerPage) {
		for (int i = cnt; i < NumberPerPage; i++) {
			for (int j = 0; j < sl; j++) {
				for (int k = xKeyContentNV[j] + 3; k < xKeyContentNV[j + 1]; k++) {
					gotoxy(k, Y_Display + 4 + i * 4);
					cout << " ";
				}
			}
		}
	}
}

//--------- tao 1 bang nhap thong tin --------
void CreateInputForm(string ct[], int sl, int length) {
	ShowCur(1);
	for (int i = 0; i < sl; i++) {
		gotoxy(X_InputForm, 7 + i * 4);
		cout << ct[i];
	}
	for (int j = 0; j < sl + 1; j++) {
		for (int i = X_InputForm - 2; i < X_InputForm - 2 + length; i++) {
			gotoxy(i, 5 + j * 4);
			cout << char(219);
		}
	}
	for (int iy = Y_InputForm; iy <= Y_InputForm + sl * 4; iy++) {
		gotoxy(X_InputForm - 2, iy);
		cout << char(219);
		gotoxy(X_InputForm - 2 + length, iy);
		cout << char(219);
	}
}

//------------ ve vien cho lua chon chuc nang nhan vien ----------
void DrawBorderFuncNV(int x, int y, int length, int height) {
	for (int ix = x; ix <= x + length; ix++) {
		gotoxy(ix, y);
		cout << char(205);

		gotoxy(ix, y + height);
		cout << char(205);
	}

	for (int iy = y; iy <= y + height; iy++) {
		gotoxy(x, iy);
		cout << char(186);

		gotoxy(x + length, iy);
		cout << char(186);
	}
	gotoxy(x, y);
	cout << char(201);
	gotoxy(x, y + height);
	cout << char(200);
	gotoxy(x + length, y);
	cout << char(187);
	gotoxy(x + length, y + height);
	cout << char(188);
}

//------- ve bang lua chon in hay update nhan vien --------
int PrintOrUpdate(int index) {
	system("color 0E");
	for (int i = 15; i <= 48; i++) {
		gotoxy(X_display + 2, i);
		cout << left << setw(45) << " ";
	}
	string ListChoice[4] = {"    Cap nhat vat tu", 
							"   In danh sach vat tu", 
							"   Cap nhat nhan vien", 
							"   In danh sach nhan vien"};
	int RowListChoice[4] = {25, 39, 25, 39};
	DrawBorderFuncNV(30, 22, 32, 6);
	DrawBorderFuncNV(30, 36, 32, 6);
	for (int i = index; i <= index + 1; i++) {
		gotoxy(32, RowListChoice[i]);
		cout << ListChoice[i];
	}
	int pick = index;
	HighlightLine();
	gotoxy(32, RowListChoice[pick]);
	cout << ListChoice[pick];
	//--------kiem tra nut len xuong
	char signal;
	while (true) {
		signal = _getch(); //kiem tra co nhap gi tu ban phim khong
		if (signal == 224) {
			signal = _getch();
		}
		switch (signal) {
		case KEY_UP:
			if (pick == index + 1) {
				NormalLine();
				gotoxy(32, RowListChoice[pick]);
				cout << ListChoice[pick];
				pick--;

				HighlightLine();
				gotoxy(32, RowListChoice[pick]);
				cout << ListChoice[pick];
			}
			break;
		case KEY_DOWN:
			if (pick == index) {
				NormalLine();
				gotoxy(32, RowListChoice[pick]);
				cout << ListChoice[pick];
				pick++;

				HighlightLine();
				gotoxy(32, RowListChoice[pick]);
				cout << ListChoice[pick];
			}
			break;
		case ESC:
			return 0;
		case ENTER:
			NormalLine();
			return pick; //luu lua chon de thuc hien chuc nang 
		}
	}
}

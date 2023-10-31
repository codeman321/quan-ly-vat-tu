#include <iostream>
#include <string>
#include "dsHoaDon.h"
#include "dsVatTu.h"
#include "GlobalVariables.h"
#include "Constrain.h"
#include "UserInterface.h"
#include <iomanip>

using namespace std;

extern string ContentNV[4];
extern string ContentHD[4];
extern string ContentVT[4];
extern string ContentCTHD[5];
extern int CurNVPage;
extern int TotalNVPage;
extern int XKeyButton[4];
extern int XKeyContentCTHD[6];
extern string ButtonFunc[2];

void Init_hd(hoa_don& hd) {
	hd.soHD = "";
	hd.ngay_lapHD.ngay = 0;
	hd.ngay_lapHD.thang = 0;
	hd.ngay_lapHD.nam = 0;
	hd.loai;
}

//----------- tao moi 1 node kieu hoa_don -----------
hd_Node* MakeHdNode(hoa_don data) {
	hd_Node* temp = new hd_Node;
	temp->data = data;
	temp->next = NULL;
	return temp;
}

//---------- them vao cuoi danh sach -----------
void AddLastListHD(ds_hoa_don*& dshd, hoa_don hd) {
	hd_Node* newNode = MakeHdNode(hd);
	if (dshd->head == NULL) {
		dshd->head = newNode;
		dshd->n_hd++;
		return;
	}
	hd_Node* temp = dshd->head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;
	dshd->n_hd++;
}

//--------- toa bang nhap hoa don ------------
void InputFormHD(string ct[], int sl, int length) {
		gotoxy(X_Title + 65, Y_Title);
		cout << " Lap hoa don ";

		for (int i = 0; i < sl; i++) {
			gotoxy(X_InputForm, 7 + i * 4);
			cout << ct[i];

			if (i == 1) {
				gotoxy(X_InputForm + 20, 7 + i * 4);
				cout << " / ";

				gotoxy(X_InputForm + 30, 7 + i * 4);
				cout << " / ";
			}
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
		gotoxy(X_InputForm + 13, Y_InputForm + 14);
		cout << "  Nhap  ";

		gotoxy(X_InputForm + 30, Y_InputForm + 14);
		cout << "  Xuat  ";
}

//----------- tim so hoa don -------------
hd_Node* FindSoHDExist(ds_hoa_don* dshd, string ID) {
	if (dshd->head == NULL) {
		return NULL;
	}
	hd_Node* temp = dshd->head;
	while (temp != NULL) {
		if (temp->data.soHD == ID) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//----------- chon loai hoa don ----------
int PickHDType() {
	ShowCur(false);
	int pointer = 1;
	HighlightLine();
	gotoxy(X_InputForm + 13, Y_InputForm + 14);
	cout << "  Nhap  ";
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
				gotoxy(X_InputForm + 30, Y_InputForm + 14);
				cout << "  Xuat  ";
				pointer--;

				HighlightLine();
				gotoxy(X_InputForm + 13, Y_InputForm + 14);
				cout << "  Nhap  ";
			}
			break;
		case KEY_RIGHT:
			if (pointer == 1) {
				NormalLine();
				gotoxy(X_InputForm + 13, Y_InputForm + 14);
				cout << "  Nhap  ";
				pointer++;

				HighlightLine();
				gotoxy(X_InputForm + 30, Y_InputForm + 14);
				cout << "  Xuat  ";
			}
			break;
		case ENTER:
			NormalLine();
			return pointer;
		}
	}
}

//----------------- ve bang in cac chi tiet hoa don cua 1 hoa don ------------
void TableOfHD() {	
	ShowCur(0);
	gotoxy(X_Title, Y_Title);
	cout << " Chon vat tu de lap hoa don ";

	//ve bang in thong tin cua hoa don
	gotoxy(X_Display + 15, Y_Display + 8);
	cout << "Thong tin hoa don";
	for (int ix = X_Display; ix <= X_Display + 50; ix++) {
		gotoxy(ix, Y_Display + 6);
		cout << char(220);

		gotoxy(ix, Y_Display + 10);
		cout << char(220);

		gotoxy(ix, Y_Display + 34);
		cout << char(220);
	}
	for (int iy = Y_Display + 7; iy <= Y_Display + 34; iy++) {
		gotoxy(X_Display, iy);
		cout << char(219);

		gotoxy(X_Display + 50, iy);
		cout << char(219);
	}

	//ve bang in thong tin vat tu cua hoa don
	for (int i = 0; i < 5; i++) {
		gotoxy(XKeyContentCTHD[i], Y_Display - 1);
		cout << ContentCTHD[i];
	}
	for (int ix = X_Display + 70; ix <= X_Display + 165; ix++) {
		gotoxy(ix, Y_Display - 3);
		cout << char(220);

		gotoxy(ix, Y_Display);
		cout << char(220);

		gotoxy(ix, Y_Display + 41);
		cout << char(220);
	}

	for (int i = 0; i < 6; i++) {
		for (int iy = Y_Display - 2; iy <= Y_Display + 41; iy++) {
			gotoxy(XKeyContentCTHD[i] - 2, iy);
			cout << char(219);
		}
	}

	//ve cac nut chuc nang
	for (int i = 0; i < 2; i++) {
		gotoxy(XKeyButton[i * 2] + 5, Y_Display + 46);
		cout << ButtonFunc[i];

		for (int ix = XKeyButton[i * 2]; ix <= XKeyButton[i * 2 + 1]; ix++) {
			gotoxy(ix, Y_Display + 43);
			cout << char(205);

			gotoxy(ix, Y_Display + 49);
			cout << char(205);
		}

		for (int iy = Y_Display + 44; iy <= Y_Display + 49; iy++) {
			gotoxy(XKeyButton[i * 2], iy);
			cout << char(186);

			gotoxy(XKeyButton[i * 2 + 1], iy);
			cout << char(186);
		}

		gotoxy(XKeyButton[i * 2], Y_Display + 43);
		cout << char(201);
		gotoxy(XKeyButton[i * 2 + 1], Y_Display + 43);
		cout << char(187);
		gotoxy(XKeyButton[i * 2], Y_Display + 49);
		cout << char(200);
		gotoxy(XKeyButton[i * 2 + 1], Y_Display + 49);
		cout << char(188);
	}
} 

//--------- in 1 chi tiet vat tu -------
void ShowCTHD(cthd_Node* cthd_temp, Vt_Node root, int pos) {
	Vt_Node vt_temp = FindVtNode(root, cthd_temp->data.maVT);
	gotoxy(XKeyContentCTHD[0], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.maVT;
	gotoxy(XKeyContentCTHD[1], Y_Display + 3 + pos * 4);
	cout << vt_temp->data.ten_vt;
	gotoxy(XKeyContentCTHD[2], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.sl;
	gotoxy(XKeyContentCTHD[3], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.donGia;
	gotoxy(XKeyContentCTHD[4], Y_Display + 3 + pos * 4);
	cout << cthd_temp->data.VAT;
	cthd_temp = cthd_temp->next;
}

//--------- in danh sach chi tiet hoa don trong 1 trang ----------
void ShowListCTHDOnePage(hd_Node* temp, Vt_Node root, int StartIndex, int CurHDPage, int TotalHDPage) {
	int sl = temp->data.dscthd->n_cthd;
	gotoxy(X_DisplayNum + 18, Y_DisplayNum);
	cout << "      ";
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong vat tu: " << sl;
	cthd_Node* cthd_temp = temp->data.dscthd->head;
	int i = 0;
	for (int j = i; j < NumberPerPage; j++) {
		for (int k = 0; k < 5; k++) {
			for (int l = XKeyContentCTHD[k]; l < XKeyContentCTHD[k + 1] - 2; l++) {
				gotoxy(l, Y_Display + 3 + j * 4);
				cout << " ";
			}
		}
	}
	for (int i = 0; i < StartIndex && i < sl; i++) {
		cthd_temp = cthd_temp->next;
	}
	for (i = 0; i + StartIndex < sl && i < NumberPerPage; i++) {
		ShowCTHD(cthd_temp, root, i);
		cthd_temp = cthd_temp->next;
	}
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurHDPage << "/" << TotalHDPage;
}

//----------- chon chuc nang trong muc lap hoa don -----------
int PickFuncHD(Vt_Node root, hd_Node* temp, int CurHDPage, int TotalHDPage) {
	ShowCur(0);
	int pointer = 0;
	DrawColor(XKeyButton[pointer * 2], Y_Display + 43, 30, 6, 1);
	gotoxy(XKeyButton[pointer * 2] + 5, Y_Display + 46);
	cout << ButtonFunc[pointer];
	char signal;
	while (true) {
		signal = _getch();
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case KEY_LEFT:
			if (pointer > 0) {
				DrawColor(XKeyButton[pointer * 2], Y_Display + 43, 30, 6, 0);
				gotoxy(XKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];

				pointer--;

				DrawColor(XKeyButton[pointer * 2], Y_Display + 43, 30, 6, 1);
				gotoxy(XKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];
			}
			break;
		case KEY_RIGHT:
			if (pointer < 1) {
				DrawColor(XKeyButton[pointer * 2], Y_Display + 43, 30, 6, 0);
				gotoxy(XKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];

				pointer++;

				DrawColor(XKeyButton[pointer * 2], Y_Display + 43, 30, 6, 1);
				gotoxy(XKeyButton[pointer * 2] + 5, Y_Display + 46);
				cout << ButtonFunc[pointer];
			}
			break;
		case PAGE_UP:
			if (CurHDPage > 1) {
				CurHDPage--;
				NormalLine();
				ShowListCTHDOnePage(temp, root, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage);
			}
			break;
		case PAGE_DOWN:
			if (CurHDPage < TotalHDPage) {
				CurHDPage++;
				NormalLine();
				ShowListCTHDOnePage(temp, root, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage);
			}
			break;
		case ENTER:
			NormalLine();
			return pointer;
		case ESC:
			NormalLine();
			return -1;
		}
	}
}


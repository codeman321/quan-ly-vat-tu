#include <iostream>
#include <string>
#include <iomanip>
#include "UserInterface.h"
#include "dsNhanVien.h"
#include "mylib.h"
#include "Constrain.h"
#include "ProcessionFile.h"

using namespace std;
	
int CurNVPage = 1;
int TotalNVPage = 1;
extern string ContentNV[4];

//----------- tim chi so cua ma nhan vien ---------
int FindIndexNV(dsNV ds, string ma) {
	for (int i = 0; i < ds.n_nv; i++) {
		if (ds.dsnv[i]->maNV == ma) {
			return i;
		}
	}
	return -1;
}

//----------- kiem tra da xoa nhan vien thanh cong hay chua -----------
bool IsDeleteNVSuccess(dsNV& ds, int index) {
	if (index < 0) {
		return false;
	}
	delete ds.dsnv[index];
	for (int i = index; i < ds.n_nv; i++) {
		ds.dsnv[i] = ds.dsnv[i + 1];
	}
	ds.n_nv--;
	return true;
}

//---------- kiem tra nhap lieu nhan vien ----------
bool CheckInfoNVEmpty(nhan_vien* nv) {
	if (nv->maNV.length() == 0 || nv->ho.length() == 0 || nv->ten.length() == 0 || nv->phai.length() == 0) {
		return false;
	}
	return true;
}

//---------- hien thong tin nhan vien -----------
void ShowNV(nhan_vien *nv, int pos) {
	int xKeyContent[5] = { 12, 30, 65, 100, 113 };

	gotoxy(xKeyContent[0] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(15) << nv->maNV;
	gotoxy(xKeyContent[1] + 3, Y_Display + 4 + pos * 4); 
	cout << left << setw(25) << nv->ho;
	gotoxy(xKeyContent[2] + 3, Y_Display + 4 + pos * 4); 
	cout << left << setw(25) << nv->ten;
	gotoxy(xKeyContent[3] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(5) << nv->phai;
}

//---------- in thong tin nhan vien tren 1 trang ---------
void ShowListNVOnePage(dsNV ds, int index) {
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong nhan vien: " << ds.n_nv;
	int i;
	for (i = 0; i + index < ds.n_nv && i < NumberPerPage; i++) {
		ShowNV(ds.dsnv[i + index], i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurNVPage << "/" << TotalNVPage;
}

//---------- thay doi trang in nhan vien ----------
void ChangeNVManagerPage(dsNV ds) {
	gotoxy(X_Title, Y_Title);
	cout << " Quan li nhan vien ";

	Display(ContentNV, sizeof(ContentNV) / sizeof(string));
	ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage);
}

//-------- nhap nhan vien ----------
void inputNV(dsNV& ds, bool Edited = false, bool Deleted = false) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	string ID = "";//ma nhan vien
	string nv_ho = "";//ho nhan vien
	string nv_ten = "";//ten nhan vien
	string nv_phai = "";// phai nhan vien
	string ho_ten = "";
	int temp = 0;
	int step = 0;//cac buoc nhap lieu
	int target = -1;

	while (true) {
		switch (step) {
		case 0: //Nhap ma nhan vien
			TypeWordAndNumber(ID, step, Saved, 10, 5);
			if (!Saved) {
				RemoveFormComplete(3);
				return;
			}

			//kiem tra viec xoa thong tin
			if (Deleted) {
				if (FindIndexNV(ds, ID) == -1) {
					Notification("ID khong ton tai!");
					break;
				}
				int target = RemoveConfirm();
				RemoveFormComplete(1);
				if (target == 2) {
					return;
				}
				if (!IsDeleteNVSuccess(ds, FindIndexNV(ds, ID))) {
					Notification("Xoa khong thanh cong!");
				}
				else {
					Notification("Xoa thanh cong!");
				}					
				TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
				ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage);
				WriteNVToFile(ds);
				return;
			}

			target = FindIndexNV(ds, ID);
			if (ID == "") {
				Notification("Vui long khong bo trong thong tin!");
				break;
			}
			//Kiem tra trong truong hop nhap
			if (target != -1 && !Edited) {
				Notification("ID da ton tai!");
				break;
			}
			//kiem tra trong truong hop chinh sua
			if (target == -1 && Edited) {
				Notification("ID khong ton tai!");
				break;
			}
			step++;
			break;
		case 1: //Nhap ho va ten
			TypeWordAndSpace(ho_ten, step, Saved, 30, 5);
			if (ho_ten == "") {
				Notification("Ho va ten khong duoc phep rong!");
				break;
			}
			for (int i = ho_ten.length() - 1; i >= 0; i--) {
				if (ho_ten[i] == ' ') {
					temp = i;
					break;
				}
			}
			nv_ho = ho_ten.substr(0, temp);
			nv_ten = ho_ten.substr(temp + 1);
			step++;
			break;
		case 2: //Nhap phai
			TypeOnlyAWord(nv_phai, step, Saved, 5, 5);
			if (nv_phai == "") {
				Notification("Gioi tinh khong duoc phep rong!");
				break;
			}
			step++;
			break;
		case 3: 
			if (Edited && target != -1) {
				ds.dsnv[target]->ho = nv_ho;
				ds.dsnv[target]->ten = nv_ten;
				ds.dsnv[target]->phai = nv_phai;
				Notification("Chinh sua thanh cong!");
			}
			else { //dung insert order
				int i;
				for (i = 0; i < ds.n_nv && ds.dsnv[i]->maNV < ID; i++);
				for (int k = ds.n_nv - 1; k >= i; k--) {
					ds.dsnv[k + 1] = ds.dsnv[k];
				}
				ds.dsnv[i] = new nhan_vien;
				ds.dsnv[i]->maNV = ID;
				ds.dsnv[i]->ho = nv_ho;
				ds.dsnv[i]->ten = nv_ten;
				ds.dsnv[i]->phai = nv_phai;
				ds.n_nv++;
				Notification("Them thanh cong!");
			}
			WriteNVToFile(ds);
			ID = "";
			nv_ho = "";
			nv_ten = "";
			nv_phai = "";
			ho_ten = "";
			temp = 0;
			step = 0;
			TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
			ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage);
			RemoveForm(3);
			break;
		}
	}
	ShowCur(0);
}

//----------- Menu quan ly nhan vien ---------
void MenuManageNV(dsNV& ds) {
	ShowCur(0);
	system("cls");
	CurNVPage = 1;
	TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
	Display(ContentNV, sizeof(ContentNV) / sizeof(string));
	ShowListNVOnePage(ds, 0);
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly nhan vien ";
	int event;
	while (true) {
		while (_kbhit()) {
			event = _getch();//nhan biet cac ki tu dac biet
			if (event == ESC) {
				return;
			}
			if (event == 224) {
				event = _getch();//lay cac ki tu dac biet
				if (event == PAGE_UP && CurNVPage > 1) {
					CurNVPage--;
					ChangeNVManagerPage(ds);
				}
				else if (event == PAGE_DOWN && CurNVPage < TotalNVPage) {
					CurNVPage++;
					ChangeNVManagerPage(ds);
				}
				else if (event == INSERT) {//them moi nhan vien
					if (ds.n_nv >= Max_NV) {
						Notification("Danh sach nhan vien da day, khong the them!");
						return;
					}
					string ContentNV[3] = { "Ma NV", "Ho va Ten", "Phai" };
					CreateInputForm(ContentNV, 3, 50);
					inputNV(ds);
					ShowCur(0);
				}
				else if (event == DEL) {
					if (ds.n_nv == 0) {
						Notification("Danh sach rong, khong the xoa");
						return;
					}
					CreateInputForm(ContentNV, 1, 50);
					inputNV(ds, false, true);
				}
				else if (event == HOME) {
					if (ds.n_nv == 0) {
						Notification("Danh sach rong, khong the chinh sua");
						return;
					}
					string ContentNV[3] = { "Ma NV", "Ho va Ten", "Phai" };
					CreateInputForm(ContentNV, 3, 50);
					inputNV(ds, true, false);
					ShowCur(0);
				}
			}
		}
	}
}
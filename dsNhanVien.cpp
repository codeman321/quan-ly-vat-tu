#include <iostream>
#include <string>
#include <iomanip>
#include "UserInterface.h"
#include "dsHoaDon.h"
#include "dsNhanVien.h"
#include "dsVatTu.h"
#include "mylib.h"
#include "Constrain.h"
#include "ProcessionFile.h"

using namespace std;
extern string ContentNV[4];
extern string ContentHD[4];
extern string ContentVT[4];
extern string ContentCTHD[5];
extern int XKeyContentCTHD[6];

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
void ShowListNVOnePage(dsNV ds, int index, int CurNVPage, int TotalNVPage) {
	gotoxy(X_DisplayNum + 28, Y_DisplayNum);
	cout << "         ";
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
void ChangeNVManagerPage(dsNV ds, int CurNVPage, int TotalNVPage) {
	/*gotoxy(X_Title, Y_Title);
	cout << " Quan li nhan vien ";*/
	ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
}

//--------- in thong tin nhan vien theo thu tu ten tang dan ------------
void ShowListNVOnePageAscending(nhan_vien* ds[], int sl, int index, int CurNVPageAscending, int TotalNVPageAscending) {
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong nhan vien: " << sl;
	int i;
	for (i = 0; i + index < sl && i < NumberPerPage; i++) {
		ShowNV(ds[i + index], i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurNVPageAscending << "/" << TotalNVPageAscending;
}

//---------- thay doi trang in nhan vien tang dan ----------
void ChangeNVManagerPageAscending(nhan_vien* ds[], int sl, int CurNVPageAscending, int TotalNVPageAscending) {
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly nhan vien ";
	ShowListNVOnePageAscending(ds, sl, (CurNVPageAscending - 1) * NumberPerPage, CurNVPageAscending, TotalNVPageAscending);
}

//---------- ve bang in danh sach nhan vien theo thu tu ten tang dan -------
void DisplayAscendingNV(nhan_vien* ds[], int sl, int CurNVPageAscending, int TotalNVPageAscending) {
	system("color 0E");
	ShowCur(0);
	system("cls");

	Display(ContentNV, sizeof(ContentNV) / sizeof(string), false);
	ShowListNVOnePageAscending(ds, sl, (CurNVPageAscending - 1) * NumberPerPage, CurNVPageAscending, TotalNVPageAscending);	gotoxy(X_Title, Y_Title);
	cout << " Quan ly nhan vien ";
}

//--------- in danh sach nhan vien theo thu tu ten tang dan -----
void PrintListNV(dsNV ds) {
	int CurNVPageAscending = 1;
	int TotalNVPageAscending = (int)ceil((double)ds.n_nv / NumberPerPage);

	nhan_vien* temp_ds[Max_NV];
	int temp_sl = ds.n_nv;
	for (int i = 0; i < temp_sl; i++) {
		temp_ds[i] = ds.dsnv[i];
	}
	for (int i = 0; i < temp_sl; i++) {
		for (int j = i + 1; j < temp_sl; j++) {
			if (temp_ds[i]->ten > temp_ds[j]->ten) {
				nhan_vien* t = temp_ds[i];
				temp_ds[i] = temp_ds[j];
				temp_ds[j] = t;
			}
			else if (temp_ds[i]->ten == temp_ds[j]->ten) {
				if (temp_ds[i]->ho > temp_ds[j]->ho) {
					nhan_vien* t = temp_ds[i];
					temp_ds[i] = temp_ds[j];
					temp_ds[j] = t;
				}
			}
		}
	}

	DisplayAscendingNV(temp_ds, temp_sl, CurNVPageAscending, TotalNVPageAscending);

	int c;
	while (true) {
		while (_kbhit()) {
			c = _getch();
			if (c == ESC) {
				return;
			}
			if (c == 224) {
				c = _getch();//lay cac ki tu dac biet
				if (c == PAGE_UP && CurNVPageAscending > 1) {
					CurNVPageAscending--;
					ChangeNVManagerPageAscending(temp_ds, temp_sl, CurNVPageAscending, TotalNVPageAscending);
				}
				else if (c == PAGE_DOWN && CurNVPageAscending < TotalNVPageAscending) {
					CurNVPageAscending++;
					ChangeNVManagerPageAscending(temp_ds, temp_sl, CurNVPageAscending, TotalNVPageAscending);
				}
			}
		}
	}
}

//--------- chon nhan vien ----------
int PickItemNv(dsNV ds, int CurNVPage, int TotalNVPage) {
	ShowCur(0);

	//--------highlight dong dang chon--------
	int lower_bound = (CurNVPage - 1) * NumberPerPage;
	int pick = lower_bound;
	int index = 0;
	int upper_bound = CurNVPage * NumberPerPage;
	HighlightLine2();
	HighLightArrow(index);
	ShowNV(ds.dsnv[pick], index);

	//--------kiem tra nut len xuong
	char signal;
	while (true) {
		signal = _getch(); //kiem tra co nhap gi tu ban phim khong
		if (signal == -32) {
			signal = _getch();
		}
		switch (signal) {
		case KEY_UP:
			if (pick > lower_bound && index > 0) {
				NormalLine();
				DeleteArrow(index);
				ShowNV(ds.dsnv[pick], index);
				pick--; index--;

				HighlightLine2();
				HighLightArrow(index);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case KEY_DOWN:
			if (pick + 1 < ds.n_nv && pick + 1 < upper_bound && index < NumberPerPage) {
				NormalLine();
				DeleteArrow(index);
				ShowNV(ds.dsnv[pick], index);
				pick++; index++;

				HighlightLine2();
				HighLightArrow(index);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case PAGE_UP:
			if (CurNVPage > 1) {
				CurNVPage--;
				lower_bound = (CurNVPage - 1) * NumberPerPage;
				upper_bound = CurNVPage * NumberPerPage;
				DeleteArrow(index);
				index = 0;
				pick = lower_bound;
				NormalLine();
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				HighlightLine2();
				HighLightArrow(index);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case PAGE_DOWN:
			if (CurNVPage < TotalNVPage) {
				CurNVPage++;
				lower_bound = (CurNVPage - 1) * NumberPerPage;
				upper_bound = CurNVPage * NumberPerPage;
				DeleteArrow(index);
				index = 0;
				pick = lower_bound;
				NormalLine();
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				HighlightLine2();
				HighLightArrow(index);
				ShowNV(ds.dsnv[pick], index);
			}
			break;
		case ENTER:
			NormalLine();
			DeleteArrow(index);
			return pick; //luu lua chon de thuc hien chuc nang ham Menu
		case ESC:
			NormalLine();
			DeleteArrow(index);
			return -1;
		}
	}
}

//-------- nhap nhan vien ----------
void inputNV(dsNV& ds, bool Edited, bool Deleted, int& CurNVPage, int& TotalNVPage) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	string ID;//ma nhan vien
	//string ID_temp;
	string nv_ho;//ho nhan vien
	string nv_ten;//ten nhan vien
	string nv_phai;// phai nhan vien
	string ho_ten;
	int temp = 0;
	int step = 1;//cac buoc nhap lieu
	int target = -1;
	int target2 = -1;

	while (true) {
		switch (step) {
		case 1: //Nhap ma nhan vien
			if (Edited) {
				string ContentNV[3] = { "Ma NV", "Ho va Ten", "Phai" };
				int IndexNv = PickItemNv(ds, CurNVPage, TotalNVPage);
				target2 = IndexNv; //dung de luu chi so de case 4 thuc hien thao tac chinh sua
				if (IndexNv == -1) {
					TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
					ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
					return;
				}

				//in ra bang nhap thong tin
				CreateInputForm(ContentNV, 3, 50);

				//gan thong tin co san cua node
				ID = ds.dsnv[IndexNv]->maNV;
				ho_ten = ds.dsnv[IndexNv]->ho + " " + ds.dsnv[IndexNv]->ten;
				nv_phai = ds.dsnv[IndexNv]->phai;

				//in thong tin node muon chinh sua
				gotoxy(X_Add + 5, Y_Add);
				cout << left << setw(15) << ID;
				gotoxy(X_Add + 5, Y_Add + 4);
				cout << left << setw(15) << ho_ten;
				gotoxy(X_Add + 5, Y_Add + 8);
				cout << left << setw(15) << nv_phai;
				step++;
				break;
			}
			//kiem tra viec xoa thong tin
			if (Deleted) {
				int IndexNv = PickItemNv(ds, CurNVPage, TotalNVPage);

				//truong hop nhan nut ESC
				if (IndexNv == -1) {
					TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
					ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
					return;
				}

				//truong hop nhan vien da lap hoa don 
				if (ds.dsnv[IndexNv]->used) {
					Notification();
					gotoxy(X_Notification + 2, Y_Notification + 4);
					cout << "Nhan vien da trong hoa don. Khong the xoa!";
					Sleep(1000);
					DeleteNotification();
					ShowNV(ds.dsnv[IndexNv], IndexNv);
					return;
				}

				target = RemoveConfirm();
				RemoveFormComplete(1);
				if (target == 2) {
					NormalLine();
					ShowNV(ds.dsnv[IndexNv], IndexNv);
					return;
				}
				if (!IsDeleteNVSuccess(ds, FindIndexNV(ds, ds.dsnv[IndexNv]->maNV))) {
					Notification();
					gotoxy(X_Notification + 2, Y_Notification + 4);
					cout << "Xoa khong thanh cong!";
					Sleep(1000);
					DeleteNotification();
					ShowCur(1);
				}
				else {
					Notification();
					gotoxy(X_Notification + 2, Y_Notification + 4);
					cout << "Xoa thanh cong!";
					Sleep(1000);
					DeleteNotification();
					ShowCur(1);
				}
				TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				return;
			}

			TypeWordAndNumber(ID, step, Saved, 10, 5);
			if (!Saved) {
				RemoveFormComplete(3);
				return;
			}
			target = FindIndexNV(ds, ID);
			if (ID == "") {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Ma nhan vien khong duoc phep rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			//Kiem tra truong hop ma nhan vien da ton tai
			if (target != -1) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Ma nhan vien da ton tai!";
				Sleep(1000);
				DeleteNotification();
				ID = "";
				RemoveForm(1);
				ShowCur(1);
				break;
			}
			step++;
			break;
		case 2: //Nhap ho va ten
			TypeWordAndSpace(ho_ten, step, Saved, 30, 5);
			if (ho_ten == "") {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Ho va ten khong duoc phep rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
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
		case 3: //Nhap phai
			TypeOnlyAWord(nv_phai, step, Saved, 5, 5);
			if (nv_phai == "") {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Gioi tinh khong duoc phep rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			step++;
			break;
		case 4: 
			if (Edited) {
				ds.dsnv[target2]->maNV = ID;
				ds.dsnv[target2]->ho = nv_ho;
				ds.dsnv[target2]->ten = nv_ten;
				ds.dsnv[target2]->phai = nv_phai;
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Chinh sua thanh cong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				RemoveFormComplete(3);
				TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
				CurNVPage = TotalNVPage;
				ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				return;
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
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Them thanh cong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
			}
			ID = "";
			nv_ho = "";
			nv_ten = "";
			nv_phai = "";
			ho_ten = "";
			temp = 0;
			step = 1;
			TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
			CurNVPage = TotalNVPage;
			ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
			RemoveForm(3);
			break;
		}
	}
	ShowCur(0);
}

//----------- Menu quan ly nhan vien ---------
void MenuManageNV(dsNV& ds) {
	system("color 0E");
	ShowCur(0);
	system("cls");
	int CurNVPage = 1;
	int TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
	Display(ContentNV, sizeof(ContentNV) / sizeof(string), true);
	ShowListNVOnePage(ds, 0, CurNVPage, TotalNVPage);
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
					ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
				}
				else if (event == PAGE_DOWN) {
					TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
					if (CurNVPage < TotalNVPage) {
						CurNVPage++;
						ChangeNVManagerPage(ds, CurNVPage, TotalNVPage);
					}
				}
				else if (event == INSERT) {//them moi nhan vien
					if (ds.n_nv >= Max_NV) {
						Notification();
						gotoxy(X_Notification + 2, Y_Notification + 4);
						cout << "Danh sach nhan vien da day, khong the them!";
						Sleep(1000);
						DeleteNotification();
						ShowCur(1);
						return;
					}
					string ContentNV[3] = { "Ma NV", "Ho va Ten", "Phai" };
					CreateInputForm(ContentNV, 3, 50);
					inputNV(ds, false, false, CurNVPage, TotalNVPage);
					ShowCur(0);
				}
				else if (event == DEL) {
					if (ds.n_nv == 0) {
						Notification();
						gotoxy(X_Notification + 2, Y_Notification + 4);
						cout << "Danh sach rong, khong the xoa";
						Sleep(1000);
						DeleteNotification();
						ShowCur(1);
						return;
					}
					inputNV(ds, false, true, CurNVPage, TotalNVPage);
					ShowCur(0);
				}
				else if (event == HOME) {
					if (ds.n_nv == 0) {
						Notification();
						gotoxy(X_Notification + 2, Y_Notification + 4);
						cout << "Danh sach rong, khong the chinh sua";
						Sleep(1000);
						DeleteNotification();
						ShowCur(1);
						return;
					}
					inputNV(ds, true, false, CurNVPage, TotalNVPage);
					ShowCur(0);
				}
			}
		}
	}
}


//================== cau e: lap hoa don ==================
//--------- nhap hoa don -------------
int InputHD(nhan_vien*& nv) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	hoa_don hd;
	hd_Node* target;
	int step = 1;
	
	while (true) {
		switch (step) {
		case 1: {//Nhap so hoa don
			gotoxy(X_Add + 5, Y_Add + 8);
			cout << nv->maNV;

			TypeWordAndNumber(hd.soHD, step, Saved, 10, 5);
			if (!Saved) {
				return 0;
			}
			target = FindSoHDExist(nv->dshd, hd.soHD);
			if (hd.soHD == "") {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "So hoa don khong duoc phep rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			//Kiem tra truong hop so hoa don da ton tai
			if (target != NULL) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "So hoa don da ton tai!";
				Sleep(1000);
				DeleteNotification();
				hd.soHD = "";
				RemoveForm(1);
				ShowCur(1);
				break;
			}
			step++;
			break; }
		case 2: //Nhap ngay lap hoa don
			TypeDate(hd.ngay_lapHD.ngay, step, Saved, 32, 5, 0, 32);
			if (hd.ngay_lapHD.ngay == 0) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Ngay lap hoa don khong duoc rong";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			step++;
			break;
		case 3: { //Nhap thang lap hoa don
			int temp = step - 1;
			TypeDate(hd.ngay_lapHD.thang, temp, Saved, 13, 15, 0, 13);
			if (hd.ngay_lapHD.thang == 0) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Thang lap hoa don khong duoc rong";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			step++;
			break;
		}
		case 4: {//Nhap nam lap hoa don
			int temp = step - 2;
			TypeDate(hd.ngay_lapHD.nam, temp, Saved, 2100, 25, 1000, 2100);
			if (hd.ngay_lapHD.nam == 0) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Nam lap hoa don khong duoc rong";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			if (hd.ngay_lapHD.thang == 4 || hd.ngay_lapHD.thang == 6 || hd.ngay_lapHD.thang == 9 || hd.ngay_lapHD.thang == 11) {
				if (hd.ngay_lapHD.ngay >= 31) {
					Notification();
					gotoxy(X_Notification + 2, Y_Notification + 4);
					cout << "Thang 4 | 6 | 9 | 11 chi co 30 ngay";
					Sleep(1000);
					DeleteNotification();
					gotoxy(X_Add + 5, Y_Add + 4);
					cout << "  ";
					hd.ngay_lapHD.ngay = 0;
					gotoxy(X_Add + 15, Y_Add + 4);
					cout << "  ";
					hd.ngay_lapHD.thang = 0;
					gotoxy(X_Add + 25, Y_Add + 4);
					cout << "    ";
					hd.ngay_lapHD.nam = 0;
					step = 2;
					ShowCur(1);
					break;
				}
			}
			if (hd.ngay_lapHD.thang == 2) {
				if (hd.ngay_lapHD.nam % 400 == 0 || (hd.ngay_lapHD.nam % 4 == 0 && hd.ngay_lapHD.nam % 100 != 0)) {
					if (hd.ngay_lapHD.ngay > 29) {
						Notification();
						gotoxy(X_Notification + 2, Y_Notification + 4);
						cout << "Day la nam nhuan, thang 2 chi co 29 ngay";
						Sleep(1000);
						DeleteNotification();
						gotoxy(X_Add + 5, Y_Add + 4);
						cout << "  ";
						hd.ngay_lapHD.ngay = 0;
						gotoxy(X_Add + 15, Y_Add + 4);
						cout << "  ";
						hd.ngay_lapHD.thang = 0;
						gotoxy(X_Add + 25, Y_Add + 4);
						cout << "    ";
						hd.ngay_lapHD.nam = 0;
						step = 2;
						ShowCur(1);
						break;
					}
				}
				else if (hd.ngay_lapHD.ngay > 28) {
					Notification();
					gotoxy(X_Notification + 2, Y_Notification + 4);
					cout << "Thang 2 chi co 28 ngay";
					Sleep(1000);
					DeleteNotification();
					gotoxy(X_Add + 5, Y_Add + 4);
					cout << "  ";
					hd.ngay_lapHD.ngay = 0;
					gotoxy(X_Add + 15, Y_Add + 4);
					cout << "  ";
					hd.ngay_lapHD.thang = 0;
					gotoxy(X_Add + 25, Y_Add + 4);
					cout << "    ";
					hd.ngay_lapHD.nam = 0;
					step = 2;
					ShowCur(1);
					break;
				}
			}
			step++;
			break;
		}
		case 5: {//Nhap loai hoa don
			(PickHDType() == 1) ? hd.loai = 'N' : hd.loai = 'X';
			step++;
			break;
		}
		case 6:
			AddLastListHD(nv->dshd, hd);
			nv->used = true;
			Notification();
			gotoxy(X_Notification + 2, Y_Notification + 4);
			cout << "Tao hoa don thanh cong!";
			Sleep(1000);
			DeleteNotification();
			system("cls");
			ShowCur(1);
			return 1;
		}
	}
	ShowCur(0);
}

//----------- nhap chi tiet chi tiet hoa don ----------
int InputCTHD(Vt_Node& root, nhan_vien*& nv, Vt_Node vt, hd_Node* temp) {
	ShowCur(1);
	bool Saved = true;//kiem tra luu lai hay chua
	chi_tiet_hd cthd;
	Vt_Node dsvt_vt = FindVtNode(root, vt->data.ma_vt); //truy cap node vat tu trong danh sach vat tu de cap nhat so luong ton
	int step = 1;

	while (true) {
		switch (step) {
		case 1: //Nhap ma vat tu
			gotoxy(X_Add + 5, Y_Add);
			cout << vt->data.ma_vt;

			cthd.maVT = vt->data.ma_vt;
			step++;
			break;
		case 2: 
			gotoxy(X_Add + 5, Y_Add + 4);
			cout << vt->data.ten_vt;
			step++;
			break;
		case 3: //Nhap so luong vat tu
			TypeOnlyNumber(cthd.sl, step, Saved, 1000000, 5);
			if (!Saved) {
				return 0;
			}
			if (cthd.sl == 0) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "So luong vat tu khong duoc rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			if (temp->data.loai == 'X' && dsvt_vt->data.sl_ton < cthd.sl) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "So luong ton khong du. Hien chi con " << dsvt_vt->data.sl_ton << " san pham";
				Sleep(1000);
				DeleteNotification();

				gotoxy(X_Add + 5, Y_Add + 8);
				cout << "       ";
				cthd.sl = 0;
				ShowCur(1);
				break;
			}

			step++;
			break;
		case 4: { //Nhap don gia cua vat tu trong cthd
			TypeDoubleNumber(cthd.donGia, step, Saved, 1000000.0, 5);
			if (cthd.donGia == 0) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "Don gia khong duoc rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			step++;
			break;
		}
		case 5: { //nhap %VAT
			TypeDoubleNumber(cthd.VAT, step, Saved, 1000000.0, 5);
			if (cthd.VAT == 0) {
				Notification();
				gotoxy(X_Notification + 2, Y_Notification + 4);
				cout << "%VAT khong duoc rong!";
				Sleep(1000);
				DeleteNotification();
				ShowCur(1);
				break;
			}
			step++;
			break;
		}
		case 6:
			AddLastCthd(nv->dshd->head->data.dscthd, cthd);
			if (temp->data.loai == 'X') {
				dsvt_vt->data.sl_ton -= cthd.sl;
			}
			else {
				dsvt_vt->data.sl_ton += cthd.sl;
			}
			dsvt_vt->data.used = true;
			system("cls");
			return 1;
		}
	}
	ShowCur(0);
}

//--------- chon nhan vien de lap hoa hon ----------
int PickNVMakeHD(dsNV ds, int CurNVPage, int TotalNVPage) {
	Display(ContentNV, sizeof(ContentNV) / sizeof(string), false);
	ShowListNVOnePage(ds, (CurNVPage - 1) * NumberPerPage, CurNVPage, TotalNVPage);
	gotoxy(X_Title - 40, Y_Title);
	cout << " Chon nhan vien de lap hoa don ";
	int pick = PickItemNv(ds, CurNVPage, TotalNVPage);
	if (pick != -1) {
		return pick;
	}
	return -1;
}

//--------- chon vat tu them vao hoa don ----------
void DisplayMenuDSHD(nhan_vien* nv, hd_Node* temp, Vt_Node root, int CurHDPage, int TotalHDPage) {
	system("cls");
	TableOfHD();
	gotoxy(X_Display + 5, Y_Display + 14);
	cout << "So hoa don             :   " << temp->data.soHD;
	gotoxy(X_Display + 5, Y_Display + 18);
	cout << "Ma nhan vien           :   " << nv->maNV;
	gotoxy(X_Display + 5, Y_Display + 22);
	cout << "Ten nhan vien          :   " << nv->ten;
	gotoxy(X_Display + 5, Y_Display + 26);
	cout << "Ngay lap hoa don       :   " << StandardDate(temp->data.ngay_lapHD.ngay, temp->data.ngay_lapHD.thang, temp->data.ngay_lapHD.nam);
	gotoxy(X_Display + 5, Y_Display + 30);
	string loai;
	temp->data.loai == 'N' ? loai = "Nhap" : loai = "Xuat";
	cout << "Loai hoa don           :   " << loai;

	ShowListCTHDOnePage(temp, root, (CurHDPage - 1) * NumberPerPage, CurHDPage, TotalHDPage);
}

//----------- menu quan ly hoa don -------------
void MenuManagerHD(dsNV& ds, Vt_Node& root) {
	ShowCur(0);
	system("cls");
	int CurNVPage = 1;
	int TotalNVPage = (int)ceil((double)ds.n_nv / NumberPerPage);
	int CurVtPage = 1;
	int TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
	int CurHDPage = 1;
	int TotalHDPage = 1;
	int index = -1;

	while (true) {
		index = PickNVMakeHD(ds, CurNVPage, TotalNVPage);
		if (index == -1) { //truong hop bam nut ESC de thoat
			return;
		}

		//nhap thong tin hoa don
		InputFormHD(ContentHD, 4, 50);
		int x = InputHD(ds.dsnv[index]);

		if (x) { //neu x == 1 nghia la tao hoa don thanh cong, qua buoc tiep theo
			break;
		}
		else { //khong thi cho tao lai
			system("cls");
		}
	}
	//tim den node hoa don moi tao
	hd_Node* hd = ds.dsnv[index]->dshd->head;
	while (hd->next != NULL) {
		hd = hd->next;
	}
	hd->data.dscthd = new ds_chi_tiet_hd;

	//chon vat tu cho vao hoa don
	while (true) {
		CurHDPage = 1;
		TotalHDPage = (int)ceil((double)hd->data.dscthd->n_cthd / NumberPerPage);
		if (TotalHDPage == 0)
			TotalHDPage = 1;
		DisplayMenuDSHD(ds.dsnv[index], hd, root, CurHDPage, TotalHDPage);
		int idx_func = PickFuncHD(root, hd, CurHDPage, TotalHDPage);
		if (idx_func == -1) {
			return;
		}
		while (idx_func == 0) {
			system("cls");
			int pick = 0;
			Display(ContentVT, sizeof(ContentVT) / sizeof(string), false);
			ChangeVtManagerPage(root, CurVtPage, TotalVtPage);
			Vt_Node vt = PickItemVt(root, pick, CurVtPage, TotalVtPage);
			if (vt == NULL) {
				break;
			}
			CreateInputForm(ContentCTHD, 5, 50);
			int temp = InputCTHD(root, ds.dsnv[index], vt, hd);
			if (!temp) {
				break;
			}
		}
		while (idx_func == 1) {
			return;
		}
	}

	gotoxy(X_Notification, Y_Notification);
	cout << "----------------------------";
	Sleep(100000);
}
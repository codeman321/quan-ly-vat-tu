#include <iostream>
#include <string>
#include <iomanip>
#include "dsVatTu.h"
#include "GlobalVariables.h"
#include "Constrain.h"
#include "mylib.h"
#include "UserInterface.h"
#include "ProcessionFile.h"

using namespace std;

int TotalVtPage = 1;
int CurVtPage = 1;
int TotalVtPageAscending = 1;
int CurVtPageAscending = 1;
extern string ContentVT[4];

//-------- tao danh sach vat tu ---------
void CreateDsvt(Vt_Node& root) {
	root = NULL;
}

//-------- tao 1 node vat tu ---------
Vt_Node MakeVtNode(vat_tu vt) {
	Vt_Node newNode = new vt_Node;
	newNode->data = vt;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}

//------- xac dinh chieu cao cua cay ---------
int height(Vt_Node root) {
	if (root == NULL) {
		return 0;
	}
	return root->height;
}

//------- thao tac xoay trai --------
Vt_Node LeftRotation(Vt_Node x) {
	if (x == NULL || x->right == NULL) {
		return x;
	}
	Vt_Node y = x->right;
	Vt_Node T2 = y->left;

	//thuc hien phep xoay
	y->left = x;
	x->right = T2;

	//cap nhat chieu cao
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	//tra ve root goc moi
	return y;
}

//------- thao tac xoay phai --------
Vt_Node RightRotation(Vt_Node y) {
	if (y == NULL || y->left == NULL) {
		return y;
	}
	Vt_Node x = y->left;
	Vt_Node T2 = x->right;

	//thuc hien phep xoay
	x->right = y;
	y->left = T2;

	//cap nhat chieu cao
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	//tra ve root goc moi
	return x;
}

//------- dem so node co tren cay -----------
int CountVtNode(Vt_Node root) {
	if (root == NULL)
		return 0;
	return 1 + CountVtNode(root->left) + CountVtNode(root->right);
}

//------- cap nhat mang luu cac node vat tu ---------
void UpdateArrVtList(Vt_Node root, Vt_Node VtNodeList[], int& index) {
	if (root != NULL) {
		VtNodeList[index] = root;
		index++;

		UpdateArrVtList(root->left, VtNodeList, index);
		UpdateArrVtList(root->right, VtNodeList, index);
	}
}

//-------- tim node co ma vt cho truoc ---------
Vt_Node FindVtNode(Vt_Node root, string ID) {
	if (root == NULL) {
		return NULL;
	}
	if (root->data.ma_vt == ID) {
		return root;
	}
	if (root->data.ma_vt < ID) {
		return FindVtNode(root->right, ID);
	}
	else {
		return FindVtNode(root->left, ID);
	}
}

//-------- lay gia tri can bang cua cay (chi chap nhan -1, 0, 1) ------
int getBalanceFactor(Vt_Node root) {
	if (root == NULL) {
		return 0;
	}
	return height(root->left) + height(root->right);
}

//-------- thao tac them vat tu ----------
Vt_Node AddVt(Vt_Node& root, vat_tu vt) {
	if (root == NULL) {
		return MakeVtNode(vt);
	}
	if (vt.ma_vt < root->data.ma_vt) {
		root->left = AddVt(root->left, vt); //di ve cay con ben trai
	}
	else if (vt.ma_vt > root->data.ma_vt) {
		root->right = AddVt(root->right, vt); //di ve cay con ben phai
	}
	else {
		return root; 
	}

	//cap nhat lai do cao cua cay khi da them 1 node
	root->height = max(height(root->left), height(root->right));

	//kiem tra lieu cay co bi mat can bang khi them node khong
	int BalanceFactor = getBalanceFactor(root);

	//co 4 truong hop cay mat can bang
	//left left
	if (BalanceFactor > 1 && vt.ma_vt < root->left->data.ma_vt) {
		return RightRotation(root);
	}

	//right right
	if (BalanceFactor < -1 && vt.ma_vt > root->right->data.ma_vt) {
		return LeftRotation(root);
	}

	//left right
	if (BalanceFactor > 1 && vt.ma_vt > root->left->data.ma_vt) {
		root->left = LeftRotation(root->left);
		return RightRotation(root);
	}

	//right left
	if (BalanceFactor < -1 && vt.ma_vt < root->right->data.ma_vt) {
		root->right = RightRotation(root->right);
		return LeftRotation(root);
	}

	return root;
}

//-------- tim node co ma vt nho nhat lon hon ma vt muon xoa ---------
Vt_Node MinVtNode(Vt_Node root) {
	Vt_Node temp = root;
	while (temp != NULL && temp->left != NULL) {
		temp = temp->left;
	}
	return temp;
}

//-------- Tien hanh xoa vat tu theo ma vt------
Vt_Node DeleteVt(Vt_Node& root, string ID) {
	if (root == NULL) {
		return root;
	}

	if (ID < root->data.ma_vt) {
		root->left = DeleteVt(root->left, ID);
	}
	else if (ID > root->data.ma_vt) {
		root->right = DeleteVt(root->right, ID);
	}
	else {
		// TH1: ID co 1 cay con hoac khong co cay con nao
		if ((root->left == NULL) || (root->right == NULL)) {
			Vt_Node temp;
			
			if (root->left) {
				temp = root->left;
			}
			else {
				temp = root->right;
			}

			// TH khong co nhanh con
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			// TH co 1 nhanh con TRAI hoac PHAI
			else {
				*root = *temp; /*truyen dia chi *TEMP cho *ROOT*/
				delete temp; /*giai phong vung nho cua temp khong dung toi nua*/
			}
		}
		// TH2 :node can xoa co 2 nhanh con
		else { 
			/*node thay the la node nho nhat lon hon node can xoa*/
			Vt_Node temp = MinVtNode(root->right);

			/*sao chep noi dung cua node temp vao node can xoa*/
			root->data = temp->data;

			/*xoa node thay the o vi tri cu di*/
			root->right = DeleteVt(root->right, temp->data.ma_vt);
		}
	}

	//neu cay chi co 1 node thi return
	if (root == NULL)
		return root;

	//cap nhat lai do cao cua node
	root->height = max(height(root->left), height(root->right)) + 1;

	//can bang lai cay
	int BalanceFactor = getBalanceFactor(root);
	
	//left left		
	if (BalanceFactor > 1 && ID < root->left->data.ma_vt) {
		return RightRotation(root);
	}

	//right right
	if (BalanceFactor < -1 && ID > root->right->data.ma_vt) {
		return LeftRotation(root);
	}

	//left right
	if (BalanceFactor > 1 && ID > root->left->data.ma_vt) {
		root->left = LeftRotation(root->left);
		return RightRotation(root);
	}

	//right left
	if (BalanceFactor < -1 && ID < root->right->data.ma_vt) {
		root->right = RightRotation(root->right);
		return LeftRotation(root);
	}
	return root;
}

//---------- hien thong tin nhan vien -----------
void ShowVt(vat_tu vt, int pos) {
	int xKeyContent[5] = { 12, 30, 65, 100, 113 };

	gotoxy(xKeyContent[0] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(15) << vt.ma_vt;
	gotoxy(xKeyContent[1] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(25) << vt.ten_vt;
	gotoxy(xKeyContent[2] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(25) << vt.dvt;
	gotoxy(xKeyContent[3] + 3, Y_Display + 4 + pos * 4);
	cout << left << setw(5) << vt.sl_ton;
}

//---------- in thong tin nhan vien tren 1 trang ---------
void ShowListVtOnePage(Vt_Node root, int StartIndex) {
	Vt_Node VtNodeList[Max_itemVt];
	int index = 0;
	UpdateArrVtList(root, VtNodeList, index);

	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong vat tu: " << index;
	int i;
	for (i = 0; i + StartIndex < index && i < NumberPerPage; i++) {
		ShowVt(VtNodeList[i + StartIndex]->data, i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurVtPage << "/" << TotalVtPage;
}

//---------- thay doi trang in nhan vien ----------
void ChangeVtManagerPage(Vt_Node root) {
	gotoxy(X_Title, Y_Title);
	cout << " Quan li nhan vien ";
	ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
}

Vt_Node PickItemVt(Vt_Node root, int& pick) {
	ShowCur(0);
	Vt_Node VtNodeList[Max_itemVt];
	int index = 0;
	UpdateArrVtList(root, VtNodeList, index);

	//--------highlight dong dang chon--------
	HighlightLine2();
	ShowVt(VtNodeList[pick]->data, pick);
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
				ShowVt(VtNodeList[pick]->data, pick);
				pick--;

				HighlightLine2();
				ShowVt(VtNodeList[pick]->data, pick);
			}
			break;
		case KEY_DOWN:
			if (pick + 1 < index) {
				NormalLine();
				ShowVt(VtNodeList[pick]->data, pick);
				pick++;

				HighlightLine2();
				ShowVt(VtNodeList[pick]->data, pick);
			}
			break;
		case ENTER:
			NormalLine();
			return VtNodeList[pick]; //luu lua chon de thuc hien chuc nang ham Menu
		case ESC:
			NormalLine();
			return NULL;
		}
	}
}

//-------- nhap 1 vat tu ----------
void InputVt(Vt_Node& root, bool Edited = false, bool Deleted = false) {
	ShowCur(1);
	bool Saved = true; //bien kiem tra luu danh sach
	string vt_ma;
	string vt_ten;
	string vt_dvt;
	int vt_slton = 0;

	int step = 1;
	int event = 0;
	int target = -1;
	Vt_Node checked = NULL;
	Vt_Node temp = NULL;
	
	while (true) {
		switch (step) {
		case 1: //nhap ma vat tu
			if (Edited) {
				string ContentVT[4] = { "Ma vat tu", "Ten vat tu", "Don vi tinh", "SL ton" };
				int pick = 0;
				Vt_Node EditedNode = PickItemVt(root, pick); //thuc hien tim node muon chinh sua

				//truong hop an nut ESC de thoat
				if (EditedNode == NULL) {
					TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
					ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
					return;
				}
				
				//in ra bang nhap thong tin
				CreateInputForm(ContentVT, 4, 50);

				//gan thong tin co san cua node
				vt_ma = EditedNode->data.ma_vt;
				vt_ten = EditedNode->data.ten_vt;
				vt_dvt = EditedNode->data.dvt;
				vt_slton = EditedNode->data.sl_ton;

				//in thong tin node muon chinh sua
				gotoxy(X_Add + 5, Y_Add);
				cout << left << setw(15) << vt_ma;
				gotoxy(X_Add + 5, Y_Add + 4);
				cout << left << setw(15) << vt_ten;
				gotoxy(X_Add + 5, Y_Add + 8);
				cout << left << setw(15) << vt_dvt;
				gotoxy(X_Add + 5, Y_Add + 12);
				cout << left << setw(15) << vt_slton;

				temp = EditedNode; //dung de luu node dung cho thao tac chinh sua o case 5

				step++;
				break;
			}
			//kiem tra viec xoa thong tin
			if (Deleted) {
				int pick = 0;
				Vt_Node DeleteNode = PickItemVt(root, pick); //thuc hien tim node muon xoa

				//truong hop an nut ESC de thoat
				if (DeleteNode == NULL) {
					TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
					ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
					return;
				}

				//xac thuc buoc 2
				target = RemoveConfirm();
				RemoveFormComplete(1);

				//truong hop user chon no
				if (target == 2) {
					NormalLine();
					ShowVt(DeleteNode->data, pick);
					return;
				}
				else {
					root = DeleteVt(root, DeleteNode->data.ma_vt);
					Notification("Xoa vat tu thanh cong!");
				}

				TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
				ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
				WriteVtToFile(root);
				return;
			}

			TypeWordAndNumber(vt_ma, step, Saved, 10, 5);
			if (!Saved) {
				RemoveFormComplete(4);
				return;
			}
			checked = FindVtNode(root, vt_ma);
			if (vt_ma == "") {
				Notification("Ma vat tu khong duoc phep trong!");
				break;
			}
			//Kiem tra trong truong hop nhap
			if (checked != NULL) {
				Notification("Ma vat tu da ton tai!");
				vt_ma = "";
				RemoveForm(1);
				break;
			}
			step++;
			break;
		case 2: //nhap ten vat tu
			TypeWordAndSpace(vt_ten, step, Saved, 30, 5);
			if (vt_ten == "") {
				Notification("Ten vat tu khong duoc phep rong!");
				break;
			}
			step++;
			break;
		case 3: //nhap don vi tinh
			TypeOnlyAWord(vt_dvt, step, Saved, 10, 5);
			if (vt_dvt == "") {
				Notification("Don vi tinh khong duoc phep rong!");
				break;
			}
			step++;
			break;
		case 4: //nhap so luong ton
			if (Edited) {
				step++;
				break;
			}
			TypeOnlyNumber(vt_slton, step, Saved, 1000000, 5);
			if (vt_slton == 0) {
				Notification("So luong ton phai >= 1!");
				break;
			}
			step++;
			break;
		case 5: //tien hanh nhap hoac chinh sua vat tu
			if (Edited) {
				temp->data.ma_vt = vt_ma;
				temp->data.ten_vt = vt_ten;
				temp->data.dvt = vt_dvt;
				temp->data.sl_ton = vt_slton;

				Notification("Chinh sua vat tu thanh cong!");
				TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
				ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
				RemoveFormComplete(4);
				return;
			}
			else {
				vat_tu vt;
				vt.ma_vt = vt_ma;
				vt.ten_vt = vt_ten;
				vt.dvt = vt_dvt;
				vt.sl_ton = vt_slton;

				root = AddVt(root, vt);
				Notification("Them vat tu thanh cong!");
			}

			WriteVtToFile(root);
			vt_ma = "";
			vt_ten = "";
			vt_dvt = "";
			vt_slton = 0;
			step = 1;
			checked = NULL;
			temp = NULL;

			TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
			ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
			RemoveForm(4);
		}
	}
}

//--------- menu quan ly vat tu ---------
void MenuManageVT(Vt_Node& root) {
	system("color 0E");
	ShowCur(0);
	system("cls");

	CurVtPage = 1;
	TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
	Display(ContentVT, sizeof(ContentVT) / sizeof(string), true);
	ShowListVtOnePage(root, (CurVtPage - 1) * NumberPerPage);
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly vat tu ";

	int event;
	while (true) {
		while (_kbhit()) {
			event = _getch();//nhan biet cac ki tu dac biet
			if (event == ESC) {
				return;
			}
			if (event == 224) {
				event = _getch();//lay cac ki tu dac biet
				if (event == PAGE_UP && CurVtPage > 1) {
					CurVtPage--;
					ChangeVtManagerPage(root);
				}
				else if (event == PAGE_DOWN && CurVtPage < TotalVtPage) {
					CurVtPage++;
					ChangeVtManagerPage(root);
				}
				else if (event == INSERT) {//them moi vat tu
					string ContentVT[4] = { "Ma vat tu", "Ten vat tu", "Don vi tinh", "SL ton" };
					CreateInputForm(ContentVT, 4, 50);
					InputVt(root);
					ShowCur(0);
				}
				else if (event == DEL) {
					if (CountVtNode(root) == 0) {
						Notification("Danh sach rong, khong the xoa");
						return;
					}
					InputVt(root, false, true);
				}
				else if (event == HOME) {
					if (CountVtNode(root) == 0) {
						Notification("Danh sach rong, khong the chinh sua");
						return;
					}
					InputVt(root, true, false);
					ShowCur(0);
				}
			}
		}
	}
}

//---------- in thong tin nhan vien tren 1 trang ---------
void ShowListVtOnePageAscending(Vt_Node ds[], int StartIndex, int sl) {
	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong vat tu: " << sl;
	int i;
	for (i = 0; i + StartIndex < sl && i < NumberPerPage; i++) {
		ShowVt(ds[i + StartIndex]->data, i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurVtPageAscending << "/" << TotalVtPageAscending;
}

//---------- thay doi trang in nhan vien ----------
void ChangeVtManagerPageAscending(Vt_Node ds[], int sl) {
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly vat tu ";
	ShowListVtOnePageAscending(ds, (CurVtPageAscending - 1) * NumberPerPage, sl);
}

void DisplayAscendingNV(Vt_Node temp_ds[], int sl) {
	system("color 0E");
	ShowCur(0);
	system("cls");

	CurVtPageAscending = 1;
	TotalVtPageAscending = (int)ceil((double)sl / NumberPerPage);
	Display(ContentVT, sizeof(ContentVT) / sizeof(string), false);
	ShowListVtOnePageAscending(temp_ds, 0, sl);
	gotoxy(X_Title, Y_Title);
	cout << " Quan ly vat tu ";
}

//------ in danh sach vat tu tang dan theo ten -------
void PrintListVT(Vt_Node root) {
	Vt_Node temp_ds[Max_item];
	int temp_sl = 0;
	UpdateArrVtList(root, temp_ds, temp_sl);

	for (int i = 0; i < temp_sl; i++) {
		for (int j = i + 1; j < temp_sl; j++) {
			if (temp_ds[i]->data.ten_vt > temp_ds[j]->data.ten_vt) {
				Vt_Node t;
				t = temp_ds[i];
				temp_ds[i] = temp_ds[j];
				temp_ds[j] = t;
			}
		}
	}
	DisplayAscendingNV(temp_ds, temp_sl);
	int c;
	while (true) {
		while (_kbhit()) {
			c = _getch();
			if (c == ESC) {
				return;
			}
			if (c == 224) {
				c = _getch();//lay cac ki tu dac biet
				if (c == PAGE_UP && CurVtPageAscending > 1) {
					CurVtPageAscending--;
					ChangeVtManagerPageAscending(temp_ds, temp_sl);
				}
				else if (c == PAGE_DOWN && CurVtPageAscending < TotalVtPageAscending) {
					CurVtPageAscending++;
					ChangeVtManagerPageAscending(temp_ds, temp_sl);
				}
			}
		}
	}
}
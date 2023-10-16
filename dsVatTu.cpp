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
const int Max_itemVt = 1000;
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
		return root;
	}
	if (root->data.ma_vt == ID) {
		return root;
	}
	if (root->data.ma_vt < ID) {
		return FindVtNode(root->left, ID);
	}
	else {
		return FindVtNode(root->right, ID);
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
		//truong hop chi co 1 cay con ben phai
		if (root->left == NULL) {
			Vt_Node temp = root->right;
			delete root;
			return temp;
		}
		//truong hop chi co 1 cay con ben trai
		else if (root->right == NULL) {
			Vt_Node temp = root->left;
			delete root;
			return temp;
		}
		else {
			Vt_Node temp = MinVtNode(root);
			root->data = temp->data;
			root->right = DeleteVt(root->right, temp->data.ma_vt);
		}
	}

	//cap nhat lai do cao cua node
	root->height = max(height(root->left), height(root->right)) + 1;

	//can bang lai cay
	int BalanceFactor = getBalanceFactor(root);
	
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
	int xKeyContent[5] = {  };

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
void ShowListVtOnePage(Vt_Node root, Vt_Node VtNodeList[], int StartIndex, int &index) {
	UpdateArrVtList(root, VtNodeList, index);

	gotoxy(X_DisplayNum, Y_DisplayNum);
	cout << "So luong vat tu: " << index + 1;
	int i;
	for (i = 0; i + StartIndex <= index && i < NumberPerPage; i++) {
		ShowVt(VtNodeList[i + StartIndex]->data, i);
	}
	RemoveExceedMember(i, 4);
	gotoxy(X_Page, Y_Page);
	cout << " Trang " << CurVtPage << "/" << TotalVtPage;
}

//---------- thay doi trang in nhan vien ----------
void ChangeVtManagerPage(Vt_Node root, Vt_Node VtNodeList[], int& index) {
	gotoxy(X_Title, Y_Title);
	cout << " Quan li nhan vien ";
	ShowListVtOnePage(root, VtNodeList, (CurVtPage - 1) * NumberPerPage, index);
}

//-------- nhap 1 vat tu ----------
void InputVt(Vt_Node& root, Vt_Node VtNodeList[], int index, bool Edited = false, bool Deleted = false) {
	ShowCur(1);
	bool Saved = true; //bien kiem tra luu danh sach
	string vt_ma;
	string vt_ten;
	string vt_dvt;
	int vt_slton = 0;

	int step = 0;
	int event = 0;
	int target = -1;
	Vt_Node checked = NULL;
	
	while (true) {
		switch (step) {
		case 1: //nhap ma vat tu
			TypeWordAndNumber(vt_ma, step, Saved, 10, 5);
			if (!Saved) {
				RemoveFormComplete(3);
				return;
			}

			//kiem tra viec xoa thong tin
			if (Deleted) {
				if (FindVtNode(root, vt_ma) == NULL) {
					Notification("Ma vat tu khong ton tai!");
					break;
				}
				target = RemoveConfirm();
				RemoveFormComplete(1);
				if (target == 2) {
					return;
				}
				else {
					root = DeleteVt(root, vt_ma);
					Notification("Xoa vat tu thanh cong!");
				}

				TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
				ShowListVtOnePage(root, VtNodeList, (CurVtPage - 1) * NumberPerPage, index);
				WriteVtToFile(root);
				return;
			}

			checked = FindVtNode(root, vt_ma);
			if (vt_ma == "") {
				Notification("Ma vat tu khong duoc phep trong!");
				break;
			}
			//Kiem tra trong truong hop nhap
			if (checked != NULL && !Edited) {
				Notification("Ma vat tu da ton tai!");
				break;
			}
			//kiem tra trong truong hop chinh sua
			if (checked == NULL && Edited) {
				Notification("Ma vat tu khong ton tai!");
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
			if (checked != NULL) {
				Notification("Khong the nhap vi vat tu da ton tai!");
				step++;
				break;
			}
			TypeOnlyNumber(vt_slton, step, Saved, 8, 5);
			if (vt_slton == 0) {
				Notification("So luong ton phai >= 1!");
				break;
			}
			step++;
			break;
		case 5: //tien hanh nhap hoac chinh sua vat tu
			if (Edited && checked != NULL) {
				Vt_Node temp = FindVtNode(root, vt_ma);
				temp->data.ma_vt = vt_ma;
				temp->data.ten_vt = vt_ten;
				temp->data.dvt = vt_dvt;
				temp->data.sl_ton = vt_slton;
				Notification("Chinh sua vat tu thanh cong!");
			}
			else {
				vat_tu vt;
				vt.ma_vt = vt_ma;
				vt.ten_vt = vt_ten;
				vt.dvt = vt_dvt;
				vt.sl_ton = vt_slton;

				AddVt(root, vt);
				Notification("Them vat tu thanh cong!");
			}

			WriteVtToFile(root);
			vt_ma = "";
			vt_ten = "";
			vt_dvt = "";
			vt_slton = 0;
			step = 0;
			int target = -1;
			Vt_Node checked = NULL;

			TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
			ShowListVtOnePage(root, VtNodeList, (CurVtPage - 1) * NumberPerPage, index);
			RemoveForm(3);
		}
	}
}

//--------- menu quan ly vat tu ---------
void MenuManageVT(Vt_Node& root) {
	system("color 0E");
	ShowCur(0);
	system("cls");

	Vt_Node VtNodeList[Max_itemVt];
	int index = 0;
	CurVtPage = 1;
	TotalVtPage = (int)ceil((double)CountVtNode(root) / NumberPerPage);
	Display(ContentVT, sizeof(ContentVT) / sizeof(string), true);
	ShowListVtOnePage(root, VtNodeList, (CurVtPage - 1) * NumberPerPage, index);
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
					ChangeVtManagerPage(root, VtNodeList, index);
				}
				else if (event == PAGE_DOWN && CurVtPage < TotalVtPage) {
					CurVtPage++;
					ChangeVtManagerPage(root, VtNodeList, index);
				}
				else if (event == INSERT) {//them moi nhan vien
					CreateInputForm(ContentVT, 4, 50);
					InputVt(root, VtNodeList, index);
					ShowCur(0);
				}
				else if (event == DEL) {
					if (CountVtNode(root) == 0) {
						Notification("Danh sach rong, khong the xoa");
						return;
					}
					CreateInputForm(ContentVT, 1, 50);
					InputVt(root, VtNodeList, index, false, true);
				}
				else if (event == HOME) {
					if (CountVtNode(root) == 0) {
						Notification("Danh sach rong, khong the chinh sua");
						return;
					}
					CreateInputForm(ContentVT, 4, 50);
					InputVt(root, VtNodeList, index, true, false);
					ShowCur(0);
				}
			}
		}
	}
}
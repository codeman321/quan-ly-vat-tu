#pragma once
#include <iostream>
#include <string>

using namespace std;

struct vat_tu {
	string ma_vt;
	string ten_vt;
	string dvt;
	int sl_ton;
};

struct vt_Node {
	vat_tu data;
	vt_Node* left;
	vt_Node* right;
	int height;
};
typedef vt_Node* Vt_Node;

void CreateDsvt(Vt_Node& root);
Vt_Node MakeVtNode(vat_tu vt);
int height(Vt_Node root);
Vt_Node LeftRotation(Vt_Node x);
Vt_Node RightRotation(Vt_Node y);
int CountVtNode(Vt_Node root);
void UpdateArrVtList(Vt_Node root, Vt_Node VtNodeList[], int& index);
int getBalanceFactor(Vt_Node root);
Vt_Node AddVt(Vt_Node& root, vat_tu vt);
Vt_Node FindVtNode(Vt_Node root, string ID);
Vt_Node MinVtNode(Vt_Node root);
Vt_Node DeleteVt(Vt_Node& root, string ID);
void ShowVt(vat_tu vt, int pos);
void ShowListVtOnePage(Vt_Node root, Vt_Node VtNodeList[], int StartIndex, int& index);
void ChangeVtManagerPage(Vt_Node root, Vt_Node VtNodeList[], int& index);
void InputVt(Vt_Node& root, Vt_Node VtNodeList[], int index, bool Edited, bool Deleted);
void MenuManageVT(Vt_Node& root);
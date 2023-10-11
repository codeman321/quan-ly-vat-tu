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
};

struct ds_vat_tu {
	vt_Node* head = NULL;
	int n_vat_tu = 0;
};

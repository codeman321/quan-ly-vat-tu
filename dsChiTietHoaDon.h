#pragma once
#include <iostream>
#include <string>

using namespace std;

struct chi_tiet_hd {
	string maVT;
	int sl;
	double donGia;
	double VAT;
};

struct cthd_Node {
	chi_tiet_hd data;
	cthd_Node* next;
};

struct ds_chi_tiet_hd {
	cthd_Node* head = NULL;
	int n_cthd = 0;
};

void Init_cthd(chi_tiet_hd& cthd);
void AddLastCthd(ds_chi_tiet_hd& ds, chi_tiet_hd data);
bool DeleteLastCthd(ds_chi_tiet_hd& ds);
#pragma once
#include <iostream>
#include <string>
#include "dsHoaDon.h"
#include "GlobalVariables.h"

using namespace std;

struct nhan_vien {
	string maNV;
	string ho;
	string ten;
	string phai;
	ds_hoa_don *dshd = NULL;
};

struct dsNV {
	nhan_vien *dsnv[Max_NV];
	int n_nv = 0;
};

int FindIndexNV(dsNV ds, string ma);
bool IsDeleteNVSuccess(dsNV& ds, int index);
bool CheckInfoNVEmpty(nhan_vien* nv);
void ShowNV(nhan_vien* nv, int pos);
void ShowListNVOnePage(dsNV ds, int index);
void ChangeNVManagerPage(dsNV ds);
void inputNV(dsNV& ds, bool Edited, bool Deleted);
void MenuManageNV(dsNV& ds);
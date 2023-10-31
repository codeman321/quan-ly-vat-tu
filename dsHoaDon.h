#pragma once
#include <iostream>
#include <string>
#include "dsChiTietHoaDon.h"
#include "dsVatTu.h"

using namespace std;

struct date {
	int ngay = 0;
	int thang = 0;
	int nam = 0;
};

struct hoa_don {
	string soHD;
	date ngay_lapHD;
	char loai;
	ds_chi_tiet_hd *dscthd = new ds_chi_tiet_hd;
};

struct hd_Node {
	hoa_don data;
	hd_Node* next;
};

struct ds_hoa_don {
	hd_Node* head = NULL;
	int n_hd = 0;
};

void Init_hd(hoa_don& hd);
hd_Node* MakeHdNode(hoa_don data);
void AddLastListHD(ds_hoa_don*& dshd, hoa_don hd);
void InputFormHD(string ct[], int sl, int length);
hd_Node* FindSoHDExist(ds_hoa_don* dshd, string ID);
int PickHDType();
void TableOfHD();
void ShowVt(vat_tu vt, int pos);
void ShowListVtOnePage(Vt_Node root, int StartIndex, int CurVtPage, int TotalVtPage);
void ShowCTHD(cthd_Node* cthd_temp, Vt_Node root, int pos);
void ShowListCTHDOnePage(hd_Node* temp, Vt_Node root, int StartIndex, int CurHDPage, int TotalHDPage);
int PickFuncHD(Vt_Node root, hd_Node* temp, int CurHDPage, int TotalHDPage);

#pragma once
#include <iostream>
#include <string>
#include "dsChiTietHoaDon.h"

using namespace std;

struct date {
	int ngay;
	int thang;
	int nam;
};

struct hoa_don {
	string soHD;
	date ngay_lapHD;
	char loai;
	ds_chi_tiet_hd *dscthd = NULL;
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
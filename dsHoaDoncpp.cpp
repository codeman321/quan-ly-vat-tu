#include <iostream>
#include <string>
#include "dsHoaDon.h"

using namespace std;

void Init_hd(hoa_don& hd) {
	hd.soHD = "";
	hd.ngay_lapHD.ngay = 0;
	hd.ngay_lapHD.thang = 0;
	hd.ngay_lapHD.nam = 0;
	hd.loai;
}

//tao moi 1 node kieu hoa_don
hd_Node* MakeHdNode(hoa_don data) {
	hd_Node* temp = new hd_Node;
	temp->data = data;
	temp->next = NULL;
	return temp;
}
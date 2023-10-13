#include <fstream>
#include <iostream>
#include <string>
#include "mylib.h"
#include "ProcessionFile.h"
#include "dsNhanVien.h"

using namespace std;

void Introduction() {
	system("color 0E"); //nen den chu mau vang
	ShowCur(0);
	string temp;
	ifstream file("ptithcm.txt", ios::in);

	if (file.good()) {
		while (file.eof() == false) {
			getline(file, temp);
			cout << temp << endl;
		}
	}
	else {
		cout << "\n Liet ke file that bai" << endl;
	}
	Sleep(1000);
	return;
}

void WriteNVToFile(dsNV& ds) {
	ofstream fileout;
	fileout.open("DSNV.TXT", ios_base::out);// ios_base::out la de ghi vao file
	if (fileout.is_open()) {
		for (int i = 0; i < ds.n_nv; i++) {
			fileout << ds.dsnv[i]->maNV << "\n" << ds.dsnv[i]->ho << "\n" << ds.dsnv[i]->ten << "\n" << ds.dsnv[i]->phai << endl;
		}
	}
	else {
	
		Notification("Ket noi file de ghi vao that bai");
	}
	fileout.close();
}

/*Doc ghi file nhan vien*/
void ReadNVFile(dsNV& ds) {
	ifstream filein;
	filein.open("DSNV.TXT", ios_base::in);// ios_base::in la de doc

	string temp;
	int i = 0;
	if (filein.is_open()) {
		while (!filein.eof()) {
			nhan_vien* nv = new nhan_vien;
			getline(filein, nv->maNV);
			if (nv->maNV == "") continue; //neu ma->nv rong nghia la ds rong
			getline(filein, nv->ho);
			getline(filein, nv->ten);
			getline(filein,nv->phai);
			// cap nhat phan tu trong mang con tro
			ds.dsnv[i++] = nv;
			// cap nhat so luong phan tu trong mang
			ds.n_nv++;
		}
	}
	filein.close();
}
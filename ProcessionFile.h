#pragma once
#include <fstream>
#include "UserInterface.h"
#include "dsNhanVien.h"

using namespace std;

void Introduction();
void WriteNVToFile(dsNV& ds);
void ReadNVFile(dsNV& ds);
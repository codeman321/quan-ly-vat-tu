#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "mylib.h"
#include "GlobalVariables.h"

using namespace std;

void NormalLine();
void HighlightLine();
void DrawTable();
int scrollMenu(); 
void Menu();
void DrawRemoveTable();
int RemoveConfirm();
void RemoveFormComplete(int sl);
void RemoveForm(int sl);
void Notification(string nd);
void DeleteNotification();
void Display(string ct[], int sl);
void RemoveExceedMember(int cnt, int sl);
void CreateInputForm(string ct[], int sl, int length);

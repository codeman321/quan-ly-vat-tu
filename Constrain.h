#pragma once
#include <iostream>
#include <string>

using namespace std;

void TypeOnlyAWord(string& result, int step, bool& Saved, int Limit_word_lenght, int distance);
void TypeWordAndSpace(string& resultd, int step, bool& Saved, int Limit_word_lenght, int distance);
void TypeOnlyNumber(int& result, int step, bool& Saved, int Limit_number, int distance);
void TypeWordAndNumber(string& result, int step, bool& Saved, int Limit_word_lenght, int distance);
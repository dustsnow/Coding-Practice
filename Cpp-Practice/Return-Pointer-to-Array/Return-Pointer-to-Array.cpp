/**
 * @file Return-Pointer-to-Array.cpp
 * @author Peng Hou
 * @data Sep 13, 2013
 * @brief This file demonstrate how to return a pointer to an array
 */

#include <iostream>

using namespace std;

string a[2] = {"Hello","World"};
string b[2] = {"Ni Hao","Shi Jie"};

/// This function return one of the two predefined string arrays depending on the modular of the input i
string (*func(int i))[2]{
    return (i%2) ? &a : &b;
}
int main()
{
	//func will return a pointer. This pointer must be dereferenced first to be able to use the array
   cout << (*(func(1)))[0] << endl;
   return 0;
}

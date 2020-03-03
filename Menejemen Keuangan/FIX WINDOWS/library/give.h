#ifndef _give_h
#define _give_h

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
//#include <conio.h>
//#include <dir.h>
//#include <process.h>
#include <cstdio>
//#include <filesystem>
//#include <stdio.h>

//#include <direct.h>
//#include <windows.h>
//#include <io.h>

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

class Give
{
//membuat tanggal
time_t now = time(0);
//convert now to string form
tm *dt = localtime(&now);
//merubah tanggal dari INT menjadi String
int tanggal1 = dt->tm_mday;
int tanggal2 = 1 + dt->tm_mon;
int tanggal3 = 1900 + dt->tm_year;

public:
	void TerimaGive(string username_transfer, string username_reciver, int jumlah_uang)
	{
		stringstream give_masuk;
     	give_masuk << "Database/" << username_reciver << "/saldo/give.txt";
	    string give_masuk_str = give_masuk.str();

	    char * give_masuk_fix = new char[give_masuk_str.length()+1];
	    strcpy (give_masuk_fix,give_masuk_str.c_str()); 

	 	ofstream buat(give_masuk_fix, ios::app);
        buat << jumlah_uang;   
	}
};
#endif
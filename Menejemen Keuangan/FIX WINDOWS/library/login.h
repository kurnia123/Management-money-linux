#ifndef _login_h
#define _login_h

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
#include "pembaruan.h"

using namespace std;

	
struct LoginStruct{
	string username;
	string password;
	string line;
	string pilih_char;
	int pilih;
}T;

class Login{
public:
	bool pengecekan_isi_file(ifstream &pFile){
      return pFile.peek() == ifstream::traits_type::eof();
    }

	int DataLogin(Pembaruan baru)
	{
		//membuat tanggal
		time_t now = time(0);
		//convert now to string form
		tm *dt = localtime(&now);
		//merubah tanggal dari INT menjadi String
		int tanggal1 = dt->tm_mday;
		int tanggal2 = 1 + dt->tm_mon;
		int tanggal3 = 1900 + dt->tm_year;

		mkdir("Database");
		mkdir("Database/Data_account");

		awal:
		system("cls");
		cout << "================= chose login or signin =================" << endl;
		cout << "1. Buat akun\n2. sudah punya akun\n  Chose : ";
		cin >> T.pilih;
		awal1:
		system("cls");
		if (T.pilih==1)
		{
			cout << "Masukkan username : ";
			cin >> T.username;
			cout << "Masukkan password : ";
			cin >> T.password;
			//========================================== MEMASUKAN DATA ACCOUNT KE DATABASE ===============================
			stringstream id;
			id << "Database/Data_account/" << T.username << ".txt";
			string id_string = id.str();

			char * id_fix = new char[id_string.length()+1];
			strcpy(id_fix, id_string.c_str());			

			ofstream buat_akun(id_fix, ios::app);
			buat_akun << T.username << "," << T.password << endl;

			//================================================= MEMBUAT FOLDER DATABASE TIAP USER ================================================================

			stringstream date, coba, saldo_str_tetap, saldo_str_masuk, pengeluaran_str, pemasukan_str,saldo_str,pengeluaran_total_str,pemasukan_total_str;
			//================================================ Create Directory Database =======================================================================
		    coba << "Database/" << T.username;
		    string cobaa = coba.str();

		    char * coba1 = new char[cobaa.length()+1];
		    strcpy (coba1,cobaa.c_str());

		    mkdir(coba1);

		    pengeluaran_str << "Database/" << T.username << "/pengeluaran";
		    pemasukan_str << "Database/" << T.username << "/pemasukan";
		    saldo_str << "Database/" << T.username << "/saldo";
		    pengeluaran_total_str << "Database/" << T.username << "/pengeluaran/total";
		    pemasukan_total_str << "Database/" << T.username << "/pemasukan/total";
		    date << "Database/" << T.username << "/date";

		    string pengeluaran_direktori = pengeluaran_str.str();
		    string pemasukan_direktori = pemasukan_str.str();
		    string saldo_direktori = saldo_str.str();
		    string pengeluaran_direktori_total = pengeluaran_total_str.str();
		    string pemasukan_direktori_total = pemasukan_total_str.str();

		    char * pengeluaran_dir = new char[pengeluaran_direktori.length()+1];
		    strcpy (pengeluaran_dir,pengeluaran_direktori.c_str());

		    char * pemasukan_dir = new char[pemasukan_direktori.length()+1];
		    strcpy (pemasukan_dir,pemasukan_direktori.c_str());

		    char * saldo_dir = new char[saldo_direktori.length()+1];
		    strcpy (saldo_dir,saldo_direktori.c_str());

		    char * pengeluaran_dir_total = new char[pengeluaran_direktori_total.length()+1];
		    strcpy (pengeluaran_dir_total,pengeluaran_direktori_total.c_str());

		    char * pemasukan_dir_total = new char[pemasukan_direktori_total.length()+1];
		    strcpy (pemasukan_dir_total,pemasukan_direktori_total.c_str());

		    mkdir(pengeluaran_dir);
		    mkdir(pemasukan_dir);
		    mkdir(saldo_dir);
		    mkdir(pengeluaran_dir_total);
		    mkdir(pemasukan_dir_total);
		    //==================================================================================================================================================

		    //==================================== MEMBUAT ISI TANGGAL TIAP  USER =======================================
		    stringstream isi_date;
		    isi_date << "Database/" << T.username << "/date.txt" ;
				
			string str_date = isi_date.str();

			char * date_char = new char[str_date.length()+1];
			strcpy(date_char, str_date.c_str());			

			ofstream date_isi(date_char, ios::out);
			date_isi << tanggal2;
			//=============================================================================================================
			cout << "Pembuatan account berhasil, ingin langsung login [y/t] : ";
			cin >> T.pilih_char;
			if (T.pilih_char == "y" || T.pilih_char == "Y")
			{
				T.pilih = 2;
				goto awal1;
			}
			else if (T.pilih_char == "t" || T.pilih_char == "T")
			{
				goto awal;
			}
		}

		else if(T.pilih==2){
			cout << "Masukkan username : ";
			cin >> T.username;
			cout << "Masukkan password : ";
			cin >> T.password;
			//========================================== MENGAMBIL DATA DARI DATABASE DAN MEMBANDINGKANNYA ===============================
			stringstream id;
			id << "Database/Data_account/" << T.username << ".txt";
			string id_string = id.str();

			char * id_fix = new char[id_string.length()+1];
			strcpy(id_fix, id_string.c_str());	

			string gabungan = T.username + "," + T.password;

			//membuka isi file
			ifstream account(id_fix);
			//========= melakukan pengecekan file ============
			if (pengecekan_isi_file(account))
			{
				cin.get();
				cout << "Data tidak ditemukan" << endl;
				cin.get();
				goto awal;
			}
			//================================================
			//============ membandingkan isi database username & password dengan inputan kita ==============
			if (account.is_open())
			{
				while(getline(account, T.line)){
					if (T.line == gabungan)
					{
						baru.DataMain(T.username);
					}
				}
			}
			//==============================================================================================
			//============================================================================================================================
		}
		return 0;
	}
};
#endif

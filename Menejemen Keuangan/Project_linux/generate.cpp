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

//membuat tanggal
  time_t now = time(0);
  //convert now to string form
  tm *dt = localtime(&now);
  //merubah tanggal dari INT menjadi String
  int tanggal1 = dt->tm_mday;
  int tanggal2 = 1 + dt->tm_mon;
  int tanggal3 = 1900 + dt->tm_year;

  // system_clock::time_point today = system_clock::now();
  // time_t tt = system_clock::to_time_t(today);

  string waktu = ctime(&now);

void pengeluaran(string &username, string &data_tanggal_bulan, int &jumlah){
	for(int i=1;i<=31;i++){
				stringstream tanggal_bulan,tanggal_total;
	    		tanggal_total << "Database/" + username + "/pengeluaran/total/Pengeluaran-" << i << "-" << data_tanggal_bulan << ".txt";
				tanggal_bulan << "Database/" + username + "/pengeluaran/Pengeluaran-" << i << "-" << data_tanggal_bulan << ".txt";
				string bulan = tanggal_bulan.str();
	    		string total_bulan = tanggal_total.str();
			
				char * bulan_char = new char[bulan.length()+1];
				strcpy (bulan_char,bulan.c_str());

	            char * bulan_char_total = new char[total_bulan.length()+1];
	            strcpy (bulan_char_total,total_bulan.c_str());
					
				
				for (int i = 0; i < 5; ++i)
				{
		    		ofstream buat(bulan_char, ios::app);
			        buat << "kategori" << " \t= Rp." << jumlah << " " << waktu;
			        ofstream buat_total(bulan_char_total, ios::app);
			        buat_total << jumlah << endl;
				}
				cout << bulan_char << " Berhasil dibuat" << endl;
				cout << bulan_char_total << " Berhasil dibuat" << endl;
	}

	    cout << "Berhasil generate" << endl;
}

void pemasukan(string &username, string &data_tanggal_bulan, int &jumlah){
	for(int i=1;i<=31;i++){
				stringstream tanggal_bulan,tanggal_total;
	    		tanggal_total << "Database/" + username + "/pemasukan/total/Pemasukan-" << i << "-" << data_tanggal_bulan << ".txt";
				tanggal_bulan << "Database/" + username + "/pemasukan/Pemasukan-" << i << "-" << data_tanggal_bulan << ".txt";
				string bulan = tanggal_bulan.str();
	    		string total_bulan = tanggal_total.str();
			
				char * bulan_char = new char[bulan.length()+1];
				strcpy (bulan_char,bulan.c_str());

	            char * bulan_char_total = new char[total_bulan.length()+1];
	            strcpy (bulan_char_total,total_bulan.c_str());
					
				
				for (int i = 0; i < 5; ++i)
				{
		    		ofstream buat(bulan_char, ios::app);
			        buat << "kategori" << " \t= Rp." << jumlah << " " << waktu;
			        ofstream buat_total(bulan_char_total, ios::app);
			        buat_total << jumlah << endl;
				}
				cout << bulan_char << " Berhasil dibuat" << endl;
				cout << bulan_char_total << " Berhasil dibuat" << endl;
	}

	    cout << "Berhasil generate" << endl;
}

void MainPage(string &username, int &jumlah){
	string data_tanggal_bulan;
	int pilih;
	cout << "Masukkan data bulan yang akan ditampilkan (BB-TTTT): ";
  	cin >> data_tanggal_bulan;

  	cout << endl;
	cout << "========== pilih generate ==========" << endl;
	cout << "= 1. pengeluaran\n= 2. pemasukan \n= 3. pemasukan dan pengeluaran\n";
	cout << "pilih : ";
	cin >> pilih;

  	system("clear");

  	if (pilih == 1)
  	{
	    pengeluaran(username, data_tanggal_bulan, jumlah);
  	}

  	else if (pilih == 2)
  	{
  		pemasukan(username, data_tanggal_bulan, jumlah);	
  	}

  	else if (pilih == 3)
  	{
  		pemasukan(username, data_tanggal_bulan, jumlah);
  		cout << endl;
  		pengeluaran(username, data_tanggal_bulan, jumlah);
  	}
}


int main()
{
	string line;
	string aku;
	string username;
	string password;
	int jumlah = 10000;

	cout << "Masukkan Username : ";
	cin >> username;

	stringstream id;
	id << "Database/Data_account/" << username << ".txt";
	string id_string = id.str();

	char * id_fix = new char[id_string.length()+1];
	strcpy(id_fix, id_string.c_str());	

	ifstream file(id_fix);
	if (!file)
	{
		return 0;
	}
	else{
		MainPage(username, jumlah);
	}
	return 0;
}
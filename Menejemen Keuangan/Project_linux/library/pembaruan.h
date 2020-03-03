/*changelog 
23.dec.2018 - sedikit penyempurnaan ejaan, penyesuaian pilihan menu, sedikit merapihkan tampilan
25.dec.2018 - sedikit tambahan info pada L:568,596,674,704
*/
#ifndef _pembaruan_h
#define _pembaruan_h

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
#include <chrono>
//#include <filesystem>
//#include <stdio.h>

//#include <direct.h>
//#include <windows.h>
//#include <io.h>

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "give.h"
#include "sorting_uang.h"

using namespace std;
using std::chrono::system_clock;

struct variabel{
  string give_usr;
  int give_uang;
  int pilih;
  char pilih_detail;
}vrb;

struct nodelinked
{
    string barang;
    int jumlah;
    string tanggal;
    nodelinked *next;
};
nodelinked *awal_ptr = NULL, *posisi;


class Pembaruan{
  //INSTANCE CLASS GIVE
  Give obj_give;
  Sorting obj_sorting;

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


  public:

    char estimasi_cout(int nilai_estimasi, int saldo_copy_tetap){
        float tetap = saldo_copy_tetap;
        float saldo = nilai_estimasi;

        float hasil = tetap / saldo;
        int persen = 100 / hasil;
        char statistik[25];
        cout << "[ ";
        for (int i = 0; i < 25; ++i)
        {
          if (i <= persen/4)
          {
            statistik[i] = '=';
          }
          else
            statistik[i] = ' ';
        }

        for (int i = 0; i < 25; ++i)
        {
          cout << statistik[i];
        }
        cout << " ] " << persen;

        if (persen <= 20)
        {
          cout << "\n(!PERINGATAN UANG ANDA MENIPIS, MOHON MENGHEMAT PENGELUARAN ANDA)";
        }
        return '%';
    }

    int convert_string_to_integer(string &username){
      string line;
      string aku;
      //================== MERUBAH TEKS MENJADI CHAR* ===========================================
      string file = "Database/" + username + "/saldo/saldo.txt";
      // char * id_fix = new char[file.length()+1];
      // strcpy(id_fix, file.c_str());  
      //==========================================================================================

      ifstream pemasukan (file);

      //Membaca file dari saldo.txt
      if(pemasukan.is_open()){

        while( getline(pemasukan,line)){
          aku = line;
        }
        pemasukan.close();
      }
      //convert string to integer
      stringstream ss(aku);
      int x;
      ss >> x;
      return x;
    }

    int convert_string_to_integer_give(string &username){
      string line;
      string aku;
      int output = 0;
      //================== MERUBAH TEKS MENJADI CHAR* ===========================================
      stringstream give;
      give << "Database/" << username << "/saldo/give.txt";
      //==========================================================================================

      ifstream pemasukan (give.str());

      //Membaca file dari saldo.txt
      if(pemasukan.is_open()){

        while( getline(pemasukan,line)){
          aku = line;
          stringstream ss(aku);
          int x;
          ss >> x;
          output += x;
        }
        pemasukan.close();
      }
      //convert string to integer
      return output;
    }

    int convert_string_to_integer_date(string &username){
      string line;
      string aku;
      int output = 0;
      //================== MERUBAH TEKS MENJADI CHAR* ===========================================
      stringstream give;
      give << "Database/" << username << "/date.txt";
      //==========================================================================================

      ifstream pemasukan (give.str());

      //Membaca file dari date.txt
      if(pemasukan.is_open()){

        while( getline(pemasukan,line)){
          aku = line;
          stringstream ss(aku);
          int x;
          ss >> x;
          output = x;
        }
        pemasukan.close();
      }
      //convert string to integer
      
      return output;
    }

    int saldo_tetap(string &username){
      string line;
      string aku;
      //=============================================================================================
      string file = "Database/" + username + "/saldo/saldo_tetap.txt";
      // char * id_fix = new char[file.length()+1];
      // strcpy(id_fix, file.c_str());  
      //=============================================================================================
      ifstream pemasukan (file);

      if(pemasukan.is_open()){

        while( getline(pemasukan,line)){
          aku = line;
        }
        pemasukan.close();
      }
      //convert string to integer
      stringstream ss(aku);
      int x;
      ss >> x;
      return x;
    }

    //pengecekan isi file
    bool pengecekan_isi_file(ifstream &pFile){
      return pFile.peek() == ifstream::traits_type::eof();
    }

    int total_pengeluaran_dan_pemasukan(string tanggal){
      string line;
      string aku;
      int x = 0;

      char * total = new char[tanggal.length()+1];
      strcpy (total,tanggal.c_str());

      ifstream pemasukan (total);

      if(pemasukan.is_open()){

        while( getline(pemasukan,line)){
          aku = line;
          stringstream ss(aku);
          int tampung;
          ss >> tampung;
          x += tampung;
        }
        pemasukan.close();
      }
      return x;
    }

    void  proses_saldo_pengeluaran(int total, string &username){
    	//proses saldo
    	  int saldo_database;
        saldo_database = convert_string_to_integer(username);
        saldo_database -= total;
        //================================================================================================================
        string file = "Database/" + username + "/saldo/saldo.txt";
        char * id_fix = new char[file.length()+1];
        strcpy(id_fix, file.c_str()); 
        //================================================================================================================
        ofstream buat_saldo(id_fix, ios::out);
        buat_saldo << saldo_database;
    }

    void proses_saldo_pemasukan(int total, string &username){
      	//proses saldo
      	int saldo_database;
      	int saldo_database_tetap;
        saldo_database = convert_string_to_integer(username);
        saldo_database_tetap = saldo_tetap(username);
        saldo_database += total;
        saldo_database_tetap += total;
        //=======================================================================================================================
        string file = "Database/" + username + "/saldo/saldo.txt";
        char * id_fix = new char[file.length()+1];
        strcpy(id_fix, file.c_str()); 

        string file_tetap = "Database/" + username + "/saldo/saldo_tetap.txt";
        char * id_fix_total = new char[file_tetap.length()+1];
        strcpy(id_fix_total, file_tetap.c_str());  
        //=======================================================================================================================
        ofstream buat_saldo(id_fix, ios::out);
        buat_saldo << saldo_database;
        //mengubah database saldo tetap
        ofstream buat_saldo_tetap(id_fix_total, ios::out);
        buat_saldo_tetap << saldo_database_tetap;
    }

    void remove_data_pengeluaran_perbulan(string &tanggal,string &username){
    	for(int i=1;i<=31;i++){
    		//===================================================================================================================================
        stringstream tanggal_bulan,tanggal_bulan_total;
    		tanggal_bulan << "Database/" << username << "/pengeluaran/Pengeluaran-" << i << "-" << tanggal << ".txt";
    		tanggal_bulan_total << "Database/" << username << "/pengeluaran/total/Pengeluaran-" << i << "-" << tanggal << ".txt";
    		string bulan = tanggal_bulan.str();
    		string bulan_total = tanggal_bulan_total.str();
    		
    		char * bulan_char = new char[bulan.length()+1];
      	strcpy (bulan_char,bulan.c_str());

    		char * bulan_total_char = new char[bulan_total.length()+1];
     		strcpy (bulan_total_char,bulan_total.c_str());
      	//====================================================================================================================================
      		ifstream kuku(bulan_char);
     		if (!kuku.fail()) {
     			kuku.close();
    			remove(bulan_char);
    			remove(bulan_total_char);
    			cout << "File " << bulan_char << " berhasil dihapus " << endl;
    			cout << "File " << bulan_total_char << " berhasil dihapus " << endl;
      		}
      		//else
      			//cout << "file " << bulan_char << " tidak ditekuman" << endl;
    	}
    	//cin.get();
    }

    void remove_data_pemasukan_perbulan(string &tanggal, string &username){
    	for(int i=1;i<=31;i++){
        //===================================================================================================================================
    		stringstream tanggal_bulan,tanggal_bulan_total;
    		tanggal_bulan << "Database/" << username << "/pemasukan/Pemasukan-" << i << "-" << tanggal << ".txt";
    		tanggal_bulan_total << "Database/" << username << "/pemasukan/total/Pemasukan-" << i << "-" << tanggal << ".txt";
    		string bulan = tanggal_bulan.str();
    		string bulan_total = tanggal_bulan_total.str();
    			
    		char * bulan_char = new char[bulan.length()+1];
      		strcpy (bulan_char,bulan.c_str());

    		char * bulan_total_char = new char[bulan_total.length()+1];
     		strcpy (bulan_total_char,bulan_total.c_str());
      	//====================================================================================================================================
      	ifstream kuku(bulan_char);
     		if (!kuku.fail()) {
        		kuku.close();
    			remove(bulan_char);
    			remove(bulan_total_char);
    			cout << "File " << bulan_char << " berhasil dihapus " << endl;
    			cout << "File " << bulan_total_char << " berhasil dihapus " << endl;
      		}
      		//else
      			//cout << "file " << bulan_char << " tidak ditekuman" << endl;
    	}	
    	//cin.get();
    }

    void remove_pengeluaran_perhari(string &tanggal, string &username){
      //=======================================================================================================================================
    	stringstream tanggal_bulan,tanggal_bulan_total;
    	tanggal_bulan << "Database/" << username << "/pengeluaran/Pengeluaran-" << tanggal << ".txt";
    	tanggal_bulan_total << "Database/" << username << "/pengeluaran/total/Pengeluaran-" << tanggal << ".txt";
    	string bulan = tanggal_bulan.str();
    	string bulan_total = tanggal_bulan_total.str();
    			
    	char * bulan_char = new char[bulan.length()+1];
     	strcpy (bulan_char,bulan.c_str());

    	char * bulan_total_char = new char[bulan_total.length()+1];
     	strcpy (bulan_total_char,bulan_total.c_str());
      //=======================================================================================================================================
      ifstream kuku(bulan_char);
     	if (!kuku.fail()) {
       		kuku.close();
    		  remove(bulan_char);
    		  remove(bulan_total_char);
    		  cout << "File " << bulan_char << " berhasil dihapus " << endl;
    		  cout << "File " << bulan_total_char << " berhasil dihapus " << endl;
      }
      else
      	cout << "file " << bulan_char << " tidak ditekuman" << endl;
    }

    void remove_pemasukan_perhari(string &tanggal, string &username){
      //=======================================================================================================================================
    	stringstream tanggal_bulan,tanggal_bulan_total;
    	tanggal_bulan << "Database/" << username << "/pemasukan/Pemasukan-" << tanggal << ".txt";
    	tanggal_bulan_total << "Database/" << username << "/pemasukan/total/Pemasukan-" << tanggal << ".txt";
    	string bulan = tanggal_bulan.str();
    	string bulan_total = tanggal_bulan_total.str();
    			
    	char * bulan_char = new char[bulan.length()+1];
     	strcpy (bulan_char,bulan.c_str());

    	char * bulan_total_char = new char[bulan_total.length()+1];
     	strcpy (bulan_total_char,bulan_total.c_str());
      //=======================================================================================================================================
      ifstream kuku(bulan_char);
     	if (!kuku.fail()) {
       		kuku.close();
    		remove(bulan_char);
    		remove(bulan_total_char);
    		cout << "File " << bulan_char << " berhasil dihapus " << endl;
    		cout << "File " << bulan_total_char << " berhasil dihapus " << endl;
      	}
      	else
      		cout << "file " << bulan_char << " tidak ditekuman" << endl;
    }

    bool cek_saldo_0(int &outmakanan,string &username){
      int cek = convert_string_to_integer(username) - outmakanan;
      if (cek <= 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    void create_file_pengeluaran(string &username, string location, string location_total, string kategori, int jumlah, string tanggal){
          proses_saldo_pengeluaran(jumlah,username);
          ofstream buat(location, ios::app);
          buat << kategori << "\t = Rp." << jumlah << "\t " << tanggal;
          ofstream buat_total(location_total, ios::app);
          buat_total << jumlah << endl;
          // cout << "Transaksi Berasil dilakukan" << endl;
    }

    void create_file_pemasukan(string &username, string location, string location_total, string kategori, int jumlah, string tanggal){
          proses_saldo_pemasukan(jumlah,username);
          ofstream buat(location, ios::app);
          buat << kategori << "\t = Rp." << jumlah << "\t " << tanggal;
          ofstream buat_total(location_total, ios::app);
          buat_total << jumlah << endl;
          // cout << "Transaksi Berasil dilakukan" << endl;
    }

    void database_saldo(string location, string location_total, int &jumlah){

          ofstream buat(location, ios::out);
          ofstream buat_tetap(location_total, ios::out);
          buat_tetap << jumlah;
          buat << jumlah;
    }

    void tambah(string barang, int jumlah, string tanggal){
      nodelinked *temp, *temp2;

      temp = new nodelinked;
      temp->barang = barang;
      temp->jumlah = jumlah;
      temp->tanggal = tanggal;
      temp->next = NULL;

      //inisialisasi pointer ketika kosong
      if (awal_ptr==NULL)
      {
        awal_ptr = temp;
        posisi = awal_ptr;
      }
      else
      {
        temp2 = awal_ptr;
        while(temp2->next != NULL){
          temp2 = temp2->next;
        }
        temp2->next = temp;
      }
    }

    void DeleteDataList(){
      nodelinked *temp, *temp2;
      temp = awal_ptr;

      while(awal_ptr->next != NULL){
        temp = awal_ptr;
        awal_ptr = awal_ptr->next;
        delete temp;
      }
      temp = awal_ptr;
      delete temp;
      awal_ptr = NULL;
    }

    void cinDataBase_pengeluaran(string &username, string location, string location_total){
      nodelinked *temp, *temp2;
      temp = awal_ptr;
      if (temp == NULL)
      {
        cout << "Maaf data kosong" << endl;
      }
      else
      {
        while(temp != NULL){
          create_file_pengeluaran(username, location, location_total, temp->barang, temp->jumlah, temp->tanggal);
          temp = temp->next;
        }
        DeleteDataList();
      }
    }

    void cinDataBase_pemasukan(string &username, string location, string location_total){
      nodelinked *temp, *temp2;
      temp = awal_ptr;
      if (temp == NULL)
      {
        cout << "Maaf data kosong" << endl;
      }
      else
      {
        while(temp != NULL){
          create_file_pemasukan(username, location, location_total, temp->barang, temp->jumlah, temp->tanggal);
          temp = temp->next;
        }
        DeleteDataList();
      }

    }

    void TampilList(){
      nodelinked *temp;
      temp = awal_ptr;
      if (temp == NULL)
      {
        cout << "List masih kosong" << endl;
      }
      else
      {
        cout << endl;
        while(temp != NULL){
          cout << temp->barang << " " << temp->jumlah << " " << temp->tanggal;
          temp = temp->next;
        }
      }
    }


    //======================================================== FUNGSI MAIN ========================================================================================================
    int DataMain(string &username){
      //DEKLARASI
      string detail_info,gabungan_total;
      const int *saldo_copy;
      int saldo;
      int outmakanan, outkost,outtugas,oututang, outlain;
      int insaku,ingaji,inhutang,inlain;

      saldo_baru:
      stringstream saldo_str_tetap, saldo_str_masuk;
      //============================================================= INISIALISASI LOKASI DATABASE ========================================================================
      stringstream ss1,ss2,ss1_total,ss2_total,tanggal;
      ss1 << "Database/" << username << "/pengeluaran/Pengeluaran-" << tanggal1 << "-" << tanggal2 << "-" << tanggal3 << ".txt";
      ss2 << "Database/" << username << "/pemasukan/Pemasukan-" << tanggal1 << "-" << tanggal2 << "-" << tanggal3 << ".txt";
      ss1_total << "Database/" << username << "/pengeluaran/total/Pengeluaran-" << tanggal1 << "-" << tanggal2 << "-" << tanggal3 << ".txt";
      ss2_total << "Database/" << username << "/pemasukan/total/Pemasukan-" << tanggal1 << "-" << tanggal2 << "-" << tanggal3 << ".txt";

      saldo_str_masuk << "Database/" << username << "/saldo/saldo.txt";
      saldo_str_tetap << "Database/" << username << "/saldo/saldo_tetap.txt";
      //==================================================================================================================================
      cout << endl << "==== APLIKASI MANAJEMEN KEUANGAN PRIBADI ====" << endl << endl;

      //USER MENGINPUTKAN SALDO AWAL USER
      system("clear");
      //====================================== MELAKUKAN PENGECEKAN FILE SALDO SUDAH ADA ATAU BELUM ================================
      ifstream file(saldo_str_masuk.str());
      if (!file) {
        cout << "Masukkan Saldo awal : ";
        cin >> saldo;
        //memasukkan nilai saldo ke database
        database_saldo(saldo_str_masuk.str(),saldo_str_tetap.str(),saldo);

      }
      else if(pengecekan_isi_file(file)){
        cout << "Masukkan Saldo awal : ";
        cin >> saldo;
        //memasukkan nilai saldo ke database
        database_saldo(saldo_str_masuk.str(),saldo_str_tetap.str(),saldo);
      }
      //============================================================================================================================
      //================================================= MELAKUKAN PENGECEKAN TANGGAL PERBULAN ====================================
      stringstream isi_date;
      isi_date << "Database/" << username << "/date.txt" ;

      //membandingkan tanggal
      if (convert_string_to_integer_date(username) < tanggal2)
      {
        system("clear");
        cout << "sudah memasuki bulan baru, apakah anda sudah gajian [Y/T] : ";
        cin >> vrb.pilih_detail;
        if (vrb.pilih_detail == 'y' || vrb.pilih_detail == 'Y')
        {
          system("clear");
          cout << "masukkan jumlah gaji : ";
          int gaji, tempGaji;
          cin >> gaji;
          tempGaji = gaji;
          gaji += convert_string_to_integer(username);
          //mengganti jumlah saldo dan saldo tetap
          database_saldo(saldo_str_masuk.str(),saldo_str_tetap.str(),gaji);
          //mengganti tanggal di database user
          ofstream date_isi(isi_date.str(), ios::out);
          date_isi << tanggal2;
          //proses memasukkan data ke database informasi pemasukan
          create_file_pemasukan(username, ss2.str(), ss2_total.str(), "Gaji", tempGaji, waktu);

        }
        else
        {
          cout << "Semoga uang anda cukup untuk kebutuhan sehari - hari" << endl;
          cin.get();
          ofstream date_isi(isi_date.str(), ios::out);
          date_isi << tanggal2;
        }
      }
      else
      {

      }
      //===========================================================================================================================

      //======================================= PENGECEKAN GIVE DARI USER LAIN =====================================================
      stringstream give_masuk;
      give_masuk << "Database/" << username << "/saldo/give.txt";
      string give_masuk_str = give_masuk.str();


      ifstream give(give_masuk.str());
      if (!give)
      {
          
      }
      else 
      {
        cout << "Ada give yang masuk nih mau diambil [Y/T] : ";
        cin >> vrb.pilih_detail;
        if (vrb.pilih_detail == 'y' || vrb.pilih_detail == 'Y')
        {
            //proses penambahan saldo dari give
            int tempGive = convert_string_to_integer_give(username);
            remove(give_masuk_str.c_str());
            proses_saldo_pemasukan(convert_string_to_integer_give(username), username);
            cout << "Give berhasil diterima" << endl;

            //proses memasukkan data ke database informasi pemasukan
            create_file_pemasukan(username, ss2.str(), ss2_total.str(), "Give", tempGive, waktu);

        }
        else if (vrb.pilih_detail == 't' || vrb.pilih_detail == 'T')
        {
            //menghapus file give.txt
            remove(give_masuk_str.c_str());
        }
      }

      //==========================================================================================================================
      start :
      time_t now = time(0);
      //convert now to string form
      tm *dt = localtime(&now);
      system("clear");
      cout << "User : " << username;
      cout << endl << "==== APLIKASI MANAJEMEN KEUANGAN PRIBADI ====" << endl << endl;
      //USER INFO
      cout << endl << "====================== INFO ======================" << endl << endl;
      cout << "= Tanggal  : " << dt->tm_mday << "-" << dt->tm_mon + 1 << "-" << 1900 + dt->tm_year << endl;
      cout << "= Saldo    : " << convert_string_to_integer(username) << endl;
      cout << "= Status   : ";
      cout << estimasi_cout(convert_string_to_integer(username), saldo_tetap(username)) << endl;
      cout << "==================================================" << endl << endl;
      //MAIN MENU
      cout << "------------MENU------------" << endl;
      cout << "= (1) Tambahkan Pengeluaran" << endl <<
              "= (2) Tambahkan Pemasukkan" << endl <<
              "= (3) Info Masukan" << endl <<
              "= (4) Info Pengeluaran" << endl <<
              "= (5) Hapus Data" << endl <<
    		      "= (6) Give" << endl <<
              "= (7) Keluar" << endl;
      cout << "Masukkan pilihan : ";
      cin >> vrb.pilih;

    //=============================================================== PEMILIHAN 1 (PENGELUARAN) PAGE UTAMA ========================================================================
    if (vrb.pilih == 1) {
      	pengeluaran:
      	system("clear");
        //Tambahkan Pengeluaran
        cout << endl << endl;
        cout << "---=Tambah Pengeluaran=---" << endl;
        cout << "= (1) Lain-lain (tuliskan sendiri) \n= (2) Kembali"<<endl;
        cout << "Pilih Kategori : ";
        cin >> vrb.pilih;
        // ofstream buat(tanggal_pengeluaran, ios::app);
        //=======================================================================================================================
        if(vrb.pilih == 1){
          //menambahkan karakter spasi di string
          char pilih = 'y';
          while (pilih == 'y' || pilih == 'Y'){
              system("clear");
              //========= menampilkan list yang akan dimasukkan ke database ==========
              TampilList();
              cout << endl;
              string pengeluaran_lain_lain="";
              cout << "Tulis kategori pengeluaran : ";
              cin.ignore();
              getline(cin,pengeluaran_lain_lain);
              
              cout << "Jumlah pengeluaran untuk lain-lain : ";
              cin >> outlain;
              //cek saldo 
              if (cek_saldo_0(outlain,username) == true)
              {
                  cin.get();
                  cout << "Maaf uang anda tidak cukup untuk melakukan transaksi" << endl;
                  cin.get();
                  goto pengeluaran;
              }
              //=========== MEMANGGIL FUNGSI LINKEDLIST ==============
              tambah(pengeluaran_lain_lain, outlain, waktu);
              cout << "Mau menamnahkan lagi[y/t] : ";
              cin >> pilih;
          }
          cinDataBase_pengeluaran(username, ss1.str(), ss1_total.str());
          cout << "Transaksi berhasil dilakukan" << endl;

        }
        //=======================================================================================================================
        else if(vrb.pilih == 2){
    		  goto start;
        }
        //=======================================================================================================================
        else{
            cout << "Input tidak valid";
            system ("pause");
            system ("clear");
            goto pengeluaran;
        }
        //=======================================================================================================================
        //PROMPT BAGI USER APABILA USER INGIN MENCATAT PENGELUARAN LAGI
        pilihan3:
        cout << "Apakah anda ingin mencatat pengeluaran lagi? (Y/T) :";
        cin >> vrb.pilih_detail;
        if (vrb.pilih_detail=='y' || vrb.pilih_detail=='Y' ){
        	goto pengeluaran;
        }
        else if(vrb.pilih_detail=='t' || vrb.pilih_detail=='T'){
    		  system("clear");
    		  goto start;
        }
        else{
    		  cout << "Input tidak valid";
    		  goto pilihan3;
        }
    }
    //=============================================================================================================================================================================
    //=============================================================== PEMILIHAN 2 (PEMASUKAN) PAGE UTAMA ==========================================================================
    else if(vrb.pilih == 2){
    	masukan:
    	system("clear");
        //Tambahkan Masukan
        cout << endl << endl;
        cout << "---=Tambah Pemasukkan=---" << endl;
        cout << "= (1) Lain-Lain \n= (2) Kembali" << endl;
        cout << "Pilih Kategori : ";
        cin >> vrb.pilih;
        // ofstream buat(tanggal_pemasukan, ios::app);
        // ofstream buat_total(tanggal_pemasukan_total_file, ios::app);
        //=======================================================================================================================
        if(vrb.pilih == 1){
          //menambahkan karakter spasi di string
          char pilih = 'y';
          while(pilih == 'y' || pilih == 'Y'){
              system("clear");
              //menampilkan list data yang akan dimasukkan ke database pemasukan
              TampilList();
              cout << endl;
              string pemasukan_lain_lain = "";
              cout << "Tulis kategori pemasukan : ";
              cin.ignore();
              getline(cin,pemasukan_lain_lain);
              
              cout << "Jumlah masukan dari lain-lain : ";
              cin >> inlain;

              //menambah linkedlist
              tambah(pemasukan_lain_lain, inlain, waktu);
              cout << "Mau menamnahkan lagi[y/t] : ";
              cin >> pilih;
          }
          //membuat fiel database pemasukan
          cinDataBase_pemasukan(username, ss2.str(), ss2_total.str());
          cout << "Transaksi berhasil dilakukan" << endl;
        }
        //=======================================================================================================================
        else if(vrb.pilih == 2){
    		  goto start;
        }	
        //=======================================================================================================================
        else{
          cout << "Input tidak valid";
          system ("clear");
          goto masukan;
        }
        //=======================================================================================================================
        pilihan4:
        //PROMPT APAKAH USER INGIN MENCATAT MASUKAN LAGI
        cout << "Apakah anda ingin mencatat masukan yang lain? (y/n)";
        cin >> vrb.pilih_detail;
        if (vrb.pilih_detail=='y' || vrb.pilih_detail=='Y'){
        	system("clear");
        	goto masukan;
        } 
        else if (vrb.pilih_detail=='n' || vrb.pilih_detail=='N'){
    		  system ("clear");
    		  goto start;
        }
        else{
    		  cout << "Input tidak valid";
    		  system("pause");
    		  goto pilihan4;
        }
    }
    //=============================================================================================================================================================================
    //=============================================================== PEMILIHAN 3 (INFO MASUKAN) PAGE UTAMA =======================================================================
    else if(vrb.pilih == 3){
        percabangan3:
        system("clear");
        cin.get();
        cout << endl << "---=Info Masukan=---" << endl;
        cout << "= (1) Uang Saku : " << "0" <<endl;
        cout << "= (2) Gaji : " << "0" <<endl;
        cout << "= (3) Hutang : " << "0" <<endl;
        cout << "= (4) Lain-lain : " << "0" <<endl;
        //mengakses File database pemasukan
        cout << "= (5) Ingin melihat detail pemasukan [Y/T] : ";
        cin >> vrb.pilih_detail;
        //=======================================================================================================================
        if(vrb.pilih_detail == 'Y' || vrb.pilih_detail == 'y'){
        	system("clear");
            cout << "--==PILIH TAMPILAN DATA==--" << endl;
            cout << "= (1) Detail Perhari " << endl;
            cout << "= (2) Detail Perbulan " << endl;
            cout << "Masukkan pilihan : ";
            cin >> vrb.pilih;
            cout << endl;
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //tampilkan data perhari
            if(vrb.pilih == 1){
            	string line;
            	string aku;
            	cout << "Masukkan data tanggal (HH-BB-TTTT): ";
            	cin >> detail_info;

              stringstream gabungan, gabungan_total;
              gabungan << "Database/" << username << "/pemasukan/Pemasukan-" << detail_info << ".txt";
              gabungan_total << "Database/" << username << "pemasukan/total/Pemasukan-" << detail_info << ".txt";

              //merubah string manejadi char
            	system("clear");
            	cout << detail_info << endl << endl;

            	ifstream pemasukan(gabungan.str());
            	if(pemasukan.is_open()){
              		while( getline(pemasukan,line)){
                		cout << line << endl;
              		}
             	    pemasukan.close();
             	    cout << "TOTAL MASUKAN : " << total_pengeluaran_dan_pemasukan(gabungan_total.str());
            	}
            	cin.get();
    		    }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    		    //tampilkan data perbulan
        		else if(vrb.pilih==2){
        			string data_tanggal_bulan;
        			string line;
        			string aku;
              int nilai;
        			
              cout << "Masukkan data bulan yang akan ditampilkan (BB-TTTT): ";
              cin >> data_tanggal_bulan;
              system("clear");

              obj_sorting.sorting_data_pemasukan(username, data_tanggal_bulan);
        			cin.get();
        		}
        		else
        			cout << "Masukkan anda salah" <<endl;
        			cin.get();
        			goto percabangan3;
            
        }
        //=======================================================================================================================
        else if(vrb.pilih_detail == 'T' || vrb.pilih_detail =='t'){
             goto start;
        }
        //=======================================================================================================================
        else{
            cout << "Masukkan anda salah [Y/T]" << endl;
            goto percabangan3;
        }
    }
    //=============================================================================================================================================================================
    //=============================================================== PEMILIHAN 4 (INFO PENGELUARAN) PAGE UTAMA ===================================================================
    else if(vrb.pilih == 4){
        percabangan4 :
        system("clear");
        cin.get();
        cout << endl << "---=Info Pengeluaran=---" << endl;
        cout << "= (1) Makanan : " << "0" << endl;
        cout << "= (2) Keperluan Kost : " << "0" << endl;
        cout << "= (3) Keperluan Tugas : " << "0" << endl;
        cout << "= (4) Bayar Hutang : " << "0" << endl;
        cout << "= (5) Lain-lain : " << "0" << endl;
        //mengakses File database pengeluaran
        cout << "= (6) Ingin melihat detail pengeluaran [Y/T] : ";
        cin >> vrb.pilih_detail;
        //=======================================================================================================================
        if(vrb.pilih_detail == 'Y' || vrb.pilih_detail == 'y'){
        	system("clear");
            cout << "--==Pilih Tampilan Data==--" << endl;
            cout << "= (1) Detail Harian " << endl;
            cout << "= (2) Detail Bulanan " << endl;
            cout << "Masukkan pilihan : ";
            cin >> vrb.pilih;
            cout << endl;
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(vrb.pilih==1){
            	string line;
            	string aku;
            	cout << "Masukkan data tanggal (HH-BB-TTTT): ";
            	cin >> detail_info;

              stringstream gabungan, gabungan_total;
              gabungan << "Database/" << username << "/pengeluaran/Pengeluaran-" << detail_info << ".txt";
              gabungan_total << "Database/" << username << "/pengeluaran/total/Pengeluaran-" << detail_info << ".txt";

            	system("clear");
            	cout << detail_info << endl << endl;

            	ifstream pemasukan(gabungan.str());

            	if(pemasukan.is_open()){
              		while(getline(pemasukan,line)){
               	 		cout << line << endl;
              		}
                  pemasukan.close();
                  cout << "TOTAL Pengeluaran : " << total_pengeluaran_dan_pemasukan(gabungan_total.str());
            	}
              cin.get();
    		    }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          	else if(vrb.pilih==2){
            	string data_tanggal_bulan;
        			string line;
        			string aku;
      			
            	cout << "Masukkan data bulan yang akan ditampilkan (BB-TTTT): ";
            	cin >> data_tanggal_bulan;
            	system("clear");

              obj_sorting.sorting_data_pengeluaran(username, data_tanggal_bulan);
              cin.get();
      		  }
    		    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        		else
        			cout << "Data yang anda masukan salah" << endl;
        			cin.get();
        			goto percabangan4;
            }
        //=======================================================================================================================
        else if(vrb.pilih_detail == 'T' || vrb.pilih_detail =='t'){
            goto start;
        }
        //=======================================================================================================================
        else{
            cout << "Masukkan anda salah [Y/T]" << endl;
            goto percabangan4;
        }
    }
    //=============================================================================================================================================================================
    //=============================================================== PEMILIHAN 5 (HAPUS DATA) PAGE UTAMA =========================================================================
    else if(vrb.pilih == 5){
    	hapus:
    	system("clear");
    	cout << "---=Pilih Tipe Data=---" << endl << endl;
    	cout << "= (1) Hapus data pengeluaran" <<endl;
    	cout << "= (2) Hapus data pemasukan" << endl;
    	cout << "= (3) Hapus keseluruhan" << endl;
    	cout << "= (4) Kembali" << endl;
    	cout << "Masukkan pilihan : ";
    	cin >> vrb.pilih;
    	//=======================================================================================================================
    	if(vrb.pilih==1){
    		pemilihan1:
    		system("clear");
    		cout << "--==Hapus Data Pengeluaran==--" << endl;
    		cout << "= (1) Hapus per-Hari" <<endl;
    		cout << "= (2) Hapus per-Bulan" << endl;
    		//cout << "= (3) Hapus semua data pengeluaran" << endl;
    		cout << "= (3) Kembali" << endl;
    		cout << "Masukkan pilihan : ";
    		cin >> vrb.pilih;
    		//====================vrb.pilih===========================
    		if(vrb.pilih == 1){
    			string data_tanggal;
            	cout << "Masukkan data hari yang akan dihapus : ";
            	cin >> data_tanggal;
            	system("clear");
            	
            	remove_pengeluaran_perhari(data_tanggal,username);
            	cin.get();
    		}
        //====================vrb.pilih===========================
    		else if(vrb.pilih == 2){
    			string data_tanggal_bulan;
            	cout << "Masukkan data bulan yang akan dihapus : ";
            	cin >> data_tanggal_bulan;
            	system("clear");
            	
            	remove_data_pengeluaran_perbulan(data_tanggal_bulan,username);
            	cin.get();
    		}
    		else if(vrb.pilih == 3){
    			goto hapus;
    		}
    		else
    			cout << "Masukkan anda Salah";
    			cin.get();
    			goto pemilihan1;
    	}
    	//=======================================================================================================================
      //=======================================================================================================================
    	else if(vrb.pilih == 2){
    		pemilihan2:
    		system("clear");
    		cout << "---=Hapus Data Pemasukkan=---" << endl;
    		cout << "= (1) Hapus per-Hari" <<endl;
    		cout << "= (2) Hapus per-Bulan" << endl;
    		//cout << "= (3) Hapus semua data pemasukan" << endl;
    		cout << "= (3) Kembali" << endl;
    		cout << "Masukkan pilihan : ";
    		cin >> vrb.pilih;
    		if(vrb.pilih == 1){
    			string data_tanggal;
            	cout << "Masukkan data hari yang akan dihapus : ";
            	cin >> data_tanggal;
            	system("clear");
            	
            	remove_pemasukan_perhari(data_tanggal,username);
            	cin.get();
    		}
    		else if(vrb.pilih == 2){
    			string data_tanggal_bulan;
            	cout << "Masukkan data bulan yang akan dihapus : ";
            	cin >> data_tanggal_bulan;
            	system("clear");
            	
            	remove_data_pemasukan_perbulan(data_tanggal_bulan,username);
            	cin.get();
    		}
    		
    		else if(vrb.pilih == 3){
    			goto hapus;
    		}
    		else
    			cout << "Masukkan anda Salah";
    			cin.get();
    			goto pemilihan1;
    	}
      //=======================================================================================================================
      //=======================================================================================================================
    	else if(vrb.pilih == 3){
    		fstream saldo_masuk;
    		fstream saldo_total;
    		//menghapus isi file bukan direktori
    		saldo_masuk.open("Database/" + username + "/saldo/saldo.txt",ios::out | ios::trunc);
    		saldo_total.open("Database/" + username + "/saldo/saldo_tetap.txt",ios::out | ios::trunc);

        string pemasukan = "rm -r Database/" + username + "/pemasukan/* && mkdir Database/" + username + "/pemasukan/total";
        string pengeluaran = "rm -r Database/" + username + "/pengeluaran/* && mkdir Database/" + username + "/pengeluaran/total";
    			
    		system(pemasukan.c_str());
    		system(pengeluaran.c_str());
    			
    		saldo_masuk.close();
    		saldo_total.close();
    		
    		goto saldo_baru;
    		system("pause");
    	}
      //=======================================================================================================================
      //=======================================================================================================================
    	else if(vrb.pilih == 4){
    		goto start;
    	}
      //=======================================================================================================================
      //=======================================================================================================================
    	else
    		cout << "data yang anda masukkan salah";
    		cin.get();
    		goto hapus;
      //=======================================================================================================================
    }
    //=============================================================================================================================================================================
    //================================================================ PEMILIHAN 6 (GIVE) PAGE UTAMA ==============================================================================
    else if (vrb.pilih == 6){
        masuk_username:
        system("clear");
        cout << "User : " << username << endl;
        cout << "Masukkan username orang yang akan diberi : ";
        cin >> vrb.give_usr;
        //=======================================================================================================================
        if (vrb.give_usr==username)
        {
            cin.get();
            cout << "Tidak bisa mengirim ke akun sendiri" << endl;
            cin.get();
            goto masuk_username;
        }
        //=======================================================================================================================
        else
        {
            stringstream id;
            id << "Database/Data_account/" << vrb.give_usr << ".txt";
            string id_string = id.str();

            char * user_give = new char[id_string.length()+1];
            strcpy(user_give, id_string.c_str());

            ifstream file(user_give);
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //pengecekan user yang akan dikirim
            if (!file)
            {
              cin.get();
              cout << "User tidak ditemukan";
              cin.get();
              goto start;
            }
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            else
            {
              masukkan_uang:
              system("clear");
              cout << "============================ INFO ==========================" << endl;
              cout << "\tUser : " << username << endl;
              cout << "\tTujuan user yang diberi : " << vrb.give_usr << endl;
              cout << "============================================================" << endl;
              cout << "Jumlah uang yang akan diberikan : ";
              cin >> vrb.give_uang;

              int cek_saldo = convert_string_to_integer(username) - vrb.give_uang;
              //*************************************************************************************
              //pengecekan saldo sebelum dikirim
              if (cek_saldo <= 0)
              {
                  cout << "saldo anda tidak cukup untuk untuk melakukan give" << endl;
                  cout << "Ingin melanjutkan traksaksi [Y/T] : ";
                  char keluar;
                  cin >> keluar;
                  if (keluar == 'y' || keluar == 'Y')
                  {
                      goto masukkan_uang;
                  }
                  else if (keluar == 't' || keluar == 'T')
                  {
                      goto start;
                  }
              }
              //*************************************************************************************
              else 
              {
                //memasukkan pengeluaran ke databse pengeluaran
                create_file_pengeluaran(username, ss1.str(), ss1_total.str(), "Give to " + vrb.give_usr, vrb.give_uang, waktu);

                obj_give.TerimaGive(username, vrb.give_usr, vrb.give_uang);

                cout << "Give berhasil dilakukan " << endl;
                cout << "Apakah anda ingin memberi lagi [Y/T] : ";
                char keluar;
                cin >> keluar;
                if (keluar == 'y' || keluar == 'Y')
                {
                    goto masukkan_uang;
                }
                else if (keluar == 't' || keluar == 'T')
                {
                    goto start;
                }
              }
            }
        }
    }
    //=============================================================================================================================================================================
    //================================================================ PEMILIHAN 7 (MENU EXIT) PAGE UTAMA =========================================================================
    else if(vrb.pilih == 7){
        char keluar;
        cout << "Apakah anda yakin ingin keluar? (Y/N) : ";
        cin >> keluar;
        	
        if (keluar == 'y' || keluar == 'Y'){
        	cout << endl << "Terimakasih! Sampai Jumpa" << endl;
          exit (0);	
    		}
        else if (keluar == 'n' || keluar == 'N'){
    			system("clear");
    			goto start;
    		}
        else{
    			cout << "Harap Masukkan Inputan yang benar!";
    		} 	
    }
    //=============================================================================================================================================================================
    	cin.get();
    	cout << "Data yang anda masukkan salah" << endl;
    	cin.get();
    	goto start;


    return 0;
    }
};
#endif
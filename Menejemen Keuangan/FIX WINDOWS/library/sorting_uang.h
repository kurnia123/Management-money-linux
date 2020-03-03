#ifndef _sorting_uang_h
#define _sorting_uang_h 

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

struct LinkData{
  LinkData *previous;
  string tggl;
  int total;
  LinkData *next;
};

LinkData *awalPtr = NULL, *akhir, *temptampil;

class Sorting
{
public:
  string TempTanggal;
  /////////// ADD LIST TO LINKED LIST ////////////////
  void Tambah(string tanggal, int total){
    LinkData *temp, *temp2;
    temp = new LinkData;
    temp->previous = NULL;
    temp->tggl = tanggal;
    temp->total = total;
    temp->next = NULL;

    if (awalPtr == NULL)
    {
      awalPtr=akhir=temp;
    }
    else
    {
      temp2 = awalPtr;
      while(temp2->next != NULL){
        temp2 = temp2->next;
      }
      temp2->next = temp;
      temp->previous =  temp2;
      akhir = temp;
    }
  }
  ///////////// DELETE LIST FROM LINKED LIST ////////////////
  void DeleteList(){
    LinkData *temp, *temp2;
    temp = awalPtr;

    while(awalPtr->next != NULL){
      temp = awalPtr;
      awalPtr = awalPtr->next;
      delete(temp);
    }
    temp = awalPtr;
    delete(temp);
    awalPtr =  NULL;
  }
  /////////////// SORTING DATA ////////////////
  void sortingLst(){
    LinkData * temphead = awalPtr;
    LinkData * TempNode = NULL;

    int tempTotal;
    string tmpdate;

    int counter = 0;

    //mengecek banyaknya jumlah link pad linkedlist
    while(temphead->next != NULL){
      temphead = temphead->next;
      counter++;
    }

    for (int i = 0; i < counter; ++i)
    {
      while(temphead->next != NULL)
      {
        if (temphead->total >  temphead->next->total)
        {
          //node tetap diam tidak berubah
          //memindahkan posisi total
            tempTotal = temphead->total;
            temphead->total = temphead->next->total;
            temphead->next->total = tempTotal;
            //memindah posisi tanggal
            tmpdate = temphead->tggl;
            temphead->tggl = temphead->next->tggl;
            temphead->next->tggl  = tmpdate;
        }
        temphead = temphead->next;
      }
      temphead = awalPtr;
    }
  }

  void tampilKecil(int pilih, string username){
    temptampil = awalPtr;
    while(temptampil != NULL){
        stringstream gabungStr;
        string line, aku;

        if (pilih==1)
        {
          gabungStr << "Database/" << username << "/pemasukan/Pemasukan-" << temptampil->tggl << ".txt";
        }
        else if (pilih==2)
        {
          gabungStr << "Database/" << username << "/pengeluaran/Pengeluaran-" << temptampil->tggl << ".txt";
        }

        char * strfix = new char[gabungStr.str().length()+1];
        strcpy(strfix, gabungStr.str().c_str());

        ifstream pemasukan1(strfix);
        
        if(pemasukan1.is_open()){
          cout << endl;
          cout <<  "Tanggal : "  << temptampil->tggl << endl;
          while( getline(pemasukan1,line)){
             aku = line;
             cout << aku << endl;
          }
          pemasukan1.close();
          cout << "Total Pengeluaran : " << temptampil->total;
          cout << endl;
        }
        temptampil = temptampil->next;
    }
    DeleteList();
  }


  void tampilBesar(int pilih, string username){
    temptampil = akhir;
    while(temptampil != NULL){
        string line, aku;
        stringstream gabungStr;

        if (pilih==1)
        {
          gabungStr << "Database/" << username << "/pemasukan/Pemasukan-" << temptampil->tggl << ".txt";
        }
        else if (pilih==2)
        {
          gabungStr << "Database/" << username << "/pengeluaran/Pengeluaran-" << temptampil->tggl << ".txt";
        }

        char * strfix = new char[gabungStr.str().length()+1];
        strcpy(strfix, gabungStr.str().c_str());

        ifstream pemasukan1(strfix);
        
        if(pemasukan1.is_open()){
          cout << endl;
          cout <<  "Tanggal : "  << temptampil->tggl << endl;
          while(getline(pemasukan1,line)){
             aku = line;
             cout << aku << endl;
          }
          pemasukan1.close();
          cout << "Total Pengeluaran : " << temptampil->total;
          cout << endl;
        }
        temptampil = temptampil->previous;
    }
    DeleteList();
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

	void sorting_data_pemasukan(string &username, string &data_tanggal_bulan){
    int nilai=0;
    int temp, choice;

    for (int i = 1; i <= 31; ++i)
    {
      stringstream ss,temp_tanggal;
      ss << "Database/" << username << "/pemasukan/total/Pemasukan-" << i << "-" << data_tanggal_bulan << ".txt";
      temp_tanggal << i <<"-" << data_tanggal_bulan;

      char * pemasukan_str = new char[ss.str().length()+1];
      strcpy(pemasukan_str, ss.str().c_str());

      TempTanggal = temp_tanggal.str();
      temp = total_pengeluaran_dan_pemasukan(pemasukan_str); 
      //meanmabahkan ke list linked list
      Tambah(TempTanggal, temp);
    }

    sortingLst();
    cout << "Urutkan berdasarkan  : "  << endl;
    cout << "1. Kecil -> Besar\n2. Besar -> Kecil\nPilih : ";
    cin  >> choice;
    if (choice == 1)
    {
        tampilKecil(1, username);
    }
    else if (choice == 2)
    {
        tampilBesar(1, username);
    }
  }

  void sorting_data_pengeluaran(string &username, string &data_tanggal_bulan){
    int nilai=0;
    int temp, choice;

    for (int i = 1; i <= 31; ++i)
    {
      stringstream ss,temp_tanggal;
      ss << "Database/" << username << "/pengeluaran/total/Pengeluaran-" << i << "-" << data_tanggal_bulan << ".txt";
      temp_tanggal << i <<"-" << data_tanggal_bulan;
      
      char * pengeluaran_str = new char[ss.str().length()+1];
      strcpy(pengeluaran_str, ss.str().c_str());

      TempTanggal = temp_tanggal.str();
      temp = total_pengeluaran_dan_pemasukan(pengeluaran_str); 
      //tambah kelinked list
      Tambah(TempTanggal, temp);
    }
    sortingLst();
    cout << "Urutkan berdasarkan  : "  << endl;
    cout << "1. Kecil -> Besar\n2. Besar -> Kecil\nPilih : ";
    cin  >> choice;
    if (choice == 1)
    {
        tampilKecil(2, username);
    }
    else if (choice == 2)
    {
        tampilBesar(2, username);
    }
    
  }

};
#endif
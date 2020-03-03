#include <iostream>
#include "library/login.h"
#include "library/pembaruan.h"

using namespace std;

int main()
{
	Login obj_login;
	Pembaruan obj_pembaruan;

	obj_login.DataLogin(obj_pembaruan);
	return 0;
}
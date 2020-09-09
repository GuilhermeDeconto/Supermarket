// Supermarket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
//global variable declaration
int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
	int mm, dd, yy;
};

ofstream fout;
ifstream fin;

class item
{
	int itemno;
	char name[25];
	date d;
public:
	void add()
	{
		cout << "\n\n\tItem No: ";
		cin >> itemno;
		cout << "\n\n\tName of the item: ";
		cin >> name;
		//gets(name);
		cout << "\n\n\tManufacturing Date(dd-mm-yy): ";
		cin >> d.mm >> d.dd >> d.yy;
	}
	void show()
	{
		cout << "\n\tItem No: ";
		cout << itemno;
		cout << "\n\n\tName of the item: ";
		cout << name;
		cout << "\n\n\tDate : ";
		cout << d.mm << "-" << d.dd << "-" << d.yy;
	}
	void report()
	{
		gotoxy(3, k);
		cout << itemno;
		gotoxy(13, k);
		puts(name);
	}
	int retno()
	{
		return(itemno);

	}

};

class amount : public item
{
	float price, qty, tax, gross, dis, netamt;
public:
	void add();
	void show();
	void report();
	void calculate();
	void pay();
	float retnetamt()
	{
		return(netamt);
	}
} amt;

void amount::add()
{
	item::add();
	cout << "\n\n\tPrice: ";
	cin >> price;
	cout << "\n\n\tQuantity: ";
	cin >> qty;
	cout << "\n\n\tTax percent: ";
	cin >> tax;
	cout << "\n\n\tDiscount percent: ";
	cin >> dis;
	calculate();
	fout.write((char*)&amt, sizeof(amt));
	fout.close();
}
void amount::calculate()
{
	gross = price + (price * (tax / 100));
	netamt = qty * (gross - (gross * (dis / 100)));
}
void amount::show()
{
	fin.open("itemstore.dat", ios::binary);
	fin.read((char*)&amt, sizeof(amt));
	item::show();
	cout << "\n\n\tNet amount: ";
	cout << netamt;
	fin.close();
}

void amount::report()
{
	item::report();
	gotoxy(23, k);
	cout << price;
	gotoxy(33, k);
	cout << qty;
	gotoxy(44, k);
	cout << tax;
	gotoxy(52, k);
	cout << dis;
	gotoxy(64, k);
	cout << netamt;
	k = k + 1;
	if (k == 50)
	{
		gotoxy(25, 50);
		cout << "PRESS ANY KEY TO CONTINUE...";
		_getch();
		k = 7;
		system("cls");
		gotoxy(30, 3);
		cout << " ITEM DETAILS ";
		gotoxy(3, 5);
		cout << "NUMBER";
		gotoxy(13, 5);
		cout << "NAME";
		gotoxy(23, 5);
		cout << "PRICE";
		gotoxy(33, 5);
		cout << "QUANTITY";
		gotoxy(44, 5);
		cout << "TAX";
		gotoxy(52, 5);
		cout << "DEDUCTION";
		gotoxy(64, 5);
		cout << "NET AMOUNT";
	}
}

void amount::pay()
{
	show();
	cout << "\n\n\n\t\t*********************************************";
	cout << "\n\t\t                 DETAILS                  ";
	cout << "\n\t\t*********************************************";
	cout << "\n\n\t\tPRICE                     :" << price;
	cout << "\n\n\t\tQUANTITY                  :" << qty;
	cout << "\n\t\tTAX PERCENTAGE              :" << tax;
	cout << "\n\t\tDISCOUNT PERCENTAGE         :" << dis;
	cout << "\n\n\n\t\tNET AMOUNT              :Rs." << netamt;
	cout << "\n\t\t*********************************************";
}

int main()
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout << setprecision(2);
	fstream tmp("temp.dat", ios::binary | ios::out);
menu:
	system("cls");
	gotoxy(25, 2);
	cout << "Super Market Billing ";
	gotoxy(25, 3);
	cout << "===========================\n\n";
	cout << "\n\t\t1.Bill Report\n\n";
	cout << "\t\t2.Add/Remove/Edit Item\n\n";
	cout << "\t\t3.Show Item Details\n\n";
	cout << "\t\t4.Exit\n\n";
	cout << "\t\tPlease Enter Required Option: ";
	int ch, ff;
	float gtotal;
	cin >> ch;
	switch (ch)
	{
	case 1:
	ss:
		system("cls");
		gotoxy(25, 2);
		cout << "Bill Details";
		gotoxy(25, 3);
		cout << "================\n\n";
		cout << "\n\t\t1.All Items\n\n";
		cout << "\t\t2.Back to Main menu\n\n";
		cout << "\t\tPlease Enter Required Option: ";
		int cho;
		cin >> cho;
		if (cho == 1)
		{
			system("cls");
			gotoxy(30, 3);
			cout << " BILL DETAILS ";
			gotoxy(3, 5);
			cout << "ITEM NO";
			gotoxy(13, 5);
			cout << "NAME";
			gotoxy(23, 5);
			cout << "PRICE";
			gotoxy(33, 5);
			cout << "QUANTITY";
			gotoxy(44, 5);
			cout << "TAX %";
			gotoxy(52, 5);
			cout << "DISCOUNT %";
			gotoxy(64, 5);
			cout << "NET AMOUNT";
			fin.open("itemstore.dat", ios::binary);
			if (!fin)
			{
				cout << "\n\nFile Not Found...";
				goto menu;
			}
			fin.seekg(0);
			gtotal = 0;
			while (!fin.eof())
			{
				fin.read((char*)&amt, sizeof(amt));
				if (!fin.eof())
				{
					amt.report();
					gtotal += amt.retnetamt();
					ff = 0;
				}
				if (ff != 0) gtotal = 0;
			}
			gotoxy(17, k);
			cout << "\n\n\n\t\t\tGrand Total=" << gtotal;
			_getch();
			fin.close();
		}
		if (cho == 2)
		{
			goto menu;
		}
		goto ss;
	case 2:
	db:
		system("cls");
		gotoxy(25, 2);
		cout << "Bill Editor";
		gotoxy(25, 3);
		cout << "=================\n\n";
		cout << "\n\t\t1.Add Item Details\n\n";
		cout << "\t\t2.Edit Item Details\n\n";
		cout << "\t\t3.Delete Item Details\n\n";
		cout << "\t\t4.Back to Main Menu  ";
		int apc;
		cin >> apc;
		switch (apc)
		{
		case 1:
			fout.open("itemstore.dat", ios::binary | ios::app);
			amt.add();
			cout << "\n\t\tItem Added Successfully!";
			_getch();
			goto db;

		case 2:
			int ino;
			flag = 0;
			cout << "\n\n\tEnter Item Number to be Edited :";
			cin >> ino;
			fin.open("itemstore.dat", ios::binary);
			fout.open("itemstore.dat", ios::binary | ios::app);
			if (!fin)
			{
				cout << "\n\nFile Not Found...";
				goto menu;
			}
			fin.seekg(0);
			r = 0;
			while (!fin.eof())
			{
				fin.read((char*)&amt, sizeof(amt));
				if (!fin.eof())
				{
					int x = amt.item::retno();
					if (x == ino)
					{
						flag = 1;
						fout.seekp(r * sizeof(amt));
						system("cls");
						cout << "\n\t\tCurrent Details are\n";
						amt.show();
						cout << "\n\n\t\tEnter New Details\n";
						amt.add();
						cout << "\n\t\tItem Details editted";
					}
				}
				r++;
			}
			if (flag == 0)
			{
				cout << "\n\t\tItem No does not exist...Please Retry!";
				_getch();
				goto db;
			}
			fin.close();
			_getch();
			goto db;

		case 3:
			flag = 0;
			cout << "\n\n\tEnter Item Number to be deleted :";
			cin >> ino;
			fin.open("itemstore.dat", ios::binary);
			if (!fin)
			{
				cout << "\n\nFile Not Found...";
				goto menu;
			}
			//fstream tmp("temp.dat",ios::binary|ios::out);
			fin.seekg(0);
			while (fin.read((char*)&amt, sizeof(amt)))
			{
				int x = amt.item::retno();
				if (x != ino)
					tmp.write((char*)&amt, sizeof(amt));
				else
				{
					flag = 1;
				}
			}
			fin.close();
			tmp.close();
			fout.open("itemstore.dat", ios::trunc | ios::binary);
			fout.seekp(0);
			tmp.open("temp.dat", ios::binary | ios::in);
			if (!tmp)
			{
				cout << "Error in File";
				goto db;
			}
			while (tmp.read((char*)&amt, sizeof(amt)))
				fout.write((char*)&amt, sizeof(amt));
			tmp.close();
			fout.close();
			if (flag == 1)
				cout << "\n\t\tItem Succesfully Deleted";
			else if (flag == 0)
				cout << "\n\t\tItem does not Exist! Please Retry";
			_getch();
			goto db;
		case 4:
			goto menu;
		default:
			cout << "\n\n\t\tWrong Choice!!! Retry";
			_getch();
			goto db;
		}
	case 3:
		system("cls");
		flag = 0;
		int ino;
		cout << "\n\n\t\tEnter Item Number :";
		cin >> ino;
		fin.open("itemstore.dat", ios::binary);
		if (!fin)
		{
			cout << "\n\nFile Not Found...\nProgram Terminated!";
			goto menu;
		}
		fin.seekg(0);
		while (fin.read((char*)&amt, sizeof(amt)))
		{
			int x = amt.item::retno();
			if (x == ino)
			{
				amt.pay();
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			cout << "\n\t\tItem does not exist....Please Retry!";
		_getch();
		fin.close();
		goto menu;
	case 4:
		system("cls");
		gotoxy(20, 20);
		cout << "Are you sure you want to exit (Y/N)?";
		char yn;
		cin >> yn;
		if ((yn == 'Y') || (yn == 'y'))
		{
			gotoxy(12, 20);
			system("cls");
			cout << "************************** See you later **************************************";
			_getch();
			exit(0);
		}
		else if ((yn == 'N') || (yn == 'n'))
			goto menu;
		else
		{
			goto menu;
		}
	default:
		cout << "\n\n\t\tWrong Choice....Please Retry!";
		_getch();
		goto menu;
	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

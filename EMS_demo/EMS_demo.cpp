// EMS_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Description: The program is used for the demo energy management of ESS and PV.

//author Hongfei Tian @ GEIRINA

//Version 1.0, this version pass the test 

//Creation date 2019-06-26

#include "M_depend.h"
using namespace std;

PGconn* conn;			//postgreSQL connection init
TimerEngine GEngine;	//timer init

class timer :public ITimerEngineCallBack
{
	virtual bool OnTimerEngineCallBack(DWORD TimerID, DWORD Param)	//All timers complete callback function
	{
		switch (TimerID)
		{
		case 1:
			cout << "this is no.1\n";	//timer 1 response
			//Check_SOC();
			break;
		case 2:
			cout << "this is no.2\n";	//timer 2 response
			//Call_EMS();
			break;
		default:
			break;
		}
		return true;
	}
};

int main()
{
	conn = PQsetdbLogin("127.0.0.1", "5432", NULL, NULL, "mydatabase", "user1", "1234");	//postgreSQL connection: subdatabase-"mydatabase", user:"user1", password:"1234"
	if (conn == NULL)		//error handle

	{

		cout << "Connection Error" << endl;

	}

	Data_load();								//Load pv and load data from csv file
	GEngine.StartEngine();						//timer's engine starts
	timer tt;									//timer instantiate
	GEngine.AddTimer(&tt, 1, 100000, INFINITY);	//timer 1 init
	GEngine.AddTimer(&tt, 2, 100000, INFINITE);	//timer 2 init

	while (1) {
		Call_EMS();
	}
												//never reach here//
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

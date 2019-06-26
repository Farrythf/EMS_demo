// EMS_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "M_depend.h"


PGconn* conn;

using namespace std;

TimerEngine GEngine;

class timer :public ITimerEngineCallBack
{
	virtual bool OnTimerEngineCallBack(DWORD TimerID, DWORD Param)
	{
		if (TimerID == 1)
		{
			cout << "this is no.1\n";
			Check_SOC();
		}
		else if (TimerID == 2)
		{
			cout << "this is no.2\n";
		}
		//printf("This is %u param:%u\n", TimerID, Param);
		return true;
	}
};

int main()
{
	conn = PQsetdbLogin("127.0.0.1", "5432", NULL, NULL, "mydatabase", "user1", "1234");
	if (conn == NULL)

	{

		cout << "Connection Error" << endl;

	}

	Data_load();
	GEngine.StartEngine();  
	timer tt;
	GEngine.AddTimer(&tt, 1, 10000, INFINITY);
	GEngine.AddTimer(&tt, 2, 2000, INFINITE);

	while (1);

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

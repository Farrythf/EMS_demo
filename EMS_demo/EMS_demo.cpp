// EMS_demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
float load[96][12], PV[96][12], SOC[96][12], net_load[96][12];

#include "M_depend.h"
#include "TimerEngine.h"
using namespace std;

TimerEngine GEngine;

class timer :public ITimerEngineCallBack
{
	virtual bool OnTimerEngineCallBack(DWORD TimerID, DWORD Param)
	{
		printf("This is %u param:%u\n", TimerID, Param);
		return true;
	}
};

int main()
{
	//load_data();
	GEngine.StartEngine();  
	timer tt;
	GEngine.AddTimer(&tt, 1, 1000, 10);
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

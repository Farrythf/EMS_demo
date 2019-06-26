#include "M_depend.h"

#define SOC_UP_BOUND 90
#define SOC_LOW_BOUND 20
#define PCS_MIN_VALUE 20
#define PCS_MAX_VALUE 280
#define MAX 0
#define MIN 999999
#define RATE 0

int  Call_EMS()
{
	std::ofstream f1("PSC.out", std::ios::app);
	if (!f1)
	{
		std::cout << "Fill open failed!\n";
	}
	char* s;
	float SOC;
	int Temp_PCS = 0;
	char time[100];
	char SQL_com[100];
	SYSTEMTIME st = { 0 };
	static int i = 1, j = 0;
	PGresult* result = PQexec(conn, "SELECT * FROM estimate WHERE times in (select max(times) from estimate)");
	std::cout << PQresultErrorMessage(result);
	s = PQgetvalue(result, 0, 2);
	SOC = atof(s);
	if (net_load[i][j] > MAX)
	{
		Temp_PCS = (net_load[i][j] - MAX) * RATE;//////////////////////////////////////////////////////
		if (Temp_PCS > PCS_MAX_VALUE)
			Temp_PCS = PCS_MAX_VALUE;
		else if (Temp_PCS < PCS_MIN_VALUE)
			Temp_PCS = PCS_MIN_VALUE;
		if (SOC < SOC_LOW_BOUND)
			Temp_PCS = 0;
	}
	else if (net_load[i][j] < MIN)
	{
		Temp_PCS = (MIN - net_load[i][j]) * RATE;//////////////////////////////////////////////////////
		if (Temp_PCS > PCS_MAX_VALUE)
			Temp_PCS = -PCS_MAX_VALUE;
		else if (Temp_PCS < PCS_MIN_VALUE)
			Temp_PCS = -PCS_MIN_VALUE;
		if (SOC < SOC_LOW_BOUND)
			Temp_PCS = 0;
	}
	else
	{
		Temp_PCS = 0;
	}
	GetLocalTime(&st);
	/*sprintf_s(time, "'%d-%d-%d %d:%d:%d.%d'", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	sprintf_s(SQL_com, "INSERT INTO pcs_control VALUES( %s, %d)", time, Temp_PCS);
	result = PQexec(conn, SQL_com);
	std::cout << PQresultErrorMessage(result);*/
	PQclear(result);
	i++;
	f1 << Temp_PCS << ", ";
	if (i == 96)
	{
		f1 << "\n";
		i = 1;
		j++;
		if (j == 12)
		{
			f1.close();
			return 0;
		}
	}
	f1.close();
}

int Check_SOC()
{
	char* s;
	char time[100];
	char SQL_com[100];
	float res;
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	PGresult* result = PQexec(conn, "SELECT * FROM estimate WHERE times in (select max(times) from pcs_data)");
	std::cout << PQresultErrorMessage(result);
	s = PQgetvalue(result, 0, 2);
	res = atof(s);
	if (res > 90 || res < 10)
	{
		sprintf_s(time, "'%d-%d-%d %d:%d:%d.%d'", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		sprintf_s(SQL_com, "INSERT INTO pcs_control VALUES( %s, 0)", time);
		result = PQexec(conn, SQL_com);
		std::cout << PQresultErrorMessage(result);
	}
	PQclear(result);
	return 0;
}


int  Call_EMS_t()
{
	std::ofstream f1("PSC.out", std::ios::app);
	if (!f1)
	{
		std::cout << "Fill open failed!\n";
	}
	char* s;
	float SOC,PV,LOAD,net_l;
	int Temp_PCS = 0;
	char time[100];
	char SQL_com[100];
	SYSTEMTIME st = { 0 };
	static int i = 1, j = 0;
	PGresult* result = PQexec(conn, "SELECT * FROM estimate WHERE times in (select max(times) from estimate)");
	std::cout << PQresultErrorMessage(result);
	s = PQgetvalue(result, 0, 2);
	SOC = atof(s);
	result = PQexec(conn, "SELECT * FROM pv_data WHERE date in (select max(date) from pv_data)");
	std::cout << PQresultErrorMessage(result);
	s = PQgetvalue(result, 0, 1);
	PV = atof(s);
	result = PQexec(conn, "SELECT * FROM load WHERE date in (select max(date) from load)");
	std::cout << PQresultErrorMessage(result);
	s = PQgetvalue(result, 0, 1);
	LOAD = atof(s);

	net_l = LOAD - PV;
	if (net_l > MAX)
	{
		Temp_PCS = (net_l - MAX) * RATE;//////////////////////////////////////////////////////
		if (Temp_PCS > PCS_MAX_VALUE)
			Temp_PCS = PCS_MAX_VALUE;
		else if (Temp_PCS < PCS_MIN_VALUE)
			Temp_PCS = PCS_MIN_VALUE;
		if (SOC < SOC_LOW_BOUND)
			Temp_PCS = 0;
	}
	else if (net_l < MIN)
	{
		Temp_PCS = (MIN - net_l) * RATE;//////////////////////////////////////////////////////
		if (Temp_PCS > PCS_MAX_VALUE)
			Temp_PCS = -PCS_MAX_VALUE;
		else if (Temp_PCS < PCS_MIN_VALUE)
			Temp_PCS = -PCS_MIN_VALUE;
		if (SOC < SOC_LOW_BOUND)
			Temp_PCS = 0;
	}
	else
	{
		Temp_PCS = 0;
	}
	GetLocalTime(&st);
	/*sprintf_s(time, "'%d-%d-%d %d:%d:%d.%d'", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	sprintf_s(SQL_com, "INSERT INTO pcs_control VALUES( %s, %d)", time, Temp_PCS);
	result = PQexec(conn, SQL_com);
	std::cout << PQresultErrorMessage(result);*/
	PQclear(result);
	i++;
	f1 << Temp_PCS << ", ";
	if (i == 96)
	{
		f1 << "\n";
		i = 1;
		j++;
		if (j == 12)
		{
			f1.close();
			return 0;
		}
	}
	f1.close();
}
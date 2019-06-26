#include "M_depend.h"

int  Call_EMS()
{
	static int i = 1, j = 0;
	float Temp_SOC;
	if (net_load[i][j] > 0.9)
	{
		Temp_SOC = SOC[i - 1][j] - 0.25 * (net_load[i][j] - 0.9) / 0.2;
		if (Temp_SOC > 0.05)
		{
			SOC[i][j] = Temp_SOC;
		}
		else
		{
			SOC[i][j] = SOC[i - 1][j];
		}
	}
	else if (net_load[i][j] < 0.5)
	{
		Temp_SOC = SOC[i - 1][j] + 0.25 * (0.5 - net_load[i][j]) / 0.2;
		if (Temp_SOC < 0.95)
		{
			SOC[i][j] = Temp_SOC;
		}
		else
		{
			SOC[i][j] = SOC[i - 1][j];
		}
	}
	else
	{
		SOC[i][j] = SOC[i - 1][j];
	}
	i++;
	if (i == 96)
	{
		i = 1;
		j++;
		if (j == 12)
		{
			return 0;
		}
	}
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
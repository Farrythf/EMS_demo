#include "M_depend.h"

void  Call_EMS()
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
	if (i == 95)
	{
		i = 0;
		j++;
	}
}
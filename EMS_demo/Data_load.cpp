#include "Data_load.h"

using namespace std;

void load_data()
{
	ifstream file("GEIRINA_load.csv", ios::in);
	string line;
	int a = 0, b = 0;
	memset(load, 0, sizeof(load));
	//memset(PV, 0, sizeof(PV));
	while (getline(file, line))
	{
		//cout << line << "\n";
		stringstream ss(line);
		string str;
		while (getline(ss, str, ','))
		{
			load[a][b] = atof(str.c_str());
			b = b + 1;
		}
		a = a + 1;
		b = 0;
	}
	file.close();
	cout << load[0][0];
	a = 0;
	b = 0;
	ifstream file1("PV.csv", ios::in);
	while (getline(file1, line))
	{
		//cout << line << "\n";
		stringstream ss(line);
		string str;
		vector<string> lineArray;
		while (getline(ss, str, ','))
		{
			PV[a][b] = atof(str.c_str());
			b = b + 1;
		}
		a = a + 1;
		b = 0;
	}
	file1.close();

	float max_load = 0, max_PV = 0;
	for (int i = 0; i < 96; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (load[i][j] > max_load)
			{
				max_load = load[i][j];
			}
		}
	}
	for (int i = 0; i < 96; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (PV[i][j] > max_PV)
			{
				max_PV = PV[i][j];
			}
		}
	}

	float united_load[96][12], united_PV[96][12];
	for (int i = 0; i < 96; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			united_load[i][j] = 1 * load[i][j] / max_load;
		}
	}
	for (int i = 0; i < 96; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			united_PV[i][j] = 0.2 * PV[i][j] / max_PV;
		}
	}
	float united_ESS = 0.2;
	for (int i = 0; i < 96; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			net_load[i][j] = united_load[i][j] - united_PV[i][j];
		}
	}
	memset(SOC, 0.5, sizeof(SOC));
}
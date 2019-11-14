#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream in("fatal_msgs.log");
	ofstream data1("plot1.dat", fstream::out);
	ofstream data2("plot2.dat", fstream::out);

	string str;
	int count = 0;
	while(getline(in, str)) 
	{
		int pos = str.find(':');
		string subStr = str.substr(pos + 1, str.size() - pos - 1);
		//cout << subStr << endl;

		double UCB = atof(subStr.c_str());
		//cout << UCB << endl;

		if(count == 0)
		{
			data1 << UCB << endl;
			count = 1;
		}
		else
		{
			data2 << UCB << endl;
			count = 0;
		}
		
	}
	return 0;
}

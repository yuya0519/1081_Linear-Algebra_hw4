#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<math.h>
using namespace std;
#define PI 3.141592653589793238462643383279502884197169399375105820974944
long double stringToDouble(string);
long double cosineTrasform(int, int,int);
int main(int argc, char* argv[])
{
	ifstream inFile;
	int n = 0;
	string word;
	inFile.open("case1.txt");
	//inFile.open(argv[1]);
	vector<long double>x,b,a,buf;
	vector<vector<long double>>B;
	while (getline(inFile, word)) {	
			x.push_back(stringToDouble(word));
			++n;
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; j++) 
			b.push_back(cosineTrasform(i, j, n));
		B.push_back(b);
		b.clear();
	}

	for (int i = 0; i < n; ++i) {
		a.push_back(0);
		for(int j=0;j< n;++j)
			a[i]+=x[j] * B[i][j];
	}

	for (int i = 0; i < a.size(); ++i) {
		if (i < 84 || i > 179)
			a[i] = 0;
	}

	for (int i = 0; i < a.size(); ++i) {
		buf.push_back(0);
		for (int j = 0; j < a.size(); ++j) 
			buf[i] += a[j] * cos((PI /n) * j * (i + 0.5) * PI / 180.0);
		buf[i] *= sqrt(2.0) / sqrt(n);
	}
	for (int i = 0; i < n; ++i) {
		x[i] += buf[i];
		cout << setprecision(6) << fixed << x[i];
		if (i < n - 1)
			cout << endl;
	}
	inFile.close();
	x.clear();
	a.clear();
	b.clear();
	buf.clear();
	for (int i = 0; i < B.size(); ++i) 
		B[i].clear();
	B.clear();
}

long double stringToDouble(string str)
{
	long double num;
	long double temp2;
	size_t pos = 0;
	string token;
	string split = "e";
	while ((pos = str.find(split)) != string::npos) {
		stringstream s1;
		token = str.substr(0, pos);
		s1 << token;
		s1 >> num;
		stringstream s2;
		s2 << str.erase(0, pos + split.length());
		s2 >> temp2;
	}
	return (num*pow(10.0,temp2));
}

long double cosineTrasform(int k, int n,int s)
{
	long double num;
	if (k == 0) 
		num = 2*sqrt(1.0 / (4.0 * s)) * cos((PI /s)* k * (n + 0.5) * PI / 180.0);

	else 
		num = 2*sqrt(1.0 / (2.0 * s)) * cos((PI / s) * k * (n + 0.5) * PI / 180.0);
	return num;
}
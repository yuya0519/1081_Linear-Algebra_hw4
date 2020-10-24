# 1081_Linear-Algebra_hw4
## 主要目標:  
使用 Cosine Transform 進行訊號處理。   

## 程式運行方式:  

**該程式執行軟體為Visual 2019。**   
請將程式碼複製至上述軟體中，再編譯執行。  
創建1個檔案，分別為 case0.txt存放原始訊號。

## 簡要使用說明:  
- Input: 輸入皆由讀檔，檔案格式為: 
- case0.txt  

![avatar](https://upload.cc/i1/2020/10/24/Se9faK.png) 
> 第 1~N 行：原始訊號 (10-20~1020間任意實數，科學記號表示)

- Output:  
> 輸出範例  
![avatar](https://upload.cc/i1/2020/10/24/Fqv6G1.png)   
> 第 1 行~第 N 行：轉換訊號(任意實數，取小數後六位，不用轉科學記號)  

## 程式結構說明:  

### 基本原理:  
要從原始訊號中獲得特定頻率訊號，可利用 mask 將 a 中特定頻率資料保留，其餘為 0，接著再利用 Inverse Cosine Transform 轉為處理後訊號。 

![avatar](https://upload.cc/i1/2020/10/24/1uAgmj.png)   

### 引用函式庫說明:
```cpp
#include<iostream> //負責輸出/輸入
#include<string> //負責處理string相關函式
#include<fstream> //負責讀檔
#include<sstream> //引入string恨int轉換公式
#include<vector> //引用vector
#include<iomanip>  //用以排版
#include<math.h>  //引用sqrt()和三角函數計算
```

### 變數說明:
```cpp
  ifstream inFile;  //讀檔
	int n = 0;  //紀錄訊號數
	string word;  //存放讀入之訊號  
	vector<long double>x;  //原始訊號、並且存放答案
  vector<long double>b;  //cosin轉換後之訊號
  vector<long double>a;  //存放𝐵^-1*x
  vector<long double>buf;  //存放Ba
	vector<vector<long double>>B;  //存放第一次轉換的答案
```
### 詳細程式碼說明

```cpp
int main(int argc, char* argv[])
{
	ifstream inFile;
	int n = 0;
	string word;
	inFile.open("case0.txt");
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
```
> 將讀入的訊號資訊做處理，  
> 存入X中。  
> 做第一次cosin轉換得到B，  
> 再計算xB^-1存入a中，  
> 再把不需要的訊號濾掉(a[0]~a[47]、a[180]~a[n])，  
> 最後把Ba計算完結果存回x中。  
> 並依照格是輸出。  

```cpp
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
```
> 將string轉換為long double。  

```cpp
long double cosineTrasform(int k, int n,int s)
{
	long double num;
	if (k == 0) 
		num = 2*sqrt(1.0 / (4.0 * s)) * cos((PI /s)* k * (n + 0.5) * PI / 180.0);

	else 
		num = 2*sqrt(1.0 / (2.0 * s)) * cos((PI / s) * k * (n + 0.5) * PI / 180.0);
	return num;
}
```
> 依照公式做cosin轉換，並回傳。

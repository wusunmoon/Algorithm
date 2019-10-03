#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<random>
#include<ctime>
#include<thread>

using namespace std;

/***************************************************************
	暴力求解(Brute Force):
	计算每一对i <= j的V(i,j)的值，返回最大值。
	复杂度：O(n^3) 
****************************************************************/
double MCS_BF(vector<double> &A)
{
	int sz = A.size();
	if(sz == 0){
		cout << "输入数组为空" << endl;
		return -1;
	}
	double vmax = A[0];
	for(int i= 0; i < sz; ++i){
		for(int j = i; j < sz; ++j){
			double sum = 0;
			for(int x = i; x <= j; ++x){
				sum += A[x];
			}
			if(sum > vmax)
				vmax = sum;
		}
	}
	return vmax;
}
/****************************************************************
	数据再利用（Data_Reuse） :
	不需要从头计算每一个V(i,j), V(i,j) = V(i,j-1) + A[j]
	复杂度：O(n^2)  
*****************************************************************/
double MCS_DR(vector<double> &A)
{
	int sz = A.size();
	if(sz == 0){
		cout << "输入数组为空" << endl;
		return -1;
	}
	double vmax = A[0];
	for(int i= 0; i < sz; ++i){
		double sum = 0;
		for(int j = i; j < sz; ++j){
			sum += A[j];
			if(sum > vmax)
				vmax = sum;
		}
	}
	return vmax;
}
/****************************************************************
	分而治之（Divide-and-Conquer） 
	复杂度：O（nlogn） 
*****************************************************************/
double FindMaxCrossingSubarr(vector<double> &A, int low, int mid, int high)
{
	double SM1 = A[mid];
	double sum = A[mid];
	for(int i = mid-1; i >= low; --i){
		sum += A[i];
		if(sum > SM1)
			SM1 = sum;
	}
	double SM2 = A[mid + 1];
	sum = A[mid + 1];
	for(int j = mid + 2; j <= high; ++j){
		sum += A[j];
		if(sum > SM2)
			SM2 = sum;
	}
	return SM1+SM2;
}
double FindMaxSubarr(vector<double> &A, int low, int high)
{
	if(low == high)
		return A[low];
	int m = floor((low + high) / 2);
	double S1 = FindMaxSubarr(A,low,m);
	double S2 = FindMaxSubarr(A,m+1,high);
	double SM = FindMaxCrossingSubarr(A,low,m,high);
	return max({S1,S2,SM});
}
double MCS_DC(vector<double> &A)
{
	if(A.empty()){
		cout << "输入数组为空" << endl;
		return -1;
	}
		
	int low = 0;
	int high = A.size() - 1;
	return FindMaxSubarr(A,low,high);
}

/*
	利用rand ()生成任意区间的随机浮点数
*/
double getRandData(int min,int max)
{
	double m1=(double)(rand()%101)/101;
	min++; 
	double m2=(double)((rand()%(max-min+1))+min); 
	m2=m2-1; 
	return m1+m2; 
}

int main()
{
	srand(time(0));
	vector<double> hun(100);
	vector<double> thou(1000);
	vector<double> tenthou(10000);
	for(int i = 0; i < 100; ++i)
		hun[i] = getRandData(-100,100);
	for(int i = 0; i < 1000; ++i)
		thou[i] = getRandData(-100,100);
	for(int i = 0; i < 10000; ++i)
		tenthou[i] = getRandData(-100,100);
	
	chrono::duration<double, milli> eps;	
	cout << "100个值：" << endl; 
	auto start = std::chrono::high_resolution_clock::now();
	cout << "BF : " << MCS_BF(hun) << "    ";
	auto end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
	start = std::chrono::high_resolution_clock::now();
	cout << "DR : " << MCS_DR(hun) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
	cout << "DC : " << MCS_DC(hun) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	cout << "1000个值：" << endl; 
	start = std::chrono::high_resolution_clock::now();
	cout << "BF : " << MCS_BF(thou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
	start = std::chrono::high_resolution_clock::now();
	cout << "DR : " << MCS_DR(thou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
	cout << "DC : " << MCS_DC(thou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	cout << "10000个值：" << endl; 
	start = std::chrono::high_resolution_clock::now();
	cout << "BF : " << MCS_BF(tenthou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
	start = std::chrono::high_resolution_clock::now();
	cout << "DR : " << MCS_DR(tenthou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
	cout << "DC : " << MCS_DC(tenthou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	return 0;
}

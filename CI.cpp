#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<ctime>
#include<thread>

using namespace std;

/***************************************************************
	暴力求解(Brute Force):
	列出每一对i<j并计数逆序，返回逆序对数量。
	复杂度：O(n^2) 
****************************************************************/
int CI_BF(vector<int>& v)
{
	int r = 0;
	int sz = v.size();
	for(int i = 0; i < sz; ++i)
		for(int j = i + 1; j < sz; ++j)
			if(v[i] > v[j])
				++r;
	return r;
}

/****************************************************************
	分而治之（Divide-and-Conquer） :
	在归并排序的基础上加了计数逆序 
	复杂度：O（nlogn） 
	备注：向量区间是左闭右开，即[lo,hi) 
*****************************************************************/
int MergeAndCount(vector<int>& v, int lo, int mi, int hi)
{
	int r = 0;	
	vector<int> v1(v.begin()+lo,v.begin()+mi);
	int sz = v1.size();
	int j = 0;	//v1的索引 
	while(j < sz && mi < hi){
		if(v1[j] <= v[mi]){
			v[lo++] = v1[j++];
		}
		else{
			v[lo++] = v[mi++];
			r += (sz - j);	//计数 
		}
	}
	while(j < sz){
		v[lo++] = v1[j++];
	}
	while(mi < hi){
		v[lo++] = v[mi++];
	}
	return r;
}
int SortAndCount(vector<int>& v, int lo, int hi)
{
	if(hi - lo < 2)
		return 0;	//递归基：单个元素自然有序，且逆序对为0 
	int mi = (lo + hi) / 2;
	int r1 = SortAndCount(v,lo,mi);
	int r2 = SortAndCount(v,mi,hi);
	int rm = MergeAndCount(v,lo,mi,hi);
	return r1+r2+rm; 
}
int CI_DC(vector<int>& v)
{
	return SortAndCount(v,0,v.size()); 
} 

/*
	利用rand ()生成任意区间的随机整数 
*/
int getRandData(int min,int max)
{	
	return (rand()%(max-min+1))+min;
}

int main()
{	
	srand(time(0));
	vector<int> hun(100);
	vector<int> thou(1000);
	vector<int> tenthou(10000);
	for(int i = 0; i < 100; ++i)
		hun[i] = getRandData(-100,100);
		
	for(int i = 0; i < 1000; ++i)
		thou[i] = getRandData(-1000,1000);
	for(int i = 0; i < 10000; ++i)
		tenthou[i] = getRandData(-10000,10000);

	chrono::duration<double, milli> eps;	
	cout << "100个值：" << endl; 
	auto start = std::chrono::high_resolution_clock::now();
	cout << "BF : " << CI_BF(hun) << "    ";
	auto end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
	cout << "DC : " << CI_DC(hun) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	cout << "1000个值：" << endl; 
	start = std::chrono::high_resolution_clock::now();
	cout << "BF : " << CI_BF(thou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
	cout << "DC : " << CI_DC(thou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	cout << "10000个值：" << endl; 
	start = std::chrono::high_resolution_clock::now();
	cout << "BF : " << CI_BF(tenthou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
	cout << "DC : " << CI_DC(tenthou) << "    ";
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	return 0;
}

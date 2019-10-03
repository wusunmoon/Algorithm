#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<thread>

#define HUN 128
#define THOU 1024
#define TENTHOU 16384

using namespace std;

/**************************************************************************************************
	暴力求解(Brute Force):
	按定义直接求解。
	复杂度：O(n^2) 
***************************************************************************************************/
void PM_BF(vector<int>& A, vector<int>& B, vector<int>& C)
{
	int n = A.size();
	int m = B.size();
	C.clear();
	C.assign(n+m-1,0);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			C[i+j] += A[i] * B[j];
		}
	}
	return;
}
/**************************************************************************************************
	分而治之（Divide-and-Conquer） 第一种:
	将两个多项式都分为两块，将整个问题分为四个子问题分别解决 
	复杂度：O（n^2） 
	备注：假定n为2的幂
***************************************************************************************************/
void PM_DC_1_Recur(vector<int>& A, int la, int ha, vector<int>& B, int lb, int hb, vector<int>& C)
{
	int n = ha - la;	//n为2的幂 
	int h = n/2;
	C.clear();
	C.assign(2*n-1,0);
	if(n == 1){	//递归基 
		C[0] = A[la] * B[lb];
		return;
	}
	vector<int> U,V,W,Z;
	PM_DC_1_Recur(A,la,la+h,B,lb,lb+h,U);
	PM_DC_1_Recur(A,la,la+h,B,lb+h,hb,V);
	PM_DC_1_Recur(A,la+h,ha,B,lb,lb+h,W);
	PM_DC_1_Recur(A,la+h,ha,B,lb+h,hb,Z);
	for(int i = 0; i < n-1; ++i){
		C[i] += U[i];
		C[i+h] += V[i] + W[i];
		C[i+n] += Z[i];
	}
	return;
}
void PM_DC_1(vector<int>& A, vector<int>& B, vector<int>& C)
{
	PM_DC_1_Recur(A,0,A.size(),B,0,B.size(),C);
	return;
}
/*
void PM_DC_1(vector<int>& A, vector<int>& B, vector<int>& C)
{
	int n = A.size();	//n为2的幂 
	int h = n/2;
	C.clear();
	C.assign(2*n-1,0);
	if(n == 1){	//递归基 
		C[0] = A[0] * B[0];
		return;
	}
	vector<int> A0(A.begin(),A.begin()+h)	;
	vector<int> A1(A.begin()+h,A.end());
	vector<int> B0(B.begin(),B.begin()+h)	;
	vector<int> B1(B.begin()+h,B.end());
	vector<int> U,V,W,Z;
	PM_DC_1(A0,B0,U);
	PM_DC_1(A0,B1,V);
	PM_DC_1(A1,B0,W);
	PM_DC_1(A1,B1,Z);
	for(int i = 0; i < n-1; ++i){
		C[i] += U[i];
		C[i+h] += V[i] + W[i];
		C[i+n] += Z[i];
	}
	return;
}*/
/**************************************************************************************************
	分而治之（Divide-and-Conquer） 第二种:
	将两个多项式都分为两块，将整个问题分为三个子问题分别解决 
	复杂度：O（n^log3） 
	备注：假定n为2的幂
***************************************************************************************************/
void PM_DC_2_Recur(vector<int>& A, int la, int ha, vector<int>& B, int lb, int hb, vector<int>& C)
{
	int n = ha - la;	//n为2的幂 
	int h = n/2;
	C.clear();
	C.assign(2*n-1,0);
	if(n == 1){	//递归基 
		C[0] = A[la] * B[lb];
		return;
	}
	vector<int> U,Z,Y;
	PM_DC_2_Recur(A,la,la+h,B,lb,lb+h,U);
	PM_DC_2_Recur(A,la+h,ha,B,lb+h,hb,Z);
	vector<int> A1(h,0);
	vector<int> B1(h,0);
	for(int i = la,j = 0; j < h; ++i,++j){
		A1[j] = (A[i] + A[i+h]);
		B1[j] = (B[i] + B[i+h]);
	} 
	PM_DC_2_Recur(A1,0,h,B1,0,h,Y);
	for(int i = 0; i < n-1; ++i){
		C[i] += U[i];
		C[i+h] += Y[i] - U[i] - Z[i];
		C[i+n] += Z[i];
	}
	return;
}
void PM_DC_2(vector<int>& A, vector<int>& B, vector<int>& C)
{
	PM_DC_2_Recur(A,0,A.size(),B,0,B.size(),C);
	return;
}
/*
void PM_DC_2(vector<int>& A, vector<int>& B, vector<int>& C)
{
	int n = A.size();	//n为2的幂 
	int h = n/2;
	C.clear();
	C.assign(2*n-1,0);
	if(n == 1){
		C[0] = A[0] * B[0];
		return;
	}
	vector<int> A0(A.begin(),A.begin()+h);
	vector<int> A1(A.begin()+h,A.end());
	vector<int> B0(B.begin(),B.begin()+h);
	vector<int> B1(B.begin()+h,B.end());
	vector<int> U,Z,Y;
	PM_DC_2(A0,B0,U);
	PM_DC_2(A1,B1,Z);
	for(int i = 0; i < h; ++i){
		A0[i] += A1[i];
		B0[i] += B1[i];
	} 
	PM_DC_2(A0,B0,Y);
	for(int i = 0; i < n-1; ++i){
		C[i] += U[i];
		C[i+h] += Y[i] - U[i] - Z[i];
		C[i+n] += Z[i];
	}
	return;
}*/
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
	vector<int> Ahun(HUN);
	vector<int> Athou(THOU);
	vector<int> Atenthou(TENTHOU);
	for(int i = 0; i < HUN; ++i)
		Ahun[i] = getRandData(-20,20);		
	for(int i = 0; i < THOU; ++i)
		Athou[i] = getRandData(-20,20);
	for(int i = 0; i < TENTHOU; ++i)
		Atenthou[i] = getRandData(-20,20);
	vector<int> Bhun(HUN);
	vector<int> Bthou(THOU);
	vector<int> Btenthou(TENTHOU);
	for(int i = 0; i < HUN; ++i)
		Bhun[i] = getRandData(-20,20);		
	for(int i = 0; i < THOU; ++i)
		Bthou[i] = getRandData(-20,20);
	for(int i = 0; i < TENTHOU; ++i)
		Btenthou[i] = getRandData(-20,20);

	vector<int> Chun1,Chun2,Cthou1,Cthou2,Ctenthou1,Ctenthou2;
	chrono::duration<double, milli> eps;	
	
	cout << HUN <<"个值：" << endl; 	
	auto start = std::chrono::high_resolution_clock::now();
	PM_BF(Ahun,Bhun,Chun1);
	auto end = std::chrono::high_resolution_clock::now();
	eps = end-start;
	cout << "BF : " << '\t' << '\t' << '\t';
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
    PM_DC_1(Ahun,Bhun,Chun2);
	end = std::chrono::high_resolution_clock::now();
	cout << "DC1 : " << '\t';
	if(Chun1 == Chun2)
		cout << "结果正确" << '\t'; 
	else
		cout << "结果错误" << '\t';
	eps = end-start;
    std::cout << eps.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    PM_DC_2(Ahun,Bhun,Chun2);
	end = std::chrono::high_resolution_clock::now();
	cout << "DC2 : " << '\t';
	if(Chun1 == Chun2)
		cout << "结果正确" << '\t'; 
	else
		cout << "结果错误" << '\t';
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	cout << THOU <<"个值：" << endl; 	
	start = std::chrono::high_resolution_clock::now();
	PM_BF(Athou,Bthou,Chun1);
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
	cout << "BF : " << '\t' << '\t' << '\t';
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
    PM_DC_1(Athou,Bthou,Chun2);
	end = std::chrono::high_resolution_clock::now();
	cout << "DC1 : " << '\t';
	if(Chun1 == Chun2)
		cout << "结果正确" << '\t'; 
	else
		cout << "结果错误" << '\t';
	eps = end-start;
    std::cout << eps.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    PM_DC_2(Athou,Bthou,Chun2);
	end = std::chrono::high_resolution_clock::now();
	cout << "DC2 : " << '\t';
	if(Chun1 == Chun2)
		cout << "结果正确" << '\t'; 
	else
		cout << "结果错误" << '\t';
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	cout << TENTHOU <<"个值：" << endl; 	
	start = std::chrono::high_resolution_clock::now();
	PM_BF(Atenthou,Btenthou,Chun1);
	end = std::chrono::high_resolution_clock::now();
	eps = end-start;
	cout << "BF : " << '\t' << '\t' << '\t';
    std::cout << eps.count() << " ms\n";
    
    start = std::chrono::high_resolution_clock::now();
    PM_DC_1(Atenthou,Btenthou,Chun2);
	end = std::chrono::high_resolution_clock::now();
	cout << "DC1 : " << '\t';
	if(Chun1 == Chun2)
		cout << "结果正确" << '\t'; 
	else
		cout << "结果错误" << '\t';
	eps = end-start;
    std::cout << eps.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    PM_DC_2(Atenthou,Btenthou,Chun2);
	end = std::chrono::high_resolution_clock::now();
	cout << "DC2 : " << '\t';
	if(Chun1 == Chun2)
		cout << "结果正确" << '\t'; 
	else
		cout << "结果错误" << '\t';
	eps = end-start;
    std::cout << eps.count() << " ms\n";

	return 0;
}

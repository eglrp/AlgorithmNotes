/*
题目描述
给出N个1-9的数字 (v1,v2,…,vN)，不改变它们的相对位置，在中间加入K个乘号和N-K-1个加号
（括号随便加）使最终结果尽量大。因为乘号和加号一共就是N-1个了，所以恰好每两个相邻数字之间都有一个符号
并说明其具有优化子结构性质及子问题重叠性质。
例如： N=5, K=2，5个数字分别为1、2、3、4、5，可以加成： 
1*2*(3+4+5)=24 
1*(2+3)*(4+5)=45 
(1*2+3)*(4+5)=45
(1+2+3)*4*5=120
解题思路
令r(n,k)为n个数字组成算式的最大结果，k为乘号的个数
从中间第x个位置切分，前x个数字插入k-1个乘号，此时剩余一个乘号，则
r(n,k) = max{r(n,k), r(x,k-1)*sum(x+1,n)}
sum(x+1,n)表示第x+1个数字到第n个数字之和
r(i,j)则表示为前i个数字插入j个乘号所得到的最大结果
具有最优子结构：问题的最优解包括子问题的最优解

r(i,0)插入零个乘号，即为前i个数之和
*/

#include<iostream>
#include<vector>
#include"../util.h"

using namespace std;

int solve(vector<int> a, int k)
{
	int n = a.size();
	int r[n+1][k+1] = {0};

	// r[i][0]为前i个数之和
	r[1][0] = a[0];
	for(int i=2; i<=n; ++i)
		r[i][0] = r[i-1][0] + a[i-1];

	// n个数
	for(int i=2; i<=n; ++i)
	{
		int m = min(i - 1, k);
		// min(i - 1, k)个乘号
		for(int j=1; j<=m; ++j)
		{
			for(int x=2; x<=i; ++x)
				r[i][j] = max(r[i][j], r[x-1][j-1] * (r[i][0] - r[x-1][0]));
		}
	}

	return r[n][k];
}

int main()
{
	vector<int> a = genRandomArray(5, 1, 9);
	printArray(a);
	cout << solve(a, 2) << endl;
}
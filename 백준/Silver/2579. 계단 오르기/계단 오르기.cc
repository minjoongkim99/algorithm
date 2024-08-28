#include <cstdio>
#include <iostream>
using namespace std;

int pHigh[310] = { 0 };

int max(int a, int b) {
	if (a >= b)
		return a;
	else return b;
}

int getMax(int* p ,int n) {
	if (n == 1) {
		pHigh[1] = p[1];
		return p[1];
	}
	if (n == 2) { //재귀가 없다 재귀 가 없다
		pHigh[2] = p[1] + p[2];
		return p[1] + p[2];
	}
	if (n == 3) return max(p[1] + p[3], p[2] + p[3]);
	if (pHigh[n] != 0) return pHigh[n];
	return pHigh[n] = max(getMax(p, n - 3) + p[n - 1] + p[n], getMax(p, n - 2) + p[n]);
}
// 각 변수마다 대입이 될 때 동일하게 적용되는 알고리즘. 작은문제로 쪼개고 동일한 답이 적용.
int main() {
	int stair;
	cin >> stair;
	int* pscore = new int[stair + 1];
	for (int i = 1; i <= stair; i++)
		cin >> pscore[i];
	cout << getMax(pscore, stair);
}
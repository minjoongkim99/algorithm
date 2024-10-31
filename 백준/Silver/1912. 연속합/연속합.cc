#include<iostream>

using namespace std;

int dp[100001];	//0번은 그냥 최댓값, 1번은 이어진 최댓값
int main() {
	int N;
	ios::sync_with_stdio(0);	cin.tie(0);		cout.tie(0);

	cin >> N;
	int* arr = new int[N];


	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	dp[0] = arr[0];
	for (int i = 1; i < N; i++) {
		if (dp[i - 1] + arr[i] > arr[i])
			dp[i] = dp[i - 1] + arr[i];
		else
			dp[i] = arr[i];
	}

	int max = -1000000;
	for (int i = 0; i < N; i++) {
		if (max < dp[i])
			max = dp[i];
	}
	cout << max;
 }
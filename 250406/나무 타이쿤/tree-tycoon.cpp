#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;

int ddy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int ddx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

int arr[20][20];
int visited[20][20];

vector<pair<int, int>> food;
vector<pair<int, int>> order;

int sum = 0;

// *1. 특수 영양제 이동 규칙에 따라 이동 시킴
void moveFood(int t) {
	int d = order[t].first;
	int p = order[t].second;

	for (int i = 0; i < food.size(); ++i) {
		int yy = food[i].first + p * ddy[d];
		int xx = food[i].second + p * ddx[d];
		
		if (yy < 1 || yy > n) {
			yy = (yy - 1 + n) % n + 1;
		}
		if (xx < 1 || xx > n) {
			xx = (xx - 1 + n) % n + 1;
		}
		food[i].first = yy;
		food[i].second = xx;
	}
}

//
void disappearFood() {
	for (int i = 0; i < food.size(); ++i) {
		arr[food[i].first][food[i].second]++;
		visited[food[i].first][food[i].second] = 1;
	}

	food.clear();
}

void increaseArr() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (visited[i][j] == 0) continue;
			int cnt = 0;

			for (int dir = 1; dir < 8; dir = dir + 2) {
				int yy = i + ddy[dir];
				int xx = j + ddx[dir];

				if (yy < 1 || yy > n || xx < 1 || xx > n) continue;
				if (arr[yy][xx] > 0)
					cnt++;
			}
			arr[i][j] += cnt;
		}
	}
}

void cutting() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (visited[i][j] == 1) continue;

			if (arr[i][j] >= 2) {
				arr[i][j] -= 2;
				food.push_back({ i, j });
			}
		}
	}
}

void getAnswer() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if(arr[i][j] > 0)
				sum += arr[i][j];
		}
	}
}

void input() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> arr[i][j];
		}
	}

	for (int i = 1; i <= m; ++i) {
		int d, p;
		cin >> d >> p;
		order.push_back({ d - 1, p });
	}

	food.push_back({ n - 1, 1}); food.push_back({ n - 1, 2 });
	food.push_back({ n , 1 });	food.push_back({ n, 2 });
}

int main() {
	int T = 1;

	//cin >> T;
	
	for (int tc = 1; tc <= T; ++tc) {
		sum = 0;
		fill(&visited[0][0], &visited[0][0] + 20 * 20, 0);
		fill(&arr[0][0], &arr[0][0] + 20 * 20, 0);
		order.clear();
		food.clear();

		input();

		for (int run = 1; run <= m; ++run) {
			fill(&visited[0][0], &visited[0][0] + 20 * 20, 0);

			moveFood(run - 1);

			disappearFood();

			increaseArr();

			cutting();
		}

		getAnswer();

		cout << sum << '\n';
	}
	return 0;
}
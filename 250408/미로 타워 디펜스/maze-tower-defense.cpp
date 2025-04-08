#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int arr[30][30];
int idx[900];
int d, p;

vector<int> v;

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };

int len = 1, cur = 0, change = 0;

int point = 0;

void attack(int dir, int len) {
	
	for (int i = 1; i <= len; ++i) {
		int yy = n / 2 + i * dy[dir];
		int xx = n / 2 + i * dx[dir];

		if (yy < 0 || yy >= n || xx < 0 || xx >= n) continue;

		if (arr[yy][xx] > 0) {
			point += arr[yy][xx];
			arr[yy][xx] = -1;
		}
	}
}

void snailEmpty() {
	v.clear();

	int cy = n / 2, cx = n / 2;
	int dir = 2;

	while (true){
		int ny = cy + dy[dir];
		int nx = cx + dx[dir];
		//cout << ny << "," << nx << " " << len << " " << cur << " " << change << "\n";
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
			break;
		}
		if (arr[ny][nx] == 0) break;
		
		if (arr[ny][nx] != -1) 
			v.push_back(arr[ny][nx]);

		cur++;
		if (cur == len) {
			cur = 0;
			dir = (dir + 3) % 4;
			change++;
		}
		if (change == 2) {
			change = 0;
			len++;
		}

		cy = ny;
		cx = nx;
	}
}

int eraseMonster() {
	fill(&idx[0], &idx[0] + 900, 0);
	int flag = 0;
	vector<int> tmp;

	for (int i = 0; i < v.size() - 3; ++i) {
		if (v[i] == v[i + 1] && v[i + 1] == v[i + 2] && v[i + 2] == v[i + 3]) {
			idx[i] = idx[i + 1] = idx[i + 2] = idx[i + 3] = 1;
			flag = 1;
		}
	}

	for (int i = 0; i < v.size(); ++i) {
		if (idx[i] == 1) point += v[i];
		else tmp.push_back(v[i]);
	}
	
	v = tmp;
	return flag;
}

void makeNewVector() {
	vector<int> tmp;

	int val = v[0];
	int cnt = 1;

	for (int i = 0; i < v.size() - 1; ++i) {
		if (v[i] == v[i + 1]) {
			cnt++;
		}
		else {
			tmp.push_back(cnt);
			tmp.push_back(val);

			val = v[i + 1];
			cnt = 1;
		}
	}

	tmp.push_back(cnt);
	tmp.push_back(val);

	v = tmp;
}

void vecToArr() {
	fill(&arr[0][0], &arr[0][0] + 30 * 30, 0);

	int cy = n / 2, cx = n / 2;
	int dir = 2;

	for (int i = 0; i < v.size(); ++i) {
		int ny = cy + dy[dir];
		int nx = cx + dx[dir];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n) break;
		arr[ny][nx] = v[i];

		cur++;

		if (cur == len) {
			cur = 0;
			dir = (dir + 3) % 4;
			change++;
		}
		if (change == 2) {
			change = 0;
			len++;
		}

		cy = ny;
		cx = nx;
	}
}


int main() {
	int T = 1;
	
	for (int tc = 1; tc <= T; ++tc) {
		//global_init();
		point = 0;
		v.clear();

		cin >> n >> m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> arr[i][j];
			}
		}

		for (int i = 1; i <= m; ++i) {
			// local_init()

			cin >> d >> p;

			attack(d, p);

			len = 1, cur = 0, change = 0;
			snailEmpty();

			while (true) {
				int flag = eraseMonster();
				if (flag == 0) break;
				//showVector();
			}

			makeNewVector();

			len = 1, cur = 0, change = 0;
			vecToArr();

			// final_init()
			v.clear();
		}

		cout << point << '\n';
	}
	return 0;
}

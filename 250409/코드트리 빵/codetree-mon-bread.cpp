#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, m;
int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };

int arr[20][20];
int visited[20][20];
int pre[20][20][2];

struct player {
	int cx, cy, ex, ey, died;
};
player P[32];

int ans = 1;

void showArr() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << arr[i][j] << "\t";
		}
		cout << '\n';
	}
	cout << "\n";
}

void showPlayer() {
	cout << "SHOW PLAYER\n";

	for (int idx = 1; idx <= m; ++idx) {
		if (P[idx].died == 1) {
			cout << "IDX" << idx << " IS ARRIVED\n";
		}
		else cout << "IDX" << idx << " " << P[idx].cx << " " << P[idx].cy << "\n";
	}
	cout << "\n";
}

bool canBreak() {
	for (int idx = 1; idx <= m; ++idx) {
		if (P[idx].died == 0) return false;
	}
	return true;
}

/*	1. 격자에 있는 사람들 모두가 본인이 가고 싶어하는 편의점으로 향해 1칸이동
* 최단거리로 움직이며 최단거리가 여러가지라면 상 좌 우 하 우선순위를 가짐
* 최단거리는 BFS 기준이다.
*/
int bfs(int cx, int cy, int tx, int ty) {
	queue<pair<int, int>> q;

	q.push({ cx, cy });
	visited[cx][cy] = 1;
	pre[cx][cy][0] = pre[cx][cy][1] = -1;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (x == tx && y == ty)	break;

		for (int dir = 0; dir < 4; ++dir) {
			int xx = x + dx[dir];
			int yy = y + dy[dir];

			if (xx < 1 || xx > n || yy < 1 || yy > n) continue;
			if (visited[xx][yy]) continue;
			if (arr[xx][yy] == -1) continue;

			q.push({ xx, yy });
			visited[xx][yy] = visited[x][y] + 1;
			pre[xx][yy][0] = x;
			pre[xx][yy][1] = y;
		}
	}

	return visited[tx][ty];
}

void path(int idx) {

	int cx = P[idx].ex;
	int cy = P[idx].ey;

	while (true) {
		int nx = pre[cx][cy][0];
		int ny = pre[cx][cy][1];

		if (nx == P[idx].cx && ny == P[idx].cy) {
			break;
		}
		////
		if (nx == -1 && ny == -1) {
			break;
		}
		////
		
		cx = nx;
		cy = ny;
	}
	P[idx].cx = cx;
	P[idx].cy = cy;
}

void movePlayer(int idx) {
	fill(&visited[0][0], &visited[0][0] + 20 * 20, 0);
	fill(&pre[0][0][0], &pre[0][0][0] + 20 * 20 * 2, 0);

	bfs(P[idx].cx, P[idx].cy, P[idx].ex, P[idx].ey);

	path(idx);
}

/* 2. 편의점에 도착한다면 해당 편의점에서 멈추고, 이 때 부터 다른 사람들은
해당 편의점이 있는 칸을 지나갈 수 없다.
격자에 있는 사람들이 모두 이동한 뒤
해당 칸을 지나갈 수 없음에 유의할 것
*/
void makeBlind() {
	for (int idx = 1; idx <= m; ++idx) {
		if (P[idx].died == 1) continue;
		if (P[idx].cx == P[idx].ex && P[idx].cy == P[idx].ey) {
			P[idx].died = 1;
			arr[P[idx].ex][P[idx].ey] = -1;
		}
	}
}


void entering(int idx) {
	int cur_dist = 100000000;
	int nx = 0, ny = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (arr[i][j] > 0) {
				fill(&visited[0][0], &visited[0][0] + 20 * 20, 0);
				fill(&pre[0][0][0], &pre[0][0][0] + 20 * 20 * 2, 0);
				int next_dist = bfs(i, j, P[idx].ex, P[idx].ey);
				if (next_dist == 0) continue;

				if (cur_dist > next_dist) {
					cur_dist = next_dist;
					nx = i;
					ny = j;
				}
			}
		}
	}

	P[idx].cx = nx;
	P[idx].cy = ny;
	arr[nx][ny] = -1;
}

int main() {
	int T = 1;
	cin >> T; 
	
	for (int tc = 1; tc <= T; ++tc) {
		// global_init();
		ans = 1;

		cin >> n >> m;

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> arr[i][j];

		for (int idx = 1; idx <= m; ++idx) {
			cin >> P[idx].ex >> P[idx].ey;
			P[idx].cx = P[idx].cy = P[idx].died = 0;
		}

		while (true) {
			//cout << "RUN" << ans << "\n";

			int flag = min(ans, m + 1);
			//cout << flag << "!!\n";

			for (int idx = 1; idx < flag; ++idx) {
				if (P[idx].died == 1) continue;
				movePlayer(idx);
			}

			makeBlind();

			if (flag < m + 1) {
				//cout << flag << "입장\n";
				entering(flag);
			}


			if (canBreak()) {
				break;
			}

			//showArr();

			//showPlayer();

			ans++;
		}

		cout << ans << '\n';
	}

	return 0;
}

/*
* 코드트리 빵을 구하고자 하는 m명의 사람.
* 1번사람은 1분에 2번사람은 2분에 ... m번 사람은 m분에 
각자의 베이스캠프에서 편의점으로 이동
* n * n 격자내에서 진행되며, 모두의 목표 편의점은 제각각 다르다.
* 1분에서 3가지 행동을 진행한다.
*/

/*	1. 격자에 있는 사람들 모두가 본인이 가고 싶어하는 편의점으로 향해 1칸이동
* 최단거리로 움직이며 최단거리가 여러가지라면 상 좌 우 하 우선순위를 가짐
* 최단거리는 BFS 기준이다.
*/

/* 2. 편의점에 도착한다면 해당 편의점에서 멈추고, 이 때 부터 다른 사람들은
해당 편의점이 있는 칸을 지나갈 수 없다.
격자에 있는 사람들이 모두 이동한 뒤
해당 칸을 지나갈 수 없음에 유의할 것
*/

/* t <= m 인 t분에서는 t번 사람을 자신이 가고 싶어하는 편의점과
* 가장 가까이 있는 베이스 캠프에 들어간다. 가장 가까이 있다. BFS임.
* 그런 베이스 캠프가 여러 개일 경우에는 행작 열작 순으로
* 이때부터 다른 사람들은 해당 베이스 캠프를 지날 수 없음.
* 앞으로도 계속.
*/

// 모든 사람이 편의점에 도착하는 시간을 출력하기
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, k;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };


int arr[25][25];
int cold[25][25];
int wall[25][25][4];

int visited[25][25];

int ans = 0;

void showCold() {
	cout << " COLD MAP\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << cold[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << "\n";
}

void diffuseUp(int i, int j) {
	queue<pair<int, int>> q;

	int cx = i + dx[0];
	int cy = j + dy[0];
	if (cx < 1 || cx > n || cy < 1 || cy > n) return;
	if (wall[i][j][0] == 1) return;

	q.push({ cx, cy });
	visited[cx][cy] = 5;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		int x1 = x + dx[0];
		int y1 = y + dy[0];

		if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= n) {
			if (wall[x][y][0] == 0 && visited[x][y] > 1) {
				q.push({ x1, y1 });
				visited[x1][y1] = visited[x][y] - 1;
			}
		}

		int x2 = x + dx[1];
		int y2 = y + dy[1];
		int x3 = x2 + dx[0];
		int y3 = y2 + dy[0];

		if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= n) {
			if (wall[x][y][1] == 0) {
				if (x3 >= 1 && x3 <= n && y3 >= 1 && y3 <= n) {
					if (wall[x2][y2][0] == 0 && visited[x][y] > 1) {
						q.push({ x3, y3 });
						visited[x3][y3] = visited[x][y] - 1;
					}
				}
			}
		}

		int x4 = x + dx[3];
		int y4 = y + dy[3];
		int x5 = x4 + dx[0];
		int y5 = y4 + dy[0];

		if (x4 >= 1 && x4 <= n && y4 >= 1 && y4 <= n) {
			if (wall[x4][y4][1] == 0) {
				if (x5 >= 1 && x5 <= n && y5 >= 1 && y5 <= n) {
					if (wall[x4][y4][0] == 0 && visited[x][y] > 1) {
						q.push({ x5, y5 });
						visited[x5][y5] = visited[x][y] - 1;
					}
				}
			}
		}
	}
}

void diffuseLeft(int i, int j) {
	queue<pair<int, int>> q;

	int cx = i + dx[1];
	int cy = j + dy[1];
	if (cx < 1 || cx > n || cy < 1 || cy > n) return;
	if (wall[i][j][1] == 1) return;

	q.push({ cx, cy });
	visited[cx][cy] = 5;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		int x1 = x + dx[1];
		int y1 = y + dy[1];

		if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= n) {
			if (wall[x][y][1] == 0 && visited[x][y] > 1) {
				q.push({ x1, y1 });
				visited[x1][y1] = visited[x][y] - 1;
			}
		}

		int x2 = x + dx[2];
		int y2 = y + dy[2];
		int x3 = x2 + dx[1];
		int y3 = y2 + dy[1];

		if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= n) {
			if (wall[x2][y2][0] == 0) {
				if (x3 >= 1 && x3 <= n && y3 >= 1 && y3 <= n) {
					if (wall[x2][y2][1] == 0 && visited[x][y] > 1) {
						q.push({ x3, y3 });
						visited[x3][y3] = visited[x][y] - 1;
					}
				}
			}
		}

		int x4 = x + dx[0];
		int y4 = y + dy[0];
		int x5 = x4 + dx[1];
		int y5 = y4 + dy[1];

		if (x4 >= 1 && x4 <= n && y4 >= 1 && y4 <= n) {
			if (wall[x][y][0] == 0) {
				if (x5 >= 1 && x5 <= n && y5 >= 1 && y5 <= n) {
					if (wall[x4][y4][1] == 0 && visited[x][y] > 1) {
						q.push({ x5, y5 });
						visited[x5][y5] = visited[x][y] - 1;
					}
				}
			}
		}
	}
}

void diffuseRight(int i, int j) {
	queue<pair<int, int>> q;

	int cx = i + dx[3];
	int cy = j + dy[3];
	if (cx < 1 || cx > n || cy < 1 || cy > n) return;
	if (wall[cx][cy][1] == 1) return;

	q.push({ cx, cy });
	visited[cx][cy] = 5;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		int x1 = x + dx[3];
		int y1 = y + dy[3];

		if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= n) {
			if (wall[x1][y1][1] == 0 && visited[x][y] > 1) {
				q.push({ x1, y1 });
				visited[x1][y1] = visited[x][y] - 1;
			}
		}

		int x2 = x + dx[0];
		int y2 = y + dy[0];
		int x3 = x2 + dx[3];
		int y3 = y2 + dy[3];

		if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= n) {
			if (wall[x][y][0] == 0) {
				if (x3 >= 1 && x3 <= n && y3 >= 1 && y3 <= n) {
					if (wall[x3][y3][1] == 0 && visited[x][y] > 1) {
						q.push({ x3, y3 });
						visited[x3][y3] = visited[x][y] - 1;
					}
				}
			}
		}

		int x4 = x + dx[2];
		int y4 = y + dy[2];
		int x5 = x4 + dx[3];
		int y5 = y4 + dy[3];

		if (x4 >= 1 && x4 <= n && y4 >= 1 && y4 <= n) {
			if (wall[x4][y4][0] == 0) {
				if (x5 >= 1 && x5 <= n && y5 >= 1 && y5 <= n) {
					if (wall[x5][y5][1] == 0 && visited[x][y] > 1) {
						q.push({ x5, y5 });
						visited[x5][y5] = visited[x][y] - 1;
					}
				}
			}
		}
	}
}

void diffuseDown(int i, int j) {
	queue<pair<int, int>> q;

	int cx = i + dx[2];
	int cy = j + dy[2];
	if (cx < 1 || cx > n || cy < 1 || cy > n) return;
	if (wall[cx][cy][1] == 1) return;

	q.push({ cx, cy });
	visited[cx][cy] = 5;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		int x1 = x + dx[2];
		int y1 = y + dy[2];

		if (x1 >= 1 && x1 <= n && y1 >= 1 && y1 <= n) {
			if (wall[x1][y1][0] == 0 && visited[x][y] > 1) {
				q.push({ x1, y1 });
				visited[x1][y1] = visited[x][y] - 1;
			}
		}

		int x2 = x + dx[3];
		int y2 = y + dy[3];
		int x3 = x2 + dx[2];
		int y3 = y2 + dy[2];

		if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= n) {
			if (wall[x2][y2][1] == 0) {
				if (x3 >= 1 && x3 <= n && y3 >= 1 && y3 <= n) {
					if (wall[x3][y3][0] == 0 && visited[x][y] > 1) {
						q.push({ x3, y3 });
						visited[x3][y3] = visited[x][y] - 1;
					}
				}
			}
		}

		int x4 = x + dx[1];
		int y4 = y + dy[1];
		int x5 = x4 + dx[2];
		int y5 = y4 + dy[2];

		if (x4 >= 1 && x4 <= n && y4 >= 1 && y4 <= n) {
			if (wall[x][y][1] == 0) {
				if (x5 >= 1 && x5 <= n && y5 >= 1 && y5 <= n) {
					if (wall[x5][y5][0] == 0 && visited[x][y] > 1) {
						q.push({ x5, y5 });
						visited[x5][y5] = visited[x][y] - 1;
					}
				}
			}
		}
	}
}

void diffuse(int i, int j, int dir) {
	if (dir == 2)
		dir = 1;
	else if (dir == 3)
		dir = 0;
	else if (dir == 4)
		dir = 3;
	else if (dir == 5)
		dir = 2;

	fill(&visited[0][0], &visited[0][0] + 25 * 25, 0);

	if (dir == 0)
		diffuseUp(i, j);
	else if (dir == 1)
		diffuseLeft(i, j);
	else if (dir == 2)
		diffuseDown(i, j);
	else if (dir == 3)
		diffuseRight(i, j);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cold[i][j] += visited[i][j];
}

void mixedColdMap() {
	int tmp[25][25];
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j)
			tmp[i][j] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {

			for (int dir = 0; dir < 4; ++dir) {
				int xx = i + dx[dir];
				int yy = j + dy[dir];

				if (xx < 1 || xx > n || yy < 1 || yy > n) continue;

				if (dir == 0) {
					if (wall[i][j][0] == 1) continue;
					if ((cold[i][j] - cold[xx][yy]) > 0) {
						tmp[i][j] -= (cold[i][j] - cold[xx][yy]) / 4;
						tmp[xx][yy] += (cold[i][j] - cold[xx][yy]) / 4;
					}
				}
				else if (dir == 1) {
					if (wall[i][j][1] == 1) continue;
					if ((cold[i][j] - cold[xx][yy]) > 0) {
						tmp[i][j] -= (cold[i][j] - cold[xx][yy]) / 4;
						tmp[xx][yy] += (cold[i][j] - cold[xx][yy]) / 4;
					}
				}
				else if (dir == 2) {
					if (wall[xx][yy][0] == 1) continue;
					if ((cold[i][j] - cold[xx][yy]) > 0) {
						tmp[i][j] -= (cold[i][j] - cold[xx][yy]) / 4;
						tmp[xx][yy] += (cold[i][j] - cold[xx][yy]) / 4;
					}
				}
				else if (dir == 3) {
					if (wall[xx][yy][1] == 1) continue;
					if ((cold[i][j] - cold[xx][yy]) > 0) {
						tmp[i][j] -= (cold[i][j] - cold[xx][yy]) / 4;
						tmp[xx][yy] += (cold[i][j] - cold[xx][yy]) / 4;
					}
				}

			}
		}
	}

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cold[i][j] += tmp[i][j];
}

void decrease() {
	for (int j = 1; j <= n; ++j) {
		if (cold[1][j] > 0)
			cold[1][j]--;
		if (cold[n][j] > 0)
			cold[n][j]--;
	}

	for (int i = 2; i <= n - 1; ++i) {
		if (cold[i][1] > 0)
			cold[i][1]--;
		if (cold[i][n] > 0)
			cold[i][n]--;
	}
}

bool canBreak() {

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (arr[i][j] == 1) {
				if (cold[i][j] < k) return false;
			}
			else continue;
		}
	}
	return true;
}

int main() {
	int  T = 1;
	//cin >> T;

	/*
	n = 3;
	cold[1][1] = 8; cold[1][2] = 4; cold[1][3] = 1;
	cold[2][1] = 2; cold[2][2] = 9; cold[2][3] = 3;
	cold[3][1] = 2; cold[3][2] = 1; cold[3][3] = 4;
	showCold();
	wall[3][2][0] = 1; wall[2][3][1] = 1;
	mixedColdMap();
	showCold();*/

	for (int tc = 1; tc <= T; ++tc) {
		//global_init();
		fill(&arr[0][0], &arr[0][0] + 25 * 25, 0);
		fill(&cold[0][0], &cold[0][0] + 25 * 25, 0);
		fill(&wall[0][0][0], &wall[0][0][0] + 25 * 25 * 4, 0);
		ans = 1;

		cin >> n >> m >> k;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> arr[i][j];
			}
		}

		for (int i = 1; i <= m; ++i) {
			int x, y, s;
			cin >> x >> y >> s;
			wall[x][y][s] = 1;
		}


		while (true) {
			//cout << "RUN " << ans << "\n";

			/*
			1. 바람이 나와서 공기를 만든다. 퍼져나간다. (이등변 삼각형)
			오른쪽일 경우. 위쪽 45도와 아랫쪽 45도 그리고 오른쪽. 가는길에 벽이 있으면 전파 stop
			오른쪽에서 오른쪽은 벽 하나만 체크
			아래45, 위 45도는 벽 두개 체크

			시원함의 전파는 합산이다.
			*/
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (arr[i][j] >= 2 && arr[i][j] <= 5) {
						diffuse(i, j, arr[i][j]);
						//showCold();
					}
				}
			}

			/*
			2. 공기의 섞임.
			서로 인접한 칸들에 대하여 높은 곳에서 낮은 곳으로 (시원함의 차이 / 4) 만큼 전파 된다.
			벽을 사이에 두고 있는 칸들은 일어나지 않음에 유의
			*/
			mixedColdMap();

			//cout << "AFTER MIXED\n";
			//showCold();

			/*
			3. 외벽인 칸들은 시원함이 1씩 감소한다.
			단 0이면 더이상 감소하지 안흔다
			*/

			decrease();
			//cout << "AFTER DECREASED\n";
			//showCold();

			if (canBreak())
				break;

			ans++;
		}

		cout << ans << "\n";
	}
	return 0;
}

/*
n*n 격자.  1- indexed
0 빈공간, 1 사무실 구역, 2 에어컨(왼), 3 에어컨(위), 4 에어컨(오), 5 에어컨(아래)
4가지 과정을 진행한다
*/

/*
1. 바람이 나와서 공기를 만든다. 퍼져나간다. (이등변 삼각형)
오른쪽일 경우. 위쪽 45도와 아랫쪽 45도 그리고 오른쪽. 가는길에 벽이 있으면 전파 stop
오른쪽에서 오른쪽은 벽 하나만 체크
아래45, 위 45도는 벽 두개 체크

시원함의 전파는 합산이다.
*/

/*
시원함의 합산.
*/

/*
2. 공기의 섞임.
서로 인접한 칸들에 대하여 높은 곳에서 낮은 곳으로 (시원함의 차이 / 4) 만큼 전파 된다.
벽을 사이에 두고 있는 칸들은 일어나지 않음에 유의
*/

/*
3. 외벽인 칸들은 시원함이 1씩 감소한다.
단 0이면 더이상 감소하지 안흔다
*https://www.codetree.ai/frequent-problems/problems/cooling-system/description$0/

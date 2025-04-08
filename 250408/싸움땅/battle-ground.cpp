#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

vector<int> gun[25][25];

struct player {
	int x, y, dir, s, point, gun, died;
};
player P[32];

int loser, winner;

void showPlayer() {
	for (int i = 1; i <= m; ++i) {
		cout << "IDX" << i << " " << P[i].x << "," << P[i].y << "\t\t";
	}
	cout << '\n';
}

void showPlayerGUN() {
	cout << "THIS IS GUN\n";
	for (int i = 1; i <= m; ++i) {
		cout << "IDX" << i << " " << P[i].gun << "\t\t";
	}
	cout << '\n';
}

void global_init() {
	loser = winner = 0;
	for (int i = 0; i < 25; ++i) {
		for (int j = 0; j < 25; ++j) {
			gun[i][j].clear();
		}
	}
}

bool isThere(int idx) {
	for (int i = 1; i <= m; ++i) {
		if (i == idx) continue;
		if (P[i].x == P[idx].x && P[i].y == P[idx].y) {
			return true;
		}
	}
	return false;
}


/*
이동한 방향에 플레이어가 없을 경우
해당 칸에 총이 있는지 확인.
만약 총이 있다면, 플레이어는 총을 획득한다.

플레이어가 이미 총을 가지고 있다면 놓여있는 총과 플레이어 총 가운데
공격력이 더 쎈 총 획득하고, 나머지 총들은 격자에
*/
void getGun(int idx) {
	if (gun[P[idx].x][P[idx].y].size() <= 0) return;
	//cout << P[idx].x << "AND" << P[idx].y << "\n";
	sort(gun[P[idx].x][P[idx].y].begin(), gun[P[idx].x][P[idx].y].end(), greater<int>());
	
	//cout << gun[P[idx].x][P[idx].y][0] << "!!!!\n";
	if (P[idx].gun < gun[P[idx].x][P[idx].y][0]) {
		int tmp = P[idx].gun;
		P[idx].gun = gun[P[idx].x][P[idx].y][0];
		gun[P[idx].x][P[idx].y].erase(gun[P[idx].x][P[idx].y].begin());
		gun[P[idx].x][P[idx].y].push_back(tmp);
	}
}

/*
이동한 방향에 플레이어가 있을경우
싸움 시작
플레이어들의 초기 능력치와 가지고 있는 총의 합을 비교하여 더 큰 플레이어 승리
만약 같다면, 초기 능력치가 쎈 플레이어가 승리

이긴 플레이어 점수 += 초기 능력치와 가지고 있는 총의 합의 차이만큼 포인트 획득
*/
void fight(int idx) {
	int target = 0;
	for (int i = 1; i <= m; ++i) {
		if (i == idx) continue;
		if (P[i].x == P[idx].x && P[i].y == P[idx].y) {
			target = i;
			break;
		}
	}

	if (P[idx].s + P[idx].gun > P[target].s + P[target].gun) {
		winner = idx;
		loser = target;
	}
	else if (P[idx].s + P[idx].gun < P[target].s + P[target].gun) {
		winner = target;
		loser = idx;
	}
	else {
		if (P[idx].s > P[target].s) {
			winner = idx;
			loser = target;
		}
		else {
			winner = target;
			loser = idx;
		}
	}

	P[winner].point = (P[winner].s + P[winner].gun) - (P[loser].s + P[loser].gun);
}


bool isIn(int x, int y, int idx) {
	for (int i = 1; i <= m; ++i) {
		if (i == idx) continue;
		if (x == P[i].x && y == P[i].y)
			return true;
	}
	return false;
}

/*
진 플레이어는 본인이 가진 총을 격자에 내려놓는다.
원래 방향대로 한 칸 이동해야한다
이동하려는 칸에 다른 플레이어가 있거나 격자 밖인 경우, 오른쪽으로 90도씩
회전하며 있으면 바로 이동.
이 때 총이 있다면, 해당 플레이어는 공격력이 가장 높은 총을 획득
*/
void loserMove() {
	gun[P[loser].x][P[loser].y].push_back(P[loser].gun);
	P[loser].gun = 0;

	for (int d = P[loser].dir; d < P[loser].dir + 4; ++d) {
		int dir = d % 4;

		int nx = P[loser].x + dx[dir];
		int ny = P[loser].y + dy[dir];

		if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
		if (isIn(nx, ny, loser)) {
			continue;
		}
		else {
			P[loser].x = nx;
			P[loser].y = ny;
			P[loser].dir = dir;
			break;
		}
	}
	
	getGun(loser);
}

void winnerMove() {
	getGun(winner);
}

/*
* 첫번째 플레이어부터 순차적으로 본인이 향하고 있는 방향으로 1만큼 이동
* 해당 격자가 OOB일 경우에는 정반대로 방향을 바꾸어 1만큼 이동
*/
void movePlayer(int idx) {

	int nx = P[idx].x + dx[P[idx].dir];
	int ny = P[idx].y + dy[P[idx].dir];

	if (nx < 1 || nx > n || ny < 1 || ny > n) {
		P[idx].dir = (P[idx].dir + 2) % 4;
	}
	nx = P[idx].x + dx[P[idx].dir];
	ny = P[idx].y + dy[P[idx].dir];

	P[idx].x = nx;
	P[idx].y = ny;

}

void movePlayers() {
	for (int idx = 1; idx <= m; ++idx) {
		//cout << idx << " 이동\n";
		movePlayer(idx);
		/*
		이동한 방향에 플레이어가 없을 경우
		해당 칸에 총이 있는지 확인.
		만약 총이 있다면, 플레이어는 총을 획득한다.

		플레이어가 이미 총을 가지고 있다면 놓여있는 총과 플레이어 총 가운데
		공격력이 더 쎈 총 획득하고, 나머지 총들은 격자에
		*/

		if (isThere(idx)) {
			fight(idx);
			//cout << "FIGHT!! WINNER" << winner << " LOSER" << loser << "\n";
			loserMove();
			winnerMove();
		}
		else {
			//cout << " NO FIGHT\n";
			getGun(idx);
		}

		//showPlayer();
		//showPlayerGUN();
	}
}

int	main() {
	int T = 1;

	//cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		global_init();

		cin >> n >> m >> k;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				int x;
				cin >> x;
				gun[i][j].push_back(x);
			}
		}
		for (int idx = 1; idx <= m; ++idx) {
			cin >> P[idx].x >> P[idx].y >> P[idx].dir >> P[idx].s;
			P[idx].gun = P[idx].died = 0;
		}

		for (int run = 1; run <= k; ++run) {
			//cout << "RUN" << run << '\n';

			//showPlayer();
			loser = 0, winner = 0;
			movePlayers();

			//cout << "\n======================================\n";
		}

		for (int idx = 1; idx <= m; ++idx) {
			cout << P[idx].point << ' ';
		}
		cout << '\n';
	}
	return 0;
}
/*
n*n 격자 크기에서 진행.
각각의 격자에는 무기들이 있을 수 있다.
초기에 무기들이 없는 빈 격자에 플레이어들이 위치.
각 플레이어는 초기 능력치를 가진다.
*/

/*
* 첫번째 플레이어부터 순차적으로 본인이 향하고 있는 방향으로 1만큼 이동
* 해당 격자가 OOB일 경우에는 정반대로 방향을 바꾸어 1만큼 이동
*/

/*
이동한 방향에 플레이어가 없을 경우
해당 칸에 총이 있는지 확인.
만약 총이 있다면, 플레이어는 총을 획득한다.

플레이어가 이미 총을 가지고 있다면 놓여있는 총과 플레이어 총 가운데
공격력이 더 쎈 총 획득하고, 나머지 총들은 격자에
*/

/*
이동한 방향에 플레이어가 있을경우
싸움 시작
플레이어들의 초기 능력치와 가지고 있는 총의 합을 비교하여 더 큰 플레이어 승리
만약 같다면, 초기 능력치가 쎈 플레이어가 승리

이긴 플레이어 점수 += 초기 능력치와 가지고 있는 총의 합의 차이만큼 포인트 획득
*/

/*
진 플레이어는 본인이 가진 총을 격자에 내려놓는다.
원래 방향대로 한 칸 이동해야한다
이동하려는 칸에 다른 플레이어가 있거나 격자 밖인 경우, 오른쪽으로 90도씩
회전하며 있으면 바로 이동.
이 때 총이 있다면, 해당 플레이어는 공격력이 가장 높은 총을 획득
*/

/*
이긴 플레이어는 승리한 칸에 떨어져있는 총들과 보유한 총 중
가장 큰 것을 획득한다
*/

// k라운드 진행하며 각 플레이어들이 획득한 포인트를 출력.
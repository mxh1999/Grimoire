#include <bits/stdc++.h>
using namespace std;
int vis[55][55][55][55], kase;
double dp[55][55][55][55];
const double INF = 1e9;
const double eps = 1e-9;
int def[3];

double calc(double tmp[2][2], double p1, double p2) {
	return tmp[0][0] * p1 * p2 + tmp[0][1] * p1 * (1 - p2) + tmp[1][0] * (1 - p1) * p2 + tmp[1][1] * (1 - p1) * (1 - p2);
}

double DP(int atk1, int hp1, int atk2, int hp2) {
	if (hp1 <= 0) return hp2 <= 0 ? 0 : -100;
	if (hp2 <= 0) return 100;
	
	if (vis[atk1][hp1][atk2][hp2] == kase) return dp[atk1][hp1][atk2][hp2];
	vis[atk1][hp1][atk2][hp2] = kase;
	double &res = dp[atk1][hp1][atk2][hp2];
	
	double tmp[2][2];
	for (int i = 0; i < 2; ++i) {
		if (i) std::swap(atk1, hp1);
		for (int j = 0; j < 2; ++j) {
			if (j) std::swap(atk2, hp2);
			tmp[i][j] = DP(atk1, hp1 - (atk2 + def[1] - 1) / def[1], atk2, hp2 - (atk1 + def[2] - 1) / def[2]);
			if (j) std::swap(atk2, hp2);
		}
		if (i) std::swap(atk1, hp1);
	}
	
	for (int i = 0; i < 2; ++i) {
		if (tmp[i][0] >= tmp[i ^ 1][0] && tmp[i][1] >= tmp[i ^ 1][1]) return res = std::min(tmp[i][0], tmp[i][1]);
		if (tmp[0][i] <= tmp[0][i ^ 1] && tmp[1][i] <= tmp[1][i ^ 1]) return res = std::max(tmp[0][i], tmp[1][i]);
	}
/*if (hp1 == 5) {*/
//	cout << calc(tmp, 1, 1) << endl;
/*}*/
	/*res = -INF;
	res = max(res, calc(tmp, 0, 0));
	res = max(res, calc(tmp, 0, 1));
	res = max(res, calc(tmp, 1, 0));
	res = max(res, calc(tmp, 1, 1));*/
	double a = tmp[0][0], b = tmp[0][1], c = tmp[1][0], d = tmp[1][1];
	if (fabs(a + d - b - c) > eps) {
		double p1 = (d - c) / (a + d - b - c),
				p2 = (d - b) / (a + d - b - c);
		p1 = min(p1, 1.0);
		p1 = max(p1, 0.0);
		p2 = min(p2, 1.0);
		p2 = max(p2, 0.0);
		if (p1 > -eps && p2 > -eps && p1 < 1 + eps && p2 < 1 + eps) {
			res = calc(tmp, p1, p2);
		}
	} else {
		res = max(0.0, b - d) + min(0.0, c - d) + d;
	}
	/*cout << hp1 << " " << atk1 << " " << hp2 << " " << atk2 << endl;
	cout << tmp[0][0] << " " << tmp[0][1] << endl;
	cout << tmp[1][0] << " " << tmp[1][1] << endl;
	cout << "res = " << res << endl;
	cout << endl;*/
	return res;
}

int main() {
	int atk[3], hp[3];
	
	int caseCnt; scanf("%d", &caseCnt);
	for (kase = 1; kase <= caseCnt; ++kase) {
		for (int i = 1; i <= 2; ++i) scanf("%d%d%d", hp + i, atk + i, def + i);
		
		printf("Case #%d: %.8f\n", kase, DP(atk[1], hp[1], atk[2], hp[2]));
	}
	
	return 0;
}

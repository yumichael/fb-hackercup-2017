#include <vector>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

#define _(i, j) [n * min((i), (j)) + max((i), (j))]

template<typename T>
inline T minPos(T x, T y) {
	return x < 0 ? y : (y < 0 ? x : min(x, y));
}

template<typename T>
inline T addPos(T x, T y) {
	return x >= 0 && y >= 0 ? x + y : -1;
}

template<typename Matrix>
void floydWarshall(int n, Matrix const& graph, Matrix& dist) {
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			dist _(i, j) = graph _(i, j);
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				dist _(i, j) = minPos(dist _(i, j), addPos(dist _(i, k), dist _(k, j)));
			}
		}
	}
}


void mm(char const* input) {
	freopen(input, "r", stdin);
	freopen("out.txt", "w", stdout);
	int nCases;
	cin >> nCases;
	for (int iCase = 1; iCase <= nCases; ++iCase) {
		cout << "Case #" << iCase << ": ";
		int n, m, k;
		cin >> n >> m >> k;
		vector<long> w(n * n, -1);
		for (int i = 0; i < m; ++i) {
			int a, b, g;
			cin >> a >> b >> g;
			w _(a - 1, b - 1) = g;
		}
		for (int i = 0; i < n; ++i) {
			w _(i, i) = 0;
		}
		vector<long> d(n * n, -1);
		floydWarshall<>(n, w, d);
		vector<int> s(k + 3, 0);
		vector<int> t(k + 3, 0);
		t[0] = 0;
		s[0] = -1;
		for (int i = 1; i <= k; ++i) {
			cin >> s[i] >> t[i];
			--s[i];
			--t[i];
		}
		vector<long> x((k + 1) * 4);
		// Let i index the last delivery made, starting at 1
		// Case 0. Just made delivery i, carrying 0 belongings now.
		// Case 1. Just made delivery i, carrying belonging i + 1.
		// Case 2. Just picked up belonging i + 1 and carrying only that.
		// Case 3. Just picked up belonging i + 2 and carrying i + 1 also.
		int i = 0;
		long travel, travel1, travel2, option1, option2;
		
		x[4 * i + 0] = 0;
		
		x[4 * i + 1] = -1;
		
		travel = d _(t[0], s[1]);
		x[4 * i + 2] = addPos(x[0], travel);
		
		travel = d _(s[1], s[2]);
		x[4 * i + 3] = addPos(x[2], travel);
		if (i + 2 > k) {
			x[4 * i + 3] = -1;
		}
		
		for (i = 1; i <= k; ++i) {
			travel1 = d _(t[i - 1], t[i]);
			option1 = addPos(x[4 * (i - 1) + 1], travel1);
			travel2 = d _(s[i], t[i]);
			option2 = addPos(x[4 * (i - 1) + 2], travel2);
			x[4 * i + 0] = minPos(option1, option2);
			
			travel = d _(s[i + 1], t[i]);
			x[4 * i + 1] = addPos(x[4 * (i - 1) + 3], travel);
			
			travel = d _(t[i], s[i + 1]);
			x[4 * i + 2] = addPos(x[4 * i + 0], travel);
			if (i + 1 > k) {
				x[4 * i + 2] = -1;
			}

			travel1 = d _(t[i], s[i + 2]);
			option1 = addPos(x[4 * i + 1], travel1);
			travel2 = d _(s[i + 1], s[i + 2]);
			option2 = addPos(x[4 * i + 2], travel2);
			x[4 * i + 3] = minPos(option1, option2);
			if (i + 2 > k) {
				x[4 * i + 3] = -1;
			}
		}
		cout << x[4 * k] << endl;
	}
}

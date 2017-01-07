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

void ll(char const* input) {
	freopen(input, "r", stdin);
	freopen("out.txt", "w", stdout);
	int nCases;
	cin >> nCases;
	for (int iCase = 1; iCase <= nCases; ++iCase) {
		cout << "Case #" << iCase << ": ";
		int n;
		cin >> n;
		vector<int> w(n);
		for (int i = 0; i < n; ++i) {
			cin >> w[i];
		}
		sort(w.begin(), w.end(), greater<>());
		int moved = 0;
		int trip;
		for (trip = 0; moved < n; ++trip) {
			auto x = div(50, w[trip]);
			moved += x.quot + bool(x.rem);
		}
		if (moved > n) {
			--trip;
		}
		cout << trip << endl;
	}
}

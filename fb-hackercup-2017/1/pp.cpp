#include <vector>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>

using namespace std;

void pp(char const* input) {
	assert(freopen(input, "r", stdin));
	assert(freopen("out.txt", "w", stdout));
	int nCases;
	cin >> nCases;
	for (int iCase = 1; iCase <= nCases; ++iCase) {
		cout << "Case #" << iCase << ": ";
		int n, m;
		cin >> n >> m;
		vector<long> c(n * m);
		auto c0 = c.begin();
		int total = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> c[m * i + j];
			}
			sort(c0 + m * i, c0 + m * (i + 1));
			for (int j = 0; j < m; ++j) {
				c[m * i + j] += 2 * j + 1;
			}
			inplace_merge(c0 + i, c0 + m * i, c0 + m * (i + 1));
			total += c[i];
		}
		cout << total << endl;
	}
}

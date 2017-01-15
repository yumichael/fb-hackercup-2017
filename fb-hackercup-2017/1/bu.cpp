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

// http://stackoverflow.com/questions/16443682/c-power-of-integer-template-meta-programming
template<class T>
inline constexpr T powConst(const T base, unsigned const exponent)
{
	// (parentheses not required in next line)
	return (exponent == 0) ? 1 :
		(exponent % 2 == 0) ? powConst(base, exponent / 2)*powConst(base, exponent / 2) :
		base * powConst(base, (exponent - 1) / 2) * powConst(base, (exponent - 1) / 2);
}

//typedef unsigned long Small;
//typedef unsigned long long Large; // this gives me a boatload of trouble idk why
#define Small long
#define Large long long // idk why but I can't initialize memo when Large has been defined by typedef
const long long p{ 1'000'000'007 }; // long long avoids overflow when multiplying
// (yes I know there's a way to do it mod p even with long but that requires custom multiplication mod p code which may or may not be slower than 64 bit mult)
//const long long pow4[]{ 1, 4, 16, 64, 256, 1'024, 4'096, 16'384, 65'536, 262'144, 1'048'576 };
static Large *memo[15];

static Large inverse[2001];

Large invert(Large n) {
	Large t = 0;
	Large r = p;
	Large t1 = 1;
	Large r1 = n;
	while (r1) {
		Large q = r / r1;
		Large temp = t - q * t1;
		Large remp = r - q * r1;
		t = t1;
		r = r1;
		t1 = temp;
		r1 = remp;
	}
	if (t < 0) {
		t += p;
	}
	return t;
}

void init() { // precalculate rising factorial ranges and inverses
	for (Large i = 1; i <= 2000; ++i) {
		inverse[i] = invert(i);
	}
	cout << "inverses done, now rising factorials" << endl;
	for (int l = 1; l < 15; ++l) {
		memo[l] = new Large[p / powConst(4, l)];
	} // costs about 2.7 GB
	cout << 1 << endl;
	memo[1][0] = 1 * 2 * 3;
	for (Large i = 1; i < p / 4; ++i) {
		memo[1][i] = (i * 4) * (i * 4 + 1) % p * (i * 4 + 2) % p * (i * 4 + 3) % p;
	}
	for (int l = 2; l <= 14; ++l) {
		cout << l << endl;
		for (Large i = 0; i < p / powConst(4, l); ++i) {
			// want to calculate prod(begin=i*4^l, end=(i+1)*4^l)
			memo[l][i] = memo[l - 1][4 * i] * memo[l - 1][4 * i + 1] % p * memo[l - 1][4 * i + 2] % p * memo[l - 1][4 * i + 3] % p;
		}
	}
	cout << "init done" << endl;
}

void kill() {
	for (int l = 1; l < 15; ++l) {
		delete[] memo[l];
	}
}

inline Large risingMemo(int l, Large i) {
	if (l) {
		return memo[l][i];
	}
	else if (i >= 1) {
		return i;
	}
	else {
		return 1;
	}
}

vector<int> base4(Large x) {
	vector<int> result(15, 0);
	for (int i = 0; i < 15; ++i) {
		result[i] = x % 4;
		x /= 4;
	}
	return result;
}

Large rising(Large x, Small n) { // rising factorial function
	Large ans = 1;
	Large formed = 0;
	Large low = x;
	Large high = x + n + 1;
	auto lo = base4(low);
	auto hi = base4(high);
	int k;
	for (k = 14; k >= 0; --k) {
		if (hi[k] != lo[k]) {
			break;
		}
		formed += hi[k];
		formed *= 4;
	}
	// if k == -1
	for (auto d = lo[k] + 1; d < hi[k]; ++d) {
		ans = risingMemo(k, formed + d) * ans % p;
	}
	Large hiformed = (formed + hi[k]) * 4;
	for (int hk = k - 1; hk >= 0; --hk) {
		for (int d = 0; d < hi[hk]; ++d) {
			ans = risingMemo(hk, hiformed + d) * ans % p;
		}
		hiformed += hi[hk];
		hiformed *= 4;
	}
	Large loformed = (formed + lo[k]) * 4;
	for (int lk = k - 1; lk >= 0; --lk) {
		for (int d = 3; d > lo[lk]; --d) {
			ans = risingMemo(lk, loformed + d) * ans % p;
		}
		loformed += lo[lk];
		loformed *= 4;
	}
	return ans;
}

void bu(char const* input) {
	assert(freopen(input, "r", stdin));
	assert(freopen("out.txt", "w", stdout));
	int nCases;
	cin >> nCases;
	for (int iCase = 1; iCase <= nCases; ++iCase) {
		cout << "Case #" << iCase << ": ";
		Small n;
		Large m;
		cin >> n >> m;
		vector<Small> r(n);
		Large r_sum = 0;
		for (Small i = 0; i < n; ++i) {
			cin >> r[i];
			r_sum += r[i];
		}
		r_sum *= 2;
		sort(r.begin(), r.end());
		Small lo = 0;
		Small hi = 0;
		Large combo;
		Large total = 0;
		if (n == 1) {
			cout << m << endl;
			continue;
		}
		for (Small i = 0; i < n; ++i) {
			for (Small j = i + 1; j < n; ++j) {
				//cout << "(i, j) = (" << i << ", " << j << ")" << endl;
				if (r[i] == lo && r[j] == hi) {
					total = (total + combo) % p;
					//cout << "total =" << total << endl;
					continue;
				}
				Large s = m - 1 + r[i] + r[j] - r_sum;
				//cout << "s = " << s << endl;
				combo = s >= 0 ? rising(s, n) : 0;
				//cout << "combo = " << combo << endl;
				total = (total + combo)  % p;
				//cout << "total = " << total << endl;
				lo = r[i];
				hi = r[j];
			}
		}
		total = total * 2 % p * inverse[n] % p * inverse[n - 1] % p;
		cout << total << endl;
	}
}

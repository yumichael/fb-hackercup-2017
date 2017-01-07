#include <vector>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

double const m_2pi = 6.283185307179586476925286766559005768394338798750211641949;
double const m_pi_2 = 1.570796326794896619231321691639751442098584699687552910487;

template<typename Number>
Number mod(Number x, Number m) {
	return fmod((fmod(x, m) + m), m);
}

void pp(char const* input) {
	freopen(input, "r", stdin);
	freopen("out.txt", "w", stdout);
	int nCases;
	cin >> nCases;
	for (int iCase = 1; iCase <= nCases; ++iCase) {
		cout << "Case #" << iCase << ": ";
		int p, x, y;
		cin >> p >> x >> y;
		x -= 50;
		y -= 50;
		if (x * x + y * y >= 50 * 50) {
			cout << "white";
		}
		else if (p == 0) {
			cout << "white";
		}
		else {
			double angle = mod(m_pi_2 - atan2(y, x), m_2pi);
			if (angle / m_2pi * 100 <= p - 1) {
				cout << "black";
			}
			else if (angle <= p / 100. * m_2pi) {
				cout << "black";
			}
			else {
				cout << "white";
			}
		}
		cout << endl;
	}
}

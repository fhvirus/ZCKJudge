#include<bits/stdc++.h>
#include"jngen.h"
using namespace std;

//const int kN = 3e5;
const int kN = 10;
//const int kC = 1e9;
const int kC = 100;

int main(){
	int N = rnd.next(1, kN);
	int Q = rnd.next(1, kN);
	int K = rnd.next(1, N);
	cout << N << ' ' << Q << ' ' << K << '\n';
	auto a = Array::random(N, 1, kC);
	cout << a << '\n';
	for(int i = 0; i < Q; ++i)
		cout << rnd.nextp(1, N, opair) << '\n';
	return 0;
}

// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif


const int kN = 505;
const int kC = 505;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, c; cin >> n >> c;
	vector<int> p(n), a(n), b(n);
	for(int &i: p) cin >> i;
	for(int &i: a) cin >> i;
	for(int &i: b) cin >> i;

	ll ans = 0;
	for(int i = 0; i < n; ++i){
		int w = min(p[i], a[i]);
		ans += w;
		p[i] -= w;
	}
	debug(ans);

	vector<int> can;
	for(int i = n-1; i >= 0; --i){
		// insert b[i]
		can.pb(b[i]);
		for(int k = can.size()-1; k > 0; --k){
			if(can[k-1] >= can[k]) break;
			swap(can[k-1], can[k]);
		}
		debug(i, p[i], can);

		// greedy
		int in = p[i];
		for(int k = 0; k < (int) can.size(); ++k){
			if(i + k >= n or in == 0) break;
			int w = min({ in, c, can[k] });
			ans += w;
			can[k] -= w;
			in -= w;
		}
		debug(can);

		// sort (or merge)
		sort(AI(can), greater<int>());
		while(!can.empty() and can.back() == 0)
			can.pop_back();
		debug(can);
	}
	cout << ans << '\n';
	return 0;
}

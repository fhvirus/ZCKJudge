//Challenge: Accepted
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <bitset>
#include <deque>
#include <stack>
using namespace std;
void debug(){cout << endl;};
template<class T, class ...U> void debug(T a, U ... b){cout << a << " ", debug(b ...);};
template<class T> void pary(T l, T r) {
	while (l != r) cout << *l << " ", l++;
	cout << endl;
};
#define ll long long
#define maxn 300005
#define mod 1000000007
#define pii pair<int, int>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int a[maxn], mi[maxn];
struct query{
	int l, r, id;
	query(){l = r = id = 0;}
	query(int a, int b, int c){l = a, r = b, id = c;}
};
vector<query> que[maxn];
ll ans[maxn];
int main() {
	io
	int n, q, k;
	cin >> n >> q >> k;	
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = 0;i < q;i++) {
		int l, r;
		cin >> l >> r;
		que[l % k].push_back(query(l, r, i));	
	}
	deque<int> deq;
	for (int i = n;i >= 1;i--) {
		while (deq.size() && a[i] <= a[deq.back()]) deq.pop_back();
		deq.push_back(i);
		while (deq.size() && deq.front() >= i + k) deq.pop_front();
		mi[i] = a[deq.front()];	
	}
	for (int x = 0;x < k;x++) {
		sort(que[x].begin(), que[x].end(), [&](query p, query q){return p.l > q.l;});
		int c = (x + 1) % k;
		int cur = c + k * ((n - c) / k), ind = (n - c) / k - 1, num = ind, siz = que[x].size();
		vector<int> stk;
		for (auto q:que[x]) {
			int cur = a[q.l];
			while (q.l <= q.r) {
				ans[q.id] += cur;
				cur = min(cur, mi[q.l + 1]);
				q.l += k;
			}
		}
	}
	for (int i = 0;i < q;i++) cout << ans[i] << "\n";
}



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
ll a[maxn], mi[maxn];
struct query{
	int l, r, id;
	query(){l = r = id = 0;}
	query(int a, int b, int c){l = a, r = b, id = c;}
};
vector<query> que[maxn];
ll ans[maxn];
struct segtree{
	ll seg[4 * maxn], tag[4 * maxn];
	void init(int cur, int l, int r) {
		//debug(cur);
		seg[cur] = 0, tag[cur] = 0;
		if (r - l <= 1) return;
		int mid = (l + r) / 2;
		init(cur * 2, l, mid), init(cur * 2 + 1, mid, r);
	}
	void push(int cur, int l, int r) {
		if (!tag[cur]) return;
		seg[cur] = tag[cur] * (r - l);
		if (r - l > 1) {
			tag[cur * 2] = tag[cur];
			tag[cur * 2 + 1] = tag[cur];
		}
		tag[cur] = 0;
	}
	void pull(int cur, int l, int r) {
		int m = (l + r) / 2;
		push(cur, l, r);
		if (r - l > 2) {
			push(cur * 2, l, m), push(cur * 2 + 1, m, r);
			seg[cur] = seg[cur * 2] + seg[cur * 2 + 1];
		}
	}
	void modify(int cur, int l, int r, int ql, int qr, ll val) {
		if (r <= l || ql >= r || qr <= l) return;
		push(cur, l, r);
		if (ql <= l && qr >= r) {
			tag[cur] = val;
			push(cur, l, r);
			return;	
		}	
		int m = (l + r) / 2;
		modify(cur * 2, l, m, ql, qr, val);
		modify(cur * 2 + 1, m, r, ql, qr, val);
		pull(cur, l, r);
	}
	ll query(int cur, int l, int r, int ql, int qr) {
		if (r <= l || ql >= r || qr <= l) return 0;
		pull(cur, l, r);
		if (ql <= l && qr >= r) {
			return seg[cur];
		}
		int m = (l + r) / 2;
		return query(cur * 2, l, m, ql, qr) + query(cur * 2 + 1, m, r, ql, qr);
	}
}tree;
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
		//debug(mi[i]);
	}
	for (int x = 0;x < k;x++) {
		sort(que[x].begin(), que[x].end(), [&](query p, query q){return p.l > q.l;});
		int c = (x + 1);
		int cur = c + k * ((n - c) / k), ind = (cur-x) / k, num = ind, siz = que[x].size();
		//debug(cur,ind);
		tree.init(1, 0, num + 1);
		vector<int> stk;
		for (auto q:que[x]) {
			while (cur >= q.l + 1) {
				while (stk.size() && mi[cur] <= mi[stk.back()]) stk.pop_back();
				tree.modify(1, 0, num + 1, (cur - x) / k, stk.size() ? (stk.back() - x) / k : num + 1, mi[cur]);
				stk.push_back(cur);
				cur -= k, ind--;
			}
			ans[q.id] = a[q.l];
			//debug(7122, cur);
			//pary(stk.begin(), stk.end());
			if (q.r != q.l) {
				int lef = (q.l - x + 1) / k, rig = (q.r - x) / k;
				if (stk.size()) {
					int low = -1, up = stk.size();
					while (low < up - 1) {
						int mid = (low + up) / 2;
						if (a[q.l] < mi[stk[mid]]) up = mid;
						else low = mid;
					}
					//debug(q.l, q.r, lef, rig, (low >= 0 ? (stk[low] - x) / k : low), (low >= 0 ? mi[stk[low]] : low), a[q.l]);
					if (low == -1) ans[q.id] += a[q.l] * (rig - lef);
					else {
						int pos = min(rig, (stk[low] - x) / k);
						ans[q.id] += a[q.l] * (pos - lef);
						lef = pos;
						ans[q.id] += tree.query(1, 0, num + 1, lef, rig);
					}
				}
			}
		}
	}
	for (int i = 0;i < q;i++) cout << ans[i] << "\n";
}
/*
*/



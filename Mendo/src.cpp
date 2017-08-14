#include <bits/stdc++.h>

typedef long long ll;

struct treap {
	ll val, prior, size;
	treap *l, *r;
};

typedef treap* ptreap;

ll size(ptreap p){
	if(p){
		return p->size;
	}

	return 0;
}

ll update_size(ptreap p){
	if(p){
		p->size = 1 + size(p->l) + size(p->r);
	}
}

void split(ptreap pos, ptreap& l, ptreap& r, ll val){
	if(!pos){
		l = r = NULL;
	} else if(val <= pos->val){
		split(pos->l, l, pos->l, val);
		r = pos;
	} else {
		split(pos->r, pos->r, r, val);
		l = pos;
	}

	update_size(pos);
}

void insert(ptreap& pos, ptreap add){
	if(!pos){
		pos = add;
	} else if(add->prior > pos->prior){
		split(pos, add->l, add->r, add->val);
		pos = add;
	} else if(add->val <= pos->val){
		insert(pos->l, add);
	} else {
		insert(pos->r, add);
	}

	update_size(pos);
}

ll count(ptreap pos, ll val){
	if(!pos){
		return 0;
	} else if(val <= pos->val){
		return count(pos->l, val);
	} else {
		return count(pos->r, val) + size(pos->l) + 1;
	}
}

const ll maxn = 500005;
ptreap pos[maxn], neg[maxn];

ptreap init(ll ind, ll val, ll prior){
	pos[ind] = new treap;
	pos[ind]->val = val;
	pos[ind]->prior = prior;
	pos[ind]->size = 1;
	pos[ind]->l = NULL;
	pos[ind]->r = NULL;

	return pos[ind];
}

ll curr = 1;
ll other = maxn - 1;

std::unordered_map<ll, ll> m;

void initialize(ll n, ll m){

}

void update(ll x, ll y1, ll y2){
	ll ind = m[x];

	if(ind == 0){
		m[x] = curr;
		ind = curr;
		curr++;
	}

	insert(pos[ind], init(other, y1, rand()));
	insert(neg[ind], init(other, y2 + 1, rand()));
	other--;
}

ll query(ll x, ll y){
	ll ind = m[x];

	if(ind == 0){
		return 0;
	} else {
		return count(pos[ind], y + 1) - count(neg[ind], y + 1);
	}
}

int main(){
	std::ios::sync_with_stdio(false);

	ll y, x;
	std::cin >> y >> x;

	ll t;

	initialize(y, x);

	while(std::cin >> t){
		if(t == 0){
			ll qx, qy1, qy2;
			std::cin >> qx >> qy1 >> qy2;

			update(qx, qy1, qy2);
		} else {
			ll qx, qy;
			std::cin >> qx >> qy;

			std::cout << query(qx, qy) << '\n';
		}
	}
}

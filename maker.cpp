#include<bits/stdc++.h>

using namespace std;

#define fr(a, b, c) for(int a = b, __ = c; a < __; a++)

typedef pair<int, int> ii;

int adj[1000],deg[1000],ant[100000],n,to[100000],from[100000],mkd[1000],col[1000],z;
void add(int a,int b){
	ant[z]=adj[a];
	to[z]=b;
	from[z]=a;
	adj[a]=z;
	z++;
	swap(a,b);
	ant[z]=adj[a];
	to[z]=b;
	from[z]=a;
	adj[a]=z;
	z++;
}

void generate(int n, int m) {
	if (m < n - 1) return;
	if (2 * m > n * (n - 1)) return;

	set<ii> s;
	fr (v, 1, n) {
		int u = rand() % v;
		add(u, v);
		s.insert({u, v});
	}

	vector<ii> edges;
	fr (u, 0, n) {
		fr (v, u + 1, n) {
			if (s.count({u, v})) continue;
			edges.push_back({u, v});
		}
	}

	fr(i, 0, m - (n - 1)) {
		int idx = rand() % edges.size();
		swap(edges[idx], edges[edges.size() - 1]);
		add(edges.back().first, edges.back().second);
		edges.pop_back();
	}
}

int best;
bool check(){
	fr(i,0,z)if(!mkd[to[i]]&&!mkd[from[i]])return 0;
	return 1;
}
void go(int v,int cst){
	if(check())best=min(cst,best);
	if(v==n)return;
	if(cst>=best)return;
	int has_free_edge=0;
	for(int i=adj[v];~i;i=ant[i]){
		if(!mkd[to[i]]&&!mkd[from[i]])has_free_edge=1;
	}
	go(v+1,cst);
	mkd[v]=1;
	if(has_free_edge)go(v+1,cst+1);
	mkd[v]=0;
}
int m2aprox(){
	memset(mkd,0,sizeof mkd);
	int ans=0;
	fr(i,0,z){
		if(!mkd[to[i]]&&!mkd[from[i]]){
			mkd[to[i]]=1;
			mkd[from[i]]=1;
			ans+=2;
		}
	}
	best=min(best,ans);
	return ans;
}
int mgreedy(){
	int ans=0,bd=0,bi;
	memset(mkd,0,sizeof mkd);
	memset(deg,0,sizeof deg);
	fr(i,0,n){
		for(int ad=adj[i];~ad;ad=ant[ad])deg[i]++;
	}
	while(true){
		bd=0;
		fr(i,0,n)if(!mkd[i]){
			if(deg[i]>bd){
				bd=deg[i];
				bi=i;
			}
		}
		if(bd){
			mkd[bi]=1;
			ans++;
			for(int ad=adj[i];~ad;ad=ant[ad])deg[to[ad]]--;
		}else break;
	}
	best=min(best,ans);
}
int m2greedy(){
	int ans=0,bd=0,bi;
	memset(mkd,0,sizeof mkd);
	memset(deg,0,sizeof deg);
	fr(i,0,n){
		for(int ad=adj[i];~ad;ad=ant[ad])deg[i]++;
	}
	while(true){
		bd=0;
		fr(i,0,n)if(!mkd[i]){
			if(deg[i]>bd){
				bd=deg[i];
				bi=i;
			}
		}
		if(bd){
			mkd[bi]=1;
			ans++;
			for(int ad=adj[bi];~ad;ad=ant[ad])deg[to[ad]]--;
			int aaa=to[adj[bi]];
			if(!mkd[aaa]){
				mkd[aaa]=1;
				ans++;
				for(int ad=adj[aaa];~ad;ad=ant[ad])deg[to[ad]]--;
			}
		}else break;
	}
	best=min(best,ans);
}
void solve(){
	best=1e9;
	int v2aprox=m2aprox();
	int v2greedy=m2greedy();
	int vgreedy=mgreedy();
	memset(mkd,0,sizeof mkd);
	go(0,0);
}
int main(){
	srand(time(NULL));
}

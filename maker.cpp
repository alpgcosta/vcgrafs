#include<bits/stdc++.h>
#include "json/json.h"
#include "jsoncpp.cpp"
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
	memset(adj,-1,sizeof adj);
	z=0;
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
	int has_free_bef=0;
	for(int i=adj[v];~i;i=ant[i]){
		if(!mkd[to[i]]&&!mkd[from[i]])has_free_edge++;
		if(to[i]<v&&!mkd[to[i]])has_free_bef=1;
	}
	if(!has_free_bef&&cst+has_free_edge<best)
		go(v+1,cst);
	mkd[v]=1;
	if(has_free_edge)go(v+1,cst+1);
	mkd[v]=0;
}
/*int ord[1000];
int bak[1000];
int best2;
void go2(int id,int cst){
	if(check())best2=min(cst,best2);
	if(id==n)return;
	if(cst>=best2)return;
	int has_free_edge=0;
	int has_free_bef=0;
	int v = ord[id];
	for(int i=adj[v];~i;i=ant[i]){
		if(!mkd[to[i]]&&!mkd[from[i]])has_free_edge++;
		if(bak[to[i]] < id && !mkd[to[i]])has_free_bef=1;
	}
	if(!has_free_bef&&cst+has_free_edge<best2)
		go2(id+1,cst);
	mkd[v]=1;
	if(has_free_edge)go2(id+1,cst+1);
	mkd[v]=0;
}*/
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
			for(int ad=adj[bi];~ad;ad=ant[ad])deg[to[ad]]--;
		}else break;
	}
	best=min(best,ans);
	return ans;
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
	return ans;
}
int v2aprox,vgreedy,v2greedy;
void jsonme(string namey){
	ofstream file(namey);
	Json::Value json;
	Json::Value graphs;
	Json::Value entry;
	entry["nodes"]=n;
	entry["edges"]=z/2;
	entry["none"]=best;
	entry["2aprox"]=v2aprox;
	entry["greedy"]=vgreedy;
	entry["2greedy"]=v2greedy;
	Json::Value graph;
	graph["n"]=n;
	Json::Value edges;
	fr(i,0,z/2){
		Json::Value edge;
		edge.append(to[i<<1]);
		edge.append(from[i<<1]);
		edges.append(edge);
	}
	graph["edges"]=edges;
	entry["graph"]=graph;
	
	graphs.append(entry);
	json["graphs"] = graphs;
	file<<json;
}
/*
bool compDeg(int u, int v) {
  return deg[u] < deg[v];
}*/

void solve(){
	best=1e9;
	v2aprox=m2aprox();
	// cerr<<"2aprox"<<endl;
	vgreedy=mgreedy();
	// cerr<<"greedy"<<endl;
	v2greedy=m2greedy();
	// cerr<<"2greedy"<<endl;
	// memset(mkd,0,sizeof mkd);
	// go(0, 0);
	//sort(ord, ord + n, compDeg);
/*	fr(i, 0, n) {
		bak[ord[i]] = i;
	}*/
	memset(mkd,0,sizeof mkd);
	go(0, 0);
}
int main(){
	string namey;
	string cmdd;
	srand(time(NULL));
	fr(i,7,201){
		cerr<<i<<endl;
		fr(j,1,6){
			cerr<<" - "<<j<<endl;
			fr(k, 0, 1) {
				int m;
				n=i;
				if(j==1)m=n-1;
				if(j==2)m=n*2;
				if(j==3)m=n*3;
				if(j==4)m=n*n/5;
				if(j==5)m=n*n/4;
				namey="json"+to_string(i)+"-"+to_string(j)+"-"+to_string(k)+".json";
				generate(n,m);
				solve();
				jsonme(namey);
				cmdd="curl -X POST -d @"+namey+" -H \"Content-Type: application/json\" 162.243.157.230:5000/graph";
				system(cmdd.c_str());
			}
		}
	}
}

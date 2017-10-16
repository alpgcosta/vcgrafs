#include<bits/stdc++.h>
#include "json/json.h"
#include "jsoncpp.cpp"
#define fr(a,b,c) for(int a=b;a<c;a++)
using namespace std;
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
			for(int ad=adj[bi];~ad;ad=ant[ad])deg[to[ad]]--;
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
int v2aprox,vgreedy,v2greedy;
void jsonme(){
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
		edge.append(to[i]);
		edge.append(from[i]);
		edges.append(edge);
	}
	graph["edges"]=edges;
	entry["graph"];
	
	graphs.append(entry);
	json["graphs"] = graphs;
	cout<<json;
}
void solve(){
	best=1e9;
	v2aprox=m2aprox();
	v2greedy=m2greedy();
	vgreedy=mgreedy();
	memset(mkd,0,sizeof mkd);
	go(0,0);
}
int main(){
	jsonme();
}

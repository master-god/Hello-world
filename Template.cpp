#pragma optimise GCC(-O2)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<ll,ll>
#define ve(x) vector<x>
#define f(a,b,c) for(int a=b;a<c;a++)
#define foto(x,v) for(auto x:v)
#define read(t) ll t; cin>>t;
#define reads(t) string t; cin>>t;
#define readarr(arr,n) ll arr[n]; f(i,0,n) cin>>arr[i];
#define forstl(i,v) for(auto &i: v)
#define ln endl
#define Endl endl
#define dbg(x) cout<<#x<<" = "<<x<<ln;
#define dbg2(x,y) cout<<#x<<" = "<<x<<" & "<<#y<<" = "<<y<<ln;
#define dbgstl(v) cout<<#v<<" = \n"; { int c=0; forstl(it,v) \
cout<<"    Term "<< ++c <<" = "<<it<<ln;} cout<<ln;
#define dbgstlp(v) cout<<#v<<" = \n"; { int c=0; forstl(it,v) \
cout<<"    Term "<< ++c <<" = "<<it.fi<<" , "<<it.se<<ln;} cout<<ln;
#define dbgarr(v,s,e) cout<<#v<<" = "; f(i,s,e) cout<<v[i]<<", "; cout<<ln;
#define addEdge(tr,k) f(i,0,k) { ll x,y; cin>>x>>y, tr[x].push_back(y), tr[y].push_back(x);}
#define all(v) v.begin(),v.end()

mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) { uniform_int_distribution<int> uid(0, lim - 1); return uid(rang); }

//														GLOBAL VARS
ll INF =LLONG_MAX;
const ll M= 1000000007;

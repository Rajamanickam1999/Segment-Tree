#include"bits/stdc++.h"
#define ll long long int
using namespace std;
const int N  = 1e6+10;
ll a[N];
ll s[4*N];
ll lazy[4*N];
void build(ll l,ll r,ll p){
    if(l==r) {
        s[p]=a[l];
        return;
    }
    ll m=(l+r)/2;
    build(l,m,2*p+1);
    build(m+1,r,2*p+2);
    s[p]=s[2*p+1]+s[2*p+2];
}
void update(ll l,ll r,ll i,ll j,ll p,ll v) {
    if(lazy[p]!=0){
        s[p]+=(r-l+1)*lazy[p];
        if(l!=r){
            lazy[2*p+1]+=lazy[p];
            lazy[2*p+2]+=lazy[p];
        }
        lazy[p]=0;
    }
    if(l>r || r<i || l>j) return;
    if(l>=i&&r<=j) {
        s[p]+=(r-l+1)*v;
        if(l!=r){
            lazy[2*p+1]+=v;
            lazy[2*p+2]+=v;
        }
        return;
    }
    ll m=(l+r)/2;
    update(l,m,i,j,2*p+1,v);
    update(m+1,r,i,j,2*p+2,v);
    s[p]=s[2*p+1]+s[2*p+2];
}
ll query(ll l,ll r ,ll i,ll j,ll p) {
         if(lazy[p]!=0){
        s[p]+=(r-l+1)*lazy[p];
        if(l!=r){
            lazy[2*p+1]+=lazy[p];
            lazy[2*p+2]+=lazy[p];
        }
        lazy[p]=0;
    }
    if(l>r || r<i || l>j) return 0;
    if(l>=i&&r<=j) {
       return s[p];
    }
    ll m=(l+r)/2;
    ll ans1=query(l,m,i,j,2*p+1);
    ll ans2=query(m+1,r,i,j,2*p+2);
    return ans1+ans2;
}
int main()
{
    ll t,n,c;
    cin>>t;
    ll x,y,z,v;
    while(t--) {
        cin>>n>>c;
        memset(a,0,sizeof(a));
        memset(lazy,0,sizeof(lazy));
        memset(s,0,sizeof(s));
        while(c--) {
        cin>>x;
        if(x==0) {
            cin>>y>>z>>v;
            update(0,n-1,y,z,0,v);
        }
        else {
            cin>>y>>z;
            cout<<query(0,n-1,y,z,0)<<endl;
        }
        }      
    }
}
#include"bits/stdc++.h"
#define ll long long int
using namespace std;
const int N  = 1e6+10;
ll a[N];            //The array you are going to get the numbers or initialise to 0
ll s[4*N];          //segment tree
ll lazy[4*N];       //lazy tree
/*Function to build the segment tree and l=left and r=right*/

void build(ll l,ll r,ll p)
{ 
    // If it is a leaf node then insert into the segment tree --- > this is the base condition
    if(l==r) 
    {              
        s[p]=a[l];
        return;         // important since if it is not given then function continues leading to segmentation fault 
    }
    ll m=(l+r)/2;       
    build(l,m,2*p+1);   // building the left segment tree
    build(m+1,r,2*p+2); // building the right segment tree
    
    /*since this is sum on a range question addition 
      this can also modfied depending on the question like min and max*/
    
    s[p]=s[2*p+1]+s[2*p+2]; 
}
/*Function to update the segment tree in a given range */

void update(ll l,ll r,ll i,ll j,ll p,ll v) {// left ,right,i-->starting range to be updated ,j-->ending range to be updated ,v-->value
    
    /*The following if condition is because if there are any pending updates then it must be updated */
  
    if(lazy[p]!=0)
    {
        s[p]+=(r-l+1)*lazy[p];
        if(l!=r)
        {
            lazy[2*p+1]+=lazy[p];
            lazy[2*p+2]+=lazy[p];
        }
        lazy[p]=0;
    }
    // checking of conditions must be done only after the pending updates are done  ! *** very important ***
    // checking of conditions ---> partial or complete or no match 
    
    if(l>r || r<i || l>j) return;  // no match 
    
    /*Complete overlap*/
    
    if(l>=i&&r<=j)
    {
        s[p]+=(r-l+1)*v;        // this is updating the segment tree the "(r-l+1)" part is for counting the number of elements 
        if(l!=r)                //If it is not a child node then update the value in its children in lazy tree
        {   
            lazy[2*p+1]+=v; // left
            lazy[2*p+2]+=v;// right
        }
        return;                 // return after the job is done else leads to segmentation fault 
    }
    ll m=(l+r)/2;
    update(l,m,i,j,2*p+1,v);
    update(m+1,r,i,j,2*p+2,v);
    s[p]=s[2*p+1]+s[2*p+2];
}
ll query(ll l,ll r ,ll i,ll j,ll p) // querying range i to j inclusive
{
    // checking for pending updates if any update same as the above update one !
    if(lazy[p]!=0)
    {
      s[p]+=(r-l+1)*lazy[p];
      if(l!=r)
      {
            lazy[2*p+1]+=lazy[p];
            lazy[2*p+2]+=lazy[p];
        }
        lazy[p]=0;
    }
    //Checking for total,partial and no-overlap conditions 
    
    if(l>r || r<i || l>j) return 0;// no overlap
    if(l>=i&&r<=j)                 // complete overlap
    {
       return s[p];
    }
    ll m=(l+r)/2;
    ll ans1=query(l,m,i,j,2*p+1);
    ll ans2=query(m+1,r,i,j,2*p+2);
    return ans1+ans2;           // return the answer
}
int main()
{
    ll t,n,c;
    cin>>t;                 // number of testcases
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

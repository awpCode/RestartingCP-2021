#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define int long long
#define mkp make_pair
#define pb push_back
#define ff first
#define ss second
#define debug1(a) cout<<a<<endl;
#define debug2(a,b) cout<<a<<' '<<b<<endl;
#define debug3(a,b,c) cout<<a<' '<<b<<' '<<c<<endl;
#define rep(i,n) for(int i=0;i<n;i++)
#define repre(i,a,b)for(int i=a;i<=b;i++)
#define clr1(arr) memset(arr,-1,sizeof(arr));
#define clr0(arr) memset(arr,0,sizeof(arr));
#define pi pair<int,int>
#define pii pair<int,pi>
#define aint(v) v.begin(),v.end()
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
using namespace __gnu_pbds;
using namespace std;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> orderedSet;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> orderedMSet;
struct custom_hash {
static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#define ump gp_hash_table<int,int,custom_hash>
//*p.find_by_order(index) return value at index
//p.order_of_key(key) return index
/*int **dp,in main function,int row,col;dp=new int*[n];rep(i,n)dp[i]=new int[m]*/
//**** Maths Section*******/
int power(int x,int y);
bool isPrime(int n);
int modInv(int a,int b);
int gcdExtended(int a,int b,int *x,int* y);
int mpower(int a,int b,int p);
/***************************/
int32_t main()
{
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);
  fastio
  int t;
  cin>>t;
  while(t--)
  {
    int n;
    cin>>n;
    int h[n],w[n];
    rep(i,n)cin>>h[i]>>w[i];
    vector<pii >hs;
    vector<pii >ws;
    rep(i,n){
      hs.pb({h[i],{w[i],i}});
    }
    sort(hs.begin(),hs.end());
    pi prefhs[n];
    prefhs[0] = {hs[0].ss.ff,hs[0].ss.ss};
    repre(i,1,n-1)
    {
      if(hs[i].ss.ff < prefhs[i-1].ff)
      {
        prefhs[i] = {hs[i].ss.ff,hs[i].ss.ss};
      }
      else prefhs[i] = prefhs[i-1];
    }
    int ans[n];
    clr1(ans);
    rep(i,n)
    {
      int low = 0;
      int high = n-1;
      int ele = h[i];
      while(low <= high)
      {
        int mid = (low+high)/2;
        if(ele <= hs[mid].ff)
          high = mid - 1;
        else low = mid + 1;
      }
      low--;
      if(low<0 || prefhs[low].ff >= w[i])
      {
          low = 0;
          high = n-1;
          ele = w[i];
          while(low <= high)
          {
            int mid = (low+high)/2;
            if(ele <= hs[mid].ff)
              high = mid - 1;
            else low = mid + 1;
          }
          low--;
          if(low<0)continue;
          else //alternate orientation
          {
            if(prefhs[low].ss!=i && prefhs[low].ff < h[i])
              ans[i] = prefhs[low].ss + 1;
          }
      }
      else if(low>=0 && prefhs[low].ff < w[i]) //same orientation
      {
        ans[i] = prefhs[low].ss + 1;
      }
    }
    rep(i,n)cout<<ans[i]<<" ";
    cout<<'\n';
  }

  return 0;
}

int modInv(int a, int m)
{
int x, y;
int g = gcdExtended(a, m, &x, &y);
int res = (x%m + m) % m;
return res;
}

int gcdExtended(int a, int b, int *x, int *y)
{
if (a == 0){
    *x = 0, *y = 1;
    return b;
  }
  int x1, y1;
  int gcd = gcdExtended(b%a, a, &x1, &y1);
  *x = y1 - (b/a) * x1;
  *y = x1;
  return gcd;
}

int mpower(int x, int y, int p)
{
int res = 1;
x = x % p;
while(y > 0){
    if(y & 1) res = (res*x) % p;
      y = y>>1;
      x = (x*x) % p;
    }
    return res;
}
int power(int x, int y)
{
int res = 1;
while (y > 0){
    if (y & 1) res = res*x;
      y = y>>1;
      x = x*x;
    }
    return res;
}

bool isPrime(int n)
{
if (n <= 1)  return false;
  if (n <= 3)  return true;
    if (n%2 == 0 || n%3 == 0) return false;
      int p=sqrt(n);
      for(int i=5;i<=p;i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
          return false;
      return true;
}

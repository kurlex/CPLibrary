#include <bits/stdc++.h>
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double db;
//typedef double db;
#define int ll
#define ss second
#define ff first
#define pb push_back
#define vi vector<int>
#define pii pair<int,int>
#define vii vector<pii>
#define vl vector<ll>
#define pll pair<ll,ll>
#define vll vector<pll>
#define vd vector<db>
#define pdd  pair<db,db>
#define vdd  vector<pdd>
#define mll map <ll,ll>
#define sl set <ll>
#define sll set <pll>
#define f(i,j,k,l) for(ll i=j;i<k;i+=l)
#define fj(j,m) for(auto j=m.begin();j!=m.end();j++)
#define yes cout<<"Yes"<<endl;
#define no cout<<"No"<<endl;
#define endl "\n"

ll add(ll a, ll b){
    return (a + b) % mod;
}
ll sub(ll a, ll b){
    return (a - b + mod) % mod;
}
ll mul(ll a, ll b){
    return (((ll)a%mod) * ((ll)b%mod)) % mod;
}
ll bin_pow(ll n, ll k){
    if(k == 0)return 1;
    if(k == 1)return n;
    if(k % 2 == 1) return mul(n, bin_pow(n, k - 1));
    ll t = bin_pow(n, k / 2);
    return mul(t, t);
}
const int MAXN = 5001;
int fact[MAXN];
int inv_fact[MAXN];
ll rev(int x){
    return bin_pow(x, mod - 2);
}
int C(int n, int k){
    //C(n, k) = n! / ((n - k)! * k!)
    if(n < k || k < 0)return 0;
    return mul(fact[n], mul(inv_fact[k], inv_fact[n - k]));
}
ll power(ll x , ll y)
{
    return bin_pow(x,y)%mod;
}
ll mod_inv (ll a)
{
    return power(a,mod-2);
}
void preprocess(){
    fact[0] = 1;
    for(int i = 1;i < MAXN;i++){
        fact[i] = mul(i, fact[i - 1]);
    }
    inv_fact[MAXN - 1] = rev(fact[MAXN - 1]);
    for(int i = MAXN - 2;i >= 0;i--){
        inv_fact[i] = mul(inv_fact[i + 1], i + 1ll);
    }
}

int main() {
}
// problem find the sum of squares of all paths in a tree (updated version of sum of all paths in a tree)
// in each node sum of distanses starting from that node , sum of square of distances from that node and apply math 

#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less
#include <iostream>
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    oset;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define fo(i, s, e) for (int i = s; i < e; i++)
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
#define ld long double
#define ff first
#define ss second
#define in insert
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define yes cout << "YES\n"
#define no cout << "NO\n"
using vi = vector<int>;
using vl = vector<ll>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
ll mod = 1e9 + 7;
#define add(a, b) (((a % mod) + (b % mod)) % mod)
#define mul(a, b) (((a % mod) * (b % mod)) % mod)
#define sub(a, b) (((a % mod) - (b % mod) + mod) % mod)

vi subtreeSize , sumOfPathNodeStart ,sumOfPathSquareNodeStart, sumOfAllPaths,sumOfAllPathsSquare;
void dfs(int node,int par,vvi&adj){
    subtreeSize[node] = 1 ;
    for(auto child : adj[node]){
        if(child==par)continue;
        dfs(child,node,adj) ;
        subtreeSize[node] += subtreeSize[child] ;
    }

    //individual sum of square (x^2) for each node will be stored in sumOfPathSquareNodeStart
    //calculate sum(X^2) --> sum((x+1)^2)
    int sumOfAllXsquare = 0 ;
    map<int,int>Xsquare ; 
    for(auto child : adj[node]){
        if(child==par)continue;
        int Xsquare_val = sumOfPathSquareNodeStart[child]+2*sumOfPathNodeStart[child] + subtreeSize[child];
        Xsquare[child] = Xsquare_val ;
        sumOfAllXsquare += Xsquare_val ; 
        cout<<"child "<<child<<" Xsquare_val "<<Xsquare_val<<"\n";
        int sumOfPathNodeStartForEachSubtree = sumOfPathNodeStart[child]+subtreeSize[child] ; 
        sumOfPathNodeStart[node] += sumOfPathNodeStartForEachSubtree;
    }

    cout<<"node "<<node<<"\n";
    cout<<"subtreeSize[node] "<<subtreeSize[node]<<"\n" ;
    cout<<"sumOfPathNodeStart[node] "<<sumOfPathNodeStart[node]<<"\n";

    sumOfPathSquareNodeStart[node] = sumOfAllXsquare ;
    sumOfAllPathsSquare[node] = 0 ;

    cout<<"sumOfPathSquareNodeStart[node] "<<sumOfPathSquareNodeStart[node]<<"\n";

    for(auto child : adj[node]){
        if(child==par)continue;
        int rem_nodes = subtreeSize[node]-subtreeSize[child]-1 ;
        int Ysquare = sumOfAllXsquare - Xsquare[child] ;
        int Xsum = sumOfPathNodeStart[child]+subtreeSize[child] ;
        int Ysum = sumOfPathNodeStart[node] - Xsum ;
        int XplusYsquareSum = Xsquare[child]*rem_nodes + Ysquare*subtreeSize[child]
             + 2*Xsum*Ysum; 
        sumOfAllPathsSquare[node] += XplusYsquareSum ;
    }
    sumOfAllPathsSquare[node] /= 2 ;
    sumOfAllPathsSquare[node] += sumOfPathSquareNodeStart[node] ;
    cout<<"sumOfAllPathsSquare[node] "<<sumOfAllPathsSquare[node]<<"\n\n";
    // int sumOfPathSquareChild = 0 ;
    // for(auto child:adj[node]){
    //     if(child==par)continue;
    //     int sumOfPathNodeStartForEachSubtree = sumOfPathNodeStart[child]+subtreeSize[child] ; 
    //     sumOfPathNodeStart[node] += sumOfPathNodeStartForEachSubtree;
        
    //     int sumOfPathSquareNodeStartForEachSubtreeSingleContri = sumOfPathSquareNodeStart[child]+2*sumOfPathNodeStart[child]+subtreeSize[child] ; 
    //     sumOfPathSquareNodeStart[node] += sumOfPathSquareNodeStartForEachSubtreeSingleContri;
    //     sumOfPathSquareChild += sumOfPathSquareNodeStart[child] ;
    //     // sumOfAllPaths[node] += sumOfPathNodeStartForEachSubtree*(subtreeSize[node]-subtreeSize[child]) ;
    // }
    // cout<<"node "<<node<<"\n";
    // cout<<"subtreeSize[node] "<<subtreeSize[node]<<"\n";
    // for(auto child:adj[node]){
    //     if(child==par)continue;
    //     int sumOfPathNodeStartForEachSubtree = sumOfPathNodeStart[child]+subtreeSize[child] ; 
    //     int sumOfPathSquareNodeStartForEachSubtreeSingleContri = sumOfPathSquareNodeStart[child]+2*sumOfPathNodeStart[child]+subtreeSize[child] ;
    //     cout<<"child "<<child<<" sumOfPathSquareNodeStartForEachSubtreeSingleContri "<<sumOfPathSquareNodeStartForEachSubtreeSingleContri<<"\n";
    //     int sumOfPathSquareNodeStartForEachSubtreeCombineContri = sumOfPathSquareNodeStartForEachSubtreeSingleContri*(subtreeSize[node]-subtreeSize[child]) + 
    //     subtreeSize[child]*(sumOfPathSquareChild-sumOfPathSquareNodeStart[child])+2*sumOfPathNodeStartForEachSubtree*(sumOfPathNodeStart[node]-sumOfPathNodeStartForEachSubtree); 
    //     sumOfAllPathsSquare[node] += sumOfPathSquareNodeStartForEachSubtreeCombineContri ;
    //     cout<<"sumOfPathSquareNodeStartForEachSubtreeCombineContri "<<sumOfPathSquareNodeStartForEachSubtreeCombineContri<<"\n\n";
    // }

    // cout<<"sumOfPathNodeStart[node] "<<sumOfPathNodeStart[node]<<"\n" ;
    // cout<<"sumOfPathSquareNodeStart[node] "<<sumOfPathSquareNodeStart[node]<<"\n" ;
    // cout<<"sumOfAllPathsSquare[node] "<<sumOfAllPathsSquare[node]<<"\n\n" ;
    // cout<<"sumOfAllPaths[node] "<<sumOfAllPaths[node]<<"\n";

    
}
void solve()
{
    int n ;
    cin>>n ;
    subtreeSize.assign(n+1,0) ;
    sumOfPathNodeStart.assign(n+1,0) ;
    sumOfPathSquareNodeStart.assign(n+1,0) ;
    sumOfAllPaths.assign(n+1,0) ;
    sumOfAllPathsSquare.assign(n+1,0) ;
    vvi adj(n+1) ;

    fo(i,0,n-1){
        int a,b ;
        cin>>a>>b ;
        adj[a].pb(b) ;
        adj[b].pb(a) ;
    }
    dfs(1,-1,adj) ;
}

int main()
{
    FASTIO;
    int tt = 1;
    // cin >> tt;
    while (tt--)
    {
        solve();
    }
    return 0;
};

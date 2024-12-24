/*
  没有上司的舞会：当某个职工的直接上属参加舞会时，该职工不能参加；

  思路：状态定义 dp[node][0]：表示当前节点不参加的最大人数，dp[node][1]表示当前节点参加的最大人数
  	状态转移：dp[cur][0] = sum(dp[son][0], dp[son][1]), dp[cur][1] = sum(dp[son][0])
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 6005
int h[MAXN];
int v[MAXN];
vector<int> son[MAXN];
int f[MAXN][2];
void dp(int x)
{
 f[x][0]=0;
 f[x][1]=h[x];
 for(int i=0;i<son[x].size();i++)
 {
  int y=son[x][i];
  dp(y);
  f[x][0]+=max(f[y][0],f[y][1]);
  f[x][1]+=f[y][0];
 }
}
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n;i++) cin>>h[i];
 for(int i=1;i<=n-1;i++)
 {
  int x,y;
  cin>>x>>y;
  son[y].push_back(x);
  v[x]=1;
 }
 int root;
 for(int i=1;i<=n;i++)
 if(!v[i]) {root=i;break;}
 dp(root);
 cout<<max(f[root][0],f[root][1])<<endl;
 return 0;
}

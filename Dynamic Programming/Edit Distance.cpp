#include<bits/stdc++.h>


using namespace std;

int EditDistance(string &a,string &b){
    int n=a.size(),m=b.size();
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++){
            if(i==0){
                dp[i][j]=j;
                continue;
            }
            if(j==0){
                dp[i][j]=i;
                continue;
            }
            if(a[i-1]==b[j-1])
                dp[i][j]=dp[i-1][j-1];
            else
                dp[i][j]=min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]})+1;
        }
        return dp[n][m];
}
int main(){
    int T;
    cin >> T;
    while(T--){
        string a,b;
        cin >> a >> b;
        cout << EditDistance(a,b) << endl;;
    }
}

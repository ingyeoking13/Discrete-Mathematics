#include<vector>
using namespace std;

int ans=0;
int min(int a, int b){
    if (a>b) return b;
    return a;
}

int solution(vector<vector<int>> b){
    
    for (int i=0; i<b.size(); i++){
        for (int j=0; j<b[0].size();j++){
            if (i==0 || j==0){
                if(b[i][j]) ans=ans>1?ans:1;
            }
            else{
                if(b[i][j]){
                    b[i][j]=min(min(b[i-1][j],b[i][j-1]),b[i-1][j-1])+1;
                    if(b[i][j]>ans) ans=b[i][j];   
                }
            }
        }
    }
            
    return ans*ans;
}

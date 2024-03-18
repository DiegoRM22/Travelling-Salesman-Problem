#include<iostream>
using namespace std;
#define MAX 9999
int n=4;
int distan[20][20] = {{0, 25, 10, 45},
   {25, 0, 10, 15},
   {10, 10, 0, 5},
   {45, 15, 5, 0}
};
int completed_visit = (1<<n) -1;
int DP[32][8];
int TSP(int mark, int position){
   if(mark==completed_visit) {
      return distan[position][0];
   }
   if(DP[mark][position]!=-1) {
      return DP[mark][position];
   }
   int answer = MAX;
   for(int city=0; city<n; city++) {
      if((mark&(1<<city))==0) {
         int newAnswer = distan[position][city] + TSP( mark|(1<<city),city);
         answer = min(answer, newAnswer);
      }
   }
   return DP[mark][position] = answer;
}
int main(){
   for(int i=0; i<(1<<n); i++) {
      for(int j=0; j<n; j++) {
         DP[i][j] = -1;
      }
   }
   cout << "Minimum Distance Travelled -> " << TSP(1,0) << endl;
   return 0;
}
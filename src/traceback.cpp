#include <bits/stdc++.h>
#include "traceback.h"

using namespace std;

using ll = long long;



string trace_back(vector<vector<double>> dp, string seq, int N){
  stack<pair<int, int>> st;
  string ans(N, '.');
  st.push(make_pair(1,N));

  for(; !st.empty();){
    pair<int, int> buf = st.top();
    st.pop();
    int i = buf.first, j = buf.second;

    if(i>=j){

    }else if(dp.at(i).at(j-1) == dp.at(i).at(j)){
      st.push(make_pair(i, j-1));
    }else{
      for(int k=1; k<j; k++){
        if(match(seq.at(k-1), seq.at(j-1))){
          if(dp.at(i).at(k-1) + dp.at(k+1).at(j-1) +1 == dp.at(i).at(j)){
            ans.at(k-1) = '(';
            ans.at(j-1) = ')';
            st.push(make_pair(i, k-1));
            st.push(make_pair(k+1, j-1));
            break;
          }
        }
      }
    }
  }
  return ans;
}



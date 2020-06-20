#include <bits/stdc++.h>
#include "zuker.h"

string find_pair(string rna, int i, int j){
  rna.at(i-1) = '(';
  rna.at(j-1) = ')';
  return rna;
}


string Zuker::W_traceback(){
  stack<pair<int, int>> st;
  rna_2d = string(N, '.');
  st.push(make_pair(1,N));

  for(; !st.empty();){
    pair<int, int> buf = st.top();
    st.pop();
    int i = buf.first, j = buf.second;

    if(i>=j){

    }else if(W.at(i).at(j-1) == W.at(i).at(j)){
      st.push(make_pair(i, j-1));
    }else{
      for(int k=i;k<j;k++){
        if(is_match(k, j)){
          if(W.at(i).at(j) == W.at(i).at(k-1) + V.at(k).at(j)){
            rna_2d = find_pair(rna_2d, k, j);
            /* rna_2d.at(k) = '('; */
            /* rna_2d.at(j) = ')'; */
            st.push(make_pair(i, k-1));
            V_traceback(k, j);
            break;
          }
        }
      }
    }
  }
  return rna_2d;
}

int Zuker::V_traceback(int i, int j){
  cout << "V_traceback" << i << " " << j << endl;
  if(V.at(i).at(j) == eH(i, j)){
    cout << i << " " << j << " eH" << endl;
    return 0;
  }else if(V.at(i).at(j) == V.at(i+1).at(j-1) + eS(i, j, i+1, j-1)){
    cout << i << " " << j << " eS" << endl;
    rna_2d = find_pair(rna_2d, i+1, j-1);
    /* rna_2d.at(i+1) = '('; */
    /* rna_2d.at(j-1) = ')'; */
    V_traceback(i+1, j-1);
    return 0;
  }else{
    for(int ii=i+1; ii<j;ii++){
      for(int jj=ii+1; jj<j;jj++){
        if(is_match(ii, jj)){
          if(V.at(i).at(j) == V.at(ii).at(jj)+eL(i, j, ii, jj)){
            cout << i << " " << j << " " << ii << " " << jj<< " eL" << endl;
            rna_2d = find_pair(rna_2d, ii, jj);
            /* rna_2d.at(ii) = '('; */
            /* rna_2d.at(jj) = ')'; */
            V_traceback(ii, jj);
            return 0;
          }
        }
      }
    }
    //calc multi
    double multi = INF;
    for(int k=i+1; k<j; k++){
      if(V.at(i).at(j) ==  calc_VM(i+1, k) + calc_VM(k+1, j-1) + multi_a){
        cout << "oh multi loop" <<endl;
        //TODO multi loopのときのトレースバックを実装する
        VM_traceback(i+1, k);
        VM_traceback(k+1, j-1);
        return 0;
      }
    }
  }
  cout << "error traceback" << endl;
  return 1;
}

int Zuker::VM_traceback(int i, int j){
  cout << "VM_traceback" << i << " " << j << endl;
  if(j-i <= M){
    return 0;
    return INF;
  }else if(i<1 | i>N | j<1| j>N){
    cout << "traceback_VM_error" << endl;
    return 1;
  }else{
    double multi_seg = INF;
    if(VM.at(i).at(j) == VM.at(i).at(j-1) + multi_c){
      VM_traceback(i, j-1);
      return 0;
    }else if(VM.at(i).at(j) == VM.at(i+1).at(j) + multi_c){
      VM_traceback(i+1, j);
      return 0;
    }else if(VM.at(i).at(j) == V.at(i).at(j) + multi_b){
      rna_2d = find_pair(rna_2d, i, j);
      /* V_traceback(i, j); */
      // loopしてしまう？　ここについては調べる必要がない？
      return 0;
    }else{
      double non_closed = INF;
      for(int k=i+1; k<j; k++){
        if(VM.at(i).at(j) == calc_VM(i, k) + calc_VM(k+1, j)){
          VM_traceback(i, k);
          VM_traceback(k+1, j);
          return 0;
          break;
        }
      }
    }
  }
  return 1;
}

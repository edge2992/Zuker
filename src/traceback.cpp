#include "zuker.h"

string find_pair(string rna, int i, int j){
  rna.at(i-1) = '(';
  rna.at(j-1) = ')';
  return rna;
}


string Zuker::W_traceback(){
  spdlog::info("traceback");
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
        if(seq.is_WCpair(k, j)){
          if(W.at(i).at(j) == W.at(i).at(k-1) + V.at(k).at(j)){
            rna_2d = find_pair(rna_2d, k, j);
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
  if(V.at(i).at(j) == eH(i, j)){
    //hairpin loop
    return 0;
  }else if(V.at(i).at(j) == V.at(i+1).at(j-1) + eS(i, j, i+1, j-1)){
    //stacking
    rna_2d = find_pair(rna_2d, i+1, j-1);
    V_traceback(i+1, j-1);
    return 0;
  }else{
    //internal or buldge loop?
    for(int ii=i+1; ii<j;ii++){
      for(int jj=ii+1; jj<j;jj++){
        if(seq.is_GCpair(ii, jj)){
          if(V.at(i).at(j) == V.at(ii).at(jj)+eL(i, j, ii, jj)){
            rna_2d = find_pair(rna_2d, ii, jj);
            V_traceback(ii, jj);
            return 0;
          }
        }
      }
    }
    //multi loop?
    double multi = INF;
    for(int k=i+1; k<j; k++){
      if(V.at(i).at(j) ==  calc_VM(i+1, k) + calc_VM(k+1, j-1) + multi_a){
        spdlog::info("oh this is multi loop");
        VM_traceback(i+1, k);
        VM_traceback(k+1, j-1);
        return 0;
      }
    }
  }
  spdlog::error("V_traceback was something wrong!!");
  return 1;
}

int Zuker::VM_traceback(int i, int j){
  spdlog::info("VM_traceback");
  if(j-i <= M){
    return 0;
  }else if(i<1 | i>N | j<1| j>N){
    spdlog::error("VM_traceback was something wrong. sequence out of range error");
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
  spdlog::error("VM_traceback was something wrong.");
  return 1;
}

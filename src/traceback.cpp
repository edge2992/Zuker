#include "zuker.h"

string find_pair(string rna, int i, int j){
  rna.at(i-1) = '(';
  rna.at(j-1) = ')';
  return rna;
}

bool Zuker::F_traceback(){
  spdlog::info("traceback");
  stack<int> st;
  st.push(N);

  for(; !st.empty();){
    int j = st.top();
    st.pop();
    /* spdlog::info(j); */
    if(j<1){
      spdlog::info("traceback fin");
      break;
    }

    if(F.at(j) == F.at(j-1)){
      //不安　V.at(i).at(j) = 0の場合
      st.push(j-1);
    }else{
      int counter = 0;
      for(int i=1;i<j;i++){
        if(seq.is_WCpair(i, j)){
          if(F.at(j) == F.at(i-1) + V.at(i).at(j)){
            counter += 1;
            if(V_traceback(i, j)){
              rna_2d = find_pair(rna_2d, i, j);
              st.push(i-1);
            }else{
              spdlog::error("F_traceback (1)");
            }
          }
        }
      }
      //error check
      if(counter!=1){
        spdlog::error("F error {0}", counter);
      }
    }
  }
  return true;
}


bool Zuker::V_traceback(int i, int j){
  if(!seq.is_WCpair(i, j)){
    spdlog::error("V_traceback error {0} {1} is not pair", i, j);
    return false;
  }

  if(V.at(i).at(j) == eH(i, j)){
    //hairpin loop
    return true;
  }else if(seq.is_WCpair(i+1, j-1) and V.at(i).at(j) == V.at(i+1).at(j-1) + eS(i, j, i+1, j-1) and V_traceback(i+1, j-1)){
    //stacking
    //TODO ここでエラーしてる
    rna_2d = find_pair(rna_2d, i+1, j-1);
    return true;
  }else if(V.at(i).at(j) == VBI.at(i).at(j)){
    //internal and buldge loop
    return VBI_traceback(i, j);
  }else{
    for(int k=i+1; k<j-1; k++){
      if(V.at(i).at(j) == W.at(i+1).at(k) + W.at(k+1).at(j-1) + multi_a){
        return W_traceback(i+1, k) and W_traceback(k+1, j-1);
      }
    }
  }
  spdlog::error("V_traceback error");
  return false;
}


bool Zuker::W_traceback(int i, int j){
  spdlog::info("W_traceback");
  double multi_seg = INF;
  if(W.at(i).at(j) == W.at(i).at(j-1) + multi_c){
    if(W_traceback(i, j-1)){
        return true;
    }else{
      spdlog::error("W error 1");
    }
    /* return W_traceback(i, j-1); */
  }else if(W.at(i).at(j) == W.at(i+1).at(j) + multi_c){
    if(W_traceback(i+1, j)){
      return true;
    }else{
      spdlog::error("W error 2");
    }
  }else if(seq.is_WCpair(i, j) and W.at(i).at(j) == V.at(i).at(j) + multi_b){
    if(V_traceback(i, j)){
      rna_2d = find_pair(rna_2d, i, j);
      return true;
    }else{
      spdlog::error("W error 3");
    }
  }else{
    for(int k=i+1; k<j; k++){
      if(W.at(i).at(j) == W.at(i).at(k) + W.at(k+1).at(j)){
        if(W_traceback(i, k) and W_traceback(k+1, j)){
            return true;
        }else{
          spdlog::error("W error 4"); 
        }
      }
    }
  }
  spdlog::error("W_traceback was something wrong.");
  return false;
}


bool Zuker::VBI_traceback(int i, int j){
  //internal or buldge loop?
  /* spdlog::info("VBI_traceback"); */
  for(int ii=i+1; ii<j;ii++){
    for(int jj=ii+1; jj<j;jj++){
      if(seq.is_WCpair(ii, jj)){
        if(V.at(i).at(j) == V.at(ii).at(jj)+eL(i, j, ii, jj)){
          if(V_traceback(ii, jj)){
            rna_2d = find_pair(rna_2d, ii, jj);
            return true;
          }else{
            spdlog::error("vbi error 1");
          }
        }
      }
    }
  }
  spdlog::error("VBI_traceback error");
  return false;
}


#include "zuker.h"

using namespace std;

using ll = long long;


/**
 * @brief constractor
 *
 * @param rna_seq RNA sequence
 */
Zuker::Zuker(string rna_seq)
  : seq(Rna_seq(rna_seq)), N(rna_seq.length())
{
  W = vector<vector<double>>(N+1, vector<double>(N+1, INF));
  V = vector<vector<double>>(N+1, vector<double>(N+1, INF));
  VBI = vector<vector<double>>(N+1, vector<double>(N+1, INF));
  F = vecetor<double>(N+1, INF);
  VM_iscalced = vector<vector<bool>>(N+1, vector<bool>(N+1, false));
  for(int k=0; k<N; k++){
    for(int i= 1; i<=N; i++){
      //対角線上に左上から右下に計算
      int j = i+k;
      calc_VBI(i, j);
      calc_V(i, j);
      calc_W(i, j);
    }
  }
  for(int j = 1; j<=N; j++){
    //1-jまでの断片行列の自由エネルギーを計算する
    calc_F(j);
  }
}


Zuker::~Zuker(){
  spdlog::info("deconstract zuker");
}

double Zuker::calc_VBI(int i, int j){
  //内部ループとバルジループを計算する
  double internal = INF;
  for(int ii=i+1; ii<j;ii++){
    for(int jj=ii+1; jj<j;jj++){
      if(ii - i + j - jj > 2 and seq.is_WCpair(ii, jj)){
          internal = min(internal, V.at(ii).at(jj)+eL(i, j, ii, jj));
      }
    }
  }
  VBI.at(i).at(j) = internal;
  return internal;
}


/**
 * @brief multi loop energy calculator
 *
 * @param i
 * @param j
 *
 * @return energy of i-j segment
 */
double Zuker::calc_VM(int i, int j){
  if(VM_iscalced.at(i).at(j)){
    return VM.at(i).at(j);
  }else{
    if(j-i <= M){
      VM_iscalced.at(i).at(j) = true;
      return INF;
    }else if(i<1 | i>N | j<1| j>N){
      VM_iscalced.at(i).at(j) = true;
      return INF;
    }else{
      double multi_seg = INF;
      double j_unpair = calc_VM(i, j-1) + multi_c;
      double i_unpair = calc_VM(i+1, j) + multi_c;
      double non_closed = INF;
      for(int k=i+1; k<j; k++){
        non_closed = min(non_closed, calc_VM(i, k) + calc_VM(k+1, j));
      }
      if(seq.is_WCpair(i, j)){
        multi_seg = min({j_unpair, i_unpair, non_closed, V.at(i).at(j) + multi_b});
      }else{
        multi_seg = min({j_unpair, i_unpair, non_closed});
      }
      VM.at(i).at(j) = multi_seg;
      VM_iscalced.at(i).at(j) = true;
      return multi_seg;
    }
  }
}



/**
 * @brief V calculator by using DP
 */
void Zuker::calc_V(int i, int j){
  //calc VM shold be executed before calc V
  spdlog::info("calc_V");
  if(j-i <= M){
    VM.at(i).at(j) = INF;
  }else if(!seq.is_WCpair(i, j)){
    spdlog::error(" V this is not base pair {0} {1}", i, j);
    VM.at(i).at(j) = INF;
  }else{
    //計算する
    double hairpin = eH(i, j);
    double stacking = stacking = V.at(i+1).at(j-1)+ eS(i, j, i+1, j-1);
    double multi = INF;
    for(int k=i+1; k<j-1; k++){
      //TODO ここから
      multi = min(multi, calc_VM(i+1, k) + calc_VM(k+1, j-1) + multi_a);
    }
    V.at(i).at(j) = min({hairpin, stacking, internal, multi});
  }
}


/**
 * @brief calcurate V by using DP
 */
void Zuker::calc_W(){
  //calc V should be executed before calc W
  spdlog::info("calc_W");

  for(int i=N;i>0; i--){
    for(int j=i; j<=N;j++){
      if(j-i<=M){
        W.at(i).at(j) = 0;
      }else{
        double buf = INF;
        for(int k=i;k<j;k++){
          if(seq.is_WCpair(k, j)){
            buf= min(buf, W.at(i).at(k-1) + V.at(k).at(j));
          }
        }
        W.at(i).at(j) = min(buf, W.at(i).at(j-1));
      }
    }
  }
}


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
  F = vector<double>(N+1, INF);
  for(int k=0; k<N; k++){
    //並列化可能
    for(int i= 1; i<=N; i++){
      //対角線上に左上から右下に計算
      int j = i+k;
      if(j<=N){
        calc_VBI(i, j);
        calc_V(i, j);
        calc_W(i, j);
      }
    }
  }
  /* spdlog::info("calc_F"); */
  for(int j = 1; j<=N; j++){
    //1-jまでの断片行列の自由エネルギーを計算する
    calc_F(j);
  }
  rna_2d = string(N, '.');
}


Zuker::~Zuker(){
  spdlog::info("deconstract zuker");
}

void Zuker::calc_VBI(int i, int j){
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
}


/**
 * @brief multi loop energy calculator
 *
 * @param i
 * @param j
 *
 * @return energy of i-j segment
 */
void Zuker::calc_W(int i, int j){
  // multi loopの計算
  double multi_seg = INF;
  if(j-i <= M){
    multi_seg = INF;
  }else if(i<1 | i>N | j<1| j>N){
    multi_seg = INF;
  }else{
    double i_unpair = V.at(i+1).at(j) + multi_c;
    double j_unpair = V.at(i).at(j-1) + multi_c;

    double non_closed = INF;
    for(int k=i+1; k<j; k++){
      non_closed = min(non_closed, W.at(i).at(k) + W.at(k+1).at(j));
    }
    if(seq.is_WCpair(i, j)){
      multi_seg = min({j_unpair, i_unpair, non_closed, V.at(i).at(j) + multi_b});
    }else{
      multi_seg = min({j_unpair, i_unpair, non_closed});
    }
  }
  W.at(i).at(j) = multi_seg;
}


/**
 * @brief V calculator by using DP
 */
void Zuker::calc_V(int i, int j){
  //calc V shold be executed before calc V
  if(j-i <= M){
    V.at(i).at(j) = INF;
  }else if(!seq.is_WCpair(i, j)){
    /* spdlog::error(" V this is not base pair {0} {1}", i, j); */
    V.at(i).at(j) = INF;
  }else{
    //計算する
    double hairpin = eH(i, j);
    double stacking = V.at(i+1).at(j-1)+ eS(i, j, i+1, j-1);
    double multi = INF;
    for(int k=i+1; k<j-1; k++){
      multi = min(multi , W.at(i+1).at(k) + W.at(k+1).at(j-1) + multi_a);
    }
    V.at(i).at(j) = min({hairpin, stacking, multi, VBI.at(i).at(j)});
  }
}


/**
 * @brief calcurate F by using DP
 */
void Zuker::calc_F(int j){
  //calc V should be executed before calc W
  double buf = INF;

  for(int i =1; i<j; i++){
    buf = min(buf, V.at(i).at(j) + F.at(i-1));
  }

  F.at(j) = min(F.at(j-1), buf);
}


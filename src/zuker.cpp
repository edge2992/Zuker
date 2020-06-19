#include <bits/stdc++.h>
#include "zuker.h"

using namespace std;

using ll = long long;


Zuker::Zuker(string rna_seq)
  : seq(rna_seq), N(rna_seq.length())
{
  W = vector<vector<double>>(N+1, vector<double>(N+1, INF));
  V = vector<vector<double>>(N+1, vector<double>(N+1, INF));
  VM = vector<vector<double>>(N+1, vector<double>(N+1, INF));
  /* calc_VM(); */
  calc_V();
  calc_W();
}


Zuker::~Zuker(){
  cout << "deconstract zuker" << endl;
}


bool Zuker::is_match(int i, int j){
  map<char, char> augc{
    {'A', 'U'},
    {'U', 'A'},
    {'G', 'C'},
    {'C', 'G'},
  };
  if(i<1 | i>N | j<1| j>N){
    return false;
  }else if(augc.find(seq.at(i-1)) != augc.end() | augc.find(seq.at(j-1)) != augc.end() ){
    return augc.at(seq.at(i-1)) == seq.at(j-1);
  }else{
  //TODO AUGC 以外だった時のエラー処理
    cout << "not AUGC" << endl;
    return false;
  }
}


double Zuker::calc_VM(int i, int j){
  //TODO 計算済みだったら値は変わらないはずなので、再度計算しない
  if(j-i <= M){
    return INF;
  }else if(i<1 | i>N | j<1| j>N){
    return INF;
  }else{
    double multi_seg = INF;
    double j_unpair = calc_VM(i, j-1) + multi_c;
    double i_unpair = calc_VM(i+1, j) + multi_c;
    double non_closed = INF;
    for(int k=i+1; k<j; k++){
      non_closed = min(non_closed, calc_VM(i, k) + calc_VM(i+1, j));
    }
    if(is_match(i, j)){
      multi_seg = min({j_unpair, i_unpair, non_closed, V.at(i).at(j) + multi_b});
    }else{
      multi_seg = min({j_unpair, i_unpair, non_closed});
    }
    VM.at(i).at(j) = multi_seg;
    return multi_seg;
  }
}



void Zuker::calc_V(){
  //calc VM shold be executed before calc V
  cout << "calc_V" << endl;
  for(int j=1;j<=N; j++){
    for(int i=j; i>0; i--){
      if(j-i <= M){
        VM.at(i).at(j) = INF;
      }else if(!is_match(i, j)){
        VM.at(i).at(j) = INF;
      }else{
        double hairpin = eH(i, j);
        // ii jjがペアであることを確認する
        double stacking = INF;
        if(is_match(i+1, j-1)){
            stacking = V.at(i+1).at(j-1)+ eS(i, j);
        }
        //calc internal
        double internal = INF;
        for(int ii=i+1; ii<j;ii++){
          for(int jj=ii+1; jj<j;jj++){
            if(is_match(ii, jj)){
                internal = min(internal, V.at(ii).at(jj)+eL(i, j, ii, jj));
            }
          }
        }
        //calc multi
        double multi = INF;
        for(int k=i+1; k<j; k++){
          multi = min(multi, calc_VM(i+1, k) + calc_VM(k+1, j-1) + multi_a);
        }
        V.at(i).at(j) = min({hairpin, stacking, internal, multi});
      }
    }
  }
}


void Zuker::calc_W(){
  //calc V should be executed before calc W
  cout << "calc_W" << endl;

  for(int i=N;i>0; i--){
    for(int j=i; j<=N;j++){
      if(j-i<=M){
        W.at(i).at(j) = 0;
      }else{
        double buf = INF;
        for(int k=i;k<j;k++){
          if(is_match(k, j)){
            buf= min(buf, W.at(i).at(k-1) + V.at(k).at(j));
          }
        }
        W.at(i).at(j) = min(buf, W.at(i).at(j-1));
      }
    }
  }
}


double Zuker::eH(int i, int j){
  double hairpin[32] = {INF, INF, INF,4.4,4.6,4.7,4.4,5.0,4.5,5.4,5.5,5.6,5.7,5.8,5.9,5.9,6.0,6.1,6.1,6.2,6.2,6.3,6.3,6.4,6.4,6.5,6.5,6.5,6.6,6.6,6.7,INF};
  int h = j-i;
  if(h<3){
    return INF;
  }else if(h>30){
    return INF;
  }else{
    return hairpin[h];
  }
}


double Zuker::eS(int i, int j){
  double internal[32] = {INF, INF,1.0,1.0,1.1,2.0,2.0,2.1,2.3,2.4,2.5,2.6,2.7,2.8,2.9,2.9,3.0,3.1,3.1,3.2,3.3,3.3,3.4,3.4,3.5,3.5,3.5,3.6,3.6,3.7,3.7,INF};
  int h = j-i;
  if(h<2){
    return INF;
  }else if(h>30){
    return INF;
  }else{
    return internal[h];
  }
}


double Zuker::eL(int i, int j, int ii, int jj){
  double buldge[32] = {INF, 1.0,1.0,1.0,1.1,2.0,2.0,2.1,2.3,2.4,2.5,2.6,2.7,2.8,2.9,2.9,3.0,3.1,3.1,3.2,3.3,3.3,3.4,3.4,3.5,3.5,3.5,3.6,3.6,3.7,3.7,INF};
  int h = (ii-i) + (j-jj);
  if(h<1){
    return INF;
  }else if(h>30){
    return INF;
  }else{
    return buldge[h];
  }
}



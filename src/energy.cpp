#include <bits/stdc++.h>
#include "zuker.h"

using namespace std;

using ll = long long;


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


double Zuker::eS(int i, int j, int ii, int jj){
  if(seq.is_GCpair(i, j)){
    if(seq.is_GCpair(ii, jj)){
      return -3.0;
    }else if(seq.is_AUpair(ii, jj) || seq.is_GUpair(ii, jj)){
      return -2.0;
    }else{
      cout << "[eS] error " << endl;
      return INF;
    }
  }else if(seq.is_AUpair(i, j) || seq.is_GUpair(i, j)){
    if(seq.is_GCpair(ii, jj)){
      return -2.0;
    }else if(seq.is_AUpair(ii, jj) || seq.is_GUpair(ii, jj)){
      return -0.5;
    }else{
      cout << "[eS] error " << endl;
      return INF;
    }
  }else{
    return INF;
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

#include <bits/stdc++.h>
#include "energy.h"
using namespace std;

using ll = long long;


double eH(int i, int j){
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

double eS(int i, int j){
  return 0;
}

double eL(int i, int j, int ii, int jj){
  return 0;
}


#ifndef ZUKER_H
#define ZUKER_H
#include "gtest/gtest_prod.h"
#include <bits/stdc++.h>

using namespace std;


const double INF = 10000;

class Zuker{
  public:
    const string seq;
    const int N;
    vector<vector<double>> W;
    vector<vector<double>> V;
    vector<vector<double>> VM;
    Zuker(string seq);
    ~Zuker();
  private:
    FRIEND_TEST(ZukerTest, EnergyTest);
    const int M = 4; //loopの最小値
    const double multi_a = 6.0;
    const double multi_b = -1.0;
    const double multi_c = 0.1;
    void calc_V();
    void calc_W();
    double calc_VM(int i, int j);
    //hairpin loop
    double eH(int i, int j);
    //stacking loop
    double eS(int i, int j);
    //internal loop
    double eL(int i, int j, int ii, int jj);
    // base pair?
    bool is_match(int i, int j);
};


#endif

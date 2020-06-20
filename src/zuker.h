#ifndef ZUKER_H
#define ZUKER_H
#include "gtest/gtest_prod.h"
#include <bits/stdc++.h>
#include "rna_seq.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace std;


const double INF = 10000;

class Zuker{
  public:
    Rna_seq seq;
    /* const string seq; */
    const int N;
    string rna_2d; //二次構造
    vector<vector<double>> W;
    vector<vector<double>> V;
    vector<vector<double>> VM;
    Zuker(string seq);
    ~Zuker();
    string W_traceback();
  private:
    FRIEND_TEST(ZukerTest, EnergyTest);
    const int M = 3; //loopの最小値
    const double multi_a = 6.0;
    const double multi_b = -1.0;
    const double multi_c = 0.1;
    vector<vector<bool>> VM_iscalced;
    void calc_V();
    void calc_W();
    double calc_VM(int i, int j);
    //hairpin loop
    double eH(int i, int j);
    //stacking loop
    double eS(int i, int j, int ii, int jj);
    //internal loop
    double eL(int i, int j, int ii, int jj);
    // base pair?
    /* bool is_match(int i, int j); */
    int V_traceback(int i, int j);
    int VM_traceback(int i, int j);
};


#endif

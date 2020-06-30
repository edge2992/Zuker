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
    vector<double> F;
    vector<vector<double>> W;
    vector<vector<double>> V;
    vector<vector<double>> VBI;
    bool F_traceback();
    Zuker(string seq);
    ~Zuker();
  private:
    FRIEND_TEST(ZukerTest, EnergyTest);
    const int M = 3; //loopの最小値
    const double multi_a = 6.0;
    const double multi_b = -1.0;
    const double multi_c = 0.1;
    vector<vector<bool>> VM_iscalced;
    void calc_F(int j);
    void calc_W(int i, int j);
    void calc_V(int i, int j);
    void calc_VBI(int i, int j);
    //hairpin loop
    double eH(int i, int j);
    //stacking loop
    double eS(int i, int j, int ii, int jj);
    //internal loop
    double eL(int i, int j, int ii, int jj);
    // base pair?
    /* bool is_match(int i, int j); */
    bool W_traceback(int i, int j);
    bool V_traceback(int i, int j);
    bool VBI_traceback(int i, int j);
};


#endif

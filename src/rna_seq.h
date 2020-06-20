#ifndef RNA_SEQ_H
#define RNA_SEQ_H
#include<bits/stdc++.h>

using namespace std;

class Rna_seq{
  public:
    const string rna;
    const int N;
    Rna_seq(string seq);
    ~Rna_seq();
    bool is_WCpair(int i, int j);
    bool is_GCpair(int i, int j);
    bool is_AUpair(int i, int j);
    bool is_GUpair(int i, int j); //ゆらぎ塩基対
  private:
    bool is_rna();
};

#endif

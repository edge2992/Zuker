#include "rna_seq.h"


Rna_seq::Rna_seq(string seq)
  :rna(seq), N(seq.length())
{
  if(!is_rna()){
    cout << "this is not rna (augc)" << endl;
  }
}


Rna_seq::~Rna_seq(){
}


bool is_pair(char i, char j, char target1, char target2){
  if(i == target1 & j == target2){
    return true;
  }else if(i == target2 & j == target1){
    return true;
  }else{
    return false;
  }
}


bool Rna_seq::is_WCpair(int i, int j){
  if(i<1 | i>N | j<1| j>N){
    return false;
  }else{
    return is_GCpair(i, j) | is_AUpair(i, j);
  }
}


bool Rna_seq::is_GCpair(int i, int j){
  if(i<1 | i>N | j<1| j>N){
    return false;
  }else{
    return is_pair(rna.at(i-1), rna.at(j-1), 'G', 'C');
  }
}


bool Rna_seq::is_AUpair(int i, int j){
  if(i<1 | i>N | j<1| j>N){
    return false;
  }else{
    return is_pair(rna.at(i-1), rna.at(j-1), 'A', 'U');
  }
}


bool Rna_seq::is_GUpair(int i, int j){ //ゆらぎ塩基対
  if(i<1 | i>N | j<1| j>N){
    return false;
  }else{
    return is_pair(rna.at(i-1), rna.at(j-1), 'G', 'U');
  }
}

bool Rna_seq::is_rna(){
  for(char base : rna){
    if(base == 'A' | base == 'U' | base == 'G' | base == 'C'){

    }else{
      return false;
    }
  }
  return true;
}




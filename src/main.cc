#include <iostream>
#include <fstream>
#include "zuker.h"

#define F "memo.txt"

void print_all(vector<vector<double>> Z){
  int N = Z.size();
  ofstream outputfile(F);
  for(int i=1; i<N; i++){
    for(int j=1; j<N; j++){
      if(i>j){
        outputfile << string(8, '-') << " ";
      }else{
        if(Z.at(i).at(j) > 0){
          outputfile << scientific << setprecision(2) <<  Z.at(i).at(j) << " ";
        }else{
          outputfile << scientific << setprecision(1) <<  Z.at(i).at(j) << " ";
        }
      }
    }
    outputfile << endl;
  }
  outputfile.close();
}


int main()
{
  spdlog::info("Zuker algorithm");
  spdlog::info("please enter rna sequence (augc sequence)");
  string rna_seq;
  std::cin >> rna_seq;
  Zuker zuker(rna_seq);
  print_all(zuker.VM);
  /* print_all(zuker.V); */
  /* cout << "zuker w" << endl; */
  /* print_all(zuker.W); */
  cout << zuker.W_traceback() << endl;


  return 0;
}


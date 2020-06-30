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
  list<string> rna_seq;
  rna_seq.push_back("GGGCCCAUAGCUCAGUGGUAGAGUGCCUCCUUUGCAAGGAGGAUGCCCUGGGUUCGAAUCCCAGUGGGUCCA");
  rna_seq.push_back("UGUGGUGUAGUGGUUAUCACGUUUGCCUUACACGCAAAAGGUCUCCAGUUCGAUCCUGGGCAGCACCA");
  rna_seq.push_back("GGUGCUGUGGUGUAGUGGUUAUCACGUUUGCCUUACACGCAAAAGGUCUCCAGUUCGAUCCUGGGCAGCACCA");
  rna_seq.push_back("CUCUGGUAACUAGAGAUCCCUCAGACCCUUUUAGUCAGUGUGGAAAAUCUCUAGCAGUGGCGCCCGAACAGGGACUUGAAAGCGAAAGGGAAACCAGAG");
  /* std::cin >> rna_seq; */
  for(string seq : rna_seq){
    Zuker zuker(seq);
    print_all(zuker.VM);
    cout << zuker.W_traceback() << endl;
  }


  /* Zuker zuker(rna_seq); */
  /* print_all(zuker.VM); */
  /* cout << zuker.W_traceback() << endl; */

  /* spdlog::info("Zuker algorithm"); */
  /* string rna_se = "UGUGGUGUAGUGGUUAUCACGUUUGCCUUACACGCAAAAGGUCUCCAGUUCGAUCCUGGGCAGCACCA"; */
  /* /1* zuker.~Zuker(); *1/ */
  /* Zuker zuke(rna_se); */
  /* print_all(zuke.VM); */
  /* /1* print_all(zuker.V); *1/ */
  /* /1* cout << "zuker w" << endl; *1/ */
  /* /1* print_all(zuker.W); *1/ */
  /* cout << zuke.W_traceback() << endl; */



  return 0;
}


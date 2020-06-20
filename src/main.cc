#include <iostream>
#include "zuker.h"

void print_all(vector<vector<double>> Z){
  int N = Z.size();
  for(int i=1; i<N; i++){
    for(int j=1; j<N; j++){
      if(i>j){
        cout << "-----" << " ";
      }else{
      cout << setw(5) <<  Z.at(i).at(j) << " ";
      }
    }
    cout << endl;
  }
}


int main()
{
  std::cout << "Zuker algorithm" << std::endl;
  string rna_seq;
  std::cin >> rna_seq;
  Zuker zuker(rna_seq);
  print_all(zuker.V);
  cout << "zuker w" << endl;
  print_all(zuker.W);
  cout << zuker.W_traceback() << endl;


  return 0;
}


#ifndef ENERGY_H
#define ENERGY_H

const double INF = 10000;
//hairpin loop
double eH(int i, int j);
//stacking loop
double eS(int i, int j);
//internal loop
double eL(int i, int j, int ii, int jj);

#endif

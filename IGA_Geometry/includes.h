#ifndef INCLUDES_H
#define INCLUDES_H

#include<cmath>
#include<iostream>
#include<fstream>
#include<ostream>
#include<sstream>
#include<vector>
using namespace std;
int knotVecCreate(int num_elem_1D, int p, double ki, double kf, double h,
                  vector<double>*knot_vec);
int Extraction_1D(int p, vector<double> Xi,
                  vector<vector<vector <double> > > * C);
int set_Identity(vector<vector<double> > * A, int m);
int ien_1D(int n, int p, int num_elem, vector<vector<int> > *ien,
                  vector<double>* Xi);
int ien_3D(vector<vector<int> > ien_1D, vector<vector<int> > * IEN,
                  int num_elem_1D, int num_elems, int n_dof_local, int p);
int print_ien( vector<vector<int> > ien);




#endif

#include "includes.h"
using namespace std;
int main()
{
  //parametric definitions
  int p = 3; //polynomial order
  int num_elems = 16;//number of elements in 1 direction (full domain is ne^3)
  int n;//number of basis functions in 1D
  vector<double> Xi;//knot vector
  vector<vector<vector<double> > > C;//extraction operator
  C.resize(num_elems, vector<vector<double> >(p+1, vector<double>(p+1)));
  double ki = 0.0;//domain goes from 0 to pi in each direction
  double kf = M_PI;
  double h = kf/num_elems;//element size

  knotVecCreate(num_elems, p, ki, kf, h, &Xi);//create knot vector
  n = Xi.size() - p - 1;//get number of shape functions
  cout<< "n = " << n << endl;
  // for(auto & x : Xi)
  // {
  //   cout << x << ", " ;
  // }
  // cout << endl;

  Extraction_1D(p, Xi, &C); //compute extraction operators

  //////////////////////////////////////////////////////////////////////////////
  //print out the extraction operator for each element

  int num_elemTot = num_elems*num_elems*num_elems;

  ofstream ExtractFile;
  ExtractFile.open ("extraction.op");


  int i, j, k, e;
  //ExtractFile << "Writing this to a file.\n";
  for(e = 0; e < num_elemTot; e++)
  {
    ExtractFile << e << "\n"; //print element number
    k = e / (num_elems*num_elems);
    j = (e - k*num_elems*num_elems) / num_elems;
    i = e - k*num_elems*num_elems - j*num_elems;

    for(auto & x : C[i]) //print i extraction operator
    {
      for(auto & y: x)
      {
        ExtractFile << y << ", ";
      }
      ExtractFile << "\n";
    }
    ExtractFile << "\n";

    for(auto & x : C[j])//print j extraction operator
    {
      for(auto & y: x)
      {
        ExtractFile << y << ", ";
      }
      ExtractFile << "\n";
    }
    ExtractFile << "\n";

    for(auto & x : C[k]) //print k extraction operator
    {
      for(auto & y: x)
      {
        ExtractFile << y << ", ";
      }
      ExtractFile << "\n";
    }
    ExtractFile << "\n";
  }
  ExtractFile.close();

  //////////////////////////////////////////////////////////////////////////////
  //compute IEN array
  vector<vector<int> > ien1D, ien3D;
  ien_1D(n, p, num_elems, &ien1D, &Xi);
  ien_3D(ien1D, &ien3D, num_elems, num_elemTot, (p+1), p);
  cout << ien3D.size() << ", " << ien3D[0].size() << endl;

  //print the IEN
  print_ien(ien3D);
}

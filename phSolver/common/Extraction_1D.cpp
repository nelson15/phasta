  // Extraction_1D.cpp
  // AUTHOR:  Corey Wetterer-Nelson
  // DATE:    6-Nov-2017

  //Function Extraction_1D()
  //computes the extraction operator for a 1D set of B-spline bases

//INPUTS:
// n = number of basis functions (len(Xi) - p - 1)
// p = polynomial degree
// Xi = knot vector

//OUTPUTS:
// C = list of element extraction matrices
#include "run_functions.h"

int Extraction_1D(int n, int p, vector<double> Xi, double *** C)
{
  int num_elem = Xi.size() - 2*p - 1;
  int a = p;//first element
  int b = a+1;
  int nb = 0; //number of elements
  int i, mult, r, save, s;//some indices and iterators needed below
  double numer = 0; double alpha;

  vector<double> alphas;
  alphas.resize(p-1);

  set_Identity(C[0], p+1); //set first extraction op to identity

  while(b < n+p+1)
  {
    if(nb+1 < num_elem)
    {
      set_Identity(C[nb+1],p+1); //initialize next operator
    }
    i = b;
    //Scoot over to next unrepeated knot
    while (b < n+p+1 && Xi[b+1] == Xi[b]){ b++; }
    mult = b - i + 1; //get multiplicity of last knot
    if(mult < p)
    {
      numer = Xi[b] - Xi[a]; //Correct!
      //cout << "numer " << numer << endl;
      fill(alphas.begin(), alphas.end(), 0.0);
      for(int j = mult+1; j < p+1; j++)//compute alphas from Bohm's Algorithm
      {

        alphas[j-mult-1] = numer/(Xi[a+j] - Xi[a]);
      }

      r = p-mult;//compute the number of added knots
      for( int j = 1; j < r+1; j++)
      {
        save = r - j;//get the region of overlap
        s = mult + j;
        for(int k = p; k >= s; k--)
        {
          alpha = alphas[k-s];
          for(int l = 0; l < p+1; l++)//application of Bohm's Algorithm
          {
            C[nb][l][k] = alpha * C[nb][l][k] + (1-alpha) * C[nb][l][k-1];
          }
        }
        if(b < n+p+1 && nb+1 < num_elem)
        {
          for(int l = 0; l < j+1; l++)//update overlapping coefficients
          {
            C[nb+1][save+l][save] = C[nb][p-j + l][p];
          }
        }
      }
    }
    if(b < n+p+1)
    {
      a = b;
      b++;
      nb++;
    }
  }//end while(b < n+p+1)

  return 0;//success!
}//end function


////////////////////////////////////////////////////////////////////////////////
//sets a matrix to the identity matrix
//assume square matrix with dimension m
//sort of quick and dirty, but will get the job done
int set_Identity(double ** A, int m)
{
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < m; j++)
    {
      if( i == j ){ A[i][j] = 1.0; }
      else{ A[i][j] = 0.0; }
    }
  }
  return 0; //success!
}

#include "run_functions.h"

int basisFuncsAndDers(vector<double> * Xi, const int p,
                      const double xi, const int numDers, vector<double> * ders)
{
	ders->clear();

	//Find the span in which xi lies.  Return if
	//xi is not within the limits of the knot vector.
	int span = findSpan( *Xi, p, xi);
	if( span < 0 )
		return span;

	//Don't calculate zero derivatives.
	int nDers = numDers;
	//if( nDers > p )
	//	nDers = p;

	ders->resize( (p+1)*(nDers+1), 0.0 );

	int j, r;

	double** ndu = new double*[p+1];
	for( j = 0; j <= p; j++ )
		ndu[j] = new double[p+1];
	double* left = new double[p+1];
	double* right = new double[p+1];

	//Calculate basis functions and knot differences.
	ndu[0][0] = 1.0;
	for( j = 1; j <= p; j++ )
	{
		left[j] = xi - Xi->at(span+1-j);
		right[j] = Xi->at(span+j) - xi;

		double saved = 0.0;
		for( r = 0; r < j; r++ )
		{
			ndu[j][r] = right[r+1]+left[j-r];
			double temp = ndu[r][j-1]/ndu[j][r];

			ndu[r][j] = saved + right[r+1]*temp;
			saved = left[j-r]*temp;
		}
		ndu[j][j] = saved;
	}
	//Load the basis functions.
	for( j = 0; j <= p; j++ )
		ders->at(j*(nDers+1)) = ndu[j][p];

	double* a[2];
	a[0] = new double[p+1];
	a[1] = new double[p+1];

	//Compute the derivatives.
	int k;
	for( r = 0; r <= p; r++ )
	{
		int s1 = 0;
		int s2 = 1;

		a[0][0] = 1.0;

		//Compute the kth derivatives.
		for( k = 1; k <= nDers; k++ )
		{
			double d = 0.0;
			int rk = r-k;
			int pk = p-k;
			if( r >= k )
			{
				a[s2][0] = a[s1][0]/ndu[pk+1][rk];
				d = a[s2][0]*ndu[rk][pk];
			}

			int j1, j2;
			if( rk >= -1 )
				j1 = 1;
			else
				j1 = -rk;

			if( r-1 <= pk )
				j2 = k-1;
			else
				j2 = p - r;

			for( j = j1; j <= j2; j++ )
			{
				a[s2][j] = (a[s1][j] - a[s1][j-1])/ndu[pk+1][rk+j];
				d += a[s2][j]*ndu[rk+j][pk];
			}

			if( r <= pk )
			{
				a[s2][k] = -a[s1][k-1]/ndu[pk+1][r];
				d += a[s2][k]*ndu[r][pk];
			}

			ders->at(r*(nDers+1)+k) = d;

			//switch rows.
			j = s1;
			s1 = s2;
			s2 = j;
		}
	}

	//Multiply through be the correct factors.
	r = p;
	for( k = 1; k <= nDers; k++ )
	{
		for( j = 0; j <= p; j++ )
			ders->at(j*(nDers+1)+k) *= r;

		r*= (p-k);
	}


	//Clean up memory
	for( j = 0; j <= p; j++ )
		delete [] ndu[j];
	delete [] ndu;
	delete [] a[0];
	delete [] a[1];
	delete [] left;
	delete [] right;

	return span;
}

////////////////////////////////////////////////////////////////////////////////
//compute the bernstein polynomials over a 2D element at point (xi_u,xi_v)
// INPUTS:
//    vector< array <double,3> > * B = stores values, derivatives of bases
//                                   B[i][0] = value of basis i
//                                   B[i][1] = u derivative of basis i
//                                   B[i][2] = v derivative of basis i
//    int p_u = polynomial order in u direction
//    int p_v = polynomial order in v direction
//    double xi_u = location in u direction
//    double xi_v = location in v direction
int BernsteinBasisAndDerivs2D(vector < array <double, 3> > * B,
                              int p_u, int p_v, double xi_u, double xi_v)
{
  int n_loc = (p_u + 1) * (p_v + 1);//number of bases in 2D element
  B->resize(n_loc); // resize vector to fit number of bases in element

  int i = 0; //index for B
    for (int i1 = 1; i1 <= p_u+1; i1++)
    {
      for (int i2 = 1; i2 <= p_v+1; i2++)
      {
        //simple tensor product to get value of basis at point
        B->at(i)[0] = bern(i1,p_u,xi_u) * bern(i2,p_v,xi_v);

        //derivatives are defined in terms of lower order Bernstein polynomials
        B->at(i)[1] = p_u * (bern(i1-1,p_u-1,xi_u) - bern(i1,p_u-1,xi_u));
        B->at(i)[2] = p_v * (bern(i2-1,p_v-1,xi_v) - bern(i2,p_v-1,xi_v));
        i = i + 1;
      }
    }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//compute value of 1D Bernstein polynomial i of order p at point x
//bern returns the value of the berstein polynomial at x in [0,1]
//  INPUTS:
//    i = polynomial number
//    p = polynomial degree
//    x = x value
int bern(int i, int p, double x)
{
  if (p == 0 && i == 1)
    return 1;
  else if (i < 1 || i > p+1)
    return 0;
  else
    return (1-x)*bern(i,p-1,x) + x * bern(i-1,p-1,x);
}

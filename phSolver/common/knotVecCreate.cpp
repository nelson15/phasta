#include "run_functions.h"

/*
function knotVecCreate() creates 1D knot vector
INPUTS: num_elem_1D = number of elements in 1D
        p           = polynomial order
        ki          = initial knot (usually 0)
        kf          = final knot (often 1, but maybe pi (ie. TaylorGreenVortex))
        type        = string determining the type of knot (linear, stretch etc)
        knot        = pointer to knot vector to be filled
*/
int knotVecCreate(int num_elem_1D, int p, double ki, double kf, double h,
                    string type, vector<double>*knot_vec)
{
  knot_vec->resize(num_elem_1D + 2*p+1, ki); //assumes an open knot vector
  if(!type.compare("linear"))
  {
    //fill interior knots
    for ( int i = 0; i < num_elem_1D; ++i )
    {
      knot_vec->at(i+p+1) = knot_vec->at(i+p) + h;
    }
    //fill last knots (open knot vector assumed)
    fill(knot_vec->end()-(p+1), knot_vec->end(), kf);
  }
  return 0; //sucess!
}

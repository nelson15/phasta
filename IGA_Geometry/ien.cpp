//ien.cpp
// AUTHOR:  Corey Wetterer-Nelson
// DATE:    29-Nov-2017
#include "includes.h"

////////////////////////////////////////////////////////////////////////////////
// builds an IEN array in 1 direction u or v (0 or 1)
int ien_1D(int n, int p, int num_elem, vector<vector<int> > *ien, vector<double>* Xi)
{

  //resize ien array to be size (num_elem, p+1)
  ien->resize(num_elem, vector<int>(p+1));


  int l = p+1; //knot span
  int e = 0; //element

  while(l < n + 2)
  {
    for(int a = 0; a < p+1; a++) //fill element e's ien vector
    {
      ien->at(e)[a] = (l+a) - (p+1);
      //cout <<ien->at(e)[a] << ", ";
    }
    //cout << endl;
    l++;

    while(Xi->at(l) == Xi->at(l-1) && l < (Xi->size() - 1))
    {
      l++;
    }
    e++;
  }
  return 0; //success!
}

////////////////////////////////////////////////////////////////////////////////
//IEN_3D builds the 3D IEN array on the surface
 int ien_3D(vector<vector<int> > ien_1D, vector<vector<int> > * IEN, int num_elem_1D, int num_elems, int n, int p)
 {

   IEN->resize(num_elems, vector<int>(n));

   int eu, ev, ew, au, av, aw, iu, iv, iw, e, a, i;
   for(eu = 0; eu < num_elem_1D; eu++)
   {

     for(au = 0; au < p + 1; au++)
     {
       iu = ien_1D[eu][au];

       for(ev = 0; ev < num_elem_1D; ev++)
       {
         for(av = 0; av < p + 1; av++)
         {
           iv = ien_1D[ev][av];
           for(ew = 0; ew < num_elem_1D; ew++)
           {
             for(aw = 0; aw < p+1; aw++)
             {
               iw = ien_1D[ew][aw];
               e = eu + ev*num_elem_1D + ew*num_elem_1D*num_elem_1D;
               a = au + av*(p+1) + aw*(p+1)*(p+1);
               i = iu + iv*n + iw*n*n;
               IEN->at(e)[a] = i;
             }
           }

         }
       }
     }
   }
   return 0; //success!
 }

////////////////////////////////////////////////////////////////////////////////
//print the ien array
int print_ien( vector<vector<int> > ien)
{
  ofstream fil;
  fil.open ("ien.op");
  for(auto & e : ien)
  {
    for(auto & a: e)
    {
      fil << a << ", ";
    }
    fil << endl;
  }
  fil.close();
  return 0; //success!
}

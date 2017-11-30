//#include "libraries.h"
#include "run_functions.h"

int findSpan(const std::vector<double>& knotVec, const int cDegree, const double value)
{
	if( value < knotVec[0] || value > knotVec.back() )
	{
		std::cerr << "Error: value outside knot vector end points in findSpan()" << std::endl;
		return -1;
	}

	int high = (knotVec.size()-1) - cDegree;
	int low = cDegree;
	int mid = (low + high)/2;

	//Special end case.
	if( value == knotVec[high] )
		return high - 1;


	while( value < knotVec[mid] || value >= knotVec[mid+1] )
	{
		if( value < knotVec[mid] )
			high = mid;
		else
			low = mid;
		mid = (high + low)/2;
	}
	return mid;
}

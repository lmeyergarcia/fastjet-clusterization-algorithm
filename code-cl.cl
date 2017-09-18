#include "tracking.h"
using namespace std;

__kernel void makeSimpleSegment(__global char* string, __global vector<PrPixelHit> nextHits, __global vector<PrPixelHit> currentHits){
	vector<TrackSegment> tSegment;
	for(int id_current = 0; id_current < (int) currentHits.size(); id_current++){
		float x_zero = currentHits[id_current].x();
		float y_zero = currentHits[id_current].y();
		float z_zero = currentHits[id_current].z();
		for(int id_next = 0; id_next < (int) nextHits.size(); id_next++){
			float x_one = nextHits[id_next].x();
			float y_one = nextHits[id_next].y();
			float z_one = nextHits[id_next].z();
			float tx = (x_one - x_zero)/(z_one - z_zero); // x = bx + tx*z
			float ty = (y_one - y_zero)/(z_one - z_zero); // y = by + ty*z
			float bx = x_zero - tx*z_zero;
			float by = y_zero - ty*z_zero;
			float x_1000 = bx + tx*1000;
			float y_1000 = by + ty*1000;
			//see the angle between the two hits
			if(true  /*sqrt(tx*tx+ty*ty) <= ACCEPTANCE_ANGLE*/){
                                     	vector<PrPixelHit> tmp;
				//make segment object
				tmp.push_back(currentHits[id_current]);
				tmp.push_back(nextHits[id_next]);
				TrackSegment aux (tmp, INITIAL_STATUS, tx, ty, x_1000, y_1000);
				//print the segment on file
				//printHit(currentHits[id_current]);
				//printHit(nextHits[id_next]);
				//segFile << endl;
				//count the segment
				//no_segments++;
				tSegment.push_back(aux);
				tmp.clear();

			}
		}
	}
	//segFile << no_segments << endl;
  return tSegment;
}

// > gcc -I /path-to-NVIDIA/OpenCL/common/inc -L /path-to-NVIDIA/OpenCL/common/lib/Linux64 -o hello hello.c -lOpenCL (64-bit Linux)

/* date = December 13th 2022 10:32 pm */

#ifndef INCLUDE_H
#define INCLUDE_H

#define internal static
#define local    static
#define global   static

global int  *global_matrix;

struct matrix {
	int* start;
	int* end;
};

global struct matrix global_matrix_struct;

#include "sequence.h"
#include "algorithms.h"

#include "sequence.cpp"
#include "algorithms.cpp"

#endif //INCLUDE_H

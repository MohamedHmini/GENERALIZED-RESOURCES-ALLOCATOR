#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "HLCio/dataframe.h"

#ifndef GRA_H
#define GRA_H


typedef struct GRA_RESULTS{
	int optimal_value;
	DF_ELEMENT policies;
}GRA_RESULTS;


DATAFRAME *fit_to_find_one_optimal_path(DATAFRAME*);
DATAFRAME *fit_to_find_multiple_optimal_paths(DATAFRAME*);
void load_policies(DATAFRAME*, int, int, DF_ELEMENT*, DF_ELEMENT*);
void display_results(GRA_RESULTS);


#endif



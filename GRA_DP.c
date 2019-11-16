#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"HLCio/dataframe.h"
#include"HLCio/advio.h"
#include "GRA.h"


void main(){
    FILE *file = open_file("E:\\INSEA-STUDENT\\S1\\TECH-OPT\\GRA-PROJECT\\datasEts\\sorted.csv", "r");
	DATAFRAME *r = csv_to_df(file);
    // display_df(r);
	df_retype(r, DF_ELEMENT_TInt);

    DATAFRAME *f = fit_to_find_multiple_optimal_paths(r);
    // display_df(f);
    GRA_RESULTS *results = malloc(sizeof(GRA_RESULTS));
    results->optimal_value = f->data[f->len_rows - 1][f->len_cols - 1].node.Arr->data[0].node.Arr->data[2].node.Int;
    results->policies = arrcreate(0);
    DF_ELEMENT policy = arrcreate(0);
    load_policies(f, f->len_rows, f->len_cols - 1, &policy, &results->policies);
    // display_results(*results);

    arrfree(&results->policies);
    arrfree(&policy);
    df_free(f);
    df_free(r);
	fclose(file);
}

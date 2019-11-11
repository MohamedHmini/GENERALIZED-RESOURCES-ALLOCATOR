#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"dataframe.h"
#include"advio.h"



// typedef struct PATH_ELEMENT{
//     int current_allocation;
//     int next_allocation;
//     int generated_wealth;
// }PATH_ELEMENT;


// typedef PATH_ELEMENT* SOLUTION_PATH;
// typedef SOLUTION_PATH* PATHS;


void getOptimalPaths(DATAFRAME *r, DATAFRAME *f){
    DATAFRAME *paths = Dataframe(0,0,NULL);



}


DATAFRAME *fit(DATAFRAME *r){

    DF_ELEMENT e;
    e.Int_Array_element = (int*) malloc(sizeof(int) * 3);
    e.Int_Array_element[0] = 0;
    e.Int_Array_element[1] = 0;
    e.Int_Array_element[2] = 0;

	DATAFRAME *f = df_full(r->len_rows + 1, r->len_cols, DF_ELEMENT_TIntArray, e);


    int N = f->len_rows;
    int k = N - 1;
    int M = r->len_cols;

    while(k > 0){
        
        int m ;
        for(m = 0; m < M; m++){
            int i;
            for(i = 0; i< m + 1; i++){
                int j = m - i;
                int v = r->data[k - 1][i].Int_element + f->data[N - k - 1][j].Int_Array_element[2];

                DF_ELEMENT e;
                e.Int_Array_element = (int*) malloc(sizeof(int) * 3);
                e.Int_Array_element[0] = i;
                e.Int_Array_element[1] = j;
                e.Int_Array_element[2] = v;

                f->data[N - k][m] = v > f->data[N - k][m].Int_Array_element[2] ? e : f->data[N - k][m];
            }
        }

        k--;
    }


	return f;  

}



void main(){
    FILE *file = open_file("E:\\INSEA-STUDENT\\S1\\TECH-OPT\\GRA-PROJECT\\sorted.csv", "r");
	DATAFRAME *r = csv_to_df(file);
    display_df(r);
	df_retype(r, DF_ELEMENT_TInt);

    DATAFRAME *f = fit(r);
    display_df(f);
    free(r);
	fclose(file);
}
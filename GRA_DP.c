#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"HLCio/dataframe.h"
#include"HLCio/advio.h"



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

    DF_ELEMENT e = arrcreate(3);

    for(int i = 0; i< e.node.Arr->size; i++){
        e.node.Arr->data[i].type = DF_ELEMENT_TInt;
        e.node.Arr->data[i].node.Int = 0;
    }

	DATAFRAME *f = df_full(r->len_rows + 1, r->len_cols, DF_ELEMENT_TArray, e);
    
    int N = f->len_rows;
    int k = N - 1;
    int M = r->len_cols;

    while(k > 0){
        
        int m ;
        for(m = 0; m < M; m++){
            int i;
            for(i = 0; i< m + 1; i++){
                int j = m - i;
                int v = r->data[k - 1][i].node.Int + f->data[N - k - 1][j].node.Arr->data[2].node.Int;

                DF_ELEMENT e = arrcreate(3);
                int coords[3] = {i,j,v};
                
                for(int c = 0;c<3;c++){
                    e.node.Arr->data[c].type = DF_ELEMENT_TInt;
                    e.node.Arr->data[c].node.Int = coords[c];
                }

                f->data[N - k][m] = v > f->data[N - k][m].node.Arr->data[2].node.Int ? e : f->data[N - k][m];
            }
        }

        k--;
    }


	return f;  

}

DATAFRAME *fit2(DATAFRAME *r){

    DF_ELEMENT e = arrcreate(1);
    e.node.Arr->data[0] = arrcreate(3);

    for(int i = 0;i < 3; i++){
        e.node.Arr->data[0].node.Arr->data[i].type = DF_ELEMENT_TInt;
        e.node.Arr->data[0].node.Arr->data[i].node.Int = 0;
    }


	DATAFRAME *f = df_full(r->len_rows + 1, r->len_cols, DF_ELEMENT_TArray, e);

    int N = f->len_rows;
    int k = N - 1;
    int M = r->len_cols;

    while(k > 0){
        
        int m ;
        for(m = 0; m < M; m++){
            int i;
            for(i = 0; i< m + 1; i++){
                int j = m - i;
                int v = r->data[k - 1][i].node.Int + f->data[N - k - 1][j].node.Arr->data[0].node.Arr->data[2].node.Int;
              
                if(v >= f->data[N - k][m].node.Arr->data[0].node.Arr->data[2].node.Int){
                   if(v > f->data[N - k][m].node.Arr->data[0].node.Arr->data[2].node.Int){
                        free(f->data[N - k][m].node.Arr);
                        f->data[N - k][m] = arrcreate(0);
                    }

                    DF_ELEMENT e = arrcreate(3);
                    int coords[3] = {i,j,v};
                    
                    for(int c = 0;c < 3; c++){
                        e.node.Arr->data[c].type = DF_ELEMENT_TInt;
                        e.node.Arr->data[c].node.Int = coords[c];
                    }
                    arrpush(&f->data[N - k][m], e);
                }
            }
        }

        k--;
    }


	return f;  

}

// needs to be debugged/!
void get_policies(DATAFRAME *f, int k, int i, DF_ELEMENT *policy, DF_ELEMENT *policies) {
    if(k == 0){
        DF_ELEMENT copy = df_element_copy(*policy);
        arrpush(policies, copy);
        return;
    }

    for(int j = 0; j < f->data[k - 1][i].node.Arr->size; j++){
        arrpush(policy, f->data[k - 1][1].node.Arr->data[j].node.Arr->data[0]);
        get_policies(f, k - 1, f->data[k - 1][1].node.Arr->data[j].node.Arr->data[1].node.Int, policy, policies);
        arrpop(policy);
    }
}

void main(){
    FILE *file = open_file("E:\\INSEA-STUDENT\\S1\\TECH-OPT\\GRA-PROJECT\\sorted.csv", "r");
	DATAFRAME *r = csv_to_df(file);
    // display_df(r);
	df_retype(r, DF_ELEMENT_TInt);

    DATAFRAME *f = fit2(r);
    display_df(f);
    DF_ELEMENT policies = arrcreate(0);
    DF_ELEMENT policy = arrcreate(0);
    get_policies(f, f->len_rows, f->len_cols - 1, &policy, &policies);

    for(int i = 0; i<policies.node.Arr->size; i++){
        for(int j = 0; j < policies.node.Arr->data[i].node.Arr->size; j++){
            printf("%d ",policies.node.Arr->data[i].node.Arr->data[j].node.Int);
        }
        printf("\n");
    }

    free(f);
    free(r);
	fclose(file);
}
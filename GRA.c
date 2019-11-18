#include<stdlib.h>
#include<stdio.h>
#include"HLCio/dataframe.h"
#include"HLCio/advio.h"
#include "GRA.h"



GRA_RESULTS *gracreate(){
    return malloc(sizeof(GRA_RESULTS));
}

DATAFRAME *fit_to_find_one_optimal_path(DATAFRAME *r){

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

DATAFRAME *fit_to_find_multiple_optimal_paths(DATAFRAME *r){

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
                        arrfree(&f->data[N - k][m]);
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

void load_policies(DATAFRAME *f, int k, int i, DF_ELEMENT *policy, DF_ELEMENT *policies) {
    if(k == 0){
        DF_ELEMENT copy = df_element_copy(*policy);
        arrpush(policies, copy);
        return;
    }
    
    for(int j = 0; j < f->data[k - 1][i].node.Arr->size; j++){
        arrpush(policy, f->data[k - 1][i].node.Arr->data[j].node.Arr->data[0]);
        load_policies(f, k - 1, f->data[k - 1][i].node.Arr->data[j].node.Arr->data[1].node.Int, policy, policies);
        arrpop(policy);
    }
}


void display_results(GRA_RESULTS results){
    for(int i = 0; i<results.policies.node.Arr->size; i++){
        printf("POLICY(%d) -> [",i + 1);
        for(int j = 0; j < results.policies.node.Arr->data[i].node.Arr->size; j++){
            printf("%d ",results.policies.node.Arr->data[i].node.Arr->data[j].node.Int);
        }
        printf("] \n");
    }
    printf("\nOPTIMAL VALUE : (%d)\n", results.optimal_value);
}
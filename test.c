#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include "GRA.h"
#include "HLCio/advio.h"
#include "HLCio/dataframe.h"
#include<string.h>

void main(){

	DF_ELEMENT e = create_array(3);

	for(int i = 0; i < e.node.Arr->size; i++){
		e.node.Arr->data[i].type = DF_ELEMENT_TInt;
		e.node.Arr->data[i].node.Int = i;
	}

	pop_array(&e);
	for(int i = 0; i < e.node.Arr->size; i++){
		printf("%d ",e.node.Arr->data[i].node.Int);
	}
	


	// FILE *file = open_file("E:\\INSEA-STUDENT\\S1\\TECH-OPT\\GRA-PROJECT\\zz.csv", "r");
	// DATAFRAME *df = csv_to_df(file);
	// display_df(df);
	// display_df(df);
	// df_retype(df, DF_ELEMENT_TInt);
	// display_df(df);
	// fclose(file);

	// DF_ELEMENT e;
	// e.type = DF_ELEMENT_TArray;
	// e.node.Arr = malloc(sizeof(Array) * 3);
	// int i = 0;
	// e.node.Arr->size = 3;
	// e.node.Arr->data = malloc(sizeof(DF_ELEMENT) * 3);
	// for(i; i< 3; i++){
	// 	e.node.Arr->data[i].node.Arr = malloc(sizeof(Array));
	// 	e.node.Arr->data[i].node.Arr->data = malloc(sizeof(DF_ELEMENT) * 3);
	// 	e.node.Arr->data[i].type = DF_ELEMENT_TArray;
	// 	e.node.Arr->data[i].node.Arr->size = 3;
	// 	for(int j = 0; j<3 ; j++){
	// 		e.node.Arr->data[i].node.Arr->data[j].type = DF_ELEMENT_TInt;
	// 		e.node.Arr->data[i].node.Arr->data[j].node.Int = 4;
	// 	}

	// }

	// DATAFRAME *df = df_full(10,10, e.type, e);
	// display_df(df);
	// df->data[0][0].node.Arr->data[0].node.Arr->data[0].node.Int = 7;
	// display_df(df);

	
	// free(df);
// 	int* e = malloc(sizeof(int) * 3);
// 	e[0] = 0;
// 	e[1] = 1;
// 	e[2] = 2;
// 	DF_ELEMENT element;
// 	element.Int_Array_element = e;
// 	DATAFRAME *df = df_full(10, 20, DF_ELEMENT_TIntArray, element);
// 	display_df(df);
// 	free(df);
// //	printf("%d", atoi("1"));
//	printf("\n%d", sizeof(strsep(strdup("mohamed hmini is here"), " ")));
/*	int isclosed = close_file(file);



	if(isclosed == 1){
		printf("FILE IS CLOSED !");
	}
	else{
		printf("FILE ISN'T CLOSED DUE TO AN UNKNOWN REASON!");
	}
*/
}

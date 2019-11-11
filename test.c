#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include "GRA.h"
#include "advio.h"
#include "dataframe.h"
#include<string.h>

void main(){
	
	FILE *file = open_file("E:\\INSEA-STUDENT\\S1\\TECH-OPT\\GRA-PROJECT\\zz.csv", "r");
	DATAFRAME *df = csv_to_df(file);
	// display_df(df);
	// df_retype(df, DF_ELEMENT_TInt);
	// display_df(df);
	close_file(file);
	
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

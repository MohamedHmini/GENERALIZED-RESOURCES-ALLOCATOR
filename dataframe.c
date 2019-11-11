#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include "dataframe.h"




DATAFRAME *Dataframe(
	int len_rows, 
	int len_columns, 
	DF_DATA_CONTAINER data
	){

	DATAFRAME *df = (DATAFRAME*) malloc(sizeof(DATAFRAME));

	df->len_rows = len_rows;
	df->len_cols = len_columns;
	df->data = data;
	
	return df;

}



DATAFRAME *df_full(
	int rows, 
	int cols, 
	DF_ELEMENT_TYPE type, 
	DF_ELEMENT init_val
	){

	DATAFRAME *df = Dataframe(rows, cols, NULL);
	df->type = type;
	df->data = (DF_DATA_CONTAINER) malloc(sizeof(DF_ELEMENT_CONTAINER) * rows);

	int j = 0;

	while(j < rows){

		df->data[j] = (DF_ELEMENT_CONTAINER) malloc(sizeof(DF_ELEMENT) * cols);
		int k = 0;

		while(k < cols){
			df->data[j][k] = init_val;
			k++;
		}	

		j++;
	}

	return df;
}




void DF_STR_TO_INT(DF_ELEMENT* df_element){
	df_element->Int_element = atoi(df_element->Str_element);
}

void DF_INT_TO_STR(DF_ELEMENT* df_element){
	itoa(df_element->Int_element, df_element->Str_element, 10);
}

// this function allows a mapping of elements of a particular dataframe : 
//typedef void (*cfun)();

void df_map(
	DATAFRAME *df, 
	void (*fun)(DF_ELEMENT* df_element),
	...
	){

	int i,j;

//	va_list cfuns;
//	va_start(cfuns, cfun);
	
//	cfun p = va_arg(cfuns, cfun);
//	(*p)();

	for(i = 0; i< df->len_rows;i++){
		for(j = 0; j< df->len_cols; j++){
			fun( &df->data[i][j] );
		}
//		cfun p = va_arg(cfuns, cfun);
//		(*p)();
	}

//	cfun p = va_arg(cfuns, cfun);
//	p();
}


void df_retype(DATAFRAME *df, DF_ELEMENT_TYPE type){
	// if col == -1 then we r retyping the whole dataframe with the same type : 

	switch(type){
		case DF_ELEMENT_TStr:{
			df->type = type;
			df_map(df, DF_INT_TO_STR);
		}break;
		case DF_ELEMENT_TInt:{
			df->type = type;
			df_map(df, DF_STR_TO_INT);
		}break;
		case DF_ELEMENT_TDouble:{

		}break;
		default:{

		}
	}
}


/*
TYEP type_of(char data_element){
	TYPE type;
	//...
	return type;

}



*/

void display_df(DATAFRAME *df){
	int i,j;

	printf("ROWS : %d\n", df->len_rows);
	printf("COLS : %d\n", df->len_cols);

	for(i = 0; i< df->len_rows;i++){
		printf("[ ");
		for(j = 0; j< df->len_cols; j++){
			if(df->type == DF_ELEMENT_TStr){
				printf("%s ", df->data[i][j] );
			}
			else if(df->type == DF_ELEMENT_TInt)
				printf("%d ", df->data[i][j] );
			else
			{
				printf("%d ", df->data[i][j].Int_Array_element[2]);
			}
			
		}
		printf(" ]\n");
	}

}


void show(DATAFRAME *DF){
	//..
}
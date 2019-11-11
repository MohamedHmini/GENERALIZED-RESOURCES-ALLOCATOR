/*
	HIGH-LEVEL-C (HLCio) // pronounced : etch-EL-Cio
	
	THIS LIB IS FOR A LARGE SCOPE REASON, WHICH CONSISTS OF DATA MANUPILATION IN A LOW-LEVEL LANGUAGE LIKE 'C'
	DATAFRAMES ARE A GOOD WAY FOR CRUD OPERATIONS ON A DATASET AS WELL AS MORE COMPLEX/ADVANCED QUERIES.

	MOHAEMD-HMINI

*/

#ifndef DATAFRAME_H
#define DATAFRAME_H



typedef enum DF_ELEMENT_TYPE {
	DF_ELEMENT_TStr, 
	DF_ELEMENT_TInt, 
	DF_ELEMENT_TDouble, 
	DF_ELEMENT_TNaN,
	DF_ELEMENT_TIntArray
} DF_ELEMENT_TYPE;


typedef union DF_ELEMENT{
	char* Str_element;
	int Int_element;
	double Double_element;
	int* Int_Array_element;
	double* Double_Array_element;
	void* Nan_element;
} DF_ELEMENT;

typedef DF_ELEMENT* DF_ELEMENT_CONTAINER;
typedef DF_ELEMENT_CONTAINER* DF_DATA_CONTAINER;


typedef struct DATAFRAME{

	int len_rows;
	int len_cols;
	DF_ELEMENT_TYPE type;
	DF_DATA_CONTAINER data;

}DATAFRAME;





DATAFRAME *Dataframe(int,int , DF_DATA_CONTAINER );
DATAFRAME *df_full(int, int ,DF_ELEMENT_TYPE ,DF_ELEMENT);
void DF_STR_TO_INT(DF_ELEMENT*);
void DF_INT_TO_STR(DF_ELEMENT*);
void df_map(DATAFRAME *,void (*fun)(DF_ELEMENT* df_element),...);
void df_retype(DATAFRAME *, DF_ELEMENT_TYPE );
void display_df(DATAFRAME *);
void show(DATAFRAME *);



#endif
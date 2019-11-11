#include<stdbool.h>
#include "dataframe.h"


#ifndef ADVIO_H
#define ADVIO_H


// DECLARE DEFINED FUNCTIONS : 


FILE *open_file(char*, char*);
bool close_file(FILE *);
char* get_line(FILE *);
char** read_lines(FILE *);
DF_ELEMENT_CONTAINER tokenize_line(DATAFRAME *, char* , char* );
void tokenize(DATAFRAME *, char** , char* );
DATAFRAME *csv_to_df(FILE *);


#endif
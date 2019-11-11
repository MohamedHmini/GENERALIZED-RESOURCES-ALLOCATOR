#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "dataframe.h"
#include "advio.h"

// BUILT FUNCTIONS :

FILE *open_file(char* file_path, char* option){

	FILE *file = fopen(file_path, option);
	return file;
}


bool close_file(FILE *file){
	bool isclosed;
	isclosed = !fclose(file);
	return isclosed;
}


char* get_line(FILE *file){

	char* line = NULL;
	char c;
	int buff = 0;

	while(1){
		
		c = fgetc(file);
		// printf("%c",c);
		if(c == EOF || c == '\n')
			break;
		buff++;

		char* checker =  realloc(line, sizeof(char) * buff + 1);

		if(checker == NULL)
			free(checker);
		else
		{
			line = checker;
		}
		
		line[buff - 1] = c;
	}
	if(line != NULL)
		line[buff] = '\0';

	printf("%s\n", line);
	return line;
}


char** read_lines(FILE *file){
	char** lines = NULL;
	char* line = NULL;
	line = get_line(file);
	int row_i = 0;

	while(line != NULL){
		// printf("%d\n",row_i);
		row_i++;
		char** checker = realloc(lines, sizeof(char*) * row_i + 1);

		if(checker == NULL){
			free(checker);
			break;
		}
		else
		{
			lines = checker;
		}
		

		lines[row_i - 1] = line;
		line = get_line(file);
		
	}

	printf("done\n");
	lines[row_i] = NULL;
	return lines;
}


DF_ELEMENT_CONTAINER tokenize_line(DATAFRAME *df, char* line, char* tokenizer){

	DF_ELEMENT_CONTAINER tokenized_line = NULL;
	DF_ELEMENT ch;
	ch.Str_element = strtok(line, tokenizer);
	int i = 1;
	while(ch.Str_element != NULL){
		
		DF_ELEMENT_CONTAINER checker = (DF_ELEMENT_CONTAINER) realloc(tokenized_line, sizeof(DF_ELEMENT) * i);
		if(checker == NULL){
			free(checker);
			break;}
		else
		{
			tokenized_line = checker;
		}
		
		tokenized_line[i - 1].Str_element = ch.Str_element;
		ch.Str_element = strtok(NULL, tokenizer);
		i++;
	}
	// printf("\n");
	df->len_cols = i - 1;
	return tokenized_line;
}

void tokenize(DATAFRAME *df, char** lines, char* tokenizer){

	DF_DATA_CONTAINER tokenized_lines = NULL;
	DF_ELEMENT_CONTAINER dec = NULL;
	char* line = lines[0];
	int i = 1;
	
	while(line != NULL){

		DF_DATA_CONTAINER checker = (DF_DATA_CONTAINER) realloc(tokenized_lines, sizeof(DF_ELEMENT_CONTAINER) * i);
		if(checker == NULL){
			free(checker);
			break;}
		else
		{
			tokenized_lines = checker;
		}
		
		dec = tokenize_line(df, line, tokenizer);
		tokenized_lines[i - 1] = dec;

		i++;
		line = lines[i - 1];
		printf("i:%d, line:%s\n",i - 1,line);
		
	}

	df->len_rows = i - 1;
	df->type = DF_ELEMENT_TStr;
	df->data = tokenized_lines;

}



DATAFRAME *csv_to_df(FILE *csv){
	DATAFRAME *df = Dataframe(0,0,NULL); 
	char** lines = read_lines(csv);
	tokenize(df, lines, ",");
	return df;
}

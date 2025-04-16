#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>

// Fill in the TODO sections as required and DO NOT TOUCH any of the fprintf statements

void init_table(int* shift_table,int n)
{
	//TODO
}

// Construct the Bad Character Shift table
void preprocess(int* shift_table,char* pattern)
{
	//TODO
}

int string_match(int* shift_table,char* pattern,char* text,FILE* output_file)
{
	// TODO Variables initialization
	int matches;
	int star_pos;
	char star_char;
	int cmp;
	int occurance;
	fprintf(output_file,"Occurrences:");
	while(star_pos<strlen(text))
	{
		//TODO find index of occurances
		if(matches==strlen(pattern))
		{
				fprintf(output_file,"%d,",index);
				//TODO
		}
	}
	fprintf(output_file,"\n");
	fprintf(output_file,"Comparisons:%d\n\n",cmp);
	return cmp;
}

void print_table(int* shift_table, FILE* output_file)
{
	fprintf(output_file,"BCST:\n");
	for(int i=0;i<26;i++)
	{
		fprintf(output_file,"%c:%d",(char)(i+97), shift_table[i]);
	}
}

void testcase(FILE* values_file, FILE* input_file, FILE* output_file)
{
	char text[2000];
	char pattern[100];
	fscanf(input_file,"%s",text);
	fscanf(input_file,"%s",pattern);

	int* shift_table=calloc(26,sizeof(int));
	init_table(shift_table,strlen(pattern));
	preprocess(shift_table,pattern);
	print_table(shift_table, output_file);
	clock_t start = clock();
	int cmp = string_match(shift_table,pattern,text,output_file);
	clock_t end = clock();
	int elapse=(int)(((double)(end-start))/CLOCKS_PER_SEC*1000000000); //seconds to nanoseconds
	fprintf(values_file,"%ld,%ld,%d,%d\n",strlen(pattern),strlen(text),cmp,elapse);
}

int main()
{	
	FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("horspool_output.txt", "w");
    FILE *values_file = fopen("horspool_values.txt", "w");

    if (!input_file || !output_file || !values_file) {
        printf("Error opening file!\n");
        return 1;
    }
    int testcases;
	fscanf(input_file,"%d",&testcases);
	int count = 0;
	fprintf(values_file, "patternlen,textlen,cmp,timetaken\n");
	while(count < testcases)
	{
		testcase(values_file, input_file, output_file);
		count += 1;
	}
	fclose(input_file);
	fclose(output_file);
	fclose(values_file);
	return 0;
}

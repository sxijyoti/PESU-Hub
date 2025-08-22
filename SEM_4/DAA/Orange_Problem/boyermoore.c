#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/time.h>
#include<time.h>

// Fill in the TODO sections as required and DO NOT TOUCH any of the fprintf statements

// Function to create the Bad Character Shift Table
int* bcst_create(const char* pattern, int pattern_len) {
    // TODO BCST creation
    int* bcst = (int*)malloc(26 * sizeof(int));
    if (bcst == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 26; i++) {
        bcst[i] = pattern_len;
    }
    
    for (int i = 0; i < pattern_len - 1; i++) {
        if (pattern[i] >= 'a' && pattern[i] <= 'z') {
            bcst[pattern[i] - 'a'] = pattern_len - i - 1;
        }
    }
    return bcst;
}

// Function to create the Good Suffix Shift Table
int* gsst_create(const char* pattern, int pattern_len) {
    int* gsst = (int*)malloc((pattern_len + 1) * sizeof(int));
    if (gsst == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int x = 1; x <= pattern_len; x++) {
        int r2 = 0;
        char* suffix = (char*)malloc((x + 1) * sizeof(char));
        if (suffix == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
		for(int i=0;i<x;i++)
		{
			suffix[x-i-1] = pattern[pattern_len-i-1];
		}
		suffix[x] = '\0';

		char mis_char = (pattern_len - x - 1 >= 0) ? pattern[pattern_len - x - 1] : '~';

        char* rev_pattern = (char*)malloc(pattern_len * sizeof(char));
        if (rev_pattern == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for(int i=0;i<pattern_len-1;i++)
			rev_pattern[i] = pattern[pattern_len-i-2];
        rev_pattern[pattern_len-1] = '\0';

        char* rev_suffix = (char*)malloc((x + 1) * sizeof(char));
        if (rev_suffix == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for(int i=0;i<x;i++)
			rev_suffix[i] = suffix[x-i-1];
        rev_suffix[x] = '\0';

        int count = 0;
        while (1) {
            char* pos_ptr = strstr(rev_pattern, rev_suffix);
            if (pos_ptr == NULL) {
                r2 = 1;
                break;
            }
            int pos = pos_ptr - rev_pattern;
            char check_char = (pos + x < pattern_len - 1) ? rev_pattern[pos + x] : '`';
            if (check_char != mis_char) {
                gsst[x] = pos + count + 1;
                break;
            }
            rev_pattern += pos + 1;
            count += pos + 1;
        }

		char* suffix_ptr = suffix;
        if (r2) {
            char* prefix = (char*)malloc(pattern_len * sizeof(char));
            if (prefix == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < pattern_len; i++) {
                prefix[i] = pattern[i];
            }
            prefix[pattern_len] = '\0';
            while (1) {
                if (strlen(suffix) == 1) {
                    gsst[x] = pattern_len;
                    break;
                }
                suffix++;
                if (strncmp(prefix, suffix, strlen(suffix)) == 0) {
                    gsst[x] = pattern_len - strlen(suffix);
                    break;
                }
            }
            //free(prefix);
        }
        //free(suffix_ptr);
        //free(rev_suffix);
        //free(rev_pattern);
    }
    return gsst;
}

// Boyer-Moore search function
int boyer_moore(const char* text, const char* pattern, int* bcst, int* gsst, FILE* output_file) 
{
    // TODO variables initializations

	int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int pos = 0;
    int comparisons = 0;

	fprintf(output_file,"Occurrences:");
    while (pos <= text_len - pattern_len) {
        // TODO find indices of occurances
        int match = 0;
        int j = pattern_len - 1;
        int end = pos + pattern_len - 1;
        
        while (j >= 0 && pattern[j] == text[pos + j]) {
            match++;
            j--;
            comparisons++;
        }
        
        if (match == pattern_len) {
            fprintf(output_file,"%d,", end - pattern_len + 1);
            // TODO
            pos += (pattern_len > 1) ? gsst[1] : 1;
        } else {
            comparisons++;
            int bc_shift = 0;
            if (text[pos + j] >= 'a' && text[pos + j] <= 'z') {
                bc_shift = bcst[text[pos + j] - 'a'] - (pattern_len - 1 - j);
            } else {
                bc_shift = pattern_len - (pattern_len - 1 - j);
            }
            
            int gs_shift = 0;
            if (j < pattern_len - 1) {
                gs_shift = gsst[pattern_len - j - 1];
            } else {
                gs_shift = 1;
            }
            
            pos += (bc_shift > gs_shift) ? bc_shift : gs_shift;
            if (bc_shift <= 0 && gs_shift <= 0) pos++;
        }
    }
    fprintf(output_file,"\n");
    return comparisons;
}
void testcase(FILE* values_file, FILE* input_file, FILE* output_file)
{
	char text[2000];
    char pattern[500];
    fscanf(input_file,"%s",text);
    fscanf(input_file,"%s",pattern);


    int pattern_len = strlen(pattern);
    int* bcst = bcst_create(pattern, pattern_len);
    fprintf(output_file,"BCST:\n");
    for(int i = 0; i < 26; i++){
		fprintf(output_file,"%c:%d, ", (char)(i+'a'), bcst[i]);
    }
    fprintf(output_file,"\n");

    int* gsst = gsst_create(pattern, pattern_len);
    fprintf(output_file,"GSST:\n");
    for(int i = 1; i <= pattern_len; i++){
        fprintf(output_file,"%d:%d, ", i, gsst[i]);
    }
    fprintf(output_file,"\n");

    clock_t start = clock();
    int comparisons = boyer_moore(text, pattern, bcst, gsst, output_file);
    fprintf(output_file,"Comparisons:%d\n\n", comparisons);

    free(bcst);
    free(gsst);
	clock_t end = clock();
	int elapse=(int)(((double)(end-start))/CLOCKS_PER_SEC*1000000000); //seconds to nanoseconds
	fprintf(values_file,"%d,%ld,%d,%d\n",pattern_len,strlen(text),comparisons,elapse);
}

int main() {
	FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("boyermoore_output_SRN.txt", "w");
    FILE *values_file = fopen("boyermoore_values_SRN.txt", "w");

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
		testcase(values_file,input_file, output_file);
		count += 1;
	}
	fclose(input_file);
	fclose(output_file);
	fclose(values_file);
    return 0;
}

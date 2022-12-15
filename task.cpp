#include "include.h"

global char SEQUENCE_A[] = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG";

internal size_t
read_until(const char *s, char *val, char delimiter)
{
	assert_p(s   != NULL, "String is NULL: line %d in file %s\n", __LINE__, __FILE__);
	assert_p(val != NULL, "String is NULL: line %d in file %s\n", __LINE__, __FILE__);

	size_t length = 0;
	while (s[length] != delimiter && s[length] != '\0')
	{
		length++;
	}
    
	for (size_t i = 0; i < length; i++)
	{
		val[i] = s[i];
	}
    
	return length;
}

int
main(void)
{
    
	const char cpath[] = "../../../s_3_sequence_1M.txt/s_3_sequence_1M.txt";
    
	LPWSTR path = (LPWSTR)malloc(sizeof(cpath) * sizeof(char));
    
	for (int i = 0; i < sizeof(cpath); i++)
	{
		path[i] = cpath[i];
	}
    
	//assert_p( 2 == 2, "Unexpected result, wanted to find: %d\n", 1 );
    
	Sequence Task1((LPCWSTR)path, SEQUENCE_A);

	char* common_substrings = (char *)VirtualAlloc(NULL, (size_t)1 << 20,
	                                               MEM_COMMIT | MEM_RESERVE,
	                                               PAGE_READWRITE);
	
	
	assert_p(common_substrings != NULL, "Allocation error in line %d", __LINE__);
    
	char* sequence_substring = (char *)VirtualAlloc(NULL, (size_t)1 << 20,
	                                                MEM_COMMIT | MEM_RESERVE,
	                                                PAGE_READWRITE);

	assert_p(sequence_substring != NULL, "Allocation error in line %d", __LINE__);

	global_matrix = (int *)VirtualAlloc(NULL, (size_t)1 << 30,
	                                    MEM_COMMIT | MEM_RESERVE,
	                                    PAGE_READWRITE);

	assert_p(global_matrix != NULL, "Allocation error in line %d", __LINE__);

	size_t i = 0;
	while (i < Task1.buffer_size) 
	{
        
		size_t set_length = read_until(Task1.sequence_set + i,
		                               sequence_substring, '\n');
        
		//LCS(sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
		
		ED(sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
		int size = ED_Backtrack(common_substrings, sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
		
#if 1
		printf("Sequence from file  : %s\n", sequence_substring);
		printf("Preffix subsequence : %s\n", Task1.sequence_suffix);
		printf("ED Matrix: \n");
		printf("====================================================================\n");
		int *row = global_matrix_struct.start;

		for (size_t n = 0; n <= set_length; n++) 
		{
			for (size_t m = 0; m <= Task1.suffix_size; m++)
			{
				if (m == Task1.suffix_size)
					printf("%0.2d", *(row + m));
				else
					printf("%0.2d,", *(row + m));
			}
			printf("\n");
			row += Task1.suffix_size+1;
		}

		printf("====================================================================\n");

		printf("Common substring  : %s\n", common_substrings);
		printf("Size of common    : %d\n", size);
		printf("====================================================================\n");

		break;
#endif
		/*
		GA (sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
		LA (sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
        */
		i += set_length + 1;
	}
    
	VirtualFree(common_substrings,  2 << 20, MEM_RELEASE);
	VirtualFree(sequence_substring, 2 << 20, MEM_RELEASE);
	VirtualFree(sequence_substring, 1 << 30, MEM_RELEASE);
	VirtualFree(global_matrix,      1 << 30, MEM_RELEASE);

	return 0;
}
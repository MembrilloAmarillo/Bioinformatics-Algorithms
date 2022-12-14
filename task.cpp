#include "include.h"

global char SEQUENCE_A[] = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG";

internal size_t
read_until(const char *s, char *val, char delimiter)
{
	assert_p(s != NULL, "String s is NULL\n");
	assert_p(val != NULL, "String val is NULL\n");

	size_t length = 0;
	while (s[length] != delimiter && s[length] != '\0')
	{
		length++;
	}
    
	for (int i = 0; i < length; i++)
	{
		val[i] = s[i];
	}
    
	return length;
}

int
main(void)
{
    
	const char cpath[] = "../../s_3_sequence_1M.txt/s_3_sequence_1M.txt";
    
	LPWSTR path = (LPWSTR)malloc(sizeof(cpath) * sizeof(char));
    
	for (int i = 0; i < sizeof(cpath); i++)
	{
		path[i] = cpath[i];
	}
    
	//assert_p( 2 == 2, "Unexpected result, wanted to find: %d\n", 1 );
    
	Sequence Task1((LPCWSTR)path, SEQUENCE_A);
    
	char* common_substrings = (char *)VirtualAlloc(NULL, (size_t)2 << 20,
	                                               MEM_COMMIT | MEM_RESERVE,
	                                               PAGE_READWRITE);

	assert_p(common_substrings != NULL, "Allocation error in line %d", __LINE__);
    
	char* sequence_substring = (char *)VirtualAlloc(NULL, (size_t)2 << 20,
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
        
		LCS(sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
#if 0
		printf("Sequence from file: %s\n", sequence_substring);
		printf("Preffix subsequence: %s\n", Task1.sequence_suffix);
		printf("LCS Matrix: \n");
		printf("====================================================================\n");
		int *row = global_matrix;
		for (int n = 0; n < set_length; n++) 
		{
			for (int m = 0; m < Task1.suffix_size; m++)
			{
				printf("%d,", *(row + m));
			}
			printf("\n");
			row += Task1.suffix_size;
		}

		printf("====================================================================\n");

		break;
#endif

		ED (sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
		GA (sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
		LA (sequence_substring, Task1.sequence_suffix, set_length, Task1.suffix_size);
        
		i += set_length + 1;
	}
    
	VirtualFree(common_substrings, 2 << 20, MEM_RELEASE);
	VirtualFree(sequence_substring, 2 << 20, MEM_RELEASE);
	VirtualFree(sequence_substring, 1 << 30, MEM_RELEASE);
    
	return 0;
}
internal int 
__MAX(int a, int b, int c)
{
    if (a >= b)
        if (a >= c)
        	return a;
   		else
        	return c;
	else 
		if (b >= c) 
        	return b;
    	else
        	return c; 
}

internal int
__MIN(int a, int b, int c)
{
	if (a < b)
		if (a < c)
        	return a;
    	else
        	return c;
	else
		if (b < c)
        	return b;
    	else
        	return c;
}

#define MAX(a, b, c) __MAX(a, b, c)
#define MIN(a, b, c) __MIN(a, b, c)

internal size_t
my_strlen( const char *s )
{
    
    assert_p( s != NULL, "NULL string in file %s on line %d", __FILE__, __LINE__  );
    
    size_t i = 0;
    
    while( s[i] != '\0' )
    {
        i++;
    }
    
    return i;
}

internal size_t
LCS_f( int s, int r ) 
{
	return s == r ? 1 : 0;
}

internal size_t
ED_f(int s, int r)
{
	return s == r ? 0 : 1;
}

/* Longest Common Subsequence */
internal void 
LCS( const char* S, const char* R, size_t SL, size_t RL ) 
{
	int *row = global_matrix;
    
	global_matrix_struct.start = row;
    
	for (size_t n = 0; n < SL; n++)
	{
		*row = 0;
		row += RL;
	}
    
	row = global_matrix;
	for (size_t n = 0; n < RL; n++)
	{
		*row = 0;
		row += n;
	}
    
	row = global_matrix + RL;
	for (size_t n = 1; n < SL; n++)
	{
		for (size_t m = 1; m < RL; m++) 
		{
			int *val = (row + m);
			int *val_izq = (row + m - 1);
			int *val_up  = (row + m - RL);
			int *val_dia = (row - RL + m - 1);
            
			*val = MAX(*val_izq, 
                       *val_up, 
                       *val_dia + LCS_f(S[n], R[m]) 
                       );
		}
        
		row += RL;
	}
    
	global_matrix_struct.end = row - 1;
}

/* Edit Distance */
internal void 
ED( const char* S, const char* R, size_t SL, size_t RL )
{
	int *row = global_matrix;
    
	global_matrix_struct.start = row;
    
	for (size_t n = 0; n <= SL; n++)
	{
		*row = n;
		row += RL + 1;
	}
    
	row = global_matrix;
    
	for (size_t n = 0; n <= RL; n++)
	{
		row[n] = n;
	}
    
	row = global_matrix + RL + 1;
	for (size_t n = 1; n <= SL; n++)
	{
		for (size_t m = 1; m <= RL; m++) 
		{
			int *val = (row + m);
			int *val_izq = (row + m - 1);
			int *val_up  = (row - RL + m );
			int *val_dia = (row - RL + m - 1);
            
			*val = MIN(*val_izq + 1, 
			           *val_up  + 1, 
			           *val_dia + ED_f(S[n-1], R[m-1]) 
			           );
		}
        
		row += RL + 1;
	}
    
	global_matrix_struct.end = row - 1;
}

/* Global Alignment */
internal void 
GA( const char* S, const char* R, size_t SL, size_t RL )
{
    (void)S;
    (void)R;
}

/* Local Alignment */
internal void 
LA( const char* S, const char* R, size_t SL, size_t RL )
{
    (void)S;
    (void)R;
}

internal int
ED_Backtrack( char* common, const char* S, const char* R, size_t SL, size_t RL )
{
	// Start of last row
	int *row = global_matrix_struct.end - RL;
	int i = SL - 1;
	int j = RL - 1;
	int idx = 0;
    
	while( i >= 0 && j >= 0 )
	{
		//int *val     = row + j;
		int *val_izq = (row + j);
		int *val_up  = (row + j - RL);
		int *val_dia = (row - RL + j);
        
		if (S[j] != R[i])
		{
			if (val_izq <= val_up)
			{
				// Left
				printf("Row: %0.2d, Col: %0.2d\n, Val: Left\n", i, j );
				common[idx] = '-';
				j--;
			}
			else
			{
				if (val_dia <= val_up)
				{
					printf("Row: %0.2d, Col: %0.2d\n, Val: Diagonal\n", i, j );
					common[idx] = '\\';
					// Go diagonal
					row -= RL;
					j--;
					i--;
				}
				else
				{
					printf("Row: %0.2d, Col: %0.2d\n, Val: Up\n", i, j );
					// Up
					common[idx] = '|';
					row -= RL;
					i--;
				}
			}
		}
		else
		{
			printf("Row: %0.2d, Col: %0.2d\n, Val: Diagonal e\n", i, j );
			// Go diagonal
			common[idx] = S[i];
			row -= RL;
			j--;
			i--;
		}
		idx++;
	}
	return idx;
}
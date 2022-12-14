internal int 
MAX(int a, int b, int c)
{
	if (a >= b) {
		if (a >= c)
		{
			return a;
		}
		else
		{
			return c;
		}
	}
	else 
	{
		if (b >= c) 
		{
			return b;
		} 
		else
		{ 
			return c; 
		}
	}
}


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

internal void 
LCS( const char* S, const char* R, size_t SL, size_t RL ) 
{
	int *row = global_matrix;

	for (int n = 0; n < SL; n++)
	{
		*row = 0;
		row += RL;
	}

	row = global_matrix;
	for (int n = 0; n < RL; n++)
	{
		*row = 0;
		row += n;
	}

	row = global_matrix + RL;
	for (int n = 1; n < SL; n++)
	{
		for (int m = 1; m < RL; m++) 
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
}

internal void 
ED( const char* S, const char* R, size_t SL, size_t RL )
{
    (void)S;
    (void)R;
}

internal void 
GA( const char* S, const char* R, size_t SL, size_t RL )
{
    (void)S;
    (void)R;
}

internal void 
LA( const char* S, const char* R, size_t SL, size_t RL )
{
    (void)S;
    (void)R;
}
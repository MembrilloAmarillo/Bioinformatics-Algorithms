

/*NOTE: Helper function to display error*/
internal 
void DisplayError(LPTSTR lpszFunction) 
// Routine Description:
// Retrieve and output the system error message for the last-error code
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 
    
    FormatMessage(
                  FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  dw,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR) &lpMsgBuf,
                  0, 
                  NULL );
    
    lpDisplayBuf = 
    (LPVOID)LocalAlloc( LMEM_ZEROINIT, 
                       ( lstrlen((LPCTSTR)lpMsgBuf)
                        + lstrlen((LPCTSTR)lpszFunction)
                        + 40) // account for format string
                       * sizeof(TCHAR) );
    
    auto ret_val = StringCchPrintf((LPTSTR)lpDisplayBuf, 
                                   LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                                   TEXT("%s failed with error code %d as follows:\n%s"), 
                                   lpszFunction, 
                                   dw, 
                                   lpMsgBuf);
    
    if (FAILED( ret_val ) )
    {
        printf("FATAL ERROR: Unable to output error code.\n");
    }
    
    _tprintf(TEXT("ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);
    
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

// ------------------------------------------------------------------------------------------------------- //

Sequence::Sequence( LPCWSTR path_file, const char* suffix )
{
	suffix_size = my_strlen( suffix );

	sequence_suffix = (char*)VirtualAlloc( NULL, suffix_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );

	memmove(sequence_suffix, suffix, suffix_size * sizeof(char));
    
    file_handler = CreateFileW( 
                               path_file,
                               GENERIC_READ, FILE_SHARE_READ, NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                               NULL );
    OVERLAPPED ol = {0};
    buffer_size = GetFileSize( file_handler, NULL );
    
    if ( file_handler == INVALID_HANDLE_VALUE ) 
    { 
        DisplayError(TEXT("CreateFile"));
        printf("Terminal failure: unable to open file \"%ls\" for read.\n", path_file );
        exit(1); 
    }
    sequence_set = (char*)VirtualAlloc( NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
    
    /*TODO: Check if conversion from size_t to DWORD can be a problem*/
    if( !ReadFileEx( file_handler, sequence_set, (DWORD)buffer_size, &ol, NULL ) )
    {
        DisplayError(TEXT("ReadFile"));
        printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
        VirtualFree(sequence_set, buffer_size, MEM_RELEASE);
		VirtualFree(sequence_suffix, suffix_size, MEM_RELEASE);
		exit(1);
    }
    
}

Sequence::~Sequence()
{
    if ( sequence_set != NULL )
        VirtualFree(sequence_set, buffer_size, MEM_RELEASE);
	if (sequence_suffix != NULL)
		VirtualFree(sequence_suffix, suffix_size, MEM_RELEASE);

    CloseHandle( file_handler );
}
/* date = December 13th 2022 10:32 pm */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#define assert_p( pred, string, ... )  do { \
if( pred == false ) {\
printf( string, __VA_ARGS__ );  exit(1);\
}\
} while( 0 ); \

internal size_t
my_strlen( const char *s );

internal void 
LCS( const char* S, const char* R, size_t SL, size_t RL );

internal void 
ED( const char* S, const char* R, size_t SL, size_t RL );

internal void 
GA( const char* S, const char* R, size_t SL, size_t RL );

internal void 
LA( const char* S, const char* R, size_t SL, size_t RL );

internal void
ED_Backtrack(char* common, const char* S, const char* R, size_t SL, size_t RL);

#endif //ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define POSITIVE 1
#define NEGATIVE -1
#define DOMAIN 100

void Ex1();
void input_array_dyn( int **, unsigned int );
void print_array( int *, unsigned int );
void swap( int *, int * );
char is_odd( int );
void split( int *, unsigned int );
void Ex2();
long sum_digits( unsigned long int, long int );
char is_div_by_11( long int );
void Ex3();
void merge_sort( int *, int, int );
void merge( int *, int, int, int );
int* intersect_array( int *, unsigned int, int *, unsigned int, unsigned int * );
void Ex4();
char premutation( int *, int *, unsigned int );
char premutationA( int *, int *, unsigned int );
char is_array_equal( int *, int *, unsigned int );
char premutationB( int *, int *, unsigned int );
int index_of( int *list, unsigned int size, int key );
char premutationC( int *, int *, unsigned int );
void Ex5();
void remove_char( char * str, char ch );
char* input_string( void );

void main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf( "Run menu once or cyclycally?\n(Once - enter 0, cyclically - enter other number) " );
	if( scanf( "%d", &all_Ex_in_loop ) == 1 )
		do
		{
			for( i = 1; i <= 5; i++ )
				printf( "Ex%d--->%d\n", i, i );
			printf( "EXIT-->0\n" );
			do
			{
				select = 0;
				printf( "Please select 0-5: " );
				scanf( "%d", &select );
			} while( ( select < 0 ) || ( select > 5 ) );
			switch( select )
			{
				case 1:
					Ex1();
					break;
				case 2:
					Ex2();
					break;
				case 3:
					Ex3();
					break;
				case 4:
					Ex4();
					break;
				case 5:
					Ex5();
					break;
			}
		} while( all_Ex_in_loop && select );
	system( "pause" );
}

void Ex1()
{
	/*
	define pointer to array of int and size.
	gets from user natural number as size of the array.
	gets from user array elements.
	rearanges the array by following rule odd numbers in the beginning.
	prints the results.
	frees the dinamicly allocated array.
	*/
	int *list, size;
	do
	{
		size = 0;
		printf( "Enter size of array: " );
		scanf( "%d", &size );
		getchar();
	} while( size <= 0 );
	input_array_dyn( &list, ( unsigned int )size );
	split( list, size );
	printf( "The new array is:\n" );
	print_array( list, size );
	free( list );
}
void input_array_dyn( int **pa, unsigned int size )
{
	/*
	allocates dynamic array with given size
	with input from user.
	updeting the pointer pa to new array.
	*/
	unsigned int index;
	*pa = ( int * )malloc( size * sizeof( int ) );
	if( pa )
	{
		printf( "Enter the array of length %u:\n", size );
		for( index = 0; index < size; index++ )
		{
			do
			{
				printf( "Enter element (%u of %u): ", index + 1, size );
			} while( ( ( scanf( "%d", (*pa) + index ) ) != 1 ) && getchar() );
		}
	}
}
void print_array( int *list, unsigned int size )
{
	// helper function to print array of type int.
	unsigned int index;
	for( index = 0; index < size; index++ )
		printf( "%d ", *( list + index ) );
	printf( "\n" );
}
void swap( int *x, int *y )
{
	// helper function to swap x with y.
	int temp = *x;
	*x = *y;
	*y = temp;
}
char is_odd( int number )
{
	// helper function, returns TRUE if the given number is odd, FALSE overwise.
	if( number % 2 )
		return TRUE;
	return FALSE;
}
void split( int *list, unsigned int size )
{
	// function to logically split given array into two sub-array, odd elements in the head of the array
	unsigned int i, last = 0;
	for( i = 1; i < size; i++ )
		if( is_odd( list[ i ] ) )
			swap( list + ( last++ ), list + i );
}
void Ex2()
{
	/*
	function to check divisibilty of positive number by 11.
	gets from user positive number check with is_div_by_11 and prints message according to the result.
	*/
	long int number;
	char *result = "not ", *blank = "";
	do
	{
		number = 0;
		printf( "Enter positive number: " );
		scanf( "%ld", &number );
		getchar();
	} while( number <= 0 );
	if( is_div_by_11( number ) )
		result = blank;
	printf( "The number %ld is %sdivisible by 11.\n", number, result );
}
long sum_digits( unsigned long int number, long int sign )
{
	/*
	function to sum given number digit while switching sign every other digit.
	if the number greater than 9 return the sum of current digit + sum_digits of the number with opposite sign without current digit.
	else rerutn the number itself.
	*/
	if( number > 9 )
		return sign * ( number % 10 ) + sum_digits( number / 10, sign * NEGATIVE );
	return sign * number;
}
char is_div_by_11( long int number )
{
	/*
	function receives positive number sum it's digits with sum_digits function untill the result is single digit.
	makes sure that the sum of digits is in its absolute value.
	if the result is 0 the number is divisable by 11 return non-0 value
	else return 0.
	*/
	while( number > 9 )
	{
		number = sum_digits( ( unsigned long int )number, POSITIVE );
		number = ( number < 0 ? number * NEGATIVE : number );
	}
	return !number;  // 0 is divisible by 11 => !0 is TURE.
}
void Ex3()
{
	/*
	define pointer to three arrays A, B, and their intersect of int and size.
	gets from user natural number as size of the arrays.
	gets from user array elements.
	sorts both arrays with merge sort.
	populating intersect pointer with array to intersection of both arrays.
	prints the results.
	frees the dinamicly allocated array.
	*/
	int *A, *B, *A_intersect_B;
	unsigned int sizeA, sizeB, size;
	do
	{
		sizeA = 0;
		printf( "Enter size of array A: " );
		scanf( "%d", &sizeA );
		getchar();
	} while( sizeA <= 0 );
	input_array_dyn( &A, ( unsigned int )sizeA );
	do
	{
		sizeB = 0;
		printf( "Enter size of array B: " );
		scanf( "%d", &sizeB );
		getchar();
	} while( sizeB <= 0 );
	input_array_dyn( &B, ( unsigned int )sizeB );
	merge_sort( A, 0, sizeA - 1 );
	merge_sort( B, 0, sizeB - 1 );
	A_intersect_B = intersect_array( B, sizeB, A, sizeA, &size );
	if( size < 1 )
		printf( "A and B are disjoint\n" );
	else
	{
		printf( "The intersection of A, and B is:\n" );
		print_array( A_intersect_B, size );
	}
	free( A_intersect_B );
}
void merge_sort( int *a, int first, int last )
{
	// standard merge_sort function.
	int middle;
	if( first < last )
	{
		middle = ( first + last ) / 2;
		merge_sort( a, first, middle );
		merge_sort( a, middle + 1, last );
		merge( a, first, middle, last );
	}
}
void merge( int *a, int first, int middle, int last )
{
	// standard merge function.
	int i = first, j = middle + 1, k = 0;
	int* temp = ( int* )malloc( ( last - first + 1 ) * sizeof( int ) );
	while ( ( i <= middle ) && ( j <= last ) )
		if( a[ i ] < a[ j ] )
			temp[ k++ ] = a[ i++ ];
		else
			temp[ k++ ] = a[ j++ ];
	while( j <= last ) // if( i>middle )
		temp[ k++ ] = a[ j++ ];
	while( i <= middle ) // j>last
		temp[ k++ ] = a[ i++ ];

	for( i = first, k = 0; i <= last; i++, k++ ) // copy temp[] to a[]
		a[ i ] = temp[ k ];
	free( temp );
}
int* intersect_array( int *A, unsigned int sizeA, int *B, unsigned int sizeB, unsigned int *size )
{
	/*
	function to build array which is intersection of given two arrays.
	the function required arrays A, and B to be sorted.
	the function using modified merge algorithem to achieve its task.
	in brief: advancing two pointers on both array until match of elements is found and stores it in new array.
	return pointer to new array.
	*/
	unsigned int temp_size = ( sizeA < sizeB ? sizeA : sizeB );
	unsigned int indexA = 0, indexB = 0, index = 0;
	int *result = ( int* )malloc( temp_size * sizeof( int ) );
	while( ( indexA < sizeA ) && ( indexB < sizeB ) )
	{
		if( A[ indexA ] == B[ indexB ] )
		{
			result[ index++ ] = B[ indexB++ ];
			indexA++;
		}
		while( A[ indexA ] < B[ indexB ] )
			indexA++;
		while( B[ indexB ] < A[ indexA ] )
			indexB++;
	}
	*size = index;
	result = ( int* )realloc( result, *size * sizeof( int ) );
	return result;
}
void Ex4()
{
	/*
	funciont to get two array from user and their size.
	print the result of premutation test.
	*/
	int *A, *B;
	unsigned int size;
	do
	{
		size = 0;
		printf( "Enter size for both arrays A, and B: " );
		scanf( "%d", &size );
		getchar();
	} while( size <= 0 );
	input_array_dyn( &A, ( unsigned int )size );
	input_array_dyn( &B, ( unsigned int )size );
	printf( "A and B is premutation group? %s.\n", ( premutation( A, B, size ) ? "True" : "False" ) );
}
char premutation( int *A, int *B, unsigned int size )
{
	/*
	helper function to allow user to choose algorithem to test premutation group.
	the function receives two arrays and their size, interactivally gets from user algorithem to use.
	prints a brief description of selected algorithem, and
	returns the result of premutation test.
	'*/
	int i, select;
	char result;
	for( i = 0; i < 3; i++ )
		printf( "Ex4.%c--->%d\n", i + 'a', i + 1 );
	do
	{
		select = 0;
		printf( "Please select 0-3: " );
		scanf( "%d", &select );
	} while( ( select < 0 ) || ( select > 3 ) );
	switch( select )
	{
		case 1:
			printf( "First algoritherm, uses merge-sort and simple array comparison.\n" );
			result = premutationA( A, B, size );
			break;
		case 2:
			printf( "Second algoritherm, uses recursion and swap with index of.\n" );
			result = premutationB( A, B, size );
			break;
		case 3:
			printf( "Third algoritherm, static counter arrary of %d size.\n", DOMAIN );
			result = premutationC( A, B, size );
			break;
	}
	return result;
}
char premutationA( int *a, int *b, unsigned int size )
{
	/*
	first algorithem of premutation test.
	sorts both array with merge sort.
	returns result of symetricity test.
	*/
	merge_sort( a, 0, size - 1 );
	merge_sort( b, 0, size - 1 );
	return is_array_equal( a, b, size );
}
char is_array_equal( int *A, int *B, unsigned int size )
{
	/*
	helper function to check if two given arrays of same size are equal.
	equral definition: each element at the same index are equal.
	*/
	unsigned int index;
	for (index = 0 ; index < size ; index++)
		if (A[index]!=B[index])
			return FALSE;
	return TRUE;
}
char premutationB( int *A, int *B, unsigned int size )
{
	/*
	second algorithem for premutation test.
	using recursion, if first elements are equal advance to smaller arrays.
	if not equal, find with helper function index of the index of current element at array A,
	and swap. if not found return FALSE
	*/
	int exists;
	if( size == 1 )
		return A[ 0 ] == B[ 0 ] ? TRUE : FALSE;
	if( A[ 0 ] != B[ 0 ] )
	{
		exists = index_of( B + 1, size - 1, A[ 0 ] ) + 1;
		printf( "%d", exists );
		if( exists == NEGATIVE ) // key not found in array B
			return FALSE;
		swap( B, B + exists );
	}
	return premutationB( A + 1, B + 1, size - 1 );
}
int index_of( int *list, unsigned int size, int key )
{
	/*
	helper function to find key in unsorted array,
	returns the index of the key if found,
	else return -1.
	*/
	unsigned int index;
	for( index = 0; index < size; index++ )
		if( list[ index ] == key )
			return index;
	return NEGATIVE;
}
char premutationC( int *A, int *B, unsigned int size )
{
	/*
	third algorithem for premutation test.
	on first run count elemets in predefined DOMAIN the apperances of values
	of first array and substruct apperances of values of second array.
	on second run check the count array if one of the counters not equals to 0 return FALSE
	*/
	int count_array[ DOMAIN + 1 ] = { 0 };
	unsigned int index;
	for( index = 0; index < size; index++ )
	{
		count_array[ A[ index ] ]++;
		count_array[ B[ index ] ]--;
	}
	for( index = 1; index < DOMAIN + 1; index++ )
		if( count_array[ index ] != 0 )
			return FALSE;
	return TRUE;
}
void Ex5()
{
	/*
	function gets from user string and a character to remove from the string
	prints the new string without the character requested to be removed.
	*/
	char *string;
	char note;
	getchar(); // clear last char from stdin
	string = input_string();
	printf( "Please enter a note that you want to remove from string: " );
	scanf( "%c", &note );
	remove_char( string, note );
	printf( "The new string is: %s\n", string );
	free( string );
}
char* input_string(void)
{
	// helper function to get string from user.
	char tempstr[80], *longnum;
	printf("Enter a string: ");
	gets(tempstr);
	longnum=(char*)malloc((strlen(tempstr)+1)*sizeof(char));
	strcpy(longnum,tempstr);
	return longnum;
}
void remove_char( char * str, char note )
{
	/*
	function receives dynamiclly alocated array and character, and removes the character from array.
	function advancing in the array. 
	if the character in the current index is the character that need to be remove, count it. 
	else move the character left according to the count til this position.
	function count how many character needs to be removed from the array and change the size of the array 
	*/
	int size_of_string = strlen( str );
	int count = 0, index;
	for( index = 0; index < size_of_string; index++ )
	{
		if( str[ index ] == note )
			count++ ;
		else
			str[ index - count ] = str[ index ];
	}
	str[ size_of_string - count ] = '\0';
	str = ( char* )realloc( str, ( size_of_string - count + 1 ) * sizeof( char ) );
}
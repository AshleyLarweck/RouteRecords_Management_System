/*
main.c
Project 2
Ashley Larweck
File opens/reads "passenger-data.csv", checks command line argument, call functions to load, fill, count data. Asks for user input, handles cases of invalid entry and escape option.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "RouteRecords.h"

int main(int argc, char *argv[])
{

	FILE * fileIn;
	printf( "Opening passenger-data.csv... \n" );
	fileIn = fopen( argv[1] , "r" );

	if ( fileIn == NULL )
	{
		printf( "Error: Missing file name\n" );
		return 1;
	}

	RouteRecord * r;
	r = createRecords( fileIn );

	int Length;
	Length = fillRecords( r , fileIn );

	int i;
	int checker;
	char key1[5];
	char key2[5];
	SearchType st = 0;

	printMenu();
	int searchKind = 0;
	char buffer[500];

	while ( st != 5 )
	{
		checker = scanf( "%d" , &st );
		while ( checker == 0 )
		{
			printf( "Invalid input.\n" );
			fgets( buffer, 500, stdin );
			printMenu();
			checker = scanf( "%d" , &st );
		}

		switch ( st )
		{
			case 1:
				printf( "Enter the origin: ");
				scanf( "%s", key1 );
				printf( "Enter the destination: " );
				scanf( "%s" , key2 );
				break;

			case 2:
				printf( "Enter the origin: " );
				scanf( "%s" , key1 );
				break;

			case 3:
				printf( "Enter the destination: " );
				scanf( "%s" , key1 );
				break;

			case 4:
				printf( "Enter the airline: " );
				scanf( "%s" , key1 );
				break;

			case 5:
				printf( "Good-bye!\n" );
				break;

			default:
				printf( "Invalid choice.\n" );
				break;
		}

		searchRecords( r , Length , key1 , key2 , st );
		printMenu();
	}

	return 0;
}

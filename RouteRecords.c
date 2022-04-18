/*
RouteRecords.c
Project 2
Ashley Larweck
File contains functions that open/parses, load, fill, counts data in "passenger-data.csv". File isolates all duplicate lines, stores unique file lines in array. Depending on user input specified in main, user will be prompted to enter appropriate key, which will then display a set of statistics specific to the selection.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RouteRecords.h"

/*
Function: RouteRecord* createRecords
-------------------
Creates the array of RouteRecord’s and initializes it. Parses entire file and counts the total number of flights. Dynamically allocates memory for array of RouteRecords based on this count.
FILE *fileIn: pointer to input file.
Returns: pointer to the dynamically allocated array.
*/
RouteRecord* createRecords(FILE *fileIn)
{
	char buffer[500];
	int n = 0;

	while ( fgets( buffer , 500 , fileIn) != NULL )
	{
		n++;
	}

	n--;

	RouteRecord *Flights = ( RouteRecord* )malloc( ( n ) *sizeof( RouteRecord ) );

	struct RouteRecord arr_RouteRecord[6] = { 0 , 0 , 0 , 0 , 0 , 0 };
	rewind( fileIn );
	return Flights;
}

/*
Function: fillRecords
-------------------
Processes the data in the CSV file. Stores this data in an array. Calls findAirlineRoute() to further parse/process data. Stores unique flights in array.
RouteRecord *r : pointer to RouteRecord array.
FILE *inputFile: pointer to input file.
Returns: the actual number of RouteRecord’s used in the array. 
*/
int fillRecords( RouteRecord *r , FILE *inputFile )
{
	int month , length , i , n;
	char origin[4];
	char destination[4];
	char airline[4];
	char flightType[20];
	int passengers;
	int currIdx = 0;
	char buffer[500];
	int flightIndex = 0;
	int passengersIndex;

	while (fgets(buffer, 500, inputFile) != NULL)
	{
		sscanf( buffer , "%d,%3[^,],%3[^,],%3[^,],%20[^,],%d", &month , origin , destination , airline , flightType , &passengers);
		flightIndex = findAirlineRoute( r , n , origin , destination , airline , flightIndex );

		if ( flightIndex == -1 )
		{
			strcpy( (* ( r + n ) ).origin , origin );
			strcpy( (* ( r + n ) ).destination , destination );
			strcpy( (* ( r + n ) ).airline , airline);

			for ( passengersIndex = 0; passengersIndex < 6; passengersIndex++ )
			{
				(* ( r + n ) ).passengers[passengersIndex] = 0;

				(* (r + n ) ).passengers[month - 1] = passengers;
			}

			n++;
		}
		else
		{
			(* ( r + flightIndex ) ).passengers[month - 1] = passengers;
		}

		i++;

	}

	printf( "Unique routes operated by airlines: %d\n", n - 1 );
	return n - 1;
}

/*
Function: findAirlineRoute
-------------------
Finds a specific record in the RouteRecord array, as denoted by fillRecords.
RouteRecord *r: pointer to RouteRecord array.
int length: length of array.
const char *origin: origin airport.
const char *destination: destination airport.
const char *airline: airline.
int currIndex: current index of duplicate line.
Returns: returns -1 if it cannot find these three strings in the same struct object.
*/
int findAirlineRoute( RouteRecord *r , int length , const char *origin , const char *destination , const char *airline , int currIndex )
{
	int test = -1;
	int i = 0;

	while ( i < length && test == -1 )
	{
		RouteRecord compare = (* ( r + i ) );
		if ( strcmp( compare.origin , origin ) == 0)
		{
			if ( strcmp( compare.destination , destination ) == 0)
			{
				if ( strcmp( compare.airline , airline ) == 0)
				{
					test = i;
				}
			}
		}

		i++;
	}

	return test;
}

/*
Function: printMenu
-------------------
This function prints the menu. 
Returns: nothing.
*/
void printMenu()
{
	printf( "\n\n######### Airline Route Records Database MENU #########\n" );
	printf( "1. Search by Route\n" );
	printf( "2. Search by Origin Airport\n" );
	printf( "3. Search by Destination Airport\n" );
	printf( "4. Search by Airline\n" );
	printf( "5. Quit\n" );
	printf( "Enter your selection: " );
}

/*
Function: searchRecords
-------------------
Searches the RouteRecord array and prints out the results of the search and appropriate statistics.
RouteRecord *r: pointer to RouteRecord array.
int length: length of array.
const char *key1: pointer to user selection value dependent on initial search selection.
const char *key2: pointer to user selection value dependent on initial search selection.
SearchType st: user selection based on Searchtype declared enum.
Returns: nothing.
*/
void searchRecords( RouteRecord *r , int length , const char *key1 , const char *key2 , SearchType st )
{
	int i , j;
	int matches = 0;
	RouteRecord * comp;
	int checker;
	char buffer[500];

	int totalPassengers[7] = { 0 , 0 , 0 , 0 , 0 , 0 };

	switch ( st )
	{
		case 1:

			for ( i = 0; i < length; i++)
			{
				if ( strcmp( r[i].origin , key1 ) == 0 && strcmp( r[i].destination , key2 ) == 0 )
				{ 
					matches++;
					printf( "%s (%s-%s) " , r[i].airline , r[i].origin , r[i].destination );
					for ( j = 0; j < 6; j++ )
					{
						( totalPassengers[j] ) += r[i].passengers[j];
					}

					if ( i == 20 )
					{
						printf( "\n" );
					}
				}
			}

			break;

		case 2:

			for ( i = 0; i < length; i++)
			{
				if ( strcmp(r[i].origin , key1 ) == 0)
				{
					matches++;
					printf( "%s (%s-%s) ", r[i].airline , r[i].origin , r[i].destination );
					for ( j = 0; j < 6; j++ )
					{
						( totalPassengers[j]) += r[i].passengers[j];
					}

					if ( i == 10 )
					{
						printf( "\n" );
					}
				}
			}

			break;

		case 3:

			for ( i = 0; i < length; i++ )
			{
				if ( strcmp(r[i].destination , key1 ) == 0 )
				{
					matches++;
					printf( "%s (%s-%s) " , r[i].airline, r[i].origin, r[i].destination );
					for ( j = 0; j < 6; j++ )
					{
						totalPassengers[j] += r[i].passengers[j];
					}

					if ( i == 10 )
					{
						printf( "\n" );
					}
				}
			}

			break;

		case 4:

			for ( i = 0; i < length; i++ )
			{
				if ( strcmp(r[i].airline , key1 ) == 0 )
				{
					matches++;
					printf( "%s (%s-%s) " , r[i].airline, r[i].origin, r[i].destination );
					for ( j = 0; j < 6; j++ )
					{
						totalPassengers[j] += r[i].passengers[j];
					}

					if ( i == 10 )
					{
						printf( "\n" );
					}
				}
			}

			break;

		case 5:
			free( r );
			break;
	}

	if ( ( st == 1 ) || ( st == 2 ) || ( st == 3 ) || ( st == 4 ) )
	{
		printf( "\n%d matches were found.\n\nStatistics:\n" , matches );

		int totalCount = totalPassengers[0] + totalPassengers[1] + totalPassengers[2] + totalPassengers[3] + totalPassengers[4] + totalPassengers[5];

		printf("Total Passengers:\t%9d\n", totalCount);
		for ( i = 0; i < 6; i++ )
		{
			printf( "Total Passengers in Month %d:%9d\n" , i + 1, totalPassengers[i] );
		}

		printf( "\nAverage Passengers per month:%8d\n\n" , totalCount / 6 );
	}
}

/*
Function: printRecords
-------------------
Does not function.
RouteRecord *r: pointer to RouteRecord array.
Returns: nothing.
*/
void printRecords( RouteRecord *r , int length );

/*
Function: printRecord
-------------------
Does not function.
RouteRecord r: individual RouteRecord.
Returns: nothing.
*/
void printRecord( RouteRecord r );

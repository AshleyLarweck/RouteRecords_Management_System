/*
RouteRecords.h
Project 2
Ashley Larweck
File declares enum SearchType, RouteRecord struct and all functions used in source files main.c and RouteRecords.c.
*/

#ifndef ROUTERECORDS_H
#define ROUTERECORDS_H

typedef enum SearchType
{
	ROUTE = 0,
	ORIGIN,
	DESTINATION,
	AIRLINE
}

SearchType;

typedef struct RouteRecord
{
	char origin[4];
	char destination[4];
	char airline[3];
	int passengers[7];
}

RouteRecord;

/*
Function: RouteRecord* createRecords
-------------------
Creates the array of RouteRecord’s and initializes it. Parses entire file and counts the total number of flights. Dynamically allocates memory for array of RouteRecords based on this count.
FILE *fileIn: pointer to input file.
Returns: pointer to the dynamically allocated array.
*/
RouteRecord* createRecords( FILE *fileIn );

/*
Function: fillRecords
-------------------
Processes the data in the CSV file. Stores this data in an array. Calls findAirlineRoute() to further parse/process data. Stores unique flights in array.
RouteRecord *r : pointer to RouteRecord array.
FILE *inputFile: pointer to input file.
Returns: the actual number of RouteRecord’s used in the array. 
*/
int fillRecords( RouteRecord *r , FILE *fileIn );

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
int findAirlineRoute( RouteRecord *r, int length , const char *origin , const char *destination , const char *airline , int currIndex );

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
void searchRecords( RouteRecord *r , int length , const char *key1 , const char *key2 , SearchType st );

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

/*
Function: printMenu
-------------------
This function prints the menu. 
Returns: nothing.
*/
void printMenu();

#endif

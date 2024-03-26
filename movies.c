#include <stdlib.h>
#include "movie.h"


int main()
{
	Movie* genreTrees[GENRES];
	for(int i = 0; i < GENRES; ++i){
		genreTrees[i] = NULL;
	}
}

//TREE STRUCTURE
Movie* insert (Movie* root, char* name, int year, int minutes, int genre, long long revenue)
{
	if (root == NULL)
	{
		root = malloc(sizeof(Movie));
		root->name = name;
		root-> year = year;
		root->minutes = minutes;
		root->genre = genre;
		root->revenue = revenue;
		root->left = NULL;
		root->right = NULL;
	}
	else 
	{
		int cmp = compare(root, name, year);
		if (cmp < 0)
			root->left = insert(root->left, name, year, minutes, genre, revenue);
		else if (cmp > 0)
			root->right = insert(root->right, name, year, minutes, genre, revenue);
	}
	
	return root;
}

Movie* search (Movie* root, char* name, int year)
{
	if(root == NULL)
	{
		return NULL;
	}
	
	else if(compare(root->name, name, year) == 0)
	{
		return root;
	}
	
	else if(compare(root->name, name, year) < 0)
	{
		return search(root->left, name, year);
	}
	
	else
	{
		return search(root->right, name, year);
	}
}

Movie* delete (Movie* root, char* name, int year)
{
	if(root == NULL)
	{
		return NULL;
	}
	
	else if(strcmp(name, root->name) == 0)
	{
		free(root);
	}
	//not finished.

}

void clear (Movie* root)
{
	if(root != NULL)
	{
		clear(root->left);
		clear(root->right);
		free(root->name);
		free(root);
	}
}
//
//INFORMATION
void printMovie(Movie* movie)
{
	if(movie->revenue == 0) //prints revenue as unknown
	printf("Name:\t\t\t%s\n Year: \t\t\t%d\n Length:\t\t\t%d minutes\n Genre:\t\t\t%s\n Revenue:\t\t\tUnknown\n", movie->name, movie->year, movie->minutes, movie->genre);
	else{
	printf("Name:\t\t\t%s\n Year: \t\t\t%d\n Length:\t\t\t%d minutes\n Genre:\t\t\t%s\n Revenue:\t\t\t$%d\n", movie->name, movie->year, movie->minutes, movie->genre, movie->revenue);
	}
}

int printMatches (Movie* root, char* name)
{
	if(root != NULL && strcmp(root->name, name) == 0)
	{
		printMatches(root->left);
		printMovie(root);
		printMatches(root->right);
	}
	return 0;
}

void printAll (FILE* file, Movie* root);
//

//STATISTICS
int count (Movie* root);
long long totalRevenue (Movie* root);
Movie* highestGrossing (Movie* root);
//

int compare(Movie* movie, char* name, int year)
{
	int cmp = strcmp(name, movie->name);
	if (cmp == 0)
		cmp = year - movie->year;
	return cmp;	
}

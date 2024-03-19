#include <stdlib.h>
#include "movie.h"


int main()
{
	Movie* genreTrees[GENRES];
	for(int i = 0; i < GENRES; ++i){
		genreTrees[i] = NULL;
	}
}


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

Movie* search (Movie* root, char* name, int year){
	Movie* temp
	
	if(compare(root, name, year) )
		return 
	else
		return NULL;
	
	search(root->next, name, year);
}

int compare(Movie* movie, char* name, int year)
{
	int cmp = strcmp(name, movie->name);
	if (cmp == 0)
		cmp = year - movie->year;
	return cmp;	
}

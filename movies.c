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
	int counter = 0;
	if(root != NULL)
	{
		printMatches(root->left);
		if(!strcmp(root->name, name))
			{
				printMovie(root);
				counter++;
			}
		printMatches(root->right);
	}
	return counter;
}

void printAll (FILE* file, Movie* root)
{
	//preorder NLR FIX THIS. HOW TO PUT TABS IN FWRITE
	fwrite(root->name, sizeof(Movie), count(root), file);
	printf("\t");
	fwrite(root->year, sizeof(Movie), count(root), file);
	printf("\t");
	fwrite(root->length, sizeof(Movie), count(root), file);
	printf("\t");
	fwrite(root->genre, sizeof(Movie), count(root), file);
	fwrite(root->revenue, sizeof(Movie), count(root), file);
	fclose(file);
}
//

//STATISTICS
int count (Movie* root)
{
	if(root == NULL)
	{
		return 0;
	}
	
	else
	{
		return count(root->left) + count(root->right) + count(root);
	}
}

long long totalRevenue (Movie* root)
{
	if(root == NULL)
	{
		return 0;
	}
	
	else
	{
		return totalRevenue(root->left) + totalRevenue(root->right) + root->revenue;
	}
}

Movie* highestGrossing (Movie* root)
{
	Movie* temp;
	Movie* highest;
	
	if(root == NULL)
	{
		return NULL;
	}
	else
	{
		highest = root->revenue;
		temp = highestGrossing(root->left);
		if(temp != NULL && temp->revenue >= highest->revenue)
		{
			highest = temp;
		}
		
		temp = highestGrossing(root->right);
		if(temp != NULL && temp->revenue >= highest->revenue)
		{
			highest = temp;
		}
		
		if(highest == 0) //error case
		{
			return -1;
		}
		return highest;
	}
}
//

int compare(Movie* movie, char* name, int year)
{
	int cmp = strcmp(name, movie->name);
	if (cmp == 0)
		cmp = year - movie->year;
	return cmp;	
}

#include <stdlib.h>
#include <string.h>
#include "movie.h"
extern const char* GENRE_NAMES[GENRES];

int main()
{
	Movie* genreTrees[GENRES];
	for(int i = 0; i < GENRES; ++i){
		genreTrees[i] = NULL;
	}
	
	char choice[20];
	
	do
	{
		printf("Enter command: ");
		scanf("%s", choice);
		getchar(); // Eats up newline
		
		if (!strcmp(choice, "add"))
		{
			printf("\nEnter name: ");
			char name[1024];
			readToTab(stdin, name);
			
			printf("Enter year: ");
			int year;
			scanf("%d", &year);
			
			printf("Enter length in minutes: ");
			int minutes;
			scanf("%d", &minutes);
			
			printf("Enter genre: ");
			char genreName[100];
			scanf("%s", genreName);
			int genre = genreType(genreName);
			
			printf("Enter revenue: ");
			long long revenue;
			scanf("%lld", &revenue);
			
			
			if (year < 1900 || year > 2050)
			{
				printf("Add failed: Invalid year %d\n\n", year);
			}
			else if (minutes < 0)
			{
				printf("Add failed: Invalid lenth of %d minutes\n\n", minutes);
			}
			else if (genre == -1)
			{
				printf("Add failed: Invalid genre %s\n\n", genreName);
			}
			else if (revenue < 0)
			{
				printf("Add failed: Invalid revenue %lld\n\n", revenue);
			}
			else
			{
				printf("Add succeeded\n\n");
				genreTrees[genre] = insert(genreTrees[genre], name, year, minutes, genre, revenue);
			}
		}
		else if (!strcmp(choice, "clear"))
		{
			for (int i = 0; i < GENRES; i++)
			{
				free(genreTrees[i]);
				genreTrees[i] = NULL;
			}

			printf("\nAll data cleared.\n\n");
		}
		else if (!strcmp(choice, "delete"))
		{
			// Delete stuff
		}
		else if (!strcmp(choice, "find"))
		{
			printf("\nEnter name: ");
			char movieName[100];
			readToTab(stdin, movieName);
			int total = 0;
			
			for (int i = 0; i < GENRES; i++)
			{
				total += printMatches(genreTrees[i], movieName);
			}
			
			printf("%d matches found.\n\n", total);
			
		}
		else if (!strcmp(choice, "help"))
		{
			printf("\nCommand\n\nadd\n\tAdds a movie to the current list\n\n");
			printf("clear\n\tClears the current list of movies\n\n");
			printf("delete\n\tDeletes a movie from the current list\n\n");
			printf("find\n\tSearches for a movie\n\n");
			printf("help\n\tPrints the list of commands\n\n");
			printf("highest\n\tPrints the highest revenue movie for each genre\n\n");
			printf("load\n\tAdds the contents of a file to thet list of movies\n\n");
			printf("quit\n\tQuits the program\n\n");
			printf("save\n\tSaves the current list of movies to a file\n\n");
			printf("statistics\n\tPrints out statistics for each genre\n\n\n");
		}
		else if (!strcmp(choice, "load"))
		{
			printf("\nEnter file: ");
			char fileName[100];
			scanf("%s", fileName);
			
			FILE* file = fopen(fileName, "r");
			
			if (file == NULL)
			{
				printf("Load failed: File %s not found\n\n", fileName);
			}
			else
			{
				int total = readFile(file, genreTrees);			
				printf("Loaded %d movies with %d errors\n\n", total, 0);
				fclose(file);
			}
		}
		else if (!strcmp(choice, "revenue"))
		{
			printf("\nEnter name: ");
			char name[1024];
			readToTab(stdin, name);
			
			printf("Enter year: ");
			int year;
			scanf("%d", &year);
			
			printf("Enter genre: ");
			char genreName[100];
			scanf("%s", genreName);
			int genre = genreType(genreName);
			
			printf("Enter new revenue: ");
			long long revenue;
			scanf("%lld", &revenue);
			
			
			Movie* tempMovie = search(genreTrees[genre], name, year); // DUMPING CORE

			
			if (year < 1900 || year > 2050)
			{
				printf("Revenue changed failed: Invalid year %d\n\n", year);
			}
			if (genre == -1)
			{
				printf("Revnue change failed: Invalid genre %s\n\n", genreName);
			}
			else if (revenue < 0)
			{
				printf("Revenue change failed: Invalid revenue %lld\n\n", revenue);
			}
			else if (tempMovie == NULL)
			{
				printf("Revenue change failed: Movie %s (%d) not found in genre %s\n\n", name, year, genreName);
			}
			else
			{
				tempMovie->revenue = revenue;
				printf("Revenue change successful\n\n");
			}
		}
		else if (!strcmp(choice, "save"))
		{
			// Save some stuff
		}
		else if (!strcmp(choice, "statistics"))
		{
			printf("\n");
			for(int i = 0; i < GENRES; i++)
			{
				printf("%-12s\tCount:%10d\tTotal revenue: $%lld\n", GENRE_NAMES[i], count(genreTrees[i]), totalRevenue(genreTrees[i]));
			}
			printf("\n");
		}
		else
		{
			printf("\nUnknown command: %s\n\n", choice);
		}
		
	} while(strcmp(choice, "quit") != 0);
	
	for (int i = 0; i < GENRES; i++)
	{
		free(genreTrees[i]);
		genreTrees[i] = NULL;
	}

	printf("\n\nAll data cleared.\n");


}


/*****************************

	HELPER FUNCTIONS

*****************************/
int genreType(char* genreName)
{
	for (int i = 0; i < GENRES; i++) 
	{
		if (!strcmp(genreName, GENRE_NAMES[i]))
		{
			return i;
		}
	}
	
	return -1;
}

int readToTab(FILE* file, char* data)
{
	int index = 0;
	int character = fgetc(file);
	while(character != '\t' && character != '\n' && character != EOF)
	{
		data[index] = character;
		index++;
		character = fgetc(file);
	}
	
	data[index] = '\0';
	
	return index;
}



int readFile(FILE* file, Movie* genreTrees[])
{
	int total = 0;	
	char name[1024];
	
	while(readToTab(file, name))
	{
		int year;
		fscanf(file, "%d", &year);

		int minutes;
		fscanf(file, "%d", &minutes);
		fgetc(file);

		char genreName[100];
		readToTab(file, genreName);
		int genre = genreType(genreName);
		
		long long revenue;
		fscanf(file, "%lld", &revenue);
		fgetc(file);
		
		
		genreTrees[genre] = insert(genreTrees[genre], name, year, minutes, genre, revenue);
		total++;
	}
	
	return total;
}

int compare(Movie* movie, char* name, int year)
{
	int cmp = strcmp(name, movie->name);
	if (cmp == 0)
		cmp = year - movie->year;
	return cmp;	
}



/***************************

	TREE STRUCTURE

***************************/
Movie* insert (Movie* root, char* name, int year, int minutes, int genre, long long revenue)
{
	if (root == NULL)
	{
		root = malloc(sizeof(Movie));
		root->name = strdup(name);
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
	
	else if(compare(root, name, year) == 0)
	{
		return root;
	}
	
	else if(compare(root, name, year) < 0)
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




/************************

	INFORMATION

************************/
void printMovie(Movie* movie)
{
	if(movie->revenue == 0) //prints revenue as unknown
	printf("Name:\t\t%s\nYear: \t\t%d\nLength:\t\t%d minutes\nGenre:\t\t%s\nRevenue:\tUnknown\n", movie->name, movie->year, movie->minutes, GENRE_NAMES[movie->genre]);
	else{
	printf("Name:\t\t%s\nYear: \t\t%d\nLength:\t\t%d minutes\nGenre:\t\t%s\nRevenue:\t$%lld\n", movie->name, movie->year, movie->minutes, GENRE_NAMES[movie->genre], movie->revenue);
	}
}

int printMatches (Movie* root, char* name)
{
	int counter = 0;
	if(root != NULL)
	{
		counter += printMatches(root->left, name);
		if(!strcmp(root->name, name))
		{
			printMovie(root);
			printf("\n");
			counter++;
		}
		counter += printMatches(root->right, name);
	}
	return counter;
}

/*
int saveFile(FILE* file, Movie* root)
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
}
*/



/***********************

	STATISTICS

***********************/
int count (Movie* root)
{
	if(root == NULL)
	{
		return 0;
	}
	
	else
	{
		return 1 + count(root->left) + count(root->right);
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
		highest = root; // OR highest = root;
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
			return NULL;
		}
		return highest;
	}
}

movies: movies.c names.c movie.h
	gcc movies.c -o movies -Wall
	
clean:
	rm -f movies

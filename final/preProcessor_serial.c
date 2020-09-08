#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    //Hardcode how many movies you want to look at since there's a lot
    int nMovies = 100;
    //Initialize a 2d array of users x movies with all ratings set to 0
    int ratings[2700000][17770] = {0};
    char movieNames[17770];
    char prefix[8] = "./data/";
    //Get movie titles
    FILE *fPointer;
    fPointer = fopen(strcat(prefix, "movie_titles.txt"), "r");

    int id;
    int date;
    char title[150];
    // read line by line till end of file
    while( fscanf(fPointer, "%[^,],%[^,],%s\n", &id, &date, title) == 1 ) {
        movieNames[id] = title[150];
    }
    fclose(fPointer);
    for (int i = 1; i < nMovies + 1; i++) {
           char s[sizeof(i)];
           sprintf( s, "%d", i);
           char file[10];
            strcat(s, ".txt");
           strcpy(file, s);
           char prefix2[30];
           if (i < 10) {
               strcpy(prefix2, "./data/my_000000");
           }
           else if (i < 100) {
              strcpy( prefix2, "./data/my_00000");
           }
           else if (i < 1000) {
               strcpy(prefix2, "./data/my_0000");
           }
           else {
              strcpy( prefix2, "./data/my_000");
           }
           strcat(prefix2, file);
       FILE *fPointer2;
       fPointer2 = fopen(prefix2, "r");
       char singleLine[150];
 int userId;
 int rating;
 bool firstRow = true;
 // read line by line till end of file
 while( fscanf(fPointer2, "%[^,],%[^,],%s\n", &userId, &rating) == 1 ) {
     //Check for exess user id, skip first row
     if (!firstRow) {
         if ( userId > 2700000 ) {
             printf("Add more users! User id: %d", userId);
         } else {
             ratings[userId][i] = rating;
         }
     }
     if (firstRow == true) {
         firstRow = false;
     }
 }
 fclose(fPointer2);
}

return 0;
}

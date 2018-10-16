#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 1000
int main()
{
    //WRITE TO FILE
    FILE *fps;
    char writeFile[MAXCHAR];
    char* filenames = "program.txt";
    
    // Read string to write
    printf("Enter data to wite :");
    gets(writeFile);
    
    // Open file in write mode
    fps = fopen(filenames,"w+");

    // If file opened successfully, then write the string to file
    if ( fps )
    {
        fputs(writeFile,fps);
    }
    else
    {
        printf("Failed to open the file\n");
    }
    //Close the file
    fclose(fps);

    //READ DATA FROM TEXT FILE
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "program.txt";
    
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("Data from text file: %s\n", str);
    fclose(fp);

   return 0;
}
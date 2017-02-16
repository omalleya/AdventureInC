#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3
#define MAX_LEN_TYPE 11
#define NUM_ROOMS 7
#define MAX_LEN_NAME 9

char *fileNames[7] = {"one", "two", "three", "four", "five", "six", "seven"};

struct Room
{
	char name[MAX_LEN_NAME];
	int totConnections;
	int curConnections;
	char *connections[MAX_CONNECTIONS];
	char type[MAX_LEN_TYPE];
};

int endGame()
{
    return 0;
}

void getLastDir(char** finalDir)
{
    char *fd = "omalleya.rooms.";
    char currentDir[100];
    memset(currentDir, '\0', sizeof(currentDir));
    getcwd(currentDir, sizeof(currentDir));
    printf("%s\n", currentDir);
    DIR *d;
    struct dirent *dp;
    struct stat *buffer;
    buffer = malloc(sizeof(struct stat));
    dp = malloc(sizeof(struct dirent));
    time_t lastModified;
    d = opendir(currentDir);
    if (d != NULL) {
        while (dp = readdir(d)) {	
            if (strstr(dp->d_name,fd) != NULL){
                stat(dp->d_name, buffer);
                lastModified = buffer->st_mtime;
                strcpy(*finalDir, dp->d_name);
            }
        }
    }

}

void getData(char *directory)
{
    int i=0;
    char *fullName = malloc(sizeof(char)*50);
    char str[256];
    int counter = 0;

    struct Room *rooms = malloc(sizeof(struct Room)*7);

    for(i=0; i<7; i++)
    {
        strcpy(fullName, directory);
        strcat(fullName, fileNames[i]);
        strcat(fullName, ".txt");
        //printf("%s\n", fullName);
        FILE *f = fopen(fullName, "r");
        counter = 0;
        while(fgets(str, 256, f)!=NULL)
        {
            if(counter == 0)
            {
                //name
            }
            printf("%s", str);
            counter++;
        }
        fclose(f);
    }
}

int main()
{
    //get room data
    //then

    char *next;
    char *dirName = malloc(sizeof(char)*40);

    //setting up proper string to access directory
    strcpy(dirName, "./");
    getLastDir(&dirName);
    strcat(dirName, "/");
    printf("\n%s\n",dirName);

    getData(dirName);

    do
    {
        printf("%s", next);
        printf("CURRENT LOCATION: \n");
        printf("POSSIBLE CONNECTIONS: \n");
        printf("WHERE TO? > ");
        fgets(next, 10, stdin);
    }while(endGame() != 1);

    return(0);
}
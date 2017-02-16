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

struct Room* getData(char *directory)
{
    int i=0;
    char *fullName = malloc(sizeof(char)*50);
    char *str = malloc(sizeof(char)*200);
    int counter = 0;
    char  *temp = malloc(sizeof(char)*200);

    struct Room *rooms = malloc(sizeof(struct Room)*7);

    for(i=0; i<7; i++)
    {
        strcpy(fullName, directory);
        strcat(fullName, fileNames[i]);
        strcat(fullName, ".txt");
        FILE *f = fopen(fullName, "r");
        counter = 0;
        while(fgets(str, 100, f)!=0)
        {
            if(counter == 0)
            {
                printf("\n%s\n", "name");
                strncpy(rooms[i].name, str+11, 9);
                printf("\n%s\n", rooms[i].name);
            }else if(str[0] == 'C')
            {
                printf("%s\n", "connection");
                rooms[i].connections[counter] = malloc(sizeof(char)*15);
                strncpy(rooms[i].connections[counter], str+14, 9);
                printf("\n%s\n", rooms[i].connections[counter]);
                counter++;
            }else {
                printf("%s\n", "type");
                strncpy(rooms[i].type, str+11, 11);
                printf("\n%s\n", rooms[i].type);
            }
            printf("%s", str);
            counter++;
        }
        fclose(f);
    }
    return rooms;
}

int main()
{
    //get room data
    //then

    char *next;
    char *dirName = malloc(sizeof(char)*40);

    struct Room *rooms;

    //setting up proper string to access directory
    strcpy(dirName, "./");
    getLastDir(&dirName);
    strcat(dirName, "/");
    printf("\n%s\n",dirName);

    rooms = getData(dirName);

    printf("\nHELLO::: %s\n", rooms[0].name);

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
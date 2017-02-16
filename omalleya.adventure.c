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

int endGame(struct Room room)
{
    char* end = "END_ROOM";
    if(strcmp(room.type, end) == 0)
    {
        return 1;
    }else{
        return 0;
    }
}

void addToPath(char ***curPath, char *nextStep, int steps)
{
    int i = 0;

    *curPath = (char**)realloc((*curPath), steps*sizeof(char*));
    (*curPath)[steps-1] = (char*) malloc(sizeof(char)*20);
    strcpy((*curPath)[steps-1], nextStep);
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
    int connectCount=0;
    char  *temp = malloc(sizeof(char)*200);

    struct Room *rooms = malloc(sizeof(struct Room)*7);

    for(i=0; i<7; i++)
    {
        strcpy(fullName, directory);
        strcat(fullName, fileNames[i]);
        strcat(fullName, ".txt");
        FILE *f = fopen(fullName, "r");
        counter = 0;
        connectCount = 0;
        while(fgets(str, 100, f)!=0)
        {
            if(counter == 0)
            {
                printf("\n%s\n", "name");
                strncpy(rooms[i].name, str+11, 9);
                rooms[i].name[strcspn(rooms[i].name, "\n")] = 0;
                printf("\n%s\n", rooms[i].name);
            }else if(str[0] == 'C')
            {
                printf("%s\n", "connection");
                rooms[i].connections[connectCount] = malloc(sizeof(char)*15);
                strncpy(rooms[i].connections[connectCount], str+14, 9);
                rooms[i].connections[connectCount][strcspn(rooms[i].connections[connectCount], "\n")] = 0;
                printf("\n%s\n", rooms[i].connections[connectCount]);
                connectCount++;
            }else {
                printf("%s\n", "type");
                strncpy(rooms[i].type, str+11, 11);
                rooms[i].type[strcspn(rooms[i].type, "\n")] = 0;
                printf("\n%s\n", rooms[i].type);
            }
            printf("%s", str);
            counter++;
        }
        while(connectCount < 6)
        {
            rooms[i].connections[connectCount] = malloc(sizeof(char)*15);
            strcpy(rooms[i].connections[connectCount], "");
            connectCount++;
        }
        fclose(f);
    }
    return rooms;
}

struct Room* setCurrentRoom(struct Room *rooms, struct Room currentRoom, char* nextRoom, int* steps, char*** path)
{
    int i=0;
    int j=0;
    struct Room *newRoom;
    int newRoomCheck = -1;

    nextRoom[strcspn(nextRoom, "\n")] = 0;

    for(i=0; i<6; i++)
    {
        if(strcmp(currentRoom.connections[i], nextRoom) == 0)
        {
            printf("\nMATCH\n");
            //newRoom = &currentRoom;
            newRoomCheck = 0;
            break;
        }
    }

    if(newRoomCheck != 0)
    {
        printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
        newRoom = &currentRoom;
    }
    else {
        for(j=0; j<7; j++)
        {
            if(strcmp(currentRoom.connections[i], rooms[j].name) == 0)
            {
                newRoom = &rooms[j];
                (*steps)++;
                addToPath(path, rooms[j].name, *steps);
                break;
            }
        }
    }

    return newRoom;
}

int main()
{
    char *next = malloc(sizeof(char)*40);
    char *dirName = malloc(sizeof(char)*40);
    int steps = 0;
    char **path = malloc(sizeof(char*));

    struct Room *rooms;
    int i=0;

    //setting up proper string to access directory
    strcpy(dirName, "./");
    getLastDir(&dirName);
    strcat(dirName, "/");
    printf("\n%s\n",dirName);

    rooms = getData(dirName);

    struct Room *currentRoom = malloc(sizeof(struct Room));
    currentRoom = &rooms[0];

    do
    {
        printf("CURRENT LOCATION: %s\n", currentRoom->name);
        printf("POSSIBLE CONNECTIONS: ");
        for(i=0; i<6; i++)
        {
            if(strcmp(currentRoom->connections[i], "") != 0)
            {
                printf("%s",currentRoom->connections[i]);
            }
            
            if(i+1 < 6 && strcmp(currentRoom->connections[i+1], "") == 0)
            {
                printf(".\n");
                break;
            }else if(i==5)
            {
                printf(".\n");
                break;
            }else {
                printf(", ");
            }
        }
        printf("WHERE TO? >");
        fgets(next, 11, stdin);
        currentRoom = setCurrentRoom(rooms, *currentRoom, next, &steps, &path);
    }while(endGame(*currentRoom) != 1);

    printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");

    for(i=0; i<steps; i++)
    {
        printf("\n%s\n", path[i]);
    }

    return(0);
}
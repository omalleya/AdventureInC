#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3
#define MAX_LEN_NAME 9
#define MAX_LEN_TYPE 11
#define LEN_CONNECTION 14
#define NUM_ROOMS 7

struct Room
{
	char name[MAX_LEN_NAME];
	int totConnections;
	int curConnections;
	char connections[MAX_CONNECTIONS][LEN_CONNECTION + MAX_LEN_NAME];
	char type[MAX_LEN_TYPE];
};

void createRoomDir() 
{
	int pid = getpid();
	char dirName[36];
	sprintf(dirName, "./omalleya.rooms.%d", pid);
	//uncomment the below to create directory
	//mkdir(dirName, 0755);

}

void printRoom(struct Room room)
{
	int i = 0;

	printf("\nROOM NAME: %s\n", room.name);
	printf("ROOM TYPE: %s\n", room.type);
}

void createConnections(struct Room *rooms)
{
	int i = 0;
	int j = 0;
	int arraySize = NUM_ROOMS;
	int numConnections = -1;
	int randomConnection = -1;

	for(i=0; i<arraySize; i++)
	{
		if(i == 0)
		{
			strcpy(rooms[i].type, "START_ROOM");
		}else if(i == arraySize-1)
		{
			strcpy(rooms[i].type, "END_ROOM");
		}else {
			strcpy(rooms[i].type, "MID_ROOM");
		}

		numConnections = randInt(3,6);
		while(j<numConnections)
		{
			//find number of connections already
			//if less than numConnections
				//add randomConnection to this file and it's corresponding one
				//make sure randomConnection doesn't point to self

			randomConnection = randInt(0,6);
			if(randomConnection == i)
			{
				continue;
			}else {
				//TODO use matrix instead
				strcpy(rooms[i].connections[j], rooms[randomConnection].name);
				printf("\n Connection! %s\n", rooms[i].connections[j]);
				j++;
			}
		}

		printRoom(rooms[i]);
	}
}

//returns random int between max and min
int randInt(int min, int max)
{
	return rand() % (max-min + 1) + min;
}

int main()
{
	//the below two lines seed the rand function
	//now we won't get the same number every time from randInt
	time_t sysClock;
	srand((unsigned) time(&sysClock));

	printf("Hello World!\n");

	//creates initial directory for rooms
	createRoomDir();
	
	char *roomNames[10] = {"Big","SMALL", "Medium", 
	     			"L-shaped", "C-shaped", "Swag",
				"Dank", "Dungeon", "Master", "Basement"};

	int numRooms = 0;	
	struct Room rooms[7];
	int index = -1;
	int i = 0;
	for(i=0;i<7;i++)
	{
		strcpy(rooms[i].name, "");
	}

	char *test;

	while(numRooms < 7)
	{
		index = randInt(0,9);
		for(i=0; i<7; i++)
		{
			test = strstr((char*)rooms[i].name, (char *) roomNames[index]);
			if(test != 0)
			{
				index = -1;
			}
		}
		if(index!=-1)
		{
			strcpy(rooms[numRooms].name, roomNames[index]);
			numRooms++;
		}else
		{
			continue;
		}
	}

	createConnections(rooms);

	return(0);
}

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
	char **connections;
	//char connections[MAX_CONNECTIONS][LEN_CONNECTION + MAX_LEN_NAME];
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

void createConnections(struct Room *rooms, int numConnections)
{
		rooms[0].connections = (char **) malloc(numConnections * sizeof(char*));
		rooms[0].connections[0] = (char*) malloc(sizeof(char)*7);
		strcpy(rooms[0].connections[0], "connect");
		printf("\n%s\n", rooms[0].connections[0]);
}

void restOfRooms(struct Room *rooms)
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

		createConnections(rooms, numConnections);
		printf("\n%d\n", numConnections);

		printRoom(rooms[i]);
	}
}

struct Room* randomRooms()
{
	char *roomNames[10] = {"Big","SMALL", "Medium", 
	     			"L-shaped", "C-shaped", "Swag",
				"Dank", "Dungeon", "Master", "Basement"};

	int roomCheck[10] = {0,0,0,0,0,0,0,0,0,0};
	int numRooms = 0;	
	struct Room *rooms = malloc(7* sizeof(struct Room));
	int index = -1;
	int i = 0;

	char *test;

	//while we still have rooms to create
	while(numRooms < 7)
	{
		//get random index for a room name
		index = randInt(0,9);
		for(i=0; i<7; i++)
		{
			//if temp array index == 1 then it is already the name of a different room
			if(roomCheck[index]==1)
			{
				index = -1;
			}
		}
		if(index!=-1)
		{
			strcpy(rooms[numRooms].name, roomNames[index]);
			roomCheck[index] = 1;
			numRooms++;
		}else
		{
			continue;
		}
	}
	return rooms;
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

	//creates rooms with randomized names
	struct Room *rooms = randomRooms();

	//adds connections and types to rooms
	restOfRooms(rooms);

	return(0);
}

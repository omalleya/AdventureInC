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

int checkMatrix[7][7] = {
		{1,0,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,0,1}
	};

struct Room
{
	char name[MAX_LEN_NAME];
	int totConnections;
	int curConnections;
	char *connections[MAX_CONNECTIONS];
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
	int connectCount = 1;

	printf("\nROOM NAME: %s\n", room.name);
	for(i=0; i<6; i++)
	{
		if(strcmp(room.connections[i],"")!=0)
		{
			printf("CONNECTION %d: %s\n", connectCount, room.connections[i]);
			connectCount++;
		}
	}
	printf("ROOM TYPE: %s\n", room.type);
}

char * getRoomName(int index, struct Room *rooms)
{
	int i=0;
	for(i=0; i<7; i++)
	{
		if(i == index)
		{
			return rooms[i].name;
		}
	}
	return "";
}

void fillConnections(struct Room *room, int roomIndex, struct Room *rooms)
{
	int i=0;
	int j=0;
	int counter = 0;
	char *temp = malloc(sizeof(char)*20);
	
	for(i=0; i<7; i++)
	{
		if(checkMatrix[roomIndex][i] == 1 && roomIndex != i)
		{
			room->connections[j] = malloc(sizeof(char)*15);
			temp = getRoomName(i, rooms);
			strcpy(room->connections[j], temp);
			j++;
		}else if(roomIndex == i)
		{
			continue;
		}
		else {
			room->connections[j] = malloc(sizeof(char)*15);
			strcpy(room->connections[j], "");
			j++;
		}
	}
}

void createConnections(struct Room *room, int numConnections, int roomIndex, struct Room *rooms)
{
	
	int i=0;
	int j=0;
	int newConnect=-1;
	int curConnect = -1;

	for(j=0;j<7;j++)
	{
		if(checkMatrix[roomIndex][j] == 1)
		{
			curConnect++;
		}
	}

	for(i=0; i<6; i++)
	{
		if(i<numConnections && curConnect < numConnections)
		{
			do
			{
				newConnect=randInt(0,6);
			}while(checkMatrix[roomIndex][newConnect] == 1);

			if(newConnect > roomIndex)
			{
				checkMatrix[roomIndex][newConnect] = 1;
				checkMatrix[newConnect][roomIndex] = 1;
				curConnect++;
			}
			
		}else {
			break;
		}
	}

	fillConnections(room, roomIndex, rooms);

	for(i=0; i<7; i++)
	{
		printf(" %s ", getRoomName(i, rooms));
	}

	printf("\n");

	for(i=0; i<7; i++)
	{
		for(j=0; j<7; j++)
		{
			printf("%d ", checkMatrix[i][j]);
		}
		printf("\n");
	}

		
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

		createConnections(&rooms[i], numConnections, i, rooms);
		printf("\n%d\n", numConnections);

	}

	for(i=0; i<arraySize; i++)
	{
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

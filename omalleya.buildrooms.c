#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONNECTIONS 6
#define MIN_CONNECTIONS 3
#define MAX_LEN_TYPE 11
#define NUM_ROOMS 7
#define MAX_LEN_NAME 9

int checkMatrix[7][7] = {
		{1,0,0,0,0,0,0},
		{0,1,0,0,0,0,0},
		{0,0,1,0,0,0,0},
		{0,0,0,1,0,0,0},
		{0,0,0,0,1,0,0},
		{0,0,0,0,0,1,0},
		{0,0,0,0,0,0,1}
	};

char dirName[36];

//rooms data structure
struct Room
{
	char name[MAX_LEN_NAME];
	char *connections[MAX_CONNECTIONS];
	char type[MAX_LEN_TYPE];
};

//creates directory with pid
void createRoomDir() 
{
	int pid = getpid();
	sprintf(dirName, "./omalleya.rooms.%d", pid);
	//uncomment the below to create directory
	mkdir(dirName, 0755);

}

//prints room to intended file
void printRoom(struct Room room,  char* fileName)
{
	FILE *f = fopen(fileName, "w");
	int i = 0;
	int connectCount = 1;

	//print room name
	fprintf(f, "ROOM NAME: %s\n", room.name);

	//prints each connection
	for(i=0; i<6; i++)
	{
		//as long as element in connections array isn't empty
		if(strcmp(room.connections[i],"")!=0)
		{
			fprintf(f, "CONNECTION %d: %s\n", connectCount, room.connections[i]);
			//this gets the correct number next to output
			connectCount++;
		}
	}
	//prints room type
	fprintf(f, "ROOM TYPE: %s\n", room.type);

	fclose(f);
}

//gets connection's room name to put into struct
//used in combination with checkMatrix
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
	//return nothing if name couldn't be found
	return "";
}


void fillConnections(struct Room *room, int roomIndex, struct Room *rooms)
{
	int i=0;
	int j=0;
	char *temp = malloc(sizeof(char)*20);

	for(i=0; i<7; i++)
	{
		//if the room isn't already a connection 
		//and it's not the room we're making connections for
		if(checkMatrix[roomIndex][i] == 1 && roomIndex != i)
		{
			room->connections[j] = malloc(sizeof(char)*15);
			temp = getRoomName(i, rooms);
			//put this connections room name into the array for connections
			strcpy(room->connections[j], temp);
			j++;
		}
		else if(roomIndex == i)
		{
			continue;
		}
		//else fill the connection with nothing
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

	//check how many connections are currently in this room
	for(j=0;j<7;j++)
	{
		if(checkMatrix[roomIndex][j] == 1)
		{
			curConnect++;
		}
	}

	for(i=0; i<6; i++)
	{
		//if i 
		if(i<numConnections && curConnect < numConnections)
		{
			//get random numbers while the connection isn't new
			do
			{
				newConnect=randInt(0,6);
			}while(checkMatrix[roomIndex][newConnect] == 1);

			//one the random number is valid add ones to the checkMatrix
			checkMatrix[roomIndex][newConnect] = 1;
			checkMatrix[newConnect][roomIndex] = 1;
			curConnect++;
			
		}else {
			break;
		}
	}
		
}

void restOfRooms(struct Room *rooms)
{
	int i = 0;
	int j = 0;
	int arraySize = NUM_ROOMS;
	int numConnections = -1;
	int randomConnection = -1;
	char *fileNames[7] = {"one", "two", "three", "four", "five", "six", "seven"};

	//gives room proper type
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

		//get random number between 3 and 6 to use for connection number
		numConnections = randInt(3,6);

		//create the connections for this room
		createConnections(&rooms[i], numConnections, i, rooms);

	}

	//fill the connections once the checkMatrix has been completed
	for(i=0; i<arraySize; i++)
	{
		fillConnections(&rooms[i], i, rooms);
	}

	//set up files to write rooms into
	//print rooms
	char* temp = malloc(sizeof(char)*40);
	for(i=0; i<arraySize; i++)
	{
		strcpy(temp, "./");
		strcat(temp, dirName);
		strcat(temp, "/");
		strcat(temp, fileNames[i]);
		strcat(temp, ".txt");
		printRoom(rooms[i], temp);
	}
}

//just randomizes pool of 7 rooms and sets up array of structs for these
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

	//creates initial directory for rooms
	createRoomDir();

	//creates rooms with randomized names
	struct Room *rooms = randomRooms();

	//adds connections and types to rooms
	restOfRooms(rooms);

	return(0);
}

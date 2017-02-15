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
	
	printf("before1");
	char *roomNames[10] = {"Big","SMALL", "Medium", 
	     			"L-shaped", "C-shaped", "Swag",
				"Dank", "Dungeon", "Master", "Basement"};

	int numRooms = 0;	
	printf("before1");
	struct Room rooms[7];//= (struct Room*) calloc(NUM_ROOMS, sizeof(*rooms));
	printf("before");
	int index = -1;
	int i = 0;
	for(i=0;i<7;i++)
	{
		strcpy(rooms[i].name, "");
	}

	char *test;
       	test = strstr((char*)rooms[0].name, (char *) roomNames[0]);
	//printf("%s\n", rooms[0].name);
       	printf("%s\n", test);	
	//printf(":%s\n", roomNames[0]);

	while(numRooms < 7)
	{
		index = randInt(0,9);
		for(i=0; i<7; i++)
		{
			//test = strstr((char*)rooms[i].name, (char *) roomNames[index]);
			//if(test == NULL)
			//{
			//	printf("%s\n", test);	
			//	index = -1;
			//}
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

	index = 0;
	for(index=0; index<7; index++)
	{
		printf("ROOM: %s\n",rooms[index].name);
	}
	return(0);
}

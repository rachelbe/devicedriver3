#include <sg_driver.h>
#include <sg_service.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
//#include <cmpsc311_log.h>

//created cache


typedef struct 
{
    

    
    int time; // keeps the time the 
    char datablock[1024];

    uint64_t  nodeID; //node ID
    uint64_t  blockID; //block ID

    int isempty;


    //where blocks are located (20 max)
    


}blockstruct;

blockstruct block;

blockstruct *cache = NULL;  //global variable

//a fucntion that takes in a struct and prints it
void structprint(blockstruct *b)
{
	printf("Time: %d\n",b->time);
	printf("Data Blocks: ");
	for (int i = 0; i<5; i++)
	{
		printf("%c",b->datablock[i]);
	}
	printf("\n");
	printf("Node ID: %lu\n",b->nodeID);

	printf("Block ID: %lu\n",b->blockID);


}
void printcache()
{

	for (int i =0;i<32;i++)
	{
		structprint(&cache[i]);
		printf("\n\n");

	}
}


blockstruct *setcache()
{
	cache = malloc((32) * sizeof(blockstruct));
	

	for(int i=0;i<32;i++)
	{
		cache[i].isempty =1;
		//cache[i].datablock = malloc((1024) * sizeof(char));

	}

	return(cache);
}

void freecache()
{

	free(cache);
}

void addin(uint64_t  node,uint64_t  block, char *data)
{


	int highest=0;
	
	for(int k=0;k<32;k++)
	{
		if(cache[k].time>highest)
		{
			highest =cache[k].time;
			
		}
	}

	int i =0;

	while(cache[i].isempty !=1)
	{
		i++;
	}
	
	cache[i].isempty = 0;
	cache[i].time = highest + 1;

	cache[i].nodeID = node;
	cache[i].blockID = block;

	for(int j=0; j<1024;j++)
	{
		
		cache[i].datablock[j]= data[j];
	}


	

}


void evict()
{
	int lowest=999999999;
	int lowestindex =0;
	for(int i=0;i<32;i++)
	{
		if(cache[i].time<lowest && cache[i].isempty!=1)
		{
			lowest =cache[i].time;
			lowestindex=i;
		}
	}


	for(int j=0; j<1024;j++)
	{
		
		cache[lowestindex].datablock[j] = 0;
	}
	cache[lowestindex].nodeID = 0;
	cache[lowestindex].blockID = 0;
	cache[lowestindex].isempty=1;

}
//gives blockID,nodeID
char *search(uint64_t  node,uint64_t  block)
{
	for (int i=0;i<32;i++)
	{
		if(cache[i].nodeID == node && cache[i].blockID ==block)
		{
			int highest=0;
	
			for(int k=0;k<32;k++)
			{
				if(cache[k].time>highest)
				{
					highest =cache[k].time;
					
				}
			}
			cache[i].time = highest + 1;
			return &(cache[i].datablock[0]);
		}


	}

	return(NULL);

}



/*
int main()
{

	char one[1024] = "hello";
	char two[1024] = "hi";
	char three[1024] = "hey";
	setcache();

	addin(3,17,one);

	addin(2,18,two);
	
	addin(4,20,three);
	
	
	printcache();
	printf("%s\n",search(4,20));

}
*/

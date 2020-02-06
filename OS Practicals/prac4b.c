#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main(){
	int segment_id;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size=0x640000;
	
	//Allocate a shared memory segment
	segment_id=shmget (IPC_PRIVATE,shared_segment_size,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	//Attach the shared memory segment
	shared_memory=(char*) shmat(segment_id,0,0);
	printf("Shared memory attached at address:%p\n",shared_memory);

	//Determine the Segment Size
	shmctl (segment_id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	printf("Segment Size:%d\n",segment_size);

	//Write a String to the shared memory segment
	sprintf(shared_memory,"Hello,World");

	//Detach the shared memory segment
	shmdt(shared_memory);

	//Retach the shared memory segment,at a different address.
	shared_memory=(char*) shmat (segment_id,(void*) 0x5000000,0);
	printf("Shared memory reattached at address %p\n",shared_memory);

	//Print out the string from the memory
	printf("%s\n",shared_memory);

	//Detach the shared memory segment
	shmdt(shared_memory);

	//Deallocate the shared memory segment
	shmctl(segment_id,IPC_RMID,0);
	return 0;
}


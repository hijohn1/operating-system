


#include<iostream>
#include<cstdlib>
#include<ctime>
#include<pthread.h>
#include<unistd.h>
using namespace std;

#define min_pid 300         //define MARCROS
#define max_pid 5000
#define true 1
#define false 0
#define thno 10  // set up threads numbers

struct p                   // set up an object data type
{
	int pidv;
	int available;
};

p *pid;            // define an object for storing data

int allocate_map()
{
	pid = (struct p*) calloc ((max_pid - min_pid +1), sizeof(struct p)); //allocate memory to the object
	if(pid == NULL)
		return -1;
	else
	{
		pid[0].pidv = min_pid;          //mark the pid
		pid[0].available = true;
		for(int i=1; i<max_pid-min_pid+1;i++)
		{
			pid[i].pidv = pid[i-1].pidv + 1;
			pid[i].available = true;
		}
		return 1;
	}
}

int allocate_pid()
{
	int i;
	for(i=0; i<max_pid-min_pid+1;i++)
	{
		if(pid[i].available == true)      //check if the pid is available, return pid if it is available
		{
			pid[i].available = false;
			return pid[i].pidv;
		}
	}
	if(i==max_pid-min_pid+1)   
		return -1;
	else
		return 0;
}

void release_pid(int n) //release a pid if the pid is availavle
{
	pid[n-min_pid].available = true;
}

void *threadsAllocation(void *n)   //allocate threads to pid
{
	int t = *((int*) n), pid, rtime;

	pid = allocate_pid();      //allocate a pid and return pid number

	if(pid == -1)              //check if the pid is available
		cout<<"PID not available."<<endl;
	else           // assign thread to pid
	{
		cout<<"Thread "<<t<<" is assigned with PID "<<pid<<endl;

		rtime = rand()%30;         //let threads sleep between 0 to 30 secs
		
		sleep(rtime); //call sleep fucntion
		cout<<"Thread "<<t<<" PID "<<pid<<" is released after "<<rtime<<" seconds."<<endl;

		release_pid(pid);

	}

	pthread_exit(NULL);

}

int main()
{
	pthread_t p[thno]; //create threads to request pid

	srand(time(NULL));  //send of random time
	allocate_map();

	cout<<endl;

	for(int i=0;i<thno;i++)  //build up data structure so that threads can request a pid
	{
		if(pthread_create(&p[i], NULL, threadsAllocation, (void *)&i)) //if failed to create threads, program is terminated
		{
			cout<<"Failed to create thread "<<i<<endl;
			return -1;
		}
	}

	for(int i=0;i<thno;i++)   //wait until threads terminated
		pthread_join(p[i], NULL);

	cout<<endl<<"Finished !!"<<endl<<endl;
	return 0;
}



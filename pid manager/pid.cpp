#include<iostream>
#include<cstdlib>
using namespace std;

#define min_pid 300         //define MARCROS
#define max_pid 5000
#define true 1
#define false 0

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

int main()
{
	int pid;
	
	allocate_map();

	cout<<endl<<endl;
        
	//check if pids are available in the range and release one (303)
	if((pid=allocate_pid()) != -1)
		cout<<"The new pid: "<<pid<<endl;
	if((pid=allocate_pid()) != -1)
		cout<<"The new pid: "<<pid<<endl;
	if((pid=allocate_pid()) != -1)
		cout<<"The new pid: "<<pid<<endl;
	if((pid=allocate_pid()) != -1)
		cout<<"The new pid: "<<pid<<endl;

	cout<<endl<<"Releasing the pid: "<<pid<<endl<<endl;
	release_pid(pid);       //release the pid (303)

	if((pid=allocate_pid()) != -1)
		cout<<"The new pid: "<<pid<<endl;

	cout<<endl<<endl;
	return 0;
}



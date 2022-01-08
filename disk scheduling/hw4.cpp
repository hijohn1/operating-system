//CISC 3320 mw3 GuanYong Guan(23732325) HW4

#include<iostream>
#include<cmath> //use this library to calculate absolute value
#include<vector> //use vector as array to store service requests
#include<algorithm>   //use to sort array
using namespace std;

int c; //total movement of disk head (cost)

//50 requests
vector<int> t{4078, 153, 2819, 3294, 1433, 211, 1594, 2004, 2335, 2007, 771, 1043, 3950, 2784, 1881, 2931, 3599, 1245, 4086,520, 3901, 2866, 947, 3794, 2353, 3970, 3948, 1815, 4621, 372, 2684, 3088, 827, 3126, 2083, 584, 4420, 1294, 917, 2881, 3659, 2868, 100, 1581, 4581, 1664, 1001, 1213, 3439, 4706}; 


void FCFS(int n)    //first come first serve algorithm, n is initial position, a is 50 requests
{
	c=abs(t[0]-n);        //calculate movement between the first request and initial position
	for(int i=0;i<t.size()-1;i++)     //for-loop for adding up the movement of the rest service requests
	{
		c=c+abs(t[i+1]-t[i]);
	}
	cout<<"\nTotal head movement(FCFS): "<<c<<endl;
}

void SSTF(int n)  //shortest seek time first algorithm, n is initial position, a is 50 requests
{
	//min stands for minimum movement between two request, v array used to mark down if request has been visited before
	int min, v[50]={0}, flag=0, size=t.size();
	
	c=0; //reset the total movement to 0
	
	while(size--)  
	{
		min=999999;   //set up min as a maximum value so that the code can assign the first mimium movment
		for(int i=0;i<t.size();i++) //find the minimum movement between the current position and last position
		{
			if(v[i])     //if the current request has been visited before, skip it
				continue;
			if(abs(t[i]-n)<min)		       
			{
				min = abs(t[i]-n);
				flag=i;     // mark the current request
			}
		}

		c+=min;  // add up the minimum movement
		v[flag]=1; // mark down that the request just been visited
		n=t[flag]; // the value of current request
	}
	cout<<"\nTotal head movement(SSTF): "<<c<<endl;
}

void SCAN(int n, char d)  //SCAN alogrithm, n is initial position, a is 50 requests, d is disk direction for beginning moving
{
	//m used to find out if initial position in the request and mark down initial request location, ds stands for disk size
	int m=-1, ds=4999;
	vector<int> a;

	c=0; //reset the total movement to 0
	a=t;

	for(int i=0;i<a.size();i++)  //check if initial position in the 50 requests
	{
		if(a[i]==n)
			m=i;
	}

	if(m==-1)  //if initial position is not in the 50 requests, push it into the array a and sort it
	{
		a.push_back(n);
		sort(a.begin(),a.end());
	}
	else //if initial position is in the 50 requests, sort the array a
		sort(a.begin(),a.end());

	for(int i=0;i<a.size();i++) //find out the initial position location
	{
		if(a[i]==n)
			m=i;
	}

	if(m==0) // if initial position is 0, directly calculate the movement between two requests
	{
		d='r';  //change the disk direction for printing out
		for(int i=0;i<a.size()-1;i++)
		{
			c+=abs(a[i+1]-a[i]);
		}
	}

	// if initial position is the last position, directly calculate the movement between two requests instead of
	// going the nearest end first and then, move to the opposite direction	
	if(m==a.size()-1)
	{
		for(int i=m;i>0;i--)
		{
			c+=abs(a[i-1]-a[i]);
		}
	}

	//if the left side of initial position has less requests, it will move to the left side first and then move to right side
	if(m<=a.size()-1 && m>0)
	{
		for(int i=m;i>-1;i--)  //calculate the total movement of the left side
		{
			if(i>0)
				c+=abs(a[i-1]-a[i]);
		       
			//when it reaches the end of the left side request, move the head to the beginning of the disk
			else if(i==0) 
				c+=abs(0-a[i]);
		}

		//start the movement from the 0 and calculate the rest of total movement
		for(int i=m+1;i<a.size();i++)
		{
			if(i==m+1)
				c+=abs(a[i]-0);
			else if(i<a.size())
				c+=abs(a[i]-a[i-1]);
		}
	}

	if(d=='r') //print out the disk head moving direction 
		cout<<"\nThe disk head moved toward right side at the beginning in SCAN.";
	else
		cout<<"\nThe disk head moved toward left side at the beginning in SCAN";
	cout<<"\nTotal head movement(SCAN): "<<c<<endl<<endl;
}

int main()
{
	int ip=100; //initial position
	char d='l'; //direction of disk head and set to move to left side as default

	FCFS(ip);  //call first come first server, pass initial position of disk head
	SSTF(ip);  //call shortest seek time first, pass initial position of disk head
	SCAN(ip,d);  //call scan algorithm, pass initial postion of disk head and the default direction
	return 0;
}

//CISC 3320 mw3 GuanYong Guan(23732325) Extra credit

#include<iostream>
#include<cmath>  //call abs()
#include<vector> //store service request
#include<algorithm>  //used to sort array
using namespace std;

//c stands for cost, ds is disk size, t is service requests
int c, ds=4999;
vector<int> t{4078, 153, 2819, 3294, 1433, 211, 1594, 2004, 2335, 2007, 771, 1043, 3950, 2784, 1881, 2931, 3599, 1245, 4086, 520, 3901, 2866, 947, 3794, 2353, 3970, 3948, 1815, 4621, 372, 2684, 3088, 827, 3126, 2083, 584, 4420, 1294, 917, 2881, 3659, 2868, 100, 1581, 4581, 1664, 1001, 1213, 3439, 4706}; 

void CSCAN(int n, char d) //cscan function, pass initial position and 50 requests and d for the beginning moving direction
{
	int m=-1;//m used to find out if initial position in the request and mark down disk head location
	vector<int> a; //storing 50 requests

	a=t; //assign requests to another array
	c=0; //reset the total movement to 0

	for(int i=0;i<a.size();i++) //check if initial position in the 50 requests
	{
		if(a[i]==n)
			m=i;
	}

	if(m==-1) //if initial position is not in th 50 requests, push it into the array a and sort it
	{
		a.push_back(n);
		sort(a.begin(),a.end());
	}
	else //if initial position is in the 50 requests, sort the array a
		sort(a.begin(),a.end());

	for(int i=0;i<a.size();i++) //find out the disk head location
	{
		if(a[i]==n)
			m=i;
	}

	if(m==0) //if initial position(m) is 0, directly calculate the movement between two requests
	{
		for(int i=m;i<a.size()-1;i++)
		{
			c+=abs(a[i+1]-a[i]);
		}
	}

	//if initial position(m) is the last position, directly calculate the movement between two requests from the
	//end of the right side request
	if(m==a.size()-1)
	{
		d='r';  //change the disk direction for printing out
		for(int i=m;i>0;i--)
		{
			c+=abs(a[i-1]-a[i]);
		}
	}

        //if initial position(m) is between 0 and the last position(a.size()), start calculation from the right side
	//if it last request is met, move the disk head to the end of the disk(ds) and reverse its direction for the
	//left side requests.
	if(m>0 && m<a.size()-1)
	{
		for(int i=m;i<a.size()-1;i++)  //keep adding up the movement cost of right side request
		{
			c+=abs(a[i+1]-a[i]);
		}

		//add up the cost of disk head to the bottom of the disk, the bottom of the disk to the head
		//of the disk, the head of the disk to the beginning of left side request
		c=c+abs(ds-a[a.size()-1])+(ds-0)+abs(0-a[0]); 

		for(int i=0;i<m-1;i++)//start the calculation from the beginning of right side
		{
			c+=abs(a[i+1]-a[i]);
		}
	}

        if(d=='r') //print out the disk head moving direction 
		cout<<"\nThe disk head moved toward right side at the beginning in C-SCAN.";
	else
		cout<<"\nThe disk head moved toward left side at the beginning in C-SCAN";
	cout<<"\nTotal head movement(C-SCAN): "<<c<<endl<<endl;
}

void LOOK(int n, char d) //look function, n is initial position and a is 50 requests and d for the beginning moving direction
{
	int m=-1; //m used to find out if initial position in the request and mark down disk head location
	vector<int> a;
	
	a=t; //assign requests to another array
	c=0; //reset the total movement to 0

	for(int i=0;i<a.size();i++) //check if initial position in the 50 requests
	{
		if(a[i]==n)
			m=i;
	}

	if(m==-1) //if initial position is not in th 50 requests, push it into the array a and sort it
	{
		a.push_back(n);
		sort(a.begin(),a.end());
	}
	else //if initial position is in the 50 requests, sort the array a
		sort(a.begin(),a.end());

	for(int i=0;i<a.size();i++) //find out the disk head location
	{
		if(a[i]==n)
			m=i;
	}

	if(m==0) //if initial position(m) is 0, directly calcualte the movement between two requests
	{
		for(int i=0;i<a.size()-1;i++)
		{
			c+=abs(a[i+1]-a[i]);
		}
	}

        //if initial position(m) is the last position, directly calculate the movement between two requests from the end
	//of the right side
	if(m==a.size()-1)
	{
                d='r';  //change the disk direction for printing out
		for(int i=m;i>0;i--)
		{
			c+=abs(a[i-1]-a[i]);
		}
	}

	//if initial position(m) is between 0 and the last position(a.size()), start calculation from the right side
	//if it last request is met, reverse its direction to the left side request.
	if(m>0 && m<a.size()-1)
	{

		for(int i=m;i<a.size()-1;i++) //keep adding up the movement cost of right side request
		{
			c+=abs(a[i+1]-a[i]);
		}

		c+=abs(a[m-1]-a[a.size()-1]); //move disk head to the end of left side reqest (m-1) and add up the cost

		for(int i=m-1;i>0;i--) //add up the cost of movement of left side
		{
			c+=abs(a[i]-a[i-1]);
		}
	}

        if(d=='r') //print out the disk head moving direction 
		cout<<"\nThe disk head moved toward right side at the beginning in LOOK.";
	else
		cout<<"\nThe disk head moved toward left side at the beginning in LOOK";
	cout<<"\nTotal head movement(LOOK): "<<c<<endl<<endl;
}

void CLOOK(int n, char d) //clook function, n is initial position and a is 50 requests
{
	int m=-1; //m used to find out if initial position in the request and mark down disk head location
	vector<int> a;
	
	a=t;//assign requests to another array
	c=0;//reset the total movement to 0

	for(int i=0;i<a.size();i++) //check if initial position in the 50 requests
	{
		if(a[i]==n)
			m=i;
	}

	if(m==-1) //if initial position is not in th 50 requests, push it into the array a and sort it
	{
		a.push_back(n);
		sort(a.begin(),a.end());
	}
	else //if initial position is in the 50 requests, sort the array a
		sort(a.begin(),a.end());

	for(int i=0;i<a.size();i++) //find out the disk head location
	{
		if(a[i]==n)
			m=i;
	}

	if(m==0) //if initial position(m) is 0, directly calcualte the movement between two requests
	{
		for(int i=0;i<a.size()-1;i++)
		{
			c+=abs(a[i+1]-a[i]);
		}
	}

        //if initial position(m) is the last position, directly calculate the movement between two from the end
	//of the right side
	if(m==a.size()-1)
	{
                d='r';  //change the disk direction for printing out
		for(int i=m;i>0;i--)
		{
			c+=abs(a[i-1]-a[i]);
		}
	}

	//if initial position(m) is between 0 and the last position(a.size()), start calculation from the right side
	//if it last request is met, reverse its direction for the left side request.
	if(m>0 && m<a.size()-1)
	{

		for(int i=m;i<a.size()-1;i++) //keep adding up the movement cost of right side request
		{
			c+=abs(a[i+1]-a[i]);
		}


		// move head disk to the beiginning of left side request(0) and add up the cost of movement
		c+=abs(a[a.size()-1]-a[0]);

		for(int i=0;i<m-1;i++) //add up the cost of movement of the left side requests from the beginning(0)
		{
			c+=abs(a[i+1]-a[i]);
		}
	}

        if(d=='r') //print out the beginning moving direction 
		cout<<"\nThe disk head moved toward right side at the beginning in C-LOOK.";
	else
		cout<<"\nThe disk head moved toward left side at the beginning in C-LOOK";
	cout<<"\nTotal head movement(C-LOOK): "<<c<<endl<<endl;
}

int main()
{
	int ip=100; // initial position
	char d='r'; // default moving direction

	CSCAN(ip, d);  //call C-SCAN function
	LOOK(ip, d);  //call LOOK function
	CLOOK(ip, d);  //call CLOOK function
	return 0;
}

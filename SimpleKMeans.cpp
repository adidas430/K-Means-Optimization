#include<iostream>
#include<time.h>
#include<math.h>
#include<stdio.h>
#include<cstdlib>
#include<cfloat>
using namespace std;

struct point                                //X,Y and clusterID. Must update this wrt the input data.
{
	float x;
	float y;
	int clusterId;
};

float euclideanMeasure(point a, point b)   //Returns distance measure between two points. (Update this if the attributes change too!)
{
	float dist=sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
	return dist;
	
}

int randomizer(int n)                       //designed to return random numbers 
{											//Feel free to change Rand Seed in the future
	int v;
	v=rand()%n;
	return v;
}

bool checkIfInArray(int a,int b[],int n)   //Function to see if an element exist in an Array.
{
	for (int i=0;i<n;i++)
	{
		if(a==b[i])
		return true;
	}
	return false;
}

void initialize(int a[],int n)			//For setting all those variable sized arrays to -1
{
	for (int i=0;i<n;i++)
	a[i]=-1;
}

point centroidRecalculate(point a[],int id,int n)
{
	int k=0;
	float x1=0;
	float y1=0;
	for(int i=0;i<n;i++)
	{
		if (a[i].clusterId==id)
		{
			k++;
			x1+=a[i].x;
			y1+=a[i].y;
		}
	}
	x1=x1/k;
	y1=y1/k;
	
	return {x1,y1,id};
}



int main()
{
point dataset[10]; //all our points will be stored here
dataset[0]={1.0,1.0,-1};
dataset[1]={1.5,2.0,-1};
dataset[2]={3.0,4.0,-1};
dataset[3]={5.0,7.0,-1};
dataset[4]={3.5,5.0,-1};
dataset[5]={4.5,5.0,-1};
dataset[6]={3.5,4.5,-1};
dataset[7]={6,4.5,-1};
dataset[8]={3,4.5,-1};
dataset[9]={2,2,-1};


int k;
cout<<"Enter Number of Clusters"<<endl;
cin>>k;				//The K value. The number of clusters
cout<<"Enter number of data points"<<endl; //We know its 7 for now. But we'll read from files later..
int n;
cin>>n;			           	           //The n value. The number of data points.
point centroids[k]; 		          //Array to hold just the centroids.
int randomIndex[k];		 			 //Array to hold the random indices. Initiaized to -1.
initialize(randomIndex,k);
bool isRandomised=false;            //variable to see if all of the random indices have been filled.
int index=0;
int randomValue;

//////////////////////////////////////CENTROID SELECTION AREA: DO NOT TOUCH////////////////////////////////////
while(!isRandomised)
	{
		randomValue=randomizer(n);
		if(!(checkIfInArray(randomValue,randomIndex,k)))
		{
			centroids[index]={dataset[randomValue].x,dataset[randomValue].y,index};
			dataset[randomValue].clusterId=index;
			randomIndex[index]=randomValue;
			index ++;
			if(index==(k))
				isRandomised=true;
		
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


cout<<"The Centroids Selected Are"<<endl;
for (int z=0;z<k;z++)
{
   cout<<centroids[z].x<<" "<<centroids[z].y<<" "<<centroids[z].clusterId<<endl;        //Print out the selected centroids
}

////////////////////////////////////DISTANCE MINIMZATION & CENTROID UPDATION AREA///////////////////////////////

	//Distance between 2 points.Initialized to MAXIMUM possible value

int minIndex;	//Index of closest centroid
bool convergence=false;

while(!convergence)
{
convergence=true;
for(int l=0;l<n;l++)
{
	bool isSamePoint=false;
	float tempDist=FLT_MAX;
	float dist=FLT_MAX;
	for(int m=0;m<k;m++)
	{
		tempDist=euclideanMeasure(dataset[l],centroids[m]);   //Measure distance between each point and each centroid. 
		if (tempDist!=0.0)									//Asssuming no points are repeated. Take this off if that possibility exists.
		{
			if(tempDist<dist)
			{
				dist=tempDist;									//update index and centroid
				minIndex=m;
				
			}
		}
		else
		{
			isSamePoint=true;        //The data point under consideration is a seed point too. Recounting it can skew centroid values
		
			break;
			
		}
	}
	
	if(!isSamePoint)
	{
		if(dataset[l].clusterId!=centroids[minIndex].clusterId)
			convergence=false;
		dataset[l].clusterId=centroids[minIndex].clusterId;
		
	}
}

cout<<"UPDATED DATASET AFTER ONE ITERATION"<<endl;
for(int g=0;g<n;g++)
{
	cout<<dataset[g].x<<" "<<dataset[g].y<<" "<<dataset[g].clusterId<<endl;
}

cout<<"UPDATED CENTROIDS AFTER ONE ITERATION"<<endl;
for(int t=0;t<k;t++)
{
	centroids[t]=centroidRecalculate(dataset,t,n);
	cout<<centroids[t].x<<" "<<centroids[t].y<<" "<<centroids[t].clusterId<<endl;
}
}




}

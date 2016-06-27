/*
 * TestThisOut.cpp
 *
 *  Created on: May 23, 2016
 *      Author: Barrett
 */
#include <iostream>
#include <cstdarg>

using namespace std;

inline double sum(int num, ...){
	va_list argu;
	double sum;

	va_start(argu, num);
	for (int i = 0; i < num; i++){
		sum += va_arg(argu, double);
	}
	va_end(argu);
	return sum;
}

inline void hammertime(){
	cout<<"Stop! HAMMERTIME\n"<<endl;
}

struct node{
	int x;
	node *next;
};


class sampClass{
public:
	sampClass();
	~sampClass();
	void suhdude();
protected:
	int dude;
};

sampClass::sampClass(){
	dude = 8005;
}
sampClass::~sampClass(){

}
void sampClass::suhdude(){
	cout<<dude<<endl;
}


int main()
{
  int thisisanumber;
  hammertime();
  cout<<"Please enter a number: "<<endl;
  hammertime();
  cin>> thisisanumber;
  cin.ignore();
  cout<<"You entered: "<< thisisanumber <<endl;
  cout<<"SUH DUDE"<<endl;
  sampClass bruh;
  bruh.suhdude();

  node *root = new node;
  root = new node;
  root->next = 0;
  root->x = 5;

  node *second = new node;
  second->next = 0;
  second->x = 96;
  root->next = second;

  node *third = new node;
  third->next=0;
  third->x= 42;
  second->next = third;

  node *conductor;
  conductor = root;
  while(conductor != NULL){
	  cout<<conductor->x<<endl;
	  conductor = conductor->next;
  }
cout<<sum(6, 5.6, 53.2, 15.8, 15.4, 6.9, 4.1)<<endl;
cout<<sum(3, 5.6, 53.2, 15.8)<<endl;

}




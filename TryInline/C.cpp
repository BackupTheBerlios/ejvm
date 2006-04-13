#include<stdio.h>
class array{
int arr[6];
 public: inline void setatAtIndex(int index,int value){arr[index]=value;};
};
array* ptr = new array;

int main (void){

//hay hay
ptr->setatAtIndex(1,6);
//hay hay
}

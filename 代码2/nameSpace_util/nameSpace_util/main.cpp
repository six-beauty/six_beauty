#include "util.h"
#include <iostream>
using namespace std;
#define CountArray(T)  (sizeof(T)/sizeof(T[0]))
int main()
{
	Util::test();
	char crr[]={"asdf"};
	int arr[14]={1,3,4,5,6};
	cout<<Util::CountArray<char>(crr)<<endl;
	cout<<Util::CountArray<int>(arr)<<endl;
	cout<<CountArray(crr)<<endl;
	cout<<CountArray(arr)<<endl;

	return 0;
}

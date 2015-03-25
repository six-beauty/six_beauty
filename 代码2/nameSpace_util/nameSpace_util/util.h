#ifndef _UTIL_H
#define _UTIL_H
namespace Util
{
	template <typename T>
	int CountArray(T arr[])
	{
		return (sizeof(arr)/sizeof(arr[0]));
	}

	void test();


}


#endif

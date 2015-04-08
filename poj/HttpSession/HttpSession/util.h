#ifndef _util_h
#define _util_h

template<typename T>
void SafeDelete(void* pDate)
{
	if(pDate == NULL)
		return;
	try
	{
		delete pDate;
		pDate = NULL;
	}
	catch (...)
	{
	}
}



#endif


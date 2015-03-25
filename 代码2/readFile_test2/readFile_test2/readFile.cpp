#include <afx.h>
#include <iostream>
using namespace std;

int main()
{
	CFile f;
	if(!f.Open(TEXT("F:\\mailfile\\55e736d12f2eb938e9ea5eb1d5628535e4dd6fe9.jpg"),CFile::modeRead|CFile::modeNoTruncate|CFile::typeBinary))  
	{  
		return 0;  
	}  
	int len=(int)f.GetLength();  
	cout<<len<<endl;
	char *m_pFileBuffer=new char[len+1];  
	memset(m_pFileBuffer,0,len+1);  
	f.Read(m_pFileBuffer,len);  
	printf("==========================================================================\n");
	printf("%s\n",m_pFileBuffer);
	printf("==========================================================================\n");
	delete[] m_pFileBuffer;
	return 0;
}


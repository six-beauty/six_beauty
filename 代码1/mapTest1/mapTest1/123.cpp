#include<map>
#include<string>
#include<iostream>
using namespace std;
void main()  
{  
	

	map<string,int> m_string;//28  
	cout << sizeof(m_string) <<endl;  

	m_string.insert(map<string,int>::value_type("wo",1));
	m_string.insert(map<string,int>::value_type("ni",2));


	for(map<string,int>::iterator itr=m_string.begin();itr!=m_string.end();itr++)
		cout<<itr->first<<":"<<itr->second<<endl;

	cout << sizeof(m_string) <<endl;  




	

} 
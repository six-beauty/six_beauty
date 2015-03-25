#include<iostream>
#include<vector>
using namespace std;
typedef vector<int> INTVECTOR;

int main()
{	
	//vec1对象初始为空
	INTVECTOR vec1;
	//vec2对象最初有10个值为6的元素
	INTVECTOR vec2(10,6);
	//vec3对象最初有3个值为6的元素，拷贝构造
	INTVECTOR vec3(vec2.begin(),vec2.begin()+3);
	//声明一个名为itrsa的双向迭代器
/*	INTVECTOR::iterator itrsa;
	
	//从前向后显示vec1中的数据
	cout<<"vec1.begin()--vec1.end():"<<endl;
	for (itrsa =vec1.begin(); itrsa !=vec1.end(); itrsa++)
	{
		cout<<"falg"<<endl;
		cout << *itrsa << " ";
	}
	cout<<endl;
	//从前向后显示vec2中的数据
	cout<<"vec2.begin()--vex2.end():"<<endl;
	for(itrsa=vec2.begin();itrsa!=vec2.end();itrsa++)
	  cout<< *itrsa<< " ";
	cout<<endl;
	//从前向后显示vec3中的数据
	cout<<"vec3.begin()--vec3.end():"<<endl;
	for(itrsa=vec3.begin();itrsa!=vec3.end();itrsa++)
		cout<<*itrsa<<" ";
	cout<<endl;
	
	//测试添加和插入成员函数，vector不支持从前插入
	vec1.push_back(2);	//从后面添加一个成员
	vec1.push_back(4);
	//从vec1第一的位置开始插入vec3的所有成员
	vec1.insert(vec1.begin(),vec3.begin(),vec3.end());
	cout<<"aftre push() and insert() now the vec1 is:"<<endl;
	for(itrsa=vec1.begin();itrsa!=vec1.end();itrsa++)
	  cout<< *itrsa<<" ";
	cout<<endl;

	//测试赋值成员函数
	vec2.assign(8,1);	//重新给vec2复制，8个成员的初始值都为1
	cout<<"vec2.assign(8,1):"<<endl;
	for(itrsa=vec2.begin();itrsa!=vec2.end();itrsa++)
	  cout<< *itrsa<< " ";
	cout<<endl;

	vec2.assign(vec1.begin(),vec1.end());
	cout<<"vec2.assign(vec1.begin(),vec1.end()):"<<endl;
	for(itrsa=vec2.begin();itrsa!=vec2.end();itrsa++)
	  cout<< *itrsa<< " ";
	cout<<endl;

	//测试引用类函数
	cout<<"vec1.front()="<<vec1.front()<<endl;	//vec1第零个成员
	cout<<"vec1.back()="<<vec1.back()<<endl;	//vec1的最后一个成员
	cout<<"vec1.at(2)="<<vec1.at(2)<<endl;		//vec1的第5个成员
	cout<<"vec1[4]="<<vec1[4]<<endl;
	*/
	INTVECTOR::iterator itrsa;
	//测试移除和删除
	for(int i=1;i<8;i++)
		vec1.push_back(i);
	vec1.push_back(7);
	vec1.push_back(7);
	vec1.push_back(7);
	//从前向后显示vec1中的数据
	cout<<"vec1.begin()--vec1.end():"<<endl;
	for (itrsa =vec1.begin(); itrsa !=vec1.end(); itrsa++)
	{
		cout << *itrsa << " ";
	}
	cout<<endl<<"flag"<<endl;
/*	for(itrsa=vec1.begin();itrsa!=vec1.end();)
	{
		if(*itrsa==7)
			itrsa=vec1.erase(itrsa);
		else
			itrsa++;		
	}
	*/
	//从前向后显示vec1中的数据
	cout<<"vec1.begin()--vec1.end():"<<endl;
	for (itrsa =vec1.begin(); itrsa !=vec1.end(); itrsa++)
	{
		cout << *itrsa << " ";
	}
	
	return 0;
}
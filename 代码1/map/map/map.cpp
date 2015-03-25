#include<iostream>
#include<map>
#include<string>
using namespace std;

typedef struct studentInfo{
		int nId;
		string name;
		bool operator<(const studentInfo& _stu)const
		{
			if(nId<_stu.nId)return true;
			if(nId>_stu.nId)return false;
			return name.compare(_stu.name)<0;
		};
		studentInfo(int n,string nam)
		{
			nId=n;
			name=nam;
		}
	}stuInfo,*pstuInfo;	
int main()
{
	/*
	//map的声明
	map<int,string> stumap;
	//map添加数据3种方式
	stumap.insert(make_pair(1,"student1"));
	stumap.insert(make_pair(2,"student2"));
	stumap.insert(pair<int,string>(3,"student3"));
	stumap.insert(map<int,string>::value_type(4,"student4"));
	//遍历输出
	map<int,string>::iterator syitr;
	for(syitr=stumap.begin();syitr!=stumap.end();syitr++)
		cout<<syitr->first<<"   "<<syitr->second<<endl;
	//遍历查找并删除
	syitr=stumap.find(3);
	if(syitr==stumap.end())
		cout<<"no found!"<<endl;
	else
		stumap.erase(syitr);
	*/
	
	map<stuInfo,int> bullshit;
//	stuInfo stu1(1,"student1");
	//stuInfo stu2={2,"student2"};

	bullshit.insert(make_pair(studentInfo(1,"student1"),89));
	bullshit.insert(make_pair(studentInfo(1,"student2"),90));


	
	map<stuInfo,int>::iterator itrsa;
	for(itrsa=bullshit.begin();itrsa!=bullshit.end();itrsa++)
		cout<<itrsa->first.nId<<","<<itrsa->first.name<<","<<itrsa->second<<endl;




	return 0;
}
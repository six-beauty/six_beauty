#include <iostream>
#include <map>

int main ()
{
	std::multimap<char,int> mymultimap;

	mymultimap.insert(std::make_pair('x',100));
	mymultimap.insert(std::make_pair('x',100));
	mymultimap.insert(std::make_pair('x',100));
	mymultimap.insert(std::make_pair('x',100));
	mymultimap.insert(std::make_pair('x',100));
	mymultimap.insert(std::make_pair('x',100));
	mymultimap.insert(std::make_pair('x',200));
	mymultimap.insert(std::make_pair('x',350));
	mymultimap.insert(std::make_pair('x',500));
	mymultimap.insert(std::make_pair('y',500));
	std::cout << "mymultimap.size() is " << mymultimap.count('x') << '\n';
	std::cout<<"x.size="<<mymultimap.size()<<std::endl;

	return 0;
}
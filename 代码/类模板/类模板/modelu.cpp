//类的声明和实现分离，

#include "modelu.h"


template <typename Any>
void Util<Any>::Swap(Any& a, Any& b)
{
	Any sw=a;
	a=b;
	b=sw;
}


template class Util<int>;


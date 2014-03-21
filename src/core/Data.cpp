#include "Data.h"

Data::Data()
{}

Data::Data(const Data& other)
{}

Data::Data(Data&& other)
{}

IntData::IntData()
: _i(0)
{}

IntData::IntData(int i)
: _i(i)
{}

IntData::IntData(const IntData& other)
{
	_i = other._i;
}

IntData::IntData(IntData&& other)
{
	_i = other._i;
}

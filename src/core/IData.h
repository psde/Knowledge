#pragma once

#include <memory>

template<typename Derived, typename Base>
std::unique_ptr<Derived> static_unique_ptr_cast(std::unique_ptr<Base>&& p)
{
	auto d = static_cast<Derived *>(p.release());
	return std::unique_ptr<Derived>(d);
}

template<typename Derived, typename Base>
std::unique_ptr<Derived> dynamic_unique_ptr_cast(std::unique_ptr<Base>&& p)
{
	if (Derived *result = dynamic_cast<Derived *>(p.get())) {
		p.release();
		return std::unique_ptr<Derived>(result);
	}
	return std::unique_ptr<Derived>(nullptr);
}

class IData
{
public:
	IData();
	IData(const IData& other);
	IData(IData&& other);

	//Data& operator= (const Data&) {};
	//Data& operator= (Data&&){}
	virtual ~IData() { }
};
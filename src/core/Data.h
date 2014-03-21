#pragma once

class Data
{
public:
	Data();
	Data(const Data& other);
	Data(Data&& other);

	//Data& operator= (const Data&) {};
	//Data& operator= (Data&&){}
	virtual ~Data() { }
};

class IntData : public Data
{
private:
	int _i;

public:
	IntData();
	IntData(int i);
	IntData(const IntData& other);
	IntData(IntData&& other);

	int getInt()
	{
		return _i;
	}
};
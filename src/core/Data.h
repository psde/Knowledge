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
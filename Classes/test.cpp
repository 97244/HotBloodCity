#pragma once


enum MyEnum
{
	en_aa = 1,
	en_bb = 2,
};

class  AA
{
public:
	enum MyEnum
	{
		en_aa = 1,
		en_bb = 2,
	};

	void dd(MyEnum tt);
protected:
private:
};


void AA::dd(MyEnum tt)
{
	switch (tt)
	{

	}
}
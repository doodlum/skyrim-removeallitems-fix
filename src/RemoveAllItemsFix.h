#pragma once


class RemoveAllItemsFix 
{
public:
	static RemoveAllItemsFix* GetSingleton()
	{
		static RemoveAllItemsFix singleton;
		return &singleton;
	}

	void DataLoaded();
};

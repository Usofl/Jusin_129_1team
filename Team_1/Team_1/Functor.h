#pragma once


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

class Safe_delete
{
public:
	template<typename T>
	void operator()(T& _Temp)
	{
		if (_Temp)
		{
			delete _Temp;
			_Temp = nullptr;
		}
    }
};
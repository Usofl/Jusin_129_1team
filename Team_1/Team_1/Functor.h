#pragma once

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

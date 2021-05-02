#pragma once

template<class T>
void Safe_Delete(T& pObject)
{
	if (pObject)
	{
		delete pObject;
		pObject = nullptr;
	}
}
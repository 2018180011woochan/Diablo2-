#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template<typename T>
ULONG Safe_Release(T& rInstance)
{
	DWORD dwRefCnt = 0; 
	if (rInstance)
	{
		dwRefCnt = rInstance->Release(); 
		rInstance = nullptr;
		return dwRefCnt; 
	}
	return dwRefCnt; 
}
template<typename T>
void Safe_Delete(T& rInstance)
{
	if (rInstance)
	{
		delete rInstance; 
		rInstance = nullptr; 
	}
}

#endif // !__FUNCTION_H__

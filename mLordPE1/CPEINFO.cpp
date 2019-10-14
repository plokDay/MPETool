#include "stdafx.h"



CPEINFO::CPEINFO()
{
}


CPEINFO::~CPEINFO()
{
}
DWORD CPEINFO::Rva2Foa(DWORD dwRva)
{
	//文件对齐与内存对齐相等
	if (mpe.pNt->OptionalHeader.FileAlignment == mpe.pNt->OptionalHeader.SectionAlignment)
	{
		return dwRva;
	}
	DWORD offset = 0;
	//1.判断这个RVA落在哪个区段
	
	DWORD dwSectionCount = pNt->FileHeader.NumberOfSections;

	for (int i = 0; i < dwSectionCount; ++i)
	{
		if (dwRva >= pSection[i].VirtualAddress
			&& dwRva < (pSection[i].SizeOfRawData + pSection[i].VirtualAddress))
		{
			//2.遍历找到后根据公式计算
			offset = dwRva - pSection[i].VirtualAddress + pSection[i].PointerToRawData;
		}
	}
	return offset;
}

CString CPEINFO::GetSection(DWORD dwRva)
{
	//1.判断这个RVA落在哪个区段
	CString section;
	DWORD dwSectionCount = mpe.pNt->FileHeader.NumberOfSections;

	for (int i = 0; i < dwSectionCount; ++i)
	{
		if (dwRva >= mpe.pSection[i].VirtualAddress
			&& dwRva < (mpe.pSection[i].SizeOfRawData + mpe.pSection[i].VirtualAddress))
		{
			//2.遍历找到后根据公式计算
			section = (CString)mpe.pSection[i].Name;
		}
	}
	return section;
}

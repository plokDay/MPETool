#include "stdafx.h"



CPEINFO::CPEINFO()
{
}


CPEINFO::~CPEINFO()
{
}
DWORD CPEINFO::Rva2Foa(DWORD dwRva)
{
	//�ļ��������ڴ�������
	if (mpe.pNt->OptionalHeader.FileAlignment == mpe.pNt->OptionalHeader.SectionAlignment)
	{
		return dwRva;
	}
	DWORD offset = 0;
	//1.�ж����RVA�����ĸ�����
	
	DWORD dwSectionCount = pNt->FileHeader.NumberOfSections;

	for (int i = 0; i < dwSectionCount; ++i)
	{
		if (dwRva >= pSection[i].VirtualAddress
			&& dwRva < (pSection[i].SizeOfRawData + pSection[i].VirtualAddress))
		{
			//2.�����ҵ�����ݹ�ʽ����
			offset = dwRva - pSection[i].VirtualAddress + pSection[i].PointerToRawData;
		}
	}
	return offset;
}

CString CPEINFO::GetSection(DWORD dwRva)
{
	//1.�ж����RVA�����ĸ�����
	CString section;
	DWORD dwSectionCount = mpe.pNt->FileHeader.NumberOfSections;

	for (int i = 0; i < dwSectionCount; ++i)
	{
		if (dwRva >= mpe.pSection[i].VirtualAddress
			&& dwRva < (mpe.pSection[i].SizeOfRawData + mpe.pSection[i].VirtualAddress))
		{
			//2.�����ҵ�����ݹ�ʽ����
			section = (CString)mpe.pSection[i].Name;
		}
	}
	return section;
}

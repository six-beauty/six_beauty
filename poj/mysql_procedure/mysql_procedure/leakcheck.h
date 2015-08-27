#pragma once

#define CRTDBG_MAP_ALLOC
#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <iostream>
#include <Psapi.h>
#pragma comment(lib,"psapi.lib")

#ifdef _DEBUG
#define malloc(s)           _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s)        _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s)       _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)

#define new					new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

#define DEFAULT_OUT_TITLE	\
	TEXT("ȱҳ�ж���  ������(KB)  ���(KB)  ����ֵ(KB)")
#define DEFAULT_OUTPUT_FORMAT	\
	TEXT("  %u    %u    %u    %u  ")

// �ֽڵ�λת������0ȡ��
#define B2KB(x)	((x) >> 10)

///////////////////////////////////////////////////////////////////////////////////

void ConstructOutput()
{
	PROCESS_MEMORY_COUNTERS pmc;
	std::cout<<DEFAULT_OUT_TITLE<<std::endl;
	if(!GetProcessMemoryInfo(GetCurrentProcess(),&pmc,sizeof(pmc)))return ;

	char output[512] = {0};
	_sntprintf(output,sizeof(output),DEFAULT_OUTPUT_FORMAT,
		(pmc.PageFaultCount),B2KB(pmc.WorkingSetSize),B2KB(pmc.PagefileUsage),B2KB(pmc.PeakPagefileUsage));
	std::cout<<output<<std::endl;
}
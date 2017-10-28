#include "stdafx.h"
#include <process.h>

#include "CriticalSection.h"

#define THREAD_NUM 10
#define CALL_NUM 100
#define TOTAL_COUNT 1000

#define USE_CRITICAL_SECTION 1

CriticalSection cs;
int count = 0;

void test(int id)
{
#if USE_CRITICAL_SECTION == 1
	ScopedCriticalSection scs(cs);
#endif

	volatile int a;
	
	a = count;
	a++;
	Sleep(1);
	count = a;
}

unsigned __stdcall run(void *p)
{
	int id = (int)p;
	_tprintf(_T("start thread=%d\n"), id);

	for (int i = 0; i < 100; ++i) {
		test(id);
	}

	_tprintf(_T("finish thread=%d\n"), id);

	return 0;
}

int main()
{
	uintptr_t threads[THREAD_NUM];

	for (int i = 0; i < THREAD_NUM; ++i) {
		threads[i] = _beginthreadex(NULL, 0, run, (void*)i, 0, NULL);
	}

	for (int i = 0; i < THREAD_NUM; ++i) {
		WaitForSingleObject((HANDLE)(threads[i]), INFINITE);
	}

	if (count == TOTAL_COUNT) {
		_tprintf(_T("OK : count=%d\n"), count);
	}
	else {
		_tprintf(_T("NG : count=%d\n"), count);
	}

    return 0;
}


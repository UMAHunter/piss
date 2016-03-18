#include "GlobalTime.h"

GlobalTime::GlobalTime()
{
    LARGE_INTEGER fc;

    if (!QueryPerformanceFrequency(&fc))
    {
        assert(FALSE);
    }
    m_frequency = fc.QuadPart;  //计时器的频率

}

UINT64 GlobalTime::GetMicroS()
{
    assert(m_frequency>1000*1000);

    LARGE_INTEGER fc;

    if (!QueryPerformanceCounter(&fc))
    {
        assert(FALSE);
    }

    UINT64 c = fc.QuadPart;
    UINT64 s = (c) / (m_frequency / 1000 / 1000);
    return s;
}

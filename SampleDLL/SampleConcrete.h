#pragma once
#include "ISample.h"

class EXPORT SampleConcrete : public ISample
{
public:
    SampleConcrete();
    ~SampleConcrete();
    int SampleMethod1(int lhs);
    int SampleMethod2(int lhs, int rhs);
    static int StaticMethod(int lhs);
};


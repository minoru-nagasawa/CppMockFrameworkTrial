#pragma once
#include "ExportDefinition.h"

class EXPORT ISample
{
public:
    virtual int SampleMethod1(int lhs) = 0;
    virtual int SampleMethod2(int lhs, int rhs) = 0;
};

#include "stdafx.h"
#include "SampleConcrete.h"

SampleConcrete::SampleConcrete()
{
}
SampleConcrete::~SampleConcrete()
{
}
int SampleConcrete::SampleMethod1(int lhs)
{
    return lhs;
}
int SampleConcrete::SampleMethod2(int lhs, int rhs)
{
    return lhs + rhs;
}
int SampleConcrete::StaticMethod(int lhs)
{
    return lhs;
}

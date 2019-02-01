#include "stdafx.h"
#include "CppUnitTest.h"
#include "fakeit.hpp"
#include "../SampleDLL/SampleConcrete.h"

using namespace fakeit;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFakeIt
{
	TEST_CLASS(UnitTest)
	{
	public:
        TEST_METHOD(TestMethod1)
        {
            // �����������C���^�[�t�F�[�X���w�肷��
            Mock<ISample> mock;

            // �ȉ��̂悤�ɂ���ƁASampleMethod1�����s����ƁA�K��1���Ԃ��Ă���
            When(Method(mock, SampleMethod1)).AlwaysReturn(1);

            // ISample�^�̃I�u�W�F�N�g���擾
            ISample& sample = mock.get();

            // �����܂ł̏����ɂ��Asample.SampleMethod1(10)��1��Ԃ��悤�ɂȂ��Ă���B
            Assert::AreEqual(1, sample.SampleMethod1(10));
        }

        TEST_METHOD(TestMethod2)
        {
            // �����������C���^�[�t�F�[�X���w�肷��
            Mock<ISample> mock;

            // �ȉ��̂悤��Using���g���ƁA���\�b�h�̈������w��ł���B
            // SampleMethod1(1)�����s����ƁA�K��1���Ԃ��Ă���
            // SampleMethod1(2)�����s���Ă��A1�͕Ԃ��Ă��Ȃ�
            When(Method(mock, SampleMethod1).Using(1)).AlwaysReturn(1);

            // ISample�^�̃I�u�W�F�N�g���擾
            ISample& sample = mock.get();

            // �����܂ł̏����ɂ��Asample.SampleMethod1(1)��1��Ԃ��悤�ɂȂ��Ă���B
            Assert::AreEqual(1, sample.SampleMethod1(1));

            // �������w�肵�ĂȂ�sample.SampleMethod1(2)�����s����ƃe�X�g���s
            //sample.SampleMethod1(2);
        }

        TEST_METHOD(TestMethod3)
        {
            // ���������N���X�̏ꍇ�́A�I�u�W�F�N�g�𐶐�����Mock�ɓn��
            SampleConcrete       obj;
            Mock<SampleConcrete> mock(obj);

            // �������Ă��郁�\�b�h���ꕔ�������㏑���ł���
            When(Method(mock, SampleMethod1)).AlwaysReturn(5);

            // SampleConcrete�^�̃I�u�W�F�N�g���擾
            SampleConcrete& sample = mock.get();

            // �㏑���������\�b�h
            Assert::AreEqual(5, sample.SampleMethod1(1));

            // ��������Ă��錳�̃��\�b�h
            Assert::AreEqual(3, sample.SampleMethod2(1, 2));
        }
	};
}
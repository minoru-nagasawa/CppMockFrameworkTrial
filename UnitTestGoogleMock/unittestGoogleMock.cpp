#include "stdafx.h"
#include "gmock/gmock.h"
#include "CppUnitTest.h"
#include "../SampleDLL/SampleConcrete.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGoogleMock
{
    // �C���^�[�t�F�[�X�̃��b�N�N���X
    class MockSample : public ISample
    {
    public:
        MOCK_METHOD1(SampleMethod1, int(int lhs));
        MOCK_METHOD2(SampleMethod2, int(int lhs, int rhs));
    };
    // ��ۃN���X�̃��b�N�N���X
    class MockSampleConcrete : public SampleConcrete
    {
    public:
        // �������Ă��郁�\�b�h���ꕔ�������w��ł���
        MOCK_METHOD1(SampleMethod1, int(int lhs));
    };

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            // ���O�ɏ�������Mock�p�̃I�u�W�F�N�g�𐶐�
            MockSample mock;

            // �ȉ��̂悤�ɂ���ƁASampleMethod1�����s����ƁA�K��1���Ԃ��Ă���
            EXPECT_CALL(mock, SampleMethod1(testing::_)).WillRepeatedly(testing::Return(1));

            // �����܂ł̏����ɂ��Asample.SampleMethod1(10)��1��Ԃ��悤�ɂȂ��Ă���B
            Assert::AreEqual(1, mock.SampleMethod1(10));
		}

        TEST_METHOD(TestMethod2)
        {
            // ���O�ɏ�������Mock�p�̃I�u�W�F�N�g�𐶐�
            MockSample mock;

            // �ȉ��̂悤�ɁA���\�b�h�̈������w��ł���B
            // SampleMethod1(1)�����s����ƁA�K��1���Ԃ��Ă���
            // SampleMethod1(2)�����s���Ă��A1�͕Ԃ��Ă��Ȃ�
            EXPECT_CALL(mock, SampleMethod1(1)).WillRepeatedly(testing::Return(1));

            // �����܂ł̏����ɂ��Asample.SampleMethod1(1)��1��Ԃ��悤�ɂȂ��Ă���B
            Assert::AreEqual(1, mock.SampleMethod1(1));

            // mock.SampleMethod1(2)�����s����ƁA�w�肵�Ȃ��̂�0���Ԃ��Ă���
            Assert::AreEqual(0, mock.SampleMethod1(2));
        }

        TEST_METHOD(TestMethod3)
        {
            // ���O�ɏ�������Mock�p�̃I�u�W�F�N�g�𐶐�
            MockSampleConcrete mock;

            // �������Ă��郁�\�b�h���ꕔ�������㏑���ł���
            EXPECT_CALL(mock, SampleMethod1(1)).WillRepeatedly(testing::Return(1));

            // �㏑���������\�b�h
            Assert::AreEqual(1, mock.SampleMethod1(1));

            // ��������Ă��錳�̃��\�b�h
            Assert::AreEqual(3, mock.SampleMethod2(1, 2));
        }
	};
}
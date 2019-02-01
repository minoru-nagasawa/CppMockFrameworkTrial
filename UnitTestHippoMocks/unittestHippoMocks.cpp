#include "stdafx.h"
#include "CppUnitTest.h"
#include "hippomocks.h"
#include "../SampleDLL/SampleConcrete.h"
#include "../SampleDLL/GlobalFunctions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHippoMocks
{		
	TEST_CLASS(UnitTest)
	{
	public:
        TEST_METHOD(TestMethod1)
        {
            // �Ƃ肠����MockRepository�𐶐�
            MockRepository mocks;

            // ISample�^�̃I�u�W�F�N�g�ւ̃|�C���^���擾
            // mocks�̃f�X�g���N�^�ŉ�������̂ŁAsample�𒼐ډ������K�v�͂Ȃ�
            ISample* sample = mocks.Mock<ISample>();

            // �ȉ��̂悤�ɂ���ƁASampleMethod1�����s����ƁA�K��1���Ԃ��Ă���
            mocks.ExpectCall(sample, ISample::SampleMethod1).Return(1);

            // �����܂ł̏����ɂ��Asample.SampleMethod1(10)��1��Ԃ��悤�ɂȂ��Ă���B
            Assert::AreEqual(1, sample->SampleMethod1(10));
        }

        TEST_METHOD(TestMethod2)
        {
            // �Ƃ肠����MockRepository�𐶐�
            MockRepository mocks;

            // ISample�^�̃I�u�W�F�N�g�ւ̃|�C���^���擾
            // mocks�̃f�X�g���N�^�ŉ�������̂ŁAsample�𒼐ډ������K�v�͂Ȃ�
            ISample* sample = mocks.Mock<ISample>();

            // �ȉ��̂悤��With���g���ƁA���\�b�h�̈������w��ł���B
            // SampleMethod1(1)�����s����ƁA�K��1���Ԃ��Ă���
            // SampleMethod1(2)�����s���Ă��A1�͕Ԃ��Ă��Ȃ�
            mocks.ExpectCall(sample, ISample::SampleMethod1).With(1).Return(1);

            // �����܂ł̏����ɂ��Asample.SampleMethod1(1)��1��Ԃ��悤�ɂȂ��Ă���B
            Assert::AreEqual(1, sample->SampleMethod1(1));

            // �������w�肵�ĂȂ�sample.SampleMethod1(2)�����s����ƃe�X�g���s
            //sample->SampleMethod1(2);
        }

        TEST_METHOD(TestMethod3)
        {
            // �Ƃ肠����MockRepository�𐶐�
            MockRepository mocks;

            // SampleConcrete�^�̃I�u�W�F�N�g�ւ̃|�C���^���擾
            SampleConcrete* sample = mocks.Mock<SampleConcrete>();

            // �������Ă��郁�\�b�h���㏑���ł���
            mocks.ExpectCall(sample, ISample::SampleMethod1).Return(5);

            // �㏑���������\�b�h
            Assert::AreEqual(5, sample->SampleMethod1(1));

            // ��������Ă��錳�̃��\�b�h�͌ĂׂȂ��B
            // NotImplementedException���f�����B
            // https://stackoverflow.com/questions/41547660/hippomocks-throws-notimplementedexception-when-not-specifying-expectation
            //sample->SampleMethod2(1, 2);
        }

        TEST_METHOD(TestMethod4)
        {
            // �O���[�o���֐����㏑������O�́A���������ʂ�̂ӂ�܂�
            Assert::AreEqual(1, SampleMethodGlobal(1));

            // �Ƃ肠����MockRepository�𐶐�
            MockRepository mocks;

            // �O���[�o���֐����㏑���ł���
            mocks.ExpectCallFunc(SampleMethodGlobal).Return(10);

            // �㏑���������\�b�h
            Assert::AreEqual(10, SampleMethodGlobal(1));
        }

        TEST_METHOD(TestMethod5)
        {
            // �N���X��static���\�b�h���㏑������O�́A���������ʂ�̂ӂ�܂�
            Assert::AreEqual(1, SampleConcrete::StaticMethod(1));

            // �Ƃ肠����MockRepository�𐶐�
            MockRepository mocks;

            // �N���X��static���\�b�h���㏑���ł���
            mocks.ExpectCallFunc(SampleConcrete::StaticMethod).Return(10);

            // �㏑���������\�b�h
            Assert::AreEqual(10, SampleConcrete::StaticMethod(1));
        }
	};
}
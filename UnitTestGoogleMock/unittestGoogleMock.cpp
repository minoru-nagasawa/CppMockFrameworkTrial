#include "stdafx.h"
#include "gmock/gmock.h"
#include "CppUnitTest.h"
#include "../SampleDLL/SampleConcrete.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGoogleMock
{
    // インターフェースのモッククラス
    class MockSample : public ISample
    {
    public:
        MOCK_METHOD1(SampleMethod1, int(int lhs));
        MOCK_METHOD2(SampleMethod2, int(int lhs, int rhs));
    };
    // 具象クラスのモッククラス
    class MockSampleConcrete : public SampleConcrete
    {
    public:
        // 実装しているメソッドを一部だけを指定できる
        MOCK_METHOD1(SampleMethod1, int(int lhs));
    };

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            // 事前に準備したMock用のオブジェクトを生成
            MockSample mock;

            // 以下のようにすると、SampleMethod1を実行すると、必ず1が返ってくる
            EXPECT_CALL(mock, SampleMethod1(testing::_)).WillRepeatedly(testing::Return(1));

            // ここまでの準備により、sample.SampleMethod1(10)が1を返すようになっている。
            Assert::AreEqual(1, mock.SampleMethod1(10));
		}

        TEST_METHOD(TestMethod2)
        {
            // 事前に準備したMock用のオブジェクトを生成
            MockSample mock;

            // 以下のように、メソッドの引数を指定できる。
            // SampleMethod1(1)を実行すると、必ず1が返ってくる
            // SampleMethod1(2)を実行しても、1は返ってこない
            EXPECT_CALL(mock, SampleMethod1(1)).WillRepeatedly(testing::Return(1));

            // ここまでの準備により、sample.SampleMethod1(1)が1を返すようになっている。
            Assert::AreEqual(1, mock.SampleMethod1(1));

            // mock.SampleMethod1(2)を実行すると、指定しないので0が返ってくる
            Assert::AreEqual(0, mock.SampleMethod1(2));
        }

        TEST_METHOD(TestMethod3)
        {
            // 事前に準備したMock用のオブジェクトを生成
            MockSampleConcrete mock;

            // 実装しているメソッドを一部だけを上書きできる
            EXPECT_CALL(mock, SampleMethod1(1)).WillRepeatedly(testing::Return(1));

            // 上書きしたメソッド
            Assert::AreEqual(1, mock.SampleMethod1(1));

            // 実装されている元のメソッド
            Assert::AreEqual(3, mock.SampleMethod2(1, 2));
        }
	};
}
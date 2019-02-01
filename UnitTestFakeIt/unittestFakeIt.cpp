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
            // 実装したいインターフェースを指定する
            Mock<ISample> mock;

            // 以下のようにすると、SampleMethod1を実行すると、必ず1が返ってくる
            When(Method(mock, SampleMethod1)).AlwaysReturn(1);

            // ISample型のオブジェクトを取得
            ISample& sample = mock.get();

            // ここまでの準備により、sample.SampleMethod1(10)が1を返すようになっている。
            Assert::AreEqual(1, sample.SampleMethod1(10));
        }

        TEST_METHOD(TestMethod2)
        {
            // 実装したいインターフェースを指定する
            Mock<ISample> mock;

            // 以下のようにUsingを使うと、メソッドの引数を指定できる。
            // SampleMethod1(1)を実行すると、必ず1が返ってくる
            // SampleMethod1(2)を実行しても、1は返ってこない
            When(Method(mock, SampleMethod1).Using(1)).AlwaysReturn(1);

            // ISample型のオブジェクトを取得
            ISample& sample = mock.get();

            // ここまでの準備により、sample.SampleMethod1(1)が1を返すようになっている。
            Assert::AreEqual(1, sample.SampleMethod1(1));

            // 引数を指定してないsample.SampleMethod1(2)を実行するとテスト失敗
            //sample.SampleMethod1(2);
        }

        TEST_METHOD(TestMethod3)
        {
            // 実装したクラスの場合は、オブジェクトを生成してMockに渡す
            SampleConcrete       obj;
            Mock<SampleConcrete> mock(obj);

            // 実装しているメソッドを一部だけを上書きできる
            When(Method(mock, SampleMethod1)).AlwaysReturn(5);

            // SampleConcrete型のオブジェクトを取得
            SampleConcrete& sample = mock.get();

            // 上書きしたメソッド
            Assert::AreEqual(5, sample.SampleMethod1(1));

            // 実装されている元のメソッド
            Assert::AreEqual(3, sample.SampleMethod2(1, 2));
        }
	};
}
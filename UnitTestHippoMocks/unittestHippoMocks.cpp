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
            // とりあえずMockRepositoryを生成
            MockRepository mocks;

            // ISample型のオブジェクトへのポインタを取得
            // mocksのデストラクタで解放されるので、sampleを直接解放する必要はない
            ISample* sample = mocks.Mock<ISample>();

            // 以下のようにすると、SampleMethod1を実行すると、必ず1が返ってくる
            mocks.ExpectCall(sample, ISample::SampleMethod1).Return(1);

            // ここまでの準備により、sample.SampleMethod1(10)が1を返すようになっている。
            Assert::AreEqual(1, sample->SampleMethod1(10));
        }

        TEST_METHOD(TestMethod2)
        {
            // とりあえずMockRepositoryを生成
            MockRepository mocks;

            // ISample型のオブジェクトへのポインタを取得
            // mocksのデストラクタで解放されるので、sampleを直接解放する必要はない
            ISample* sample = mocks.Mock<ISample>();

            // 以下のようにWithを使うと、メソッドの引数を指定できる。
            // SampleMethod1(1)を実行すると、必ず1が返ってくる
            // SampleMethod1(2)を実行しても、1は返ってこない
            mocks.ExpectCall(sample, ISample::SampleMethod1).With(1).Return(1);

            // ここまでの準備により、sample.SampleMethod1(1)が1を返すようになっている。
            Assert::AreEqual(1, sample->SampleMethod1(1));

            // 引数を指定してないsample.SampleMethod1(2)を実行するとテスト失敗
            //sample->SampleMethod1(2);
        }

        TEST_METHOD(TestMethod3)
        {
            // とりあえずMockRepositoryを生成
            MockRepository mocks;

            // SampleConcrete型のオブジェクトへのポインタを取得
            SampleConcrete* sample = mocks.Mock<SampleConcrete>();

            // 実装しているメソッドを上書きできる
            mocks.ExpectCall(sample, ISample::SampleMethod1).Return(5);

            // 上書きしたメソッド
            Assert::AreEqual(5, sample->SampleMethod1(1));

            // 実装されている元のメソッドは呼べない。
            // NotImplementedExceptionが吐かれる。
            // https://stackoverflow.com/questions/41547660/hippomocks-throws-notimplementedexception-when-not-specifying-expectation
            //sample->SampleMethod2(1, 2);
        }

        TEST_METHOD(TestMethod4)
        {
            // グローバル関数を上書きする前は、実装した通りのふるまい
            Assert::AreEqual(1, SampleMethodGlobal(1));

            // とりあえずMockRepositoryを生成
            MockRepository mocks;

            // グローバル関数も上書きできる
            mocks.ExpectCallFunc(SampleMethodGlobal).Return(10);

            // 上書きしたメソッド
            Assert::AreEqual(10, SampleMethodGlobal(1));
        }

        TEST_METHOD(TestMethod5)
        {
            // クラスのstaticメソッドを上書きする前は、実装した通りのふるまい
            Assert::AreEqual(1, SampleConcrete::StaticMethod(1));

            // とりあえずMockRepositoryを生成
            MockRepository mocks;

            // クラスのstaticメソッドも上書きできる
            mocks.ExpectCallFunc(SampleConcrete::StaticMethod).Return(10);

            // 上書きしたメソッド
            Assert::AreEqual(10, SampleConcrete::StaticMethod(1));
        }
	};
}
#include "CppUnitTest.h"
#include "../HashTable/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(HashTableTests)
	{
	public:

		TEST_METHOD(TestInsert)
		{
			HashTable ht(10);
			Assert::IsTrue(ht.insert("key1", "value1"));
			Assert::IsTrue(ht.insert("key2", "value2"));
			Assert::IsFalse(ht.insert("key1", "value3")); 
		}

		TEST_METHOD(TestRead)
		{
			HashTable ht(10);
			ht.insert("key1", "value1");
			ht.insert("key2", "value2");

			auto value1 = ht.read("key1");
			auto value2 = ht.read("key2");
			auto value3 = ht.read("key3");

			Assert::IsTrue(value1.has_value());
			Assert::IsTrue(value2.has_value());
			Assert::IsFalse(value3.has_value());

			Assert::AreEqual(std::string("value1"), value1.value());
			Assert::AreEqual(std::string("value2"), value2.value());
		}

		TEST_METHOD(TestUpdate)
		{
			HashTable ht(10);
			ht.insert("key1", "value1");
			ht.insert("key2", "value2");

			Assert::IsTrue(ht.update("key1", "new_value1"));
			Assert::IsTrue(ht.update("key2", "new_value2"));
			Assert::IsFalse(ht.update("key3", "value3"));

			Assert::AreEqual(std::string("new_value1"), ht.read("key1").value());
			Assert::AreEqual(std::string("new_value2"), ht.read("key2").value());
		}

		TEST_METHOD(TestRemove)
		{
			HashTable ht(10);
			ht.insert("key1", "value1");
			ht.insert("key2", "value2");

			Assert::IsTrue(ht.remove("key1"));
			Assert::IsFalse(ht.remove("key1")); 
			Assert::IsFalse(ht.remove("key3"));

			Assert::IsFalse(ht.read("key1").has_value());
			Assert::IsTrue(ht.read("key2").has_value());
		}

		TEST_METHOD(TestRehash)
		{
			HashTable ht(5); 

			for (int i = 0; i < 10; ++i) {
				Assert::IsTrue(ht.insert("key" + std::to_string(i), "value" + std::to_string(i)));
			}

			for (int i = 0; i < 10; ++i) {
				auto value = ht.read("key" + std::to_string(i));
				Assert::IsTrue(value.has_value());
				Assert::AreEqual(std::string("value" + std::to_string(i)), value.value());
			}
		}

		TEST_METHOD(TestTableState)
		{
			HashTable ht(5);

			ht.insert("key1", "value1");
			ht.insert("key2", "value2");
			ht.insert("key3", "value3");
			ht.remove("key2");

			std::ostringstream oss;
			auto oldCoutBuf = std::cout.rdbuf(oss.rdbuf());

			ht.printTable();

			std::cout.rdbuf(oldCoutBuf);
			std::string output = oss.str();

			Assert::IsTrue(output.find("Index ") != std::string::npos);
			Assert::IsTrue(output.find("key1") != std::string::npos);
			Assert::IsTrue(output.find("key3") != std::string::npos);
			Assert::IsTrue(output.find("<deleted>") != std::string::npos);
		}
	};
}

#include "pch.h"
#include "CppUnitTest.h"
#include "../WeightsMatrix/WeightsMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFordBellman
{
	TEST_CLASS(UnitTestFordBellman)
	{
	public:
		TEST_METHOD(search_existing_key_in_queue)
		{
			Queue<int, string> queue;
			queue.push("A");
			queue.push("B");
			queue.push("C");
			Assert::AreEqual(queue.search_key("A"), 0);
			Assert::AreEqual(queue.search_key("B"), 1);
			Assert::AreEqual(queue.search_key("C"), 2);
		}

		TEST_METHOD(search_not_existing_key_in_queue)
		{
			Queue<int, string> queue;
			queue.push("A");
			queue.push("B");
			queue.push("C");
			Assert::AreEqual(queue.search_key("D"), -1);
		}

		TEST_METHOD(constructor_3x3)
		{
			string filename = "in.txt";
			string input = "A;B;N/A;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			Assert::AreEqual(W.get_size(), (size_t)3);
			Assert::AreEqual(W.get_cities()[0], (string)"A");
			Assert::AreEqual(W.get_cities()[1], (string)"B");
			Assert::AreEqual(W.get_cities()[2], (string)"C");
			Assert::AreEqual(W.get_weights()[0][0], (double)0);
			Assert::AreEqual(W.get_weights()[0][1], INF);
			Assert::AreEqual(W.get_weights()[0][2], (double)3);
			Assert::AreEqual(W.get_weights()[1][0], (double)1);
			Assert::AreEqual(W.get_weights()[1][1], (double)0);
			Assert::AreEqual(W.get_weights()[1][2], (double)1);
			Assert::AreEqual(W.get_weights()[2][0], (double)2);
			Assert::AreEqual(W.get_weights()[2][1], (double)4);
			Assert::AreEqual(W.get_weights()[2][2], (double)0);
		}

		TEST_METHOD(get_existing_city_index)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			Assert::AreEqual(W.get_city_index("B"), (size_t)1);
		}

		TEST_METHOD(get_not_existing_city_index)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			Assert::AreEqual(W.get_city_index("D"), (size_t)(-1));
		}

		TEST_METHOD(Matrix_3x3_1)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("A", "C");
			Assert::AreEqual(answer, (double)2);
		}
		TEST_METHOD(Matrix_3x3_2)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("C", "B");
			Assert::AreEqual(answer, (double)3);
		}

		TEST_METHOD(Matrix_3x3_3)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("C", "A");
			Assert::AreEqual(answer, (double)2);
		}

		TEST_METHOD(Matrix_3x3_4)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("B", "A");
			Assert::AreEqual(answer, (double)1);
		}

		TEST_METHOD(Matrix_3x3_5)
		{
			string filename = "in.txt";
			string input = "A;B;1;1\nA;C;3;2\nB;C;1;4";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("B", "C");
			Assert::AreEqual(answer, (double)1);
		}

		TEST_METHOD(Matrix_5x5_1)
		{
			string filename = "in.txt";
			string input = "A;B;2;1\nA;C;N/A;N/A\nA;D;4;-1\nA;E;5;N/A\nB;C;3;-2\nB;D;N/A;N/A\nB;E;4;N/A\nC;D;2;-1\nC;E;1;N/A\nD;E;1;N/A";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("A", "B");
			Assert::AreEqual(answer, (double)1);
		}

		TEST_METHOD(Matrix_5x5_2)
		{
			string filename = "in.txt";
			string input = "A;B;2;1\nA;C;N/A;N/A\nA;D;4;-1\nA;E;5;N/A\nB;C;3;-2\nB;D;N/A;N/A\nB;E;4;N/A\nC;D;2;-1\nC;E;1;N/A\nD;E;1;N/A";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("A", "C");
			Assert::AreEqual(answer, (double)3);
		}

		TEST_METHOD(Matrix_5x5_3)
		{
			string filename = "in.txt";
			string input = "A;B;2;1\nA;C;N/A;N/A\nA;D;4;-1\nA;E;5;N/A\nB;C;3;-2\nB;D;N/A;N/A\nB;E;4;N/A\nC;D;2;-1\nC;E;1;N/A\nD;E;1;N/A";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("A", "D");
			Assert::AreEqual(answer, (double)4);
		}

		TEST_METHOD(Matrix_5x5_4)
		{
			string filename = "in.txt";
			string input = "A;B;2;1\nA;C;N/A;N/A\nA;D;4;-1\nA;E;5;N/A\nB;C;3;-2\nB;D;N/A;N/A\nB;E;4;N/A\nC;D;2;-1\nC;E;1;N/A\nD;E;1;N/A";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double answer = W.FordBellman("A", "E");
			Assert::AreEqual(answer, (double)4);
		}

		TEST_METHOD(No_way)
		{
			string filename = "in.txt";
			string input = "A;C;3;N/A\nA;B;N/A;2\nC;B;N/A;1";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double** bla = W.get_weights();
			string* cities = W.get_cities();
			try
			{
				double answer = W.FordBellman("C", "B");
			}
			catch (const exception& message)
			{
				Assert::AreEqual(message.what(), "path doesn't exist");
			}
		}

		TEST_METHOD(Negative_cycle)
		{
			string filename = "in.txt";
			string input = "A;B;1;3\nA;C;2;N/A\nB;C;-1;-2";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			double** bla = W.get_weights();
			string* cities = W.get_cities();
			try
			{
				double answer = W.FordBellman("A", "C");
			}
			catch (const exception& message)
			{
				Assert::AreEqual(message.what(), "Found negative cycle");
			}
		}

		TEST_METHOD(No_such_source)
		{
			string filename = "in.txt";
			string input = "A;B;2;1\nA;C;N/A;N/A\nA;D;4;-1\nA;E;5;N/A\nB;C;3;-2\nB;D;N/A;N/A\nB;E;4;N/A\nC;D;2;-1\nC;E;1;N/A\nD;E;1;N/A";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			try
			{
				double answer = W.FordBellman("F", "A");
			}
			catch (const exception& message)
			{
				Assert::AreEqual(message.what(), "the source city doesn't exist");
			}
		}

		TEST_METHOD(No_such_target)
		{
			string filename = "in.txt";
			string input = "A;B;2;1\nA;C;N/A;N/A\nA;D;4;-1\nA;E;5;N/A\nB;C;3;-2\nB;D;N/A;N/A\nB;E;4;N/A\nC;D;2;-1\nC;E;1;N/A\nD;E;1;N/A";
			ofstream out(filename);
			out << input;
			out.close();
			WeightsMatrix W(filename);
			try
			{
				double answer = W.FordBellman("A", "F");
			}
			catch (const exception& message)
			{
				Assert::AreEqual(message.what(), "the target city doesn't exist");
			}
		}

	};
}

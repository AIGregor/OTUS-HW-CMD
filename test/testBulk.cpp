// testMatrix.cpp : Defines the entry point for the console application.
//
#include "gtest/gtest.h"
#include "Matrix.h"

class CMatrixTest : public ::testing::Test {
};

TEST_F(CMatrixTest, CheckSize)
{
	Matrix<int, -1> matrix;
	ASSERT_TRUE(matrix.size() == 0);
}

TEST_F(CMatrixTest, CheckAddValue)
{
	Matrix<int, -1> matrix;
	matrix[100][100] = 314;

	ASSERT_TRUE(matrix[100][100] == 314);
	ASSERT_TRUE(matrix.size() == 1);

	matrix[100][10] = 457;

	ASSERT_TRUE(matrix[100][10] == 457);
	ASSERT_TRUE(matrix.size() == 2);	
}

TEST_F(CMatrixTest, CheckRemoveValue)
{
	Matrix<int, -1> matrix;
	matrix[100][100] = 314;

	ASSERT_TRUE(matrix[100][100] == 314);
	ASSERT_TRUE(matrix.size() == 1);

	matrix[100][10] = 457;

	ASSERT_TRUE(matrix[100][10] == 457);
	ASSERT_TRUE(matrix.size() == 2);

	matrix[100][10] = -1;

	ASSERT_TRUE(matrix[100][10] == -1);
	ASSERT_TRUE(matrix.size() == 1);
}

TEST_F(CMatrixTest, CheckFullCells)
{
	Matrix<int, -1> matrix; 
	matrix[100][100] = 314;

	ASSERT_TRUE(matrix[100][100] == 314);
	ASSERT_TRUE(matrix.size() == 1);

	for (auto c : matrix)
	{
		std::string strTest = "";

		int x = c.first;
		for (auto e : c.second)
		{
			int y = e.first;
			int v = e.second.getValue();
			strTest = std::to_string(x) 
				+ std::to_string(y)
				+ std::to_string(v);
			ASSERT_TRUE(strTest == "100100314");
		}
	}

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


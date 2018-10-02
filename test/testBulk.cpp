// testMatrix.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include "gtest/gtest.h"

#include "log_observer.h"
#include "cmd.h"

//std::string GetActualResult(size_t test_number, int test_bulk_size);
//std::string GetExpectedResult(size_t test_number);

//class CBulkTest : public ::testing::Test {
//};

std::string GetActualResult(size_t test_number, int test_bulk_size)
{
	std::ifstream file_in("in_test" + std::to_string(test_number) + ".txt", std::ofstream::in);

	testing::internal::CaptureStdout();

	cmdBulk bulker(test_bulk_size);
	log_observer log(&bulker);
	consol_observer consl(&bulker);

	while (!file_in.eof())
	{
		std::string line;
		getline(file_in, line);

		bulker.add(line);
	}

	if (!bulker.isDynamicSizeBulk())
		bulker.notify();

	std::string output = testing::internal::GetCapturedStdout();
	return output;
}

std::string GetExpectedResult(size_t test_number)
{
	std::string file_out = "out_test" + std::to_string(test_number) + ".txt";

	std::ifstream t(file_out);
	std::string result((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return result;
}

// ASSERT_EQ(expected, actual);
TEST(CBulkTest, BulkTest1)
{
	std::string expected = GetExpectedResult(1);
	std::string actual = GetActualResult(1, 3);
	ASSERT_EQ(expected, actual);
}

TEST(CBulkTest, BulkTest2)
{
	std::string expected = GetExpectedResult(2);
	std::string actual = GetActualResult(2, 3);
	ASSERT_EQ(expected, actual);
}

TEST(CBulkTest, BulkTest3)
{
	std::string expected = GetExpectedResult(3);
	std::string actual = GetActualResult(3, 3);
	ASSERT_EQ(expected, actual);
}

TEST(CBulkTest, BulkTest4)
{
	std::string expected = GetExpectedResult(4);
	std::string actual = GetActualResult(4, 3);
	ASSERT_EQ(expected, actual);
}

TEST(CBulkTest, BulkTest5)
{
	std::string expected = GetExpectedResult(5);
	std::string actual = GetActualResult(5, 3);
	ASSERT_EQ(expected, actual);
}

TEST(CBulkTest, BulkTest6)
{
	std::string expected = GetExpectedResult(6);
	std::string actual = GetActualResult(6, 3);
	ASSERT_EQ(expected, actual);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
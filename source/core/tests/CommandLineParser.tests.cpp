
#include "gtest/gtest.h"

#include "CommandLineParser.h"

namespace ebola { namespace test {

	class Test_CommandLineParserFixture : public ::testing::Test
	{
	public:
		ebola::core::CommandLineParser CmdLineParser;
		bool InitResult;

		Test_CommandLineParserFixture()
		{
			char* argv[] = { "path/to/executable.exe", "arg1", "arg2",
				"--key1=value1", "-opt1", "--key2=value2",
				"-opt2" };
			char argc = 7;

			InitResult = CmdLineParser.Initialize(argc, argv);
		}

		~Test_CommandLineParserFixture()
		{
		}
	};


	TEST_F(Test_CommandLineParserFixture, initializes_cleanly)
	{
		ASSERT_TRUE(InitResult);
		ASSERT_EQ(0, strcmp(CmdLineParser.GetExecutablePath(), "path/to/executable.exe"));
	}

	TEST_F(Test_CommandLineParserFixture, arguments_are_parsed_and_stored)
	{
		EXPECT_EQ(2, CmdLineParser.NumArguments());
		EXPECT_TRUE(CmdLineParser.HasArgument("arg1"));
		EXPECT_TRUE(CmdLineParser.HasArgument("arg2"));
		EXPECT_FALSE(CmdLineParser.HasArgument("opt1"));
		EXPECT_FALSE(CmdLineParser.HasArgument("opt2"));
	}

	TEST_F(Test_CommandLineParserFixture, options_are_parsed_and_stored)
	{
		EXPECT_EQ(2, CmdLineParser.NumOptions());
		EXPECT_TRUE(CmdLineParser.HasOption("opt1"));
		EXPECT_TRUE(CmdLineParser.HasOption("opt2"));
		EXPECT_FALSE(CmdLineParser.HasOption("arg1"));
		EXPECT_FALSE(CmdLineParser.HasOption("arg2"));
	}

	TEST_F(Test_CommandLineParserFixture, keyvaluepairs_are_parsed_and_stored)
	{
		EXPECT_EQ(2, CmdLineParser.NumKeyValuePairs());
		EXPECT_TRUE(CmdLineParser.GetValueForKey("key1") != nullptr);
		EXPECT_TRUE(CmdLineParser.GetValueForKey("key2") != nullptr);

		EXPECT_EQ(0, strcmp(CmdLineParser.GetValueForKey("key1"), "value1"));
		EXPECT_EQ(0, strcmp(CmdLineParser.GetValueForKey("key2"), "value2"));
	}

	TEST(Test_CommandLineParser, invalidargs_argc_is_zero)
	{
		char* argv[] = { "path/to/executable.exe", "arg1", "arg2",
			"--key1=value1", "-opt1", "--key2=value2",
			"-opt2" };
		char argc = 0;

		ebola::core::CommandLineParser cmdLineParser;
		bool initSucceeded = cmdLineParser.Initialize(argc, argv);
		ASSERT_FALSE(initSucceeded);
	
		EXPECT_EQ(0, cmdLineParser.NumArguments());
		EXPECT_EQ(0, cmdLineParser.NumOptions());
		EXPECT_EQ(0, cmdLineParser.NumKeyValuePairs());
	}

	TEST(Test_CommandLineParser, invalidargs_argv_is_null)
	{
		char** argv = nullptr;
		char argc = 4;

		ebola::core::CommandLineParser cmdLineParser;
		bool initSucceeded = cmdLineParser.Initialize(argc, argv);
		ASSERT_FALSE(initSucceeded);

		EXPECT_EQ(0, cmdLineParser.NumArguments());
		EXPECT_EQ(0, cmdLineParser.NumOptions());
		EXPECT_EQ(0, cmdLineParser.NumKeyValuePairs());
	}

	TEST(Test_CommandLineParser, invalidargs_argv_contains_null_entry)
	{
		char* argv[] = { "path/to/executable.exe", "arg1", "arg2",
						 nullptr, "-opt1", "--key2=value2",
						 "-opt2" };
		char argc = 7;

		ebola::core::CommandLineParser cmdLineParser;
		bool initSucceeded = cmdLineParser.Initialize(argc, argv);
		ASSERT_FALSE(initSucceeded);

		EXPECT_EQ(0, cmdLineParser.NumArguments());
		EXPECT_EQ(0, cmdLineParser.NumOptions());
		EXPECT_EQ(0, cmdLineParser.NumKeyValuePairs());
	}

} }
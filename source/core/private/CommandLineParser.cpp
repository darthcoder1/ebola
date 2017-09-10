
#include "CommandLineParser.h"
#include <cassert>

namespace ebola { namespace core {


CommandLineParser::CommandLineParser()
{
}

CommandLineParser::~CommandLineParser()
{

}

bool CommandLineParser::Initialize(int argc, char* argv[])
{
	if (argc <= 0 || argv == nullptr)
		return false;

	m_executableName = argv[0];

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i] == nullptr)
		{
			// invalid argv entry found. abort initialization and clean up
			m_stringPairs.clear();
			m_options.clear();
			m_arguments.clear();
			return false;
		}

		if (argv[i][0] == '-')
		{
			if (argv[i][1] == '-')
			{
				// this is a key value pair
				char* value = strchr(argv[i], '=');
				assert(value != nullptr);
				
				std::string key; 
				key.append(argv[i] + 2, (value - (argv[i]+2)) );

				++value; // skip the = char

				m_stringPairs.push_back(std::make_pair(key, value));
			}
			else
			{
				// this is an option
				m_options.push_back(argv[i] + 1);
			}
		}
		else
		{
			// this is an argument
			m_arguments.push_back(argv[i]);
		}
	}

	return true;
}

bool CommandLineParser::HasArgument(const char* argName) const
{
	for (const auto& arg : m_arguments)
	{
		if (arg == argName)
			return true;
	}
	return false;
}

bool CommandLineParser::HasOption(const char* optionName) const
{
	for (const auto& opt : m_options)
	{
		if (opt == optionName)
			return true;
	}
	return false;
}

const char* CommandLineParser::GetValueForKey(const char* keyName) const
{
	for (const auto& pair : m_stringPairs)
	{
		if (pair.first == keyName)
			return pair.second.c_str();
	}
	return nullptr;
}

} // namespace core
} // namespace freed
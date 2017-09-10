#pragma once

#include <string>
#include <vector>

namespace ebola { namespace core {

// cmdline_parser
// Responsible for parsing the commandline. Provides an API for retrieval and 
// handling of command line arguments
class CommandLineParser
{
public:
	CommandLineParser();
	~CommandLineParser();

	bool Initialize(int argc, char* argv[]);

	bool HasArgument(const char* argName) const;
	bool HasOption(const char* optionName) const;
	const char* GetValueForKey(const char* keyName) const;
	const char* GetExecutablePath() const	{ return m_executableName.c_str(); };

	int NumArguments() const				{ return static_cast<int>(m_arguments.size()); }
	int NumOptions() const					{ return static_cast<int>(m_options.size()); }
	int NumKeyValuePairs() const			{ return static_cast<int>(m_stringPairs.size()); }
private:
	
	typedef std::vector<std::string> string_vector;
	typedef std::vector<std::pair<std::string, std::string> > string_pair_vector;
	
	std::string m_executableName;
	string_vector m_arguments;
	string_vector m_options;
	string_pair_vector m_stringPairs;
};

} // namespace core
} // namespace freed
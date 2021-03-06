
#include <iomanip>
#include <limits>

#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Expect
{
	char m_expected;
	Expect(char expected)
		: m_expected(expected)
	{}

	friend std::istream& operator>>(std::istream& is, Expect const& e)
	{
		char actual;
		if ((is >> actual) && (actual != e.m_expected)) 
		{
			is.setstate(std::ios::failbit);
		}

		return is;
	}
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Deploy_element {
	
	int m_brand_code = 0;
	int m_coutry_code = 0;
};

std::istream& operator>>(std::istream& is, Deploy_element& deploy_element)
{
	std::istream wrap(is.rdbuf());
	wrap.imbue(std::locale("C"));

	wrap >> Expect('(') >> deploy_element.m_brand_code
		 >> Expect(',') >> deploy_element.m_coutry_code
		 >> Expect(')');

	is.setstate(wrap.rdstate());
	return is;
}

std::ostream& operator<<(std::ostream& os, Deploy_element const& deploy_element)
{
	std::ostream wrap(os.rdbuf());
	wrap.imbue(std::locale("C"));

	wrap << std::fixed << std::setprecision(std::numeric_limits<int>::digits)
		<< '('
		<< deploy_element.m_brand_code << ", "
		<< deploy_element.m_coutry_code
		<< ')';
	os.setstate(wrap.rdstate());
	return os;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::vector<std::string> split_location_list(const std::string& location_list,
	const std::string& delim,
	const bool keep_empty = true)
{
	std::vector<std::string> result;

	if (delim.empty())
	{
		result.push_back(location_list);
		return result;
	}

	std::string::const_iterator sub_start = location_list.begin();
	std::string::const_iterator sub_end;
	for (;;)
	{
		sub_end = std::search(sub_start, location_list.end(), delim.begin(), delim.end());
		std::string temp(sub_start, sub_end);
		if (keep_empty == true || temp.empty() == false)
		{
			temp.erase(std::remove_if(temp.begin(), temp.end(), isspace), temp.end());
			result.push_back(temp);
		}
		if (sub_end == location_list.end()) {
			break;
		}
		sub_start = sub_end + delim.size();
	}
	return result;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
	std::vector<std::string> input_lines;
	
	std::ifstream ifile("input_lists.txt");
	std::string line_buffer;
	std::getline(ifile, line_buffer, '\n');
	for (; ifile.good() == true; std::getline(ifile, line_buffer, '\n'))
	{
		input_lines.push_back(line_buffer);
	}

	std::vector<std::string>::const_iterator i = input_lines.begin();
	std::vector<std::string>::const_iterator e = input_lines.end();
	for (; i != e; ++i)
	{
		const std::string& curr_input_line = *i;
		std::cout << curr_input_line << std::endl;

		const std::vector<std::string> elems(split_location_list(curr_input_line, ";"));
		std::vector<std::string>::const_iterator it = elems.begin();
		std::vector<std::string>::const_iterator it_e = elems.end();
		for (;it != it_e; ++it)
		{
			const std::string& curr_elem = *it;
			std::cout << curr_elem << std::endl;

			std::istringstream iss(curr_elem);

			Deploy_element deploy_element;

			if (iss >> deploy_element)
				std::cout << "Parsed: " << deploy_element << "\n";
			else
				std::cout << "Parsing did not succeed\n";
		}
	}

    return 0;
}

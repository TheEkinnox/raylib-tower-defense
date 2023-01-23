#include "pch.h"
#include <random>

#include "utility.h"

namespace TD
{
	std::string TrimLeft(const std::string& str)
	{
		std::string	result = str;
		size_t		firstNonSpace = 0;

		while (firstNonSpace < result.size() && isspace(result[firstNonSpace]))
			++firstNonSpace;

		result = result.erase(0, firstNonSpace);

		return result;
	}

	std::string TrimRight(const std::string& str)
	{
		std::string	result = str;
		size_t		lastNonSpace = result.size();

		while (lastNonSpace > 0 && isspace(result[lastNonSpace - 1]))
			--lastNonSpace;

		result = result.erase(lastNonSpace);

		return result;
	}

	std::string Trim(const std::string& str)
	{
		return TrimLeft(TrimRight(str));
	}

	std::string	RemoveComments(const std::string& str)
	{
		std::string result = str;

		if (str.empty())
			return result;

		const size_t	commentStart = result.find(COMMENT_CHAR);

		if (commentStart != std::string::npos)
			result = result.erase(commentStart);

		return result;
	}

	std::vector<std::string> SplitString(const std::string& str, char const* delimiter,
		const bool includeEmpty)
	{
		std::vector<std::string> result{};

		if (str.empty())
		{
			if (includeEmpty)
				result.push_back(str);

			return result;
		}

		size_t start = 0;
		size_t end = str.find(delimiter, start);
		
		while ((start) < str.size())
		{
			std::string token = str.substr(start, end - start);

			if (includeEmpty || !token.empty())
				result.push_back(std::move(token));

			if (end == std::string::npos)
				break;

			start = end + strlen(delimiter);
			end = str.find(delimiter, start);
		}

		return result;
	}

	uint32_t Unpack(const uint32_t data, const uint8_t offset, const uint8_t bitCount)
	{
		const uint32_t mask = (1 << bitCount) - 1;
		return (data >> offset) & mask;
	}

	int Random(const int min, const int max)
	{
		std::default_random_engine generator(clock());
		std::uniform_int_distribution<int> distribution(min, max);

		return distribution(generator);
	}
}

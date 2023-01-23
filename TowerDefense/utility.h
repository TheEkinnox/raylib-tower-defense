#pragma once
#include <string>
#include <vector>

#define COMMENT_CHAR '#'

namespace TD
{
	/**
	 * \brief Removes whitespaces from the left of the given string
	 * \param str The string to trim
	 * \return The trimmed string
	 */
	std::string TrimLeft(const std::string& str);

	/**
	 * \brief Removes whitespaces from the right of the given string
	 * \param str The string to trim
	 * \return The trimmed string
	 */
	std::string TrimRight(const std::string& str);
	
	/**
	 * \brief Removes whitespaces from the left and right of the given string
	 * \param str The string to trim
	 * \return The trimmed string
	 */
	std::string Trim(const std::string& str);

	/**
	 * \brief Removes comments from the given string
	 * \param str The string of which comments should be removed
	 * \return The string without comments
	 */
	std::string	RemoveComments(const std::string& str);

	/**
	 * \brief Splits the given string using the given delimiter
	 * \param str The string to split
	 * \param delimiter The delimiter to use to split the string
	 * \param includeEmpty Whether empty substrings should be included in the result
	 * \return A vector containing the sub-strings
	 */
	std::vector<std::string> SplitString(const std::string& str, char const* delimiter, bool includeEmpty);

	/**
	 * \brief Reads a given number of bits from the given data
	 * \param data The data to unpack
	 * \param offset The bit offset of the target data
	 * \param bitCount The number of bits to read
	 * \return The unpacked data
	 */
	uint32_t Unpack(uint32_t data, uint8_t offset, uint8_t bitCount);

	/**
	 * \brief Generate a random number in the given range
	 * \param min The smallest accepted value
	 * \param max The largest accepted value
	 * \return A random number in range [min, max]
	 */
	int	Random(int min, int max);
}

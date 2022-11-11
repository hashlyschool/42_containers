/*!
 * @file equal.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief
 * @version 1.0
 * @date 2022-11-09
 * @copyright Flex copyright (c) 2022
 */

#ifndef EQUAL_HPP
# define EQUAL_HPP

namespace ft {

///@brief Relational Operators Comparison Functions
template <class Ite1, class Ite2>
bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
{
	while (first1 != last1)
	{
		if (*first1 != *first2)
			return false;
		++first1; ++first2;
	}
	return true;
}

}

#endif //equal

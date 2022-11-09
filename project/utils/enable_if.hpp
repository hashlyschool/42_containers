/*!
 * @file enable_if.hpp
 * @author INikituk (inikituk@npomis.ru)
 * @brief custom implementation std::enable_if
 * @version 1.0
 * @date 2022-11-09
 * @copyright Flex copyright (c) 2022
 */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft {

	template <bool, class IsTrue = void>
	struct enable_if {};

	template <class IsTrue>
	struct enable_if<true, IsTrue> {
		typedef IsTrue type;
	};

}

#endif //enable_if

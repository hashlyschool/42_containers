/*!
 * @file less.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief
 * @version 1.0
 * @date 2022-11-10
 * @copyright Flex copyright (c) 2022
 */

#pragma once

namespace ft
{

template <class Arg1, class Arg2, class Result>
struct binary_function
{
	/* The first argument type */
	typedef Arg1 first_argument_type;

	/* The second arguement type */
	typedef Arg2 second_argument_type;

	/* The result type */
	typedef Result result_type;
};


template <class T>
struct less : binary_function<T, T, bool>
{
	bool operator() (const T& x, const T& y) const { return (x < y); }
};

}

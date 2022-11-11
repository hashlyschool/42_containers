/*!
 * @file is_integral.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief
 * @version 1.0
 * @date 2022-11-09
 * @copyright Flex copyright (c) 2022
 */

#pragma once

namespace ft {

struct	true_type { };
struct	false_type { };

template<typename T>
struct is_integral
{
	enum { value = 0 };
	typedef false_type type;
};

template<>
struct is_integral<bool>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<char>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<signed char>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<unsigned char>
{
	enum { value = 1 };
	typedef true_type type;
};

# ifdef __WCHAR_TYPE__
template<>
struct is_integral<wchar_t>
{
	enum { value = 1 };
	typedef true_type type;
};
# endif

#ifdef _GLIBCXX_USE_CHAR8_T
template<>
struct is_integral<char8_t>
{is_integral
	enum { value = 1 };
	typedef true_type type;
};
#endif

template<>
struct is_integral<short>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<unsigned short>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<int>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<unsigned int>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<long>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integral<unsigned long>
{
	enum { value = 1 };
	typedef true_type type;
};

// template<>
// struct is_integral<long long>
// {
// 	enum { value = 1 };
// 	typedef true_type type;
// };

// template<>
// struct is_integral<unsigned long long>
// {
// 	enum { value = 1 };
// 	typedef true_type type;
// };

#define __INT_N(TYPE) 			\
template<>				\
struct is_integral<TYPE>		\
{					\
	enum { value = 1 };		\
	typedef true_type type;	\
};					\
template<>				\
struct is_integral<unsigned TYPE>	\
{					\
	enum { value = 1 };		\
	typedef true_type type;	\
};

}

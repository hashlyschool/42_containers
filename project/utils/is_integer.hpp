#pragma once

namespace ft {

struct	true_type { };
struct	false_type { };

template<typename T>
struct is_integer
{
	enum { value = 0 };
	typedef false_type type;
};

template<>
struct is_integer<bool>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<char>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<signed char>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<unsigned char>
{
	enum { value = 1 };
	typedef true_type type;
};

# ifdef __WCHAR_TYPE__
template<>
struct is_integer<wchar_t>
{
	enum { value = 1 };
	typedef true_type type;
};
# endif

#ifdef _GLIBCXX_USE_CHAR8_T
template<>
struct is_integer<char8_t>
{is_integer
	enum { value = 1 };
	typedef true_type type;
};
#endif

template<>
struct is_integer<short>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<unsigned short>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<int>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<unsigned int>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<long>
{
	enum { value = 1 };
	typedef true_type type;
};

template<>
struct is_integer<unsigned long>
{
	enum { value = 1 };
	typedef true_type type;
};

// template<>
// struct is_integer<long long>
// {
// 	enum { value = 1 };
// 	typedef true_type type;
// };

// template<>
// struct is_integer<unsigned long long>
// {
// 	enum { value = 1 };
// 	typedef true_type type;
// };

#define __INT_N(TYPE) 			\
template<>				\
struct is_integer<TYPE>		\
{					\
	enum { value = 1 };		\
	typedef true_type type;	\
};					\
template<>				\
struct is_integer<unsigned TYPE>	\
{					\
	enum { value = 1 };		\
	typedef true_type type;	\
};

}

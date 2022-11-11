/*!
 * @file IteratorUtils.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief файл вспомогательных функций
 * В файле IteratorUtils.hpp находятся вспомогательные функции для реализации итераторов
 * @version 1.0
 * @date 2022-10-13
 * @copyright Flex copyright (c) 2022
 */

#ifndef FT_ITERATOR_UTILS_HPP
# define FT_ITERATOR_UTILS_HPP

#include <memory>
#include <typeinfo>
#include <cstddef>

static class nullptr_t
{
	public:
		template<class T>
		operator T*() const { return (0); }

		template<class C, class T>
		operator T C::*() const { return (0); }

	private:

		void operator&() const;

} u_nullptr = {};

namespace ft
{

struct random_access_iterator_tag { };
struct bidirectional_iterator_tag { };
struct forward_iterator_tag { };
struct input_iterator_tag { };
struct output_iterator_tag { };

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
class Iterator
{
	public:
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template<class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
{
	typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
	while (first != last)
	{
		first++;
		rtn++;
	}
	return (rtn);
}

template <class T>
class bidirectional_iterator : ft::Iterator<ft::bidirectional_iterator_tag, T>
{
	typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

	typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;

	typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;

	typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;

	typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::reference			reference;

	private:
		pointer _elem;
};

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1) return false;
		else if (*first1 < *first2) return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2 || comp(*first2, *first1)) return false;
		else if (comp(*first1, *first2)) return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template <class Ite>
size_t	itlen(Ite first, Ite last) {
	size_t	i = 0;

	while (first != last)
	{
		++first;
		++i;
	}
	return (i);
}

template <class Data_T>
struct Doubly_Linked_Node
{
	public :

		Doubly_Linked_Node	*prev;
		Doubly_Linked_Node	*next;
		Data_T				data;

		Doubly_Linked_Node()
		:
			prev(u_nullptr),
			next(u_nullptr)
		{}

		Doubly_Linked_Node(const Data_T& val)
		:
			prev(u_nullptr),
			next(u_nullptr),
			data(val)
		{}

		Doubly_Linked_Node(const Data_T& val,
			Doubly_Linked_Node *prev, Doubly_Linked_Node *next)
		:
			prev(prev),
			next(next),
			data(val)
		{}
};

template <bool is_valid, typename T>
struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };


template <typename T>
struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

template <>
struct is_input_iterator_tagged<ft::random_access_iterator_tag>
	: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

template <>
struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
	: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

template <>
struct is_input_iterator_tagged<ft::forward_iterator_tag>
	: public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

template <>
struct is_input_iterator_tagged<ft::input_iterator_tag>
	: public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

template <typename T>
class InvalidIteratorException : public std::exception
{
	private:
		std::string _msg;

	public :
		InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
		InvalidIteratorException (const InvalidIteratorException&) throw() {}
		InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
		virtual ~InvalidIteratorException() throw() {}
		virtual const char* what() const throw() { return (_msg.c_str()); }
};

} // namespace ft

#endif

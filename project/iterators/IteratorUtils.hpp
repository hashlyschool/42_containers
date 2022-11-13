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
#include <cstdlib>
#include <typeinfo>
#include <cstddef>
#include <iterator>

#ifdef __linux__
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
#else
	#define u_nullptr nullptr
#endif


namespace ft
{

struct random_access_iterator_tag { };
struct bidirectional_iterator_tag { };

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

template <typename T>
struct	mapNode
{
	private:
		bool _unused;
	#ifdef __linux__
		int _unused_for_linux;
	#endif

	public:
	T			data;
	mapNode		*parent;
	mapNode		*left;
	mapNode		*right;

	mapNode(const T &src = T())
	:
		data(src),
		parent(NULL),
		left(NULL),
		right(NULL)
	{};
};

template <typename T>
mapNode<T>	*farRight(mapNode<T> *node) {
	while (node->right != NULL)
		node = node->right;
	return (node);
}

template <typename T>
mapNode<T>	*farLeft(mapNode<T> *node) {
	while (node->left != NULL)
		node = node->left;
	return (node);
}

} // namespace ft

#endif

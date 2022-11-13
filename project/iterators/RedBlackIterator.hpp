/*!
 * @file RedBlackIterator.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief
 * @version 1.0
 * @date 2022-11-11
 * @copyright Flex copyright (c) 2022
 */

#ifndef MAP_ITE_CLASS_HPP
# define MAP_ITE_CLASS_HPP

#include "../utils/utils_include.hpp"
#include "../iterators/IteratorUtils.hpp"

namespace ft {

template <typename T, typename node_type>
class RedBlackIterator : ft::Iterator<ft::bidirectional_iterator_tag, T>
{
	protected:
		node_type						*_node;
		RedBlackIterator(node_type		*src);

	public:

		typedef typename ft::iterator_traits<ft::Iterator<ft::bidirectional_iterator_tag, T> >::iterator_category	iterator_category;

		typedef typename ft::iterator_traits<ft::Iterator<ft::bidirectional_iterator_tag, T> >::value_type	value_type;

		typedef typename ft::iterator_traits<ft::Iterator<ft::bidirectional_iterator_tag, T> >::difference_type	difference_type;

		typedef typename ft::iterator_traits<ft::Iterator<ft::bidirectional_iterator_tag, T> >::pointer	pointer;
		typedef typename ft::iterator_traits<ft::Iterator<ft::bidirectional_iterator_tag, T> >::reference	reference;

		RedBlackIterator(void);
		RedBlackIterator(const RedBlackIterator &src);
		virtual ~RedBlackIterator(void);
		RedBlackIterator	&operator=(RedBlackIterator const &rhs);

		template <class U> bool	operator==(const RedBlackIterator<U, node_type> &rhs) const;
		template <class U> bool	operator!=(const RedBlackIterator<U, node_type> &rhs) const;

		RedBlackIterator		&operator++(void);
		RedBlackIterator		operator++(int);
		RedBlackIterator		&operator--(void);
		RedBlackIterator		operator--(int);

		reference	operator*(void) const;
		pointer		operator->(void) const;

		operator RedBlackIterator<const T, node_type>(void) const {
			return RedBlackIterator<const T, node_type>(this->_node);
		}

		template <class, class, class, class>
		friend class map;

		template <class, class, class>
		friend class set;

		template <class, class>
		friend class RedBlackIterator;

}; // ****************************************************** class RedBlackIterator end //

template <typename T, typename node_type>
RedBlackIterator<T, node_type>::RedBlackIterator(void) : _node(NULL) { return ; }

template <typename T, typename node_type>
RedBlackIterator<T, node_type>::RedBlackIterator(node_type *src) { this->_node = src; }

template <typename T, typename node_type>
RedBlackIterator<T, node_type>::RedBlackIterator(const RedBlackIterator &src) { *this = src; }

template <typename T, typename node_type>
RedBlackIterator<T, node_type>::~RedBlackIterator(void) { return ; }

template <typename T, typename node_type>
RedBlackIterator<T, node_type> &RedBlackIterator<T, node_type>::operator=(const RedBlackIterator &rhs) {
	if (this == &rhs)
		return (*this);
	this->_node = rhs._node;
	return (*this);
}

template <typename T, typename node_type> template <class U>
bool	RedBlackIterator<T, node_type>::operator==(const RedBlackIterator<U, node_type> &rhs) const {
	return (this->_node == rhs._node);
}

template <typename T, typename node_type> template <class U>
bool	RedBlackIterator<T, node_type>::operator!=(const RedBlackIterator<U, node_type> &rhs) const {
	return (this->_node != rhs._node);
}

template <typename T, typename node_type>
RedBlackIterator<T, node_type> &RedBlackIterator<T, node_type>::operator++(void) {
	if (this->_node->right != NULL)
		this->_node = farLeft(this->_node->right);
	else
	{
		node_type	*child = this->_node;

		this->_node = this->_node->parent;
		while (this->_node && child == this->_node->right)
		{
			child = this->_node;
			this->_node = this->_node->parent;
		}
	}
	return (*this);
}

template <typename T, typename node_type>
RedBlackIterator<T, node_type> RedBlackIterator<T, node_type>::operator++(int) {
	RedBlackIterator	tmp(*this);
	++(*this);
	return (tmp);
}

template <typename T, typename node_type>
RedBlackIterator<T, node_type>& RedBlackIterator<T, node_type>::operator--(void) {
	if (this->_node->left != NULL)
		this->_node = farRight(this->_node->left);
	else
	{
		node_type	*child = this->_node;

		this->_node = this->_node->parent;
		while (this->_node && child == this->_node->left)
		{
			child = this->_node;
			this->_node = this->_node->parent;
		}
	}
	return (*this);
}

template <typename T, typename node_type>
RedBlackIterator<T, node_type> RedBlackIterator<T, node_type>::operator--(int) {
	RedBlackIterator	tmp(*this);
	--(*this);
	return (tmp);
}

template <typename T, typename node_type>
typename RedBlackIterator<T, node_type>::reference RedBlackIterator<T, node_type>::operator*(void) const {
	return (this->_node->data);
}

template <typename T, typename node_type>
typename RedBlackIterator<T, node_type>::pointer RedBlackIterator<T, node_type>::operator->(void) const {
	return &this->operator*();
}

}

#endif

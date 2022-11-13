/*!
 * @file set.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief custom set
 * @version 1.0
 * @date 2022-11-12
 * @copyright Flex copyright (c) 2022
 */

#pragma once

#include "./iterators/IteratorUtils.hpp"
#include "./iterators/RedBlackIterator.hpp"
#include "./iterators/ReverseIterator.hpp"
#include "./utils/utils_include.hpp"

namespace ft
{

template<
	class Key,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<Key>
>
class set
{

public:

	typedef Key													key_type;
	typedef std::size_t											size_type;
	typedef std::ptrdiff_t										difference_type;
	typedef Compare												key_compare;
	typedef key_compare											value_compare;
	typedef key_type											value_type;
	typedef Allocator											allocator_type;
	typedef value_type&											reference;
	typedef const value_type&									const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	typedef ft::mapNode<value_type>								node_type;
	typedef node_type*											node_ptr;

	typedef ft::RedBlackIterator<const value_type, node_type>	const_iterator;
	typedef const_iterator										iterator;
	typedef typename ft::ReverseIterator<iterator>				reverse_iterator;
	typedef typename ft::ReverseIterator<const_iterator>		const_reverse_iterator;

private:

	node_ptr				_data;
	key_compare				_key_cmp;
	allocator_type			_alloc;
	size_type				_size;
	const static size_type	_max_size;

public:

	explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
	:
		_data(),
		_key_cmp(comp),
		_alloc(alloc),
		_size(0)
	{
		this->_data = new node_type;
		return ;
	}

	template< class InputIt >
	set(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator &alloc = Allocator())
	:
		_data(),
		_key_cmp(comp),
		_alloc(alloc),
		_size(0)
	{
		this->_data = new node_type;
		this->_create_data_it(first, last);
	}

	set(const set& other)
	:
		_data(),
		_key_cmp(key_compare()),
		_alloc(allocator_type()),
		_size(0)
	{
		this->_data = new node_type;
		*this = other;
	}

	virtual ~set(void)
	{
		this->clear();
		delete this->_data;
	}

	set &operator=(const set & other)
	{
		if (this == &other)
			return (*this);
		this->clear();
		this->_create_data_it(other.begin(), other.end());
		return (*this);
	}

	allocator_type get_allocator() const
	{
		return this->_alloc;
	}

	size_type size() const
	{
		return (this->_size);
	}

	size_type max_size() const
	{
		return (this->_max_size);
	}

	bool empty() const
	{
		return (this->_size == 0 ? true : false);
	}

	value_compare value_comp() const
	{
		return (value_compare(key_compare()));
	}

	key_compare key_comp() const
	{
		return (key_compare());
	}

	iterator begin()
	{
		return iterator(farLeft(this->_data));
	}

	const_iterator	begin(void) const
	{
		return const_iterator(farLeft(this->_data));
	}

	iterator	end(void)
	{
		return iterator(farRight(this->_data));
	}

	const_iterator	end(void) const
	{
		return const_iterator(farRight(this->_data));
	}

	reverse_iterator	rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	const_reverse_iterator	rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	reverse_iterator		rend(void)
	{
		return reverse_iterator(this->begin());
	}

	const_reverse_iterator	rend(void) const
	{
		return const_reverse_iterator(this->begin());
	}

	void	clear(void)
	{
		node_ptr ghost = this->end()._node;

		if (this->_size == 0)
			return ;
		ghost->parent->right = NULL;
		this->_btree_clear(this->_data);
		this->_data = ghost;
		this->_size = 0;
	}

	void	swap(set &x)
	{
		set tmp;

		tmp._cpy_content(x);
		x._cpy_content(*this);
		this->_cpy_content(tmp);
	}

	iterator	find(const key_type &k)
	{
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->_key_eq(*it, k))
				break ;
			++it;
		}
		return (it);
	}

	const_iterator	find(const key_type &k) const
	{
		const_iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->_key_eq(*it, k))
				break ;
			++it;
		}
		return (it);
	}

	size_type	count(const key_type &k) const
	{
		const_iterator	it = this->begin(), ite = this->end();
		size_type		res = 0;

		while (it != ite)
		{
			if (this->_key_eq(*(it++), k))
			{
				++res;
				break ; // Because map can't have the same key twice (or more)
			}
		}
		return (res);
	}

	iterator	lower_bound(const key_type &k)
	{
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (!this->_key_cmp(*it, k))
				break;
			++it;
		}
		return (it);
	}

	const_iterator	lower_bound(const key_type &k) const
	{
		const_iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (!this->_key_cmp(*it, k))
				break;
			++it;
		}
		return (it);
	}

	iterator	upper_bound(const key_type &k)
	{
		return this->lower_bound(k);
	}

	const_iterator	upper_bound(const key_type &k) const
	{
		return this->lower_bound(k);
	}

	pair<const_iterator,const_iterator>	equal_range(const key_type &k) const
	{
		pair<const_iterator, const_iterator> res;

		res.first = this->lower_bound(k);
		res.second = this->upper_bound(k);
		return (res);
	}

	pair<iterator,iterator>	equal_range(const key_type &k)
	{
		pair<iterator, iterator> res;

		res.first = this->lower_bound(k);
		res.second = this->upper_bound(k);
		return (res);
	}

	ft::pair<iterator, bool>	insert(const value_type &val)
	{
		ft::pair<iterator, bool> res;

		res.second = !this->count(val);
		if (res.second == true)
			this->_btree_add(new node_type(val));
		res.first = this->find(val);
		return (res);
	}

	iterator	insert(iterator position, const value_type &val)
	{
		static_cast<void>(position);
		return this->insert(val).first;
	}

	template <class Ite> void
	insert(Ite first, Ite last)
	{
		while (first != last)
			this->insert(*first++);
	}

	void	erase(iterator position)
	{
		this->erase(position++, position);
	}

	size_type	erase(const key_type &k)
	{
		iterator element = this->find(k);

		if (element == this->end())
			return (0);
		this->_btree_rm(element._node);
		return (1);
	}

	void	erase(iterator first, iterator last)
	{
		while (first != last)
			this->_btree_rm((first++)._node);
	}

private:

	template <class Ite>
	void	_create_data_it(Ite first, Ite last)
	{
		this->insert(first, last);
	}

	void	_cpy_content(set &src)
	{
		this->clear();
		node_ptr tmp = this->_data;

		this->_data = src._data;
		this->_key_cmp = src._key_cmp;
		this->_alloc = src._alloc;
		this->_size = src._size;
		src._data = tmp; src._size = 0;
		tmp = NULL;
	}

	void	_btree_clear(node_ptr node)
	{
		if (node == NULL)
			return ;
		this->_btree_clear(node->left);
		this->_btree_clear(node->right);
		delete node;
	}

	void	_btree_add(node_ptr newNode)
	{
		node_ptr	*parent = &this->_data;
		node_ptr	*node = &this->_data;
		node_ptr	ghost = farRight(this->_data);
		bool		side_left = -1;

		++this->_size;
		while (*node && *node != ghost)
		{
			parent = node;
			side_left = this->_key_cmp(newNode->data, (*node)->data);
			node = (side_left ? &(*node)->left : &(*node)->right);
		}
		if (*node == NULL)
		{
			newNode->parent = (*parent);
			*node = newNode;
		}
		else // if (*node == ghost)
		{
			*node = newNode;
			newNode->parent = ghost->parent;
			ghost->parent = farRight(newNode); // Using farRight(newNode)
			farRight(newNode)->right = ghost; // in case newNode isnt alone
		}
	}

	void	_btree_rm(node_ptr rmNode)
	{
		node_ptr	replaceNode = NULL;
		node_ptr	*rmPlace = &this->_data;

		--this->_size;
		if (rmNode->parent)
			rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
		if (rmNode->left == NULL && rmNode->right == NULL)
			;
		else if (rmNode->left == NULL) // left == NULL && right != NULL
			replaceNode = rmNode->right;
		else // left != NULL && right ?= NULL
		{
			replaceNode = farRight(rmNode->left);
			if (replaceNode != rmNode->left)
				if ((replaceNode->parent->right = replaceNode->left))
					replaceNode->left->parent = replaceNode->parent;
		}
		if (replaceNode)
		{
			replaceNode->parent = rmNode->parent;
			if (rmNode->left && rmNode->left != replaceNode)
			{
				replaceNode->left = rmNode->left;
				replaceNode->left->parent = replaceNode;
			}
			if (rmNode->right && rmNode->right != replaceNode)
			{
				replaceNode->right = rmNode->right;
				replaceNode->right->parent = replaceNode;
			}
		}
		*rmPlace = replaceNode;
		delete rmNode;
	}

	bool	_key_eq(const key_type &k1, const key_type &k2) const
	{
		return (!this->_key_cmp(k1, k2) && !this->_key_cmp(k2, k1));
	}

};

template <class Key, class Compare, class Alloc>
const typename set<Key, Compare, Alloc>::size_type
set<Key, Compare, Alloc>::_max_size =
	std::numeric_limits<difference_type>::max() / sizeof(node_type);

template <class Key, class Compare, class Alloc>
bool	operator==(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class Compare, class Alloc>
bool	operator!=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
{
	return !(lhs == rhs);
}

template <class Key, class Compare, class Alloc>
bool	operator< (const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class Compare, class Alloc>
bool	operator<=(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
{
	return !(rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool	operator> (const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
{
	return (rhs < lhs);
}

template <class Key, class Compare, class Alloc>
bool	operator>=(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
{
	return !(lhs < rhs);
}

template <class Key, class Compare, class Alloc>
void	swap(set<Key, Compare, Alloc> &x, set<Key, Compare, Alloc> &y)
{
	x.swap(y);
}

} // namespace ft

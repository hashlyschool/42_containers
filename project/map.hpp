/*!
 * @file map.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief
 * @version 1.0
 * @date 2022-11-10
 * @copyright Flex copyright (c) 2022
 */

#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include "./iterators/IteratorUtils.hpp"
#include "./iterators/RedBlackIterator.hpp"
#include "./iterators/ReverseIterator.hpp"
#include "./utils/utils_include.hpp"

namespace ft
{

template<
class Key,
class T,
class Compare = ft::less<Key>,
class Alloc = std::allocator<ft::pair<const Key, T> >
>
class map
{

public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<key_type, mapped_type>				value_type;
	typedef Compare										key_compare;


	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	typedef ft::mapNode<value_type>						node_type;
	typedef node_type*									node_ptr;

	typedef ft::RedBlackIterator<value_type, node_type>			iterator;
	typedef ft::RedBlackIterator<const value_type, node_type>	const_iterator;
	typedef typename ft::ReverseIterator<iterator>		reverse_iterator;
	typedef typename ft::ReverseIterator<const_iterator>	const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t										size_type;


private:
	node_ptr				_data;
	key_compare				_key_cmp;
	allocator_type			_alloc;
	size_type				_size;
	const static size_type	_max_size;

public:
	class value_compare : ft::binary_function<value_type, value_type, bool>
	{
		friend class map<key_type, mapped_type, key_compare, Alloc>;

		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}

		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return (comp(x.first, y.first));
			}
	};

	explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
	:
		_data(),
		_key_cmp(comp),
		_alloc(alloc),
		_size(0)
	{
		this->_data = new node_type;
		return ;
	}

	template <class Ite>
	map(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first, \
	Ite last, const key_compare &comp = key_compare(), \
	const allocator_type &alloc = allocator_type())
	:
		_data(),
		_key_cmp(comp),
		_alloc(alloc),
		_size(0)
	{
		this->_data = new node_type;
		this->_create_data_it(first, last);
	}

	map(const map &src)
	:
		_data(),
		_key_cmp(key_compare()),
		_alloc(allocator_type()),
		_size(0)
	{
		this->_data = new node_type;
		*this = src;
	}

	virtual ~map(void)
	{
		this->clear();
		delete this->_data;
	}

	map	&operator=(map const &rhs)
	{
		if (this == &rhs)
			return (*this);
		this->clear();
		this->_create_data_it(rhs.begin(), rhs.end());
		return (*this);
	}

	iterator				begin(void)
	{
		return iterator(farLeft(this->_data));
	}

	const_iterator			begin(void) const
	{
		return const_iterator(farLeft(this->_data));
	}

	iterator				end(void)
	{
		return iterator(farRight(this->_data));
	}

	const_iterator			end(void) const
	{
		return const_iterator(farRight(this->_data));
	}

	reverse_iterator		rbegin(void)
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

	size_type	size(void) const
	{
		return (this->_size);
	}

	size_type	max_size(void) const
	{
		return (this->_max_size);
	}

	bool		empty(void) const
	{
		return (this->_size == 0 ? true : false);
	}

	mapped_type	&operator[](const key_type &k)
	{
		return (this->insert(value_type(k, mapped_type()))).first->second;
	}

	ft::pair<iterator, bool>	insert(const value_type &val)
	{
		ft::pair<iterator, bool> res;

		res.second = !this->count(val.first);
		if (res.second == true)
			this->_btree_add(new node_type(val));
		res.first = this->find(val.first);
		return (res);
	}

	iterator	insert(iterator position, const value_type &val)
	{
		static_cast<void>(position);
		return this->insert(val).first;
	}

	template <class Ite> void	insert(Ite first, Ite last)
	{
		while (first != last)
			this->insert(*first++);
	}

	void		erase(iterator position)
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

	void		erase(iterator first, iterator last)
	{
		while (first != last)
			this->_btree_rm((first++)._node);
	}

	void		swap(map &x)
	{
		map tmp;

		tmp._cpy_content(x);
		x._cpy_content(*this);
		this->_cpy_content(tmp);
	}

	void		clear(void)
	{
		node_ptr ghost = this->end()._node;

		if (this->_size == 0)
			return ;
		ghost->parent->right = NULL;
		this->_btree_clear(this->_data);
		this->_data = ghost;
		this->_size = 0;
	}

	key_compare		key_comp(void) const
	{
		return (key_compare());
	}

	value_compare	value_comp(void) const
	{
		return (value_compare(key_compare()));
	}

	iterator		find(const key_type &k)
	{
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->_key_eq(it->first, k))
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
			if (this->_key_eq(it->first, k))
				break ;
			++it;
		}
		return (it);
	}

	size_type		count(const key_type &k) const
	{
		const_iterator	it = this->begin(), ite = this->end();
		size_type		res = 0;

		while (it != ite)
		{
			if (this->_key_eq((it++)->first, k))
			{
				++res;
				break ; // Because map can't have the same key twice (or more)
			}
		}
		return (res);
	}

	iterator		lower_bound(const key_type &k)
	{
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (!this->_key_cmp(it->first, k))
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
			if (!this->_key_cmp(it->first, k))
				break;
			++it;
		}
		return (it);
	}

	iterator		upper_bound(const key_type &k)
	{
		iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->_key_cmp(k, it->first))
				break;
			++it;
		}
		return (it);
	}

	const_iterator	upper_bound(const key_type &k) const
	{
		const_iterator it = this->begin(), ite = this->end();

		while (it != ite)
		{
			if (this->_key_cmp(k, it->first))
				break;
			++it;
		}
		return (it);
	}

	pair<const_iterator,const_iterator>	equal_range(const key_type &k) const
	{
		pair<const_iterator, const_iterator> res;

		res.first = this->lower_bound(k);
		res.second = this->upper_bound(k);
		return (res);
	}

	pair<iterator,iterator>				equal_range(const key_type &k)
	{
		pair<iterator, iterator> res;

		res.first = this->lower_bound(k);
		res.second = this->upper_bound(k);
		return (res);
	}

private:

	template <class Ite>
	void	_create_data_it(Ite first, Ite last)
	{
		this->insert(first, last);
	}

	void	_create_data(size_type size, const value_type &val = value_type())
	{
		(void)size; (void)val;
	}

	void	_cpy_content(map &src)
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

	void				_btree_clear(node_ptr node)
	{
		if (node == NULL)
			return ;
		this->_btree_clear(node->left);
		this->_btree_clear(node->right);
		delete node;
	}

	void				_btree_add(node_ptr node)
	{
		node_ptr	*parent = &this->_data;
		node_ptr	*node = &this->_data;
		node_ptr	ghost = farRight(this->_data);
		bool		side_left = -1;

		++this->_size;
		while (*node && *node != ghost)
		{
			parent = node;
			side_left = this->_key_cmp(newNode->data.first, (*node)->data.first);
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

	void				_btree_rm(node_ptr node)
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

	bool				_key_eq(const key_type &k1, const key_type &k2) const
	{
		return (!this->_key_cmp(k1, k2) && !this->_key_cmp(k2, k1));
	}

	const typename size_type	_max_size = std::numeric_limits<difference_type>::max() (sizeof(node_type) / 2 ?: 1);

	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

};

}

#endif //ft_map_hpp

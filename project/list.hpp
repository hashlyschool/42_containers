/*!
 * @file list.hpp
 * @author INikituk (inikituk@npomis.ru)
 * @brief custom list
 * @version 1.0
 * @date 2022-11-11
 * @copyright Flex copyright (c) 2022
 */

#ifndef LIST_HPP
#define LIST_HPP

# include "./iterators/IteratorUtils.hpp"
# include "./iterators/ListIterator.hpp"
# include "./iterators/ReverseIterator.hpp"

namespace ft
{
template < class T, class Alloc = std::allocator<T> > class list
{
	public :

		typedef T											value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference   		reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer     		pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef ft::List_iterator<T>						iterator;
		typedef ft::List_const_iterator<T>					const_iterator;
		typedef ft::ReverseIterator<iterator>				reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t  size_type;

		explicit list (const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc)
		{
			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
			_last_node->prev = _last_node;
			_last_node->next = _last_node;
		}

		explicit list (size_type n, const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type())
		:
			_alloc(alloc)
		{
			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
			_last_node->prev = _last_node;
			_last_node->next = _last_node;
			this->insert(end(), n, val);
		}

		template <class InputIterator>
				list (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
		:
			_alloc(alloc)
		{
			bool is_valid;
			if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
				throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
			_last_node->prev = _last_node;
			_last_node->next = _last_node;
			this->insert(end(), first, last);
		}

		list (const list& x)
		:
			_alloc(x._alloc)
		{
			_last_node = _node_alloc.allocate(1);
			_node_alloc.construct(_last_node, Doubly_Linked_Node<T>());
			_last_node->prev = _last_node;
			_last_node->next = _last_node;

			const_iterator beg = x.begin();
			const_iterator end = x.end();

			while (beg != end)
				this->_insertBefore(_last_node, _createNode((beg++)._node->data));
		}

		~list()
		{
			this->clear();
			_node_alloc.destroy(_last_node);
			_node_alloc.deallocate(_last_node, 1);
		}

		list& operator= (const list & x)
		{
			if (&x == this)
				return (*this);
			this->clear();
			this->insert(x.begin(), x.end());
			return (*this);
		}

		iterator begin()
		{
			return (iterator(_last_node->next));
		}

		const_iterator begin() const
		{
			return (const_iterator(_last_node->next));
		}

		iterator end()
		{
			return (iterator(_last_node));
		}

		const_iterator end() const
		{
			return (const_iterator(_last_node));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (reverse_iterator(begin()));
		}

		bool empty() const
		{
			return (_last_node->next == _last_node ? true : false);
		}

		size_type size() const
		{
			return (_listSize());
		}

		size_type max_size() const
		{
			return node_allocator().max_size();
		}

		reference front()
		{
			return (_last_node->next->data);
		}

		const_reference front() const
		{
			return (_last_node->next->data);
		}

		reference back()
		{
			return (_last_node->prev->data);
		}

		const_reference back() const
		{
			return (_last_node->prev->data);
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			this->clear();
			this->insert(this->end(), first, last);
		}

		void assign (size_type n, const value_type& val)
		{
			this->clear();
			this->insert(this->end(), n, val);
		}

		void push_front (const value_type& val)
		{
			_insertBeginning(_createNode(val));
		}

		void pop_front()
		{
			_delete(_last_node->next);
		}

		void push_back(const value_type& val)
		{
			_insertEnd(_createNode(val));
		}

		void pop_back()
		{
			_delete(_last_node->prev);
		}

		iterator insert (iterator position, const value_type& val)
		{
			return (_insertBefore(position._node, _createNode(val)));
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			while (n--)
				_insertBefore(position._node, _createNode(val));
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
		{
			bool is_valid;
			if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
				throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

			difference_type n = ft::distance(first, last);
			while (n--)
				_insertBefore(position._node, _copyNode((first++)._node));
		}

		iterator erase (iterator position)
		{
			iterator rtn(position._node->next);
			_delete(position._node);
			return (rtn);
		}

		iterator erase (iterator first, iterator last)
		{
			iterator rtn(last._node->next);

			while (first != last)
				_delete((first++)._node);

			return (rtn);
		}

		void swap (list& x)
		{
			if (x == *this)
				return;

			allocator_type 			save_alloc = x._alloc;
			node_allocator			save_node_alloc = x._node_alloc;
			Doubly_Linked_Node<T>	*save_last_node = x._last_node;

			x._alloc = this->_alloc;
			x._node_alloc = this->_node_alloc;
			x._last_node = this->_last_node;

			this->_alloc = save_alloc;
			this->_node_alloc = save_node_alloc;
			this->_last_node = save_last_node;
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (this->max_size() - this->size() < n)
				throw (std::length_error("list::resize"));
			if (n > this->size())
			{
				n -= this->size();
				while (n--)
					this->_insertBefore(_last_node, _createNode(val));
			}
			else
			{
				while (this->size() > n)
					this->pop_back();
			}
		}

		void clear()
		{
			Doubly_Linked_Node<T> *tmp = _last_node->next;
			Doubly_Linked_Node<T> *next_tmp;
			while (tmp != _last_node)
			{
				next_tmp = tmp->next;
				_delete(tmp);
				tmp = next_tmp;
			}
		}


		void splice (iterator position, list& x)
		{
			iterator x_beg = x.begin();
			iterator x_save;

			while (x_beg != x.end())
			{
				x_save = (++x_beg)--;
				x._disconnect(x_beg._node);
				if (x != *this)
					_insertBefore(position._node, x_beg._node);
				x_beg = x_save;
			}
		}

		void splice (iterator position, list& x, iterator i)
		{
			x._disconnect(i._node);
			_insertBefore(position._node, i._node);
		}

		void splice (iterator position, list& x, iterator first, iterator last)
		{
			iterator x_save;

			while (first != last)
			{
				x_save = (++first)--;
				x._disconnect(first._node);
				if (x != *this)
					_insertBefore(position._node, first._node);
				first = x_save;
			}
		}

		void remove(const value_type& val)
		{
			iterator save;
			iterator first = _last_node->next;

			while (first != end())
			{
				save = (++first)--;
				if (*first == val)
					_delete(first._node);
				first = save;
			}
		}

		template <class Predicate>
				void remove_if (Predicate pred)
		{
			iterator save;
			iterator first = _last_node->next;

			while (first != end())
			{
				save = (++first)--;
				if (pred(*first))
					_delete(first._node);
				first = save;
			}
		}

		void unique()
		{
			iterator save;
			iterator first = _last_node->next;

			while (first != end())
			{
				save = (++first)--;
				if (first._node->prev != _last_node
					&& first._node->prev->data == first._node->data)
					_delete(first._node);
				first = save;
			}
		}


		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred)
		{
			iterator save;
			iterator first = _last_node->next;

			while (first != end())
			{
				save = (++first)--;
				if (first._node->prev != _last_node
					&& binary_pred(*first,*((--first)++)))
					_delete(first._node);
				first = save;
			}
		}

		void merge(list& x)
		{
			this->merge(x, ft::less<T>());
		}

		template <class Compare>
		void merge (list& x, Compare comp)
		{
			if (&x == this)
				return ;

			iterator save;
			iterator save_x;
			iterator first = _last_node->next;
			iterator first_x = x._last_node->next;

			while (first_x != x.end())
			{
				save = (++first)--;
				save_x = (++first_x)--;
				if (first._node != _last_node && comp(first._node->data, first_x._node->data))
					first = save;
				else
				{
					x._disconnect(first_x._node);
					_insertBefore(first._node, first_x._node);
					first_x = save_x;
				}
			}
		}

		void sort()
		{
			_last_node->next = _mergeSort(_last_node->next, ft::less<T>());

			Doubly_Linked_Node<T> * tmp = _last_node->next;
			Doubly_Linked_Node<T> * prev_last;

			while (tmp != _last_node)
			{
				prev_last = tmp;
				tmp = tmp->next;
			}

			_last_node->prev = prev_last;
		}

		template <class Compare>
		void sort (Compare comp)
		{
			_last_node->next = _mergeSort(_last_node->next, comp);

			Doubly_Linked_Node<T> * tmp = _last_node->next;
			Doubly_Linked_Node<T> * prev_last;

			while (tmp != _last_node)
			{
				prev_last = tmp;
				tmp = tmp->next;
			}

			_last_node->prev = prev_last;
		}

		void reverse()
		{
			Doubly_Linked_Node<T> * tmp = _last_node->next;
			Doubly_Linked_Node<T> * save_next;

			save_next = _last_node->next;
			_last_node->next = _last_node->prev;
			_last_node->prev = save_next;
			while (tmp != _last_node)
			{
				save_next = tmp->next;
				tmp->next = tmp->prev;
				tmp->prev = save_next;
				tmp = save_next;
			}
		}

	private :

		typedef typename allocator_type::template	rebind<Doubly_Linked_Node<T> >::other node_allocator;
		typedef typename node_allocator::pointer	_node_pointer;

		allocator_type 			_alloc;
		node_allocator			_node_alloc;
		Doubly_Linked_Node<T>	*_last_node;

		_node_pointer _createNode(const T& data, Doubly_Linked_Node<T> * prev = u_nullptr, Doubly_Linked_Node<T> * next = u_nullptr)
		{
			_node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Doubly_Linked_Node<T>(data));
			new_node->prev = prev;
			new_node->next = next;
			return (new_node);
		}

		_node_pointer _copyNode(const Doubly_Linked_Node<T> * node)
		{
			_node_pointer new_node = _node_alloc.allocate(1);
			_node_alloc.construct(new_node, Doubly_Linked_Node<T>(node->data));
			new_node->prev = node->prev;
			new_node->next = node->next;
			return (new_node);
		}

		size_type _listSize(void) const
		{
			size_type count = 0;
			_node_pointer tmp = _last_node->next;

			while (tmp != _last_node)
			{
				tmp = tmp->next;
				count++;
			}
			return (count);
		}

		void _insertBeginning(Doubly_Linked_Node<T>	*new_node)
		{
			if (_last_node->next == _last_node)
			{
				_last_node->next = new_node;
				_last_node->prev = new_node;
				new_node->prev = _last_node;
				new_node->next = _last_node;
			}
			else
				_insertBefore(_last_node->next, new_node);
			}

		void _insertEnd(Doubly_Linked_Node<T>	*new_node)
		{
			if (_last_node->next == _last_node)
				_insertBeginning(new_node);
			else
				_insertAfter(_last_node->prev, new_node);
		}

		iterator _insertAfter(Doubly_Linked_Node<T> *prev, Doubly_Linked_Node<T> *new_node)
		{
			new_node->prev = prev;
			if (prev->next == _last_node)
			{
				new_node->next = _last_node;
				_last_node->prev = new_node;
			}
			else
			{
				new_node->next = prev->next;
				prev->next->prev = new_node;
			}
			prev->next = new_node;
			return (iterator(prev->next));
		}

		iterator _insertBefore(Doubly_Linked_Node<T> *next,  Doubly_Linked_Node<T> *new_node)
		{
			new_node->next = next;
			if (next->prev == _last_node)
			{
				new_node->prev = _last_node;
				_last_node->next = new_node;
			}
			else
			{
				new_node->prev = next->prev;
				next->prev->next = new_node;
			}
			next->prev = new_node;
			return (iterator(next->prev));
		}

		void _delete(Doubly_Linked_Node<T> *node)
		{
			_disconnect(node);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}

		void _disconnect(Doubly_Linked_Node<T> *node)
		{
			if (node->prev == _last_node)
				_last_node->next = node->next;
			else
				node->prev->next = node->next;
			if (node->next == _last_node)
				_last_node->prev = node->prev;
			else
				node->next->prev = node->prev;
		}

		_node_pointer _split(Doubly_Linked_Node<T> *head)
		{
			_node_pointer fast = head;
			_node_pointer slow = head;

			while (fast->next != _last_node && fast->next->next != _last_node)
			{
				fast = fast->next->next;
				slow = slow->next;
			}

			_node_pointer tmp = slow->next;
			slow->next = _last_node;
			return (tmp);
		}

		template <class Compare>
		_node_pointer _merge(Doubly_Linked_Node<T> *first, Doubly_Linked_Node<T> *second, Compare comp)
		{
			if (first == _last_node)
				return (second);
			if (second == _last_node)
				return (first);

			if (comp(first->data,second->data))
			{
				first->next = _merge(first->next, second, comp);
				first->next->prev = first;
				first->prev = _last_node;
				return (first);
			}
			else
			{
				second->next = _merge(first, second->next, comp);
				second->next->prev = second;
				second->prev = _last_node;
				return (second);
			}
		}

		template <class Compare>
		_node_pointer _mergeSort(Doubly_Linked_Node<T> *head, Compare comp)
		{
			if (head == _last_node || head->next == _last_node)
				return (head);

			_node_pointer second = _split(head);

			head = _mergeSort(head, comp);
			second = _mergeSort(second, comp);

			return (_merge(head, second, comp));
		}
};

template <class T, class Alloc>
	bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::list<T>::const_iterator first1 = lhs.begin();
		typename ft::list<T>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

template <class T, class Alloc>
	bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

template <class T, class Alloc>
	bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

template <class T, class Alloc>
	bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

template <class T, class Alloc>
	bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

template <class T, class Alloc>
	bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

template <class T, class Alloc>
	void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y)
	{
		x.swap(y);
	}
}


#endif

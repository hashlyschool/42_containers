/*!
 * @file Vector.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief file brief
 * @version 1.0
 * @date 2022-10-12
 * @copyright Flex copyright (c) 2022
 */
#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <limits>

#include "./iterators/RandomAccessIterator.hpp"
#include "./iterators/ReverseIterator.hpp"
#include "./utils/utils_include.hpp"

namespace ft {

/*!
 * @author hashly (ilya12-141998@mail.ru)
 * @brief ft::vector
 * @date 2022-10-13
 *
 * @tparam T
 * @tparam Allocator
 *
 * @warning
 * @bug
 * @example "vector<int> myVec;"
 * @todo
 */
template < class T, class Allocator = std::allocator<T> >
class vector {

public:
	typedef	T											value_type;
	typedef	Allocator									allocator_type;
	typedef typename allocator_type::size_type			size_type;
	typedef	ft::RandomAccessIterator<value_type>		iterator;
	typedef	ft::RandomAccessIterator<const value_type>	const_iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename Allocator::pointer					pointer;
	typedef	typename Allocator::const_pointer			const_pointer;
	typedef	ft::ReverseIterator<iterator>				reverse_iterator;
	typedef	ft::ReverseIterator<const_iterator>		const_reverse_iterator;

private:
	pointer		_first;
	size_type		_size, _capacity;
	allocator_type	_allocator;
public:

	explicit vector (const allocator_type& alloc = allocator_type())
	:
		_first(u_nullptr),
		_size(0),
		_capacity(0),
		_allocator(alloc)
	{}

	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	:
		_size(n),
		_capacity(n),
		_allocator(alloc)
	{
		fill_initialize(n, val);
	}

	private:
	void	fill_initialize(size_type n, const value_type& val) {
		_first = _allocator.allocate(n);
		for (size_type i = 0; i < n; ++i)
			_allocator.construct(_first + i, val);
	}

	public:
	template <class InputIterator>
	vector (typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type())
	:
		_allocator(alloc)
	{
		initialize_dispatch(first, last, false_type());
		// typedef typename ft::is_integral<InputIterator>::type Integral;
		// initialize_dispatch(first, last, Integral());
	}

	private:
	template<typename Integer>
	void	initialize_dispatch(Integer n, Integer val, true_type)
	{
		this->_size = static_cast<size_type>(n);
		this->_capacity = static_cast<size_type>(n);
		this->_first = u_nullptr;
		fill_initialize(static_cast<size_type>(n), val);
	}

	template<typename InputIterator>
	void	initialize_dispatch(InputIterator first, InputIterator last, false_type)
	{
		if (first > last)
			throw std::length_error("vector");
		_size = last - first;
		_capacity = _size;
		_first = _allocator.allocate(_capacity);
		for (difference_type i = 0; i < static_cast<difference_type>(_size); ++i)
			_allocator.construct(_first + i, *(first + i));
	}

	public:
	vector(const vector& x)
	:
		_size(0),
		_capacity(0)
	{
		*this = x;
	}

	~vector()
	{
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		if(_capacity)
			_allocator.deallocate(_first, _capacity);
	}

	vector&	operator=(const vector& x) {
		if (*this == x)
			return *this;
		for (size_type i = 0; i < _size; ++i)
			_allocator.destroy(_first + i);
		this->_size = x.size();
		if (_capacity < _size) {
			if (_capacity != 0)
				_allocator.deallocate(_first, _capacity);
			_capacity = _size;
			_first = _allocator.allocate(_capacity);
		}
		for (size_type i = 0; i < _size; ++i)
			_allocator.construct(_first + i, x[i]);
		return (*this);
	}

	//ITERATORS
	iterator begin() { return (iterator(_first)); }
	const_iterator begin() const { return(const_iterator(_first)); }

	iterator end(){ return (iterator(_first + _size)); }
	const_iterator end() const { return (const_iterator(_first + _size)); }

	reverse_iterator rbegin() { return (reverse_iterator(end())); }
	const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

	reverse_iterator rend() { return (reverse_iterator(begin())); }
	const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

	///CAPACITY
	size_type	size() const { return (_size); }
	size_type	max_size() const { return(_allocator.max_size()); }

	void resize (size_type n, value_type val = value_type()) {
		if (n < _size) {
			for (size_type i = n; i < _size; ++i)
				_allocator.destroy(_first + i);
			_size = n;
		}
		else if (n > _size) {
			if (_capacity < n)
				this->reserve(_capacity * 2 > n ? _capacity * 2 : n);
			for (size_type i = _size; i < n; ++i) {
				_allocator.construct(_first + i, val);
				++_size;
			}
		}
	}

	size_type	capacity() const { return (_capacity); }

	bool empty() const { return (_size == 0); }

	void	reserve(size_type n) {
		if (n <= _capacity)
			return ;
		if (n > max_size())
			throw std::length_error("vector");
		pointer	newarr = _allocator.allocate(n);
		size_type	i = 0;
		try
		{
			for (; i < _size; ++i)
				_allocator.construct(newarr + i, *(_first + i));
		}
		catch(const std::exception& e)
		{
			while (i != 0) {
				_allocator.destroy(newarr + i - 1);
				++i;
			}
			_allocator.deallocate(newarr, n);
			throw ;
		}
		for (size_type i = 0; i < _size; ++i)
			_allocator.destroy(_first + i);
		if (_capacity)
			_allocator.deallocate(_first, _capacity);
		_capacity = n;
		_first = newarr;
	}

	reference operator[] (size_type n) { return(*(_first + n)); }

	const_reference operator[] (size_type n) const { return(*(_first + n)); }

	reference at(size_type n) {
		if (n >= _size)
			throw std::out_of_range("vector at out of range");
		return (_first[n]);
	}

	const_reference at(size_type n) const {
		if (n >= _size)
			throw std::out_of_range("vector at out of range");
		return (_first[n]);
	}

	reference front() {return (_first[0]); }
	const_reference front() const { return (_first[0]); }

	reference back() { return (_first[_size - 1]); }
	const_reference back() const { return (_first[_size - 1]); }

	value_type* data() { return (_first); }
	const value_type* data() const { return (_first); }

	///ASSIGN

	void assign (size_type n, const value_type& val) {
		fill_assign(n, val);
	}

	template <class InputIterator>
	void	assign(InputIterator first, InputIterator last) {
		typedef typename ft::is_integral<InputIterator>::type Integral;
		assign_dispatch(first, last, Integral());
	}

	private:
	template<typename Integer>
	void	assign_dispatch(Integer n, Integer val, true_type) {
		fill_assign(n, val);
	}

	template<typename InputIterator>
	void	assign_dispatch(InputIterator first, InputIterator last, false_type) {
		assign_aux(first, last);
	}

	template<typename InputIterator>
	void	assign_aux(InputIterator first, InputIterator last) {
		if (first > last)
			throw std::logic_error("vector");
		difference_type	count = last - first;
		clear();
		if (count > static_cast<difference_type>(_capacity)) {
			_allocator.deallocate(_first, _capacity);
			_first = _allocator.allocate(count);
			_capacity = count;
		}
		iterator pos = begin();
		while (first < last)
		{
			_allocator.construct(&(*pos), *first);
			pos++;
			first++;
		}
		_size = count;
	}

	void	fill_assign(size_type n, const value_type& val)
	{
		this->clear();
		if (n == 0)
			return ;
		if (n > _capacity) {
			_allocator.deallocate(_first, _capacity);
			_first = _allocator.allocate(n);
			_capacity = n;
		}
		for (size_type i = 0; i < n; ++i)
			_allocator.construct(_first + i, val);
		_size = n;
	}

	///PUSH

	public:
	void	push_back(const value_type& val) {
		if(_size == _capacity)
			reserve(_capacity == 0 ? 1 : _capacity * 2);
		_allocator.construct(_first + _size, val);
		_size++;
	}

	void	pop_back() {
		if (_size == 0)
			return ;
		_allocator.destroy(_first + _size - 1);
		_size--;
	}


	///INSERT

	iterator insert(iterator position, const value_type& val) {
		if (position < begin() || position > end())
			throw std::logic_error("vector");
		difference_type start = position - begin();
		if (_size == _capacity) {
			_capacity = _capacity * 2 + (_capacity == 0);
			pointer newarr = _allocator.allocate(_capacity);
			std::uninitialized_copy(begin(), position, iterator(newarr));
			_allocator.construct(newarr + start, val);
			std::uninitialized_copy(position, end(), iterator(newarr + start + 1));
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_first + i);
			if (_size)
				_allocator.deallocate(_first, _size);
			++_size;
			_first = newarr;
		}
		else {
			for (size_type i = _size; i > static_cast<size_type>(start); --i) {
				_allocator.destroy(_first + i);
				_allocator.construct(_first + i, *(_first + i - 1));
			}
			_allocator.destroy(&(*position));
			_allocator.construct(&(*position), val);
			_size++;
		}
		return (begin() + start);
	}

	void insert(iterator position, size_type n, const value_type& val) {
		fill_insert(position, n, val);
	}

	private:
	void	fill_insert(iterator position, size_type n, const value_type& val) {
		if (n == 0)
			return ;
		else if (max_size() - _size < n)
			throw std::length_error("vector");
		if (position < begin() || position > end())
			throw std::logic_error("vector");
		difference_type start = position - begin();
		if (_size + n > _capacity) {
			size_type new_cap = _capacity * 2 >= _size + n ? _capacity * 2 : _size + n;
			pointer new_arr = _allocator.allocate(new_cap);
			std::uninitialized_copy(begin(), position, iterator(new_arr));
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(new_arr + start + i, val);
			std::uninitialized_copy(position, end(), iterator(new_arr + start + n));
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_first + i);
			if (_capacity)
				_allocator.deallocate(_first, _capacity);
			_size += n;
			_capacity = new_cap;
			_first = new_arr;
		}
		else {
			for (size_type i = _size; i > static_cast<size_type>(start); i--) {
				_allocator.destroy(_first + i + n - 1);
				_allocator.construct(_first + i + n - 1, *(_first + i - 1));
			}
			for (size_type i = 0; i < n; i++) {
				_allocator.destroy(_first + i + start);
				_allocator.construct(_first + i + start, val);
			}
			_size += n;
		}
	}

	public:
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {
		typedef typename ft::is_integral<InputIterator>::type	Integral;
		insert_dispatch(position, first, last, Integral());
	}

	private:
	template<typename Integer>
	void	insert_dispatch(iterator position, Integer n, Integer val, true_type)
	{
		fill_insert(position, n, val);
	}

	template<typename InputIterator>
	void	insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type)
	{
		if (position < begin() || position > end() || first > last)
			throw std::logic_error("vector");
		size_type start = static_cast<size_type>(position - begin());
		size_type count = static_cast<size_type>(last - first);
		if (count == 0)
			return ;
		else if (max_size() - _size < count)
			throw std::length_error("vector");
		if (_size + count > _capacity) {
			size_type new_cap = _capacity * 2 >= _size + count ? _capacity * 2 : _size + count;
			pointer new_arr = _allocator.allocate(new_cap);
			std::uninitialized_copy(begin(), position, iterator(new_arr));
			try {
				for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
					_allocator.construct(new_arr + start + i, *first);
			}
			catch (...){
				for (size_type i = 0; i < count + start; ++i)
					_allocator.destroy(new_arr + i);
				_allocator.deallocate(new_arr, new_cap);
				throw;
			}
			std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
			for (size_type i = 0; i < _size; i++)
				_allocator.destroy(_first + i);
			_allocator.deallocate(_first, _capacity);
			_size += count;
			_capacity = new_cap;
			_first = new_arr;
		}
		else {
			for (size_type i = _size; i > static_cast<size_type>(start); i--) {
				_allocator.destroy(_first + i + count - 1);
				_allocator.construct(_first + i + count - 1, *(_first + i - 1));
			}
			for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
				_allocator.destroy(_first + i + count);
				_allocator.construct(_first + start + i, *first);
			}
			_size += count;
		}
	}

	///ERASE

	public:
	iterator	erase(iterator position) {
		if (_size == 0)
			throw std::logic_error("vector");
		size_type d = static_cast<size_type>(ft::itlen(begin(), position));
		if (d > _size - 1)
			throw std::logic_error("vector");
		for (size_type i = d; i < _size - 1; ++i){
			_allocator.destroy(_first + i);
			_allocator.construct(_first + i, *(_first + i + 1));
		}
		_size--;
		_allocator.destroy(_first + _size - 1);
		return iterator(_first + d);
	}

	iterator	erase(iterator first, iterator last)
	{
		difference_type start = ft::itlen(begin(), first);
		difference_type need_to_copy = ft::itlen(last, end());
		bool last_is_end = (last == end());
		while (first != last){
			_allocator.destroy(&(*first));
			first++;
		}
		size_type i = start;
		while (last < end()){
			if (this->_first + start)
				_allocator.destroy(_first + i);
			_allocator.construct(_first + i, *last);
			i++;
			last++;
		}
		for (size_type i = start + need_to_copy; i < _size; i++)
			_allocator.destroy(_first + i);
		_size = start + need_to_copy;
		return last_is_end ? end() : iterator(_first + start);
	}

	///SWAP

	void swap(vector& x) {
		if (x == *this)
			return;
		std::swap(_first, x._first);
		std::swap(_size, x._size);
		std::swap(_capacity, x._capacity);
		std::swap(_allocator, x._allocator);
	}

	void clear() {
		for (size_type i = 0; i < _size; i++)
			_allocator.destroy(_first + i);
		_size = 0;
	}

	allocator_type get_allocator() const {
		return(_allocator);
	}

};

template <class T, class Alloc>
bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

} // namespace ft

/// @brief STL namespace
namespace std
{

template< class T, class Alloc >
void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
{
	lhs.swap(rhs);
}

} // namespace std

#endif

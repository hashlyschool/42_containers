/*!
 * @file RandomAccessIterator.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief реализация RandomAccessIterator
 * @version 1.0
 * @date 2022-10-13
 * @copyright Flex copyright (c) 2022
 */

#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
# define FT_RANDOM_ACCESS_ITERATOR_HPP

#include "./IteratorUtils.hpp"

namespace ft
{

template <typename T>
class RandomAccessIterator : ft::Iterator<ft::random_access_iterator_tag, T>
{
	public:
		typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;

		typedef ft::Iterator<ft::random_access_iterator_tag, T>::value_type	value_type;

		typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;

		typedef T*	pointer;
		typedef T&	reference;

		RandomAccessIterator(void) : _elem(u_nullptr) {}

		RandomAccessIterator(pointer elem)
		:
			_elem(elem)
		{}

		RandomAccessIterator(const RandomAccessIterator& op) : _elem(op._elem) {}

		RandomAccessIterator &operator=(const RandomAccessIterator& op) {
			if (this == &op)
				return (*this);
			this->_elem = op._elem;
			return (*this);
		}

		virtual ~RandomAccessIterator() {}

		pointer base() const { return (this->_elem); }

		reference operator*(void) const { return (*_elem); }

		pointer operator->(void) { return &(this->operator*()); }

		RandomAccessIterator& operator++(void) {
			_elem++;
			return (*this);
		}

		RandomAccessIterator operator++(int)
		{
			RandomAccessIterator rtn(*this);
			operator++();
			return (rtn);
		}

		RandomAccessIterator& operator--(void)
		{
			_elem--;
			return (*this);
		}

		RandomAccessIterator operator--(int)
		{
			RandomAccessIterator rtn(*this);
			operator--();
			return (rtn);
		}

		RandomAccessIterator operator+(difference_type n) const { return (_elem + n); }

		RandomAccessIterator operator-(difference_type n) const { return (_elem - n); }

		RandomAccessIterator& operator+=(difference_type n)
		{
			_elem += n;
			return (*this);
		}

		RandomAccessIterator& operator-=(difference_type n)
		{
			_elem -= n;
			return (*this);
		}

		reference operator[](difference_type n) {
			return (*(operator+(n)));
		}

		operator RandomAccessIterator<const T> () const {
			return (RandomAccessIterator<const T>(this->_elem));
		}

		private:
			pointer _elem;
};

template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator==(const ft::RandomAccessIterator<T> lhs,
			const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() == rhs.base());
}

template<typename T_L, typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator==(const ft::RandomAccessIterator<T_L> lhs,
			const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator!=(const ft::RandomAccessIterator<T> lhs,
			const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() != rhs.base());
}

template<typename T_L, typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator!=(const ft::RandomAccessIterator<T_L> lhs,
			const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator<(const ft::RandomAccessIterator<T> lhs,
			const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() < rhs.base());
}

template<typename T_L, typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator<(const ft::RandomAccessIterator<T_L> lhs,
			const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator>(const ft::RandomAccessIterator<T> lhs,
			const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() > rhs.base());
}

template<typename T_L,
			typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator>(const ft::RandomAccessIterator<T_L> lhs,
			const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator<=(const ft::RandomAccessIterator<T> lhs,
			const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() <= rhs.base());
}

template<typename T_L, typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator<=(const ft::RandomAccessIterator<T_L> lhs,
			const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() <= rhs.base());
}


template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator>=(const ft::RandomAccessIterator<T> lhs,
			const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() >= rhs.base());
}

template<typename T_L,
			typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator>=(const ft::RandomAccessIterator<T_L> lhs,
			const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() >= rhs.base());
}

template<typename T>
ft::RandomAccessIterator<T> operator+(
typename ft::RandomAccessIterator<T>::difference_type n,
typename ft::RandomAccessIterator<T>& rai)
{
	return (rai.base() + n);
}

template <typename T>
typename ft::RandomAccessIterator<T>::difference_type
operator-(const ft::RandomAccessIterator<T> lhs, const ft::RandomAccessIterator<T> rhs)
{
	return (lhs.base() - rhs.base());
}

template<typename T_L, typename T_R>
typename ft::RandomAccessIterator<T_L>::difference_type
operator-(const ft::RandomAccessIterator<T_L> lhs, const ft::RandomAccessIterator<T_R> rhs)
{
	return (lhs.base() - rhs.base());
}

} // namespace ft

#endif

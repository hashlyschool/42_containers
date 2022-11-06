/*!
 * @file ReverseIterator.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief реализация reverse_iterator
 * @version 1.0
 * @date 2022-10-13
 * @copyright Flex copyright (c) 2022
 */

#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

#include "./IteratorUtils.hpp"

namespace ft
{

template <class Iterator>
class ReverseIterator
{
	public:

		typedef Iterator	iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type      value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer     pointer;
		typedef typename ft::iterator_traits<Iterator>::reference   reference;

		ReverseIterator() : _elem() {}

		explicit ReverseIterator (iterator_type it) : _elem(it) {}

		template <class Iter>
		ReverseIterator (const ReverseIterator<Iter>& rev_it) :_elem(rev_it.base()) {}

		virtual ~ReverseIterator() {}

		iterator_type base() const { return (_elem); }

		reference operator*() const
		{
			iterator_type tmp = _elem;
			return (*(--tmp));
		}

		ReverseIterator operator+ (difference_type n) const { return (ReverseIterator(_elem - n)); }

		ReverseIterator& operator++()
		{
			--_elem;
			return (*this);
		}

		ReverseIterator operator++(int)
		{
			ReverseIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		ReverseIterator& operator+= (difference_type n)
		{
			_elem -= n;
			return (*this);
		}

		ReverseIterator operator- (difference_type n) const { return (ReverseIterator(_elem + n)); }

		ReverseIterator& operator--()
		{
			++_elem;
			return (*this);
		}

		ReverseIterator operator--(int)
		{
			ReverseIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		ReverseIterator& operator-= (difference_type n)
		{
			_elem += n;
			return (*this);
		}

		pointer operator->() const { return &(operator*()); }
		reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

	private:
		iterator_type	_elem;
};

template <class Iterator>
bool operator== (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
		return (lhs.base() == rhs.base());
}

template <class Iterator_L, class Iterator_R>
bool operator== (const ReverseIterator<Iterator_L>& lhs,const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

/* For reverser_iterator != const_reverse_iterator */
template <class Iterator_L, class Iterator_R>
bool operator!= (const ReverseIterator<Iterator_L>& lhs, const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<  (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator_L, class Iterator_R>
bool operator< (const ReverseIterator<Iterator_L>& lhs, const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator_L, class Iterator_R>
bool operator<= (const ReverseIterator<Iterator_L>& lhs, const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
bool operator> (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator_L, class Iterator_R>
bool operator> (const ReverseIterator<Iterator_L>& lhs, const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator>= (const ReverseIterator<Iterator>& lhs, const ReverseIterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator_L, class Iterator_R>
bool operator>= (const ReverseIterator<Iterator_L>& lhs, const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
ReverseIterator<Iterator> operator+ (
	typename ReverseIterator<Iterator>::difference_type n,
	const ReverseIterator<Iterator>& rev_it)
{
	return (rev_it + n);
}

template <class Iterator>
typename ReverseIterator<Iterator>::difference_type operator- (
		const ReverseIterator<Iterator>& lhs,
		const ReverseIterator<Iterator>& rhs)
{
	return (lhs.base() - rhs.base());
}

template <class Iterator_L, class Iterator_R>
bool operator- (const ReverseIterator<Iterator_L>& lhs, const ReverseIterator<Iterator_R>& rhs)
{
	return (lhs.base() - rhs.base());
}

} // namespace ft

#endif

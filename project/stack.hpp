/*!
 * @file Stack.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief custom std::stack
 * @version 1.0
 * @date 2022-10-01
 *
 * @copyright Flex copyright (c) 2022
 *
 */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "./vector.hpp"

/// @brief custom namespace for school project's
namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef T									value_type;
		typedef Container							container_type;
		typedef typename Container::size_type		size_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;

	protected:
		container_type	_container;
	public:

		explicit stack(const container_type &c = container_type())
		:
			_container(c)
		{}

		stack(const stack &other)
		:
			_container(other._container)
		{}

		virtual ~stack()
		{}

		bool	empty() const
		{
			return (this->_container.empty());
		}

		size_type	size() const
		{
			return (this->_container.size());
		}

		value_type&	top()
		{
			return (this->_container.back());
		}

		const value_type&	top() const
		{
			return (this->_container.back());
		}

		void	push(const value_type& val)
		{
			this->_container.push_back(val);
		}

		void	pop()
		{
			this->_container.pop_back();
		}

		// /// @brief maybe delete???
		// stack& operator=(const stack& other)
		// {
		// 	this->_container = other._container;
		// 	return (*this);
		// }

		template <class A, class Cont>
		friend bool operator== (const ft::stack<A,Cont>& lhs, const ft::stack<A,Cont>& rhs);

		template <class A, class Cont>
		friend bool operator!= (const ft::stack<A,Cont>& lhs, const ft::stack<A,Cont>& rhs);

		template <class A, class Cont>
		friend bool operator<  (const ft::stack<A,Cont>& lhs, const ft::stack<A,Cont>& rhs);

		template <class A, class Cont>
		friend bool operator<= (const ft::stack<A,Cont>& lhs, const ft::stack<A,Cont>& rhs);

		template <class A, class Cont>
		friend bool operator>  (const ft::stack<A,Cont>& lhs, const ft::stack<A,Cont>& rhs);

		template <class A, class Cont>
		friend bool operator>= (const ft::stack<A,Cont>& lhs, const ft::stack<A,Cont>& rhs);

};

template <class T, class Container>
bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return (lhs._container == rhs._container); }

template <class T, class Container>
bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return (lhs._container != rhs._container); }

template <class T, class Container>
bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return (lhs._container < rhs._container); }

template <class T, class Container>
bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return (lhs._container <= rhs._container); }

template <class T, class Container>
bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return (lhs._container > rhs._container); }

template <class T, class Container>
bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
{ return (lhs._container >= rhs._container); }

} // namespace ft

#endif

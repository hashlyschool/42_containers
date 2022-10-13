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

# include "./Vector.hpp"

/// @brief custom namespace for school project's
namespace ft
{

	/// @brief custom implementation std::stack
	/// @tparam T тип данных для создания контейнера
	/// @tparam Container основной контейнер
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef typename Container::size_type size_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;

		protected:
			/// @brief base containers
			container_type	_container;
		public:

			/// @brief Construct a new stack object
			/// @param c основной контейнер
			explicit stack(const container_type &c = container_type()) : _container(c) {};

			/// @brief Copy constructor
			/// @param other
			stack(const stack &other): _container(other._container) {}

			/// @brief operator =
			/// @param other
			/// @return stack&
			stack& operator=(const stack& other)
			{
				_container = other._container;
				return (*this);
			}

			/// @brief check empty container
			/// @return true - empty
			/// @return false - no empty
			bool	empty() const
			{
				return (_container.empty());
			}

			/// @brief return size container
			/// @return Container::size_type
			size_type	size() const
			{
				return (_container.size());
			}

			/// @brief return link to top element
			/// @return T&
			value_type&	top()
			{
				return (_container.back());
			}

			/// @brief return const link to top element
			/// @return const T&
			const value_type&	top() const
			{
				return (_container.back());
			}

			/// @brief function for insert value in back stack
			/// @param val value to insert
			void	push(const value_type& val)
			{
				_container.push_back(val);
			}

			/// @brief function for delete element in back stack
			void	pop()
			{
				_container.pop_back();
			}

			template <class A, class Cont>
			friend bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
			{
				return(lhs._container == rhs._container);
			}

			template <class A, class Cont>
			friend bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
			{
				return(lhs._container != rhs._container);
			}

			template <class A, class Cont>
			friend bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
			{
				return(lhs._container < rhs._container);
			}

			template <class A, class Cont>
			friend bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
			{
				return(lhs._container <= rhs._container);
			}

			template <class A, class Cont>
			friend bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
			{
				return(lhs._container > rhs._container);
			}

			template <class A, class Cont>
			friend bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs)
			{
				return(lhs._container >= rhs._container);
			}

	};

} // namespace ft

#endif

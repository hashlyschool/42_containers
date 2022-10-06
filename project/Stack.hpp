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

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

/// @brief custom namespace for school project's
namespace ft
{

	/// @brief custom implementation std::stack
	/// @tparam T
	/// @tparam Container
	template <class T, class Container = std::deque<T> >
	class stack
	{
		protected:
			/// @brief base containers
			Container	_container;
		public:

			/// @brief Construct a new stack object
			/// @param c
			explicit stack(const Container &c = Container()) : _container(c) {};

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
			typename Container::size_type	size() const
			{
				return (_container.size());
			}

			/// @brief return link to top element
			/// @return T&
			T&	top()
			{
				return (_container.back());
			}

			/// @brief return const link to top element
			/// @return const T&
			const T&	top() const
			{
				return (_container.back());
			}

			/// @brief function for insert value in back stack
			/// @param val value to insert
			void	push(const T& val)
			{
				_container.push_back(val);
			}

			/// @brief function for delete element in back stack
			void	pop()
			{
				_container.pop_back();
			}

		template <class A, class Cont>
		  friend bool operator== (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container == rhs._container);
			 }
	template <class A, class Cont>
		  friend bool operator!= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container != rhs._container);
			 }
	template <class A, class Cont>
		  friend bool operator<  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container < rhs._container);
			 }
	template <class A, class Cont>
		  friend bool operator<= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container <= rhs._container);
		  }
	template <class A, class Cont>
		  friend bool operator>  (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container > rhs._container);
		  }
	template <class A, class Cont>
		  friend bool operator>= (const stack<A,Cont>& lhs, const stack<A,Cont>& rhs){
				return(lhs._container >= rhs._container);
			}
	};

} // namespace ft

#endif

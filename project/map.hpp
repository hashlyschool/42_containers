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
#include "./iterators/ReverseIterator.hpp"
#include "./utils/utils_include.hpp"

namespace ft
{

template<
class Key,
class T,
class Compare = ft::less<Key>,
class Alloc = std::allocator<ft::pair<const Key, T>>
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

	typedef ft::mapIte<value_type, node_type>			iterator;
	typedef ft::mapIte<const value_type, node_type>		const_iterator;
	typedef typename ft::ReverseIterator<iterator>		reverse_iterator;
	typedef typename ft::ReverseIterator<const_iterator>	const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t										size_type;

	class value_compare : ft::binary_function<value_type, value_type, bool>
	{
		/*friend*/ class map<key_type, mapped_type, key_compare, Alloc>;

		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}

		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return (comp(x.first, y.first));
			}
	};

};

}

#endif //ft_map_hpp

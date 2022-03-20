/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:12:23 by abambi            #+#    #+#             */
/*   Updated: 2022/02/09 23:46:42 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include <cstddef>

namespace ft
{

/*
** iterator traits for iterator types
*/

	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

/*
** iterator traits for non-iterator types
*/

	template <class T>
	struct iterator_traits<T *>
	{
		typedef		std::random_access_iterator_tag	iterator_category;
		typedef			ptrdiff_t					difference_type;
		typedef			T							value_type;
		typedef			T *							pointer;
		typedef			T &							reference;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef		std::random_access_iterator_tag	iterator_category;
		typedef			ptrdiff_t					difference_type;
		typedef			T							value_type;
		typedef			const T *					pointer;
		typedef			const T &					reference;
	};

/*
** iterator getPtr class
*/

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	class iterator
	{
		public:
			typedef		Category						iterator_category;
			typedef		Distance						difference_type;
			typedef		T								value_type;
			typedef		Pointer							pointer;
			typedef		Reference						reference;
	};

/*
** Vector Iterator
*/

	template <class Iterator>
	class vector_iterator : 
	public iterator<std::random_access_iterator_tag, typename iterator_traits<Iterator>::value_type>
	{
	public:
		typedef Iterator											iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::pointer			pointer;
		typedef typename iterator_traits<Iterator>::reference		reference;
	private:
		iterator_type												i_ptr;
	public:
		vector_iterator(void) {};
		vector_iterator(const vector_iterator &src) { *this = src; };
		vector_iterator(pointer src_ptr) { i_ptr = src_ptr; } 
		vector_iterator &operator=(const vector_iterator &src) { i_ptr = src.i_ptr; return (*this); };
		~vector_iterator() {};

		iterator_type getPtr() const { return (this->i_ptr); }

		size_t asIndex(iterator_type it) const
		{
			ptrdiff_t diff = this->i_ptr - it;
			if (diff < 0L)
				throw std::invalid_argument("invalid iterator for the vector");
			return (diff);
		}

/*
** increment/decrement
*/
		vector_iterator &operator++()
		{
			++this->i_ptr;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator temp = *this;
			++this->i_ptr;
			return (temp);
		}

		vector_iterator &operator--()
		{
			--this->i_ptr;
			return (*this);
		}

		vector_iterator operator--(int)
		{
			vector_iterator temp = *this;
			--this->i_ptr;
			return (temp);
		}

/*
** other math
*/

		vector_iterator &operator+=(difference_type n)
		{
			this->i_ptr += n;
			return (*this);
		}

		vector_iterator &operator-=(difference_type n)
		{
			this->i_ptr -= n;
			return (*this);
		}

		vector_iterator operator+(difference_type n) const
		{
			return (vector_iterator(i_ptr + n));
		}

		vector_iterator operator-(difference_type n) const
		{
			return (vector_iterator(i_ptr - n));
		}

/*
** dereference
*/

		reference operator*() const
		{
			return (*this->i_ptr);
		}

		pointer operator->() const
		{
			return (this->i_ptr);
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

/*
** compare operations
*/

	template <class Iterator>
	bool operator==(const vector_iterator<Iterator> &left,
					const vector_iterator<Iterator> &right)
	{
		return (left.getPtr() == right.getPtr());
	}

	template <class Iterator>
	bool operator!=(const vector_iterator<Iterator> &left,
					const vector_iterator<Iterator> &right)
	{
		return (left.getPtr() != right.getPtr());
	}

	template <class Iterator>
	bool operator<(const vector_iterator<Iterator> &left,
				   const vector_iterator<Iterator> &right)
	{
		return (left.getPtr() < right.getPtr());
	}

	template <class Iterator>
	bool operator<=(const vector_iterator<Iterator> &left,
					const vector_iterator<Iterator> &right)
	{
		return (left.getPtr() <= right.getPtr());
	}

	template <class Iterator>
	bool operator>(const vector_iterator<Iterator> &left,
				   const vector_iterator<Iterator> &right)
	{
		return (left.getPtr() > right.getPtr());
	}
	
	template <class Iterator>
	bool operator>=(const vector_iterator<Iterator> &left,
					const vector_iterator<Iterator> &right)
	{
		return (left.getPtr() >= right.getPtr());
	}

/*
** Reverse Iterator
*/

	template <class Iterator>
	class reverse_iterator
	{	
	public:
		typedef Iterator											iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::pointer			pointer;
		typedef typename iterator_traits<Iterator>::reference		reference;
	private:
		iterator_type												i_ptr;
	public:
		reverse_iterator() {i_ptr = NULL;}
		~reverse_iterator() {};
		reverse_iterator (reverse_iterator const &src) { *this = src; }
		reverse_iterator(pointer src_ptr) { this->i_ptr = src_ptr; }
		reverse_iterator &operator=(reverse_iterator const &src)
		{
			i_ptr = src.i_ptr;
			return (*this);
		}
		iterator_type getPtr() const { return (this->i_ptr); }

/*
** increment/decrement
*/

		reverse_iterator &operator++()
		{
			--this->i_ptr;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			--this->i_ptr;
			return (temp);
		}

		reverse_iterator &operator--()
		{
			++this->i_ptr;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			++this->i_ptr;
			return (temp);
		}

/*
** other math
*/

		reverse_iterator &operator+=(difference_type n)
		{
			this->i_ptr -= n;
			return (*this);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->i_ptr += n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(this->getPtr() + n)); //
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->getPtr() - n)); //
		}

/*
** dereference iterator
*/
		reference operator*() const
		{
			iterator_type temp = this->getPtr();
			return *--temp; //
		}
	
		pointer operator->() const
		{
			iterator_type temp = this->getPtr();
			return &*--temp; //
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

/*
** compare operations
*/

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &left,
					const reverse_iterator<Iterator> &right)
	{
		return (left.getPtr() == right.getPtr());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &left,
					const reverse_iterator<Iterator> &right)
	{
		return (left.getPtr() != right.getPtr());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &left,
				   const reverse_iterator<Iterator> &right)
	{
		return (left.getPtr() > right.getPtr());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &left,
					const reverse_iterator<Iterator> &right)
	{
		return (left.getPtr() >= right.getPtr());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &left,
				   const reverse_iterator<Iterator> &right)
	{
		return (left.getPtr() < right.getPtr());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &left,
					const reverse_iterator<Iterator> &right)
	{
		return (left.getPtr() <= right.getPtr());
	}

/*
** lexicographical compare
*/

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

/*
** equal
*/

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

/*
** enable_if
*/

	template <bool B, class T = void>
	struct enable_if
	{

	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

/*
** is_integral
*/

	template <class T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long>
	{
		static const bool value = true;
	};

/*
** is_pointer
*/

	template <typename T>
	struct is_pointer
	{
		static const bool value = false;
	};

	template <typename T>
	struct is_pointer<T *>
	{
		static const bool value = true;
	};

/*
** is_void
*/

	template <typename T>
	struct is_void
	{
		static const bool value = false;
	};

	template <>
	struct is_void<void>
	{
		static const bool value = true;
	};
}

#endif

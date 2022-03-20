/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:12:23 by abambi            #+#    #+#             */
/*   Updated: 2022/02/10 13:57:22 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
#define FT_MAP_H

#include <iostream>
#include <cstddef>
#include <limits>

#include "pair.hpp"

// #include <functional>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key 										key_type;
			typedef T 											mapped_type;
			typedef ft::pair<const key_type, mapped_type> 		value_type;
			typedef Compare 									key_compare;
			typedef Alloc 										allocator_type;
			typedef value_type &								reference;
			typedef const value_type &							const_reference;
			typedef value_type *								pointer;
			typedef const value_type *							const_pointer;
			typedef size_t 										size_type;
			typedef ptrdiff_t 									difference_type;
			class	iterator;
			class	const_iterator;
			class	reverse_iterator;
			class	const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				public:
					key_compare cmp;
					explicit value_compare(key_compare c) : cmp(c) {};
					bool operator()(const value_type &x, const value_type &y) const { return cmp(x.first, y.first); };
			};

		private:
			typedef struct 	Node
			{
				Node *		left;
				Node *		right;
				Node *		parent;
				pointer 	data;
				bool 		color;
			} 				TreeNode;

			enum Side
			{
				right = 0,
				left
			};

			typedef typename allocator_type::template rebind<TreeNode>::other ptr_alloc;

			TreeNode *					_root;
			TreeNode *					_endNode;
			TreeNode *					_beginNode;
			size_type					_size;
			key_compare					_cmp;
			ptr_alloc					_ptr_alloc;
			allocator_type				_alloc;
			const static bool _black	= false;
			const static bool _red		= true;

// Handle the tree

			void _allocEmptyMap()
			{
				_beginNode = _ptr_alloc.allocate(1);
				_beginNode->left = NULL;
				_beginNode->right = NULL;
				_beginNode->color = _black;
				_beginNode->data = NULL;

				_endNode = _ptr_alloc.allocate(1);
				_endNode->left = NULL;
				_endNode->right = NULL;
				_endNode->color = _black;
				_endNode->data = NULL;
			}

// Make a new Node

			TreeNode * _newNode(Node *parent, const_reference value, bool color)
			{
				Node *newNode = _ptr_alloc.allocate(1);
				newNode->parent = parent;
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->data = _alloc.allocate(1);
				_alloc.construct(newNode->data, value);
				newNode->color = color;
				++_size;
				return (newNode);
			}

// Destroy the Node

			void _destroyNode(TreeNode *node)
			{
				_alloc.destroy(node->data);
				_alloc.deallocate(node->data, 1);
				_ptr_alloc.deallocate(node, 1);
				--_size;
			}

// Rotate Nodes

			void _lowNode(TreeNode *newRoot, TreeNode *oldRoot)
			{
				if (oldRoot->parent != NULL)
				{
					if (_isLeftNode(oldRoot))
						oldRoot->parent->left = newRoot;
					else
						oldRoot->parent->right = newRoot;
				}
				newRoot->parent = oldRoot->parent;
				oldRoot->parent = newRoot;
			}

			void _rotateLeft(TreeNode *oldRoot)
			{
				TreeNode *newRoot = oldRoot->right;
				if (oldRoot == _root)
					_root = newRoot;
				_lowNode(newRoot, oldRoot);
				oldRoot->right = newRoot->left;
				if (newRoot->left != NULL)
					newRoot->left->parent = oldRoot;
				newRoot->left = oldRoot;
			}

			void _rotateRight(TreeNode *oldRoot)
			{
				TreeNode *newRoot = oldRoot->left;
				if (oldRoot == _root)
					_root = newRoot;
				_lowNode(newRoot, oldRoot);
				oldRoot->left = newRoot->right;
				if (newRoot->right != NULL)
					newRoot->right->parent = oldRoot;
				newRoot->right = oldRoot;
			}

// check Node

			bool _isLeftNode(TreeNode *node)
			{
				return (node == node->parent->left);
			}

			bool _hasRedChild(TreeNode *node)
			{
				return (node->left != NULL && node->left->color == _red) || \
					  (node->right != NULL && node->right->color == _red);
			}

// get Uncle

			TreeNode *_getUncleOfNode(TreeNode *node)
			{
				if (node->parent == NULL or node->parent->parent == NULL)
					return (NULL);
				if (_isLeftNode(node->parent))
					return (node->parent->parent->right);
				else
					return (node->parent->parent->left);
			}

// get Brother

			TreeNode *_getBrother(TreeNode *node)
			{
				if (node->parent == NULL)
					return (NULL);
				if (_isLeftNode(node))
					return (node->parent->right);
				else
					return (node->parent->left);
			}

// swap

			void _colorSwap(TreeNode *node1, TreeNode *node2)
			{
				bool temp = node1->color;
				node1->color = node2->color;
				node2->color = temp;
			}

			TreeNode* _valueSwap(TreeNode *replNode, TreeNode *toDel)
			{
				bool					left_or_right;
				TreeNode *repl_left		= replNode->left;
				TreeNode *repl_right	= replNode->right;

				if (replNode->parent != toDel)
				{
					TreeNode *repl_parent = replNode->parent;
					left_or_right = _isLeftNode(replNode);

					link(replNode, toDel->right, right);
					link(replNode, toDel->left, left);
					if ((_isLeftNode(toDel)))
						link(toDel->parent, replNode, left);
					else
						link(toDel->parent, replNode, right);
					if ((left_or_right))
						link(repl_parent, toDel, left);
					else
						link(repl_parent, toDel, right);
					link(toDel, repl_left, left);
					link(toDel, repl_right, right);
				}
				else
				{
					left_or_right = _isLeftNode(replNode);
					if (!left_or_right)
						link(replNode, toDel->left, left);
					else
						link(replNode, toDel->right, right);
					if (toDel->parent)
					{
						if (_isLeftNode(toDel))
							link(toDel->parent, replNode, left);
						else
							link(toDel->parent, replNode, right);
					}
					else
						replNode->parent = NULL;
					if (!left_or_right)
						link(replNode, toDel, right);
					else
						link(replNode, toDel, left);
					link(toDel, repl_right, right);
					link(toDel, repl_left, left);
				}
				if (toDel == _root)
					_root = replNode;
				return (toDel);
			}

// Balancing: left and right

			void _leftSideBalance(TreeNode *node, TreeNode *parentNode, TreeNode *grandparent)
			{
				if (_isLeftNode(node))
					_colorSwap(parentNode, grandparent);
				else
				{
					_rotateLeft(parentNode);
					_colorSwap(node, grandparent);
				}
				_rotateRight(grandparent);
			}

			void _rightSideBalance(TreeNode *node, TreeNode *parentNode, TreeNode *grandparent)
			{
				if (_isLeftNode(node))
				{
					_rotateRight(parentNode);
					_colorSwap(node, grandparent);
				}
				else
					_colorSwap(parentNode, grandparent);
				_rotateLeft(grandparent);
			}

			void _doubleBlackWithRedChild(TreeNode *brotherNode, TreeNode *parent)
			{
				if (brotherNode->left && brotherNode->left->color == _red)
				{
					if (_isLeftNode(brotherNode))
					{
						brotherNode->left->color = brotherNode->color;
						brotherNode->color = parent->color;
						_rotateRight(parent);
					}
					else
					{
						brotherNode->left->color = parent->color;
						_rotateRight(brotherNode);
						_rotateLeft(parent);
					}
				}
				else
				{
					if (_isLeftNode(brotherNode))
					{
						brotherNode->right->color = parent->color;
						_rotateLeft(brotherNode);
						_rotateRight(parent);
					}
					else
					{
						brotherNode->right->color = brotherNode->color;
						brotherNode->color = parent->color;
						_rotateLeft(parent);
					}
				}
				parent->color = _black;
			}

// Handlers: red and black

			void _redRedNodesHandler(TreeNode *node)
			{
				if (node == _root)
				{
					node->color = _black;
					return ;
				}
				TreeNode *parentNode = node->parent;
				TreeNode *grandparent = parentNode->parent;
				TreeNode *uncleOfNode = _getUncleOfNode(node);

				if (parentNode->color != _black)
				{
					if (uncleOfNode && uncleOfNode->color == _red)
					{
						parentNode->color = _black;
						uncleOfNode->color = _black;
						grandparent->color = _red;
						_redRedNodesHandler(grandparent);
					}
					else
					{
						if (_isLeftNode(parentNode))
							_leftSideBalance(node, parentNode, grandparent);
						else
							_rightSideBalance(node, parentNode, grandparent);
					}
				}
			}

			void _blackBlackNodesHandler(TreeNode *x)
			{
				if (x == _root)
					return ;
				TreeNode *brotherNode	= _getBrother(x);
				TreeNode *parent		= x->parent;
				if (!brotherNode)
					_blackBlackNodesHandler(parent);
				else
				{
					if (brotherNode->color == _red)
					{
						parent->color = _red;
						brotherNode->color = _black;
						if (_isLeftNode(brotherNode))
							_rotateRight(parent);
						else
							_rotateLeft(parent);
						_blackBlackNodesHandler(x);
					}
					else
					{
						if (_hasRedChild(brotherNode))
							_doubleBlackWithRedChild(brotherNode, parent);
						else
						{
							brotherNode->color = _red;
							if (parent->color == _black)
								_blackBlackNodesHandler(parent);
							else
								parent->color = _black;
						}
					}
				}
			}

// others

			TreeNode *getReplacingForNode(TreeNode *node)
			{
				if (node->left && node->right)
				{
					TreeNode *temp = node->right;

					while (temp->left != NULL)
						temp = temp->left;
					return (temp);
				}
				if (!node->left && !node->right)
					return (NULL);
				if (node->left)
					return (node->left);
				else
					return (node->right);
			}

// search

			TreeNode *_searchInTreeByKey(key_type key)
			{
				TreeNode *temp = _root;

				while (temp != NULL)
				{
					if (key < temp->data->first)
					{
						if (temp->left == NULL)
							break ;
						else
							temp = temp->left;
					}
					else if (key == temp->data->first)
					{
						break ;
					}
					else
					{
						if (!temp->right)
							break ;
						else
							temp = temp->right;
					}
				}
				return (temp);
			}

// link

			void link(TreeNode *parent, TreeNode *node, Side side)
			{
				if (parent == NULL)
					return ;
				if (side == right)
					parent->right = node;
				else
					parent->left = node;
				if (node != NULL)
					node->parent = parent;
			}

// insert

			bool _insert(value_type key)
			{
				TreeNode *newNode = _newNode(NULL, key, _red);

				if (_root == NULL)
				{
					newNode->color = _black;
					_root = newNode;
				}
				else
				{
					TreeNode *temp = _searchInTreeByKey(key.first);
					if (temp->data->first == key.first)
					{
						_destroyNode(newNode);
						return (false);
					}
					newNode->parent = temp;
					if (key < (*temp->data))
						temp->left = newNode;
					else
						temp->right = newNode;
					_redRedNodesHandler(newNode);
				}
				return (true);
			}

// erase

			void _erase(TreeNode *toDelete)
			{
				TreeNode *replacingForNode = getReplacingForNode(toDelete);
				bool isBothNodesBlack = \
					((replacingForNode == NULL || replacingForNode->color == _black) \
					&& (toDelete->color == _black));
				TreeNode *parent = toDelete->parent;
				if (!replacingForNode)
				{
					if (toDelete == _root)
						_root = NULL;
					else
					{
						if (isBothNodesBlack)
							_blackBlackNodesHandler(toDelete);
						else
						{
							_getBrother(toDelete) ? _getBrother(toDelete)->color = _red : 0;
						}
						if (_isLeftNode(toDelete))
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					_destroyNode(toDelete);
					return ;
				}
				if (!toDelete->left || !toDelete->right)
				{
					if (toDelete == _root)
					{
						_alloc.destroy(toDelete->data);
						_alloc.construct(toDelete->data, *(replacingForNode->data));
						toDelete->left = NULL;
						toDelete->right = NULL;
						_destroyNode(replacingForNode);
					}
					else
					{
						if (_isLeftNode(toDelete))
							parent->left = replacingForNode;
						else
							parent->right = replacingForNode;
						_destroyNode(toDelete);
						replacingForNode->parent = parent;
						if (isBothNodesBlack)
							_blackBlackNodesHandler(replacingForNode);
						else
							replacingForNode->color = _black;
					}
					return ;
				}
				replacingForNode = _valueSwap(replacingForNode, toDelete);
				_erase(replacingForNode);
			}

			bool _eraseByKey(key_type key)
			{
				if (_root == NULL)
					return (false);
				TreeNode *node = _searchInTreeByKey(key);

				if (node->data->first != key)
					return (false);
				_erase(node);
				return (true);
			}

// min

			TreeNode *getMinNode(TreeNode *node)
			{
				if (node && node->left)
					return (getMinNode(node->left));
				else
					return (node);
			}

// max

			TreeNode *getMaxNode(TreeNode *node)
			{
				if (node && node->right)
					return (getMaxNode(node->right));
				else
					return (node);
			}

		public:

// begin canonical

			explicit map(const key_compare &comp = key_compare(), \
					const allocator_type &alloc = allocator_type()) :
					_root(NULL), _size(0), _cmp(comp), _alloc(alloc)
			{
				_allocEmptyMap();
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, \
				const key_compare &comp = key_compare(), \
				const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _cmp(comp), _root(NULL), _size(0)
			{
				_allocEmptyMap();
				insert(first, last);
			}

			map(const map &x) :
				_alloc(x._alloc), _cmp(x._cmp), _root(NULL), _size(0)
			{
				_allocEmptyMap();
				*this = x;
			}

			~map()
			{
				clear();
				_ptr_alloc.deallocate(_endNode, 1);
				_ptr_alloc.deallocate(_beginNode, 1);
			}

			map &operator=(const map &x)
			{
				if (this != &x)
				{
					const_iterator iter = x.begin();
					clear();
					while (iter != x.end())
						insert(*(iter)++);
				}
				return (*this);
			}

// end canonical

			void					clear()
			{
				while (_size)
					erase(begin());
			}

// get position

			iterator				begin()
			{
				TreeNode	*node;

				if (_size)
					node = _beginNode->parent;
				else
					node = _endNode;
				return (iterator(node));
			}

			const_iterator			begin() const
			{
				TreeNode	*node;

				if (_size)
					node = _beginNode->parent;
				else
					node = _endNode;
				return (const_iterator(node));
			}

			reverse_iterator 		rbegin()
			{
				TreeNode	*node;

				if (_size)
					node = _endNode->parent;
				else
					node = _beginNode;
				return (reverse_iterator(node));
			};

			const_reverse_iterator	rbegin() const
			{
				TreeNode	*node;

				if (_size)
					node = _endNode->parent;
				else
					node = _beginNode;
				return (const_reverse_iterator(node));
			}

			iterator 				end()			{ return (iterator(_endNode)); };
			const_iterator 			end() const		{ return (const_iterator(_endNode)); };
			reverse_iterator 		rend()			{ return (reverse_iterator(_beginNode)); };
			const_reverse_iterator	rend() const	{ return (const_reverse_iterator(_beginNode)); };

// check status

			bool 					empty() const	{ return (!_size); };
			size_type 				size() const	{ return (_size); };
			// size_type 				max_size() const
			// {
			// 	return (std::numeric_limits<size_type>::max() / sizeof(_root) / 10);
			// }

			size_type max_size (void) const
			{
				// return (allocator_type.max_size() * 2 / 10);
				return (_alloc.max_size()  * 2 / 10);
			}

			size_type				count(const key_type &k) const
			{
				const_iterator	i = find(k);

				return (i != end());
			}

// find

			iterator 				find(const key_type &k)
			{
				for (iterator i = begin(); i != end(); ++i)
					if (i.getNode()->data->first == k)
						return (i);
				return (end());
			}

			const_iterator			find(const key_type &k) const
			{
				for (const_iterator i = begin(); i != end(); ++i)
					if (i.getNode()->data->first == k)
						return (i);
				return (end());
			}

// get access

			mapped_type				&at(const key_type &k)
			{
				iterator		i = lower_bound(k);

				if (i == end() || key_comp()(k, (*i).first))
					throw std::out_of_range("Out of range");
				return ((*i).second);
			}	

			const mapped_type		&at(const key_type &k) const
			{
				const_iterator	i = lower_bound(k);

				if (i == end() || key_comp()(k, (*i).first))
					throw std::out_of_range("Out of range");
				return ((*i).second);
			}

			mapped_type				&operator[](const key_type &k)
			{
				iterator		i = lower_bound(k);

				if (i == end() || key_comp()(k, (*i).first))
					i = insert(i, value_type(k, mapped_type()));
				return ((*i).second);
				// return (*((this->insert(std::make_pair(k,mapped_type()))).first)).second;
			}

// insert

			ft::pair<iterator, bool> insert(const_reference value)
			{
				if (_size)
				{
					if (_beginNode->parent)
						_beginNode->parent->left = NULL;
					if (_endNode->parent)
						_endNode->parent->right = NULL;
				}
				bool		ret = _insert(value);
				TreeNode	*tmp = getMaxNode(_root);

				link(tmp, _endNode, right);
				tmp = getMinNode(_root);
				link(tmp, _beginNode, left);
				return (ft::make_pair(find(value.first), ret));
			};

			iterator				insert(iterator position, const value_type &value)
			{
				static_cast<void>(position);
				return (insert(value).first);
			};

// 3) fill range

			template <class InputIterator>
			void					insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}

// erase

			size_type				erase(const key_type &k)
			{
				if (_size)
				{
					if (_beginNode->parent)
						_beginNode->parent->left = NULL;
					if (_endNode->parent)
						_endNode->parent->right = NULL;
				}

				bool		ret = _eraseByKey(k);
				TreeNode	*tmp = getMaxNode(_root);

				link(tmp, _endNode, right);
				tmp = getMinNode(_root);
				link(tmp, _beginNode, left);
				return (ret);
			}

			void					erase(iterator position)
			{
				if (position != iterator(_endNode))
					erase(position->first);
			}

			void					erase(iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			};

			key_compare		key_comp() const	{ return _cmp; };
			value_compare	value_comp() const	{ return value_compare(_cmp); };

			iterator 		lower_bound(const key_type &k)
			{
				iterator	first = begin();
				iterator	last = end();

				while (first != last && _cmp(first->first, k))
					++first;
				return (first);
			};

			const_iterator	lower_bound(const key_type &k) const
			{
				iterator	first = begin();
				iterator	last = end();

				while (first != last && _cmp(first->first, k))
					++first;
				return (first);
			};

			iterator 		upper_bound(const key_type &k)
			{
				iterator	iter = lower_bound(k);

				if (iter != end() && !_cmp(iter->first, k) && !_cmp(k, iter->first))
					++iter;
				return (iter);
			};

			const_iterator	upper_bound(const key_type &k) const
			{
				const_iterator	iter = lower_bound(k);

				if (iter != end() && !_cmp(iter->first, k) && !_cmp(k, iter->first))
					++iter;
				return (iter);
			};

			ft::pair<const_iterator,const_iterator> equal_range(const key_type &k) const	{ return ft::make_pair(lower_bound(k), upper_bound(k)); }
			ft::pair<iterator,iterator>             equal_range(const key_type &k)			{ return ft::make_pair(lower_bound(k), upper_bound(k)); }

			void swap(map &x)
			{
				TreeNode *temp = _root;
				_root = x._root;
				x._root = temp;

				size_type size = _size;
				_size = x._size;
				x._size = size;

				temp = _endNode;
				_endNode = x._endNode;
				x._endNode = temp;

				temp = _beginNode;
				_beginNode = x._beginNode;
				x._beginNode = temp;
			}

// iterators

	class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type>
	{
	private:
			TreeNode* knot;

	public:
		iterator(TreeNode* node = NULL): knot(node) {};
		~iterator() {};
		iterator &operator=(const iterator &src)
		{
			this->knot = src.knot;
			return (*this);
		};
		iterator(const iterator &src) { *this = src; };

		iterator &operator++()
		{
			if (knot->right != NULL)
			{
				knot = getMinNode(knot->right);
				return (*this);
			}
			else if (knot->parent && knot->parent->left == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			else if (knot->parent->right == knot)
				knot = knot->parent;
			TreeNode *temp = knot;
			while (temp->parent->right == temp)
			{
				temp = temp->parent;
				if (temp == NULL)
				{
					knot = knot->right;
					return (*this);
				}
			}
			knot = temp->parent;
			return (*this);
		};

		iterator operator++(int)
		{
			iterator temp(knot);
			operator++();
			return (temp);
		};

		iterator &operator--()
		{
			if (knot->left != NULL)
			{
				knot = getMaxNode(knot->left);
				return (*this);
			}
			else if (knot->parent && knot->parent->right == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			TreeNode *temp = knot;
			while (temp->parent->left == temp)
			{
				temp = temp->parent;
				if (temp == NULL)
				{
					knot = knot->left;
					return (*this);
				}
			}
			knot = knot->parent;
			return (*this);
		};

		iterator operator--(int)
		{
			iterator temp(knot);
			operator--();
			return (temp);
		};

		TreeNode	*getNode() const								{ return knot; }
		bool		operator==(const iterator &src) const			{ return knot == src.knot; };
		bool		operator!=(const iterator &src) const			{ return knot != src.knot; };
		bool		operator==(const const_iterator &src) const		{ return knot == src.getNode(); };
		bool		operator!=(const const_iterator &src) const		{ return knot != src.getNode(); };
		reference	operator*() const								{ return *(knot->data); }
		pointer		operator->() const								{ return knot->data; }

	private:
		TreeNode *getMinNode(TreeNode *node)
		{
			if (node->left != NULL)
				return (getMinNode(node->left));
			else
				return (node);
		}

		TreeNode *getMaxNode(TreeNode *node)
		{
			if (node->right != NULL)
				return (getMaxNode(node->right));
			else
				return (node);
		}
	};

	class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type const>
	{
	private:
		TreeNode *knot;
	public:
		const_iterator(TreeNode* node = NULL) : knot(node) {};
		const_iterator(const const_iterator &src)	{ *this = src; };
		const_iterator(const iterator &src)			{ *this = src; };
		~const_iterator() {};

		const_iterator &operator=(const const_iterator &src)
		{
			knot = src.knot;
			return (*this);
		};

		const_iterator &operator=(const iterator &it)
		{
			knot = it.getNode();
			return (*this);
		};

		const_iterator &operator++()
		{
			if (knot->right != NULL)
			{
				knot = getMinNode(knot->right);
				return (*this);
			}
			else if (knot->parent && knot->parent->left == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			else if (knot->parent->right == knot)
				knot = knot->parent;
			TreeNode *temp = knot;
			while (temp->parent->right == temp)
			{
				temp = temp->parent;
				if (temp == NULL)
				{
					knot = knot->right;
					return (*this);
				}
			}
			knot = temp->parent;
			return (*this);
		};

		const_iterator operator++(int)
		{
			const_iterator temp(knot);
			operator++();
			return (temp);
		};

		const_iterator &operator--()
		{
			if (knot->left != NULL)
			{
				knot = getMaxNode(knot->left);
				return (*this);
			}
			else if (knot->parent && knot->parent->right == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			TreeNode *temp = knot;
			while (temp->parent->left == temp)
			{
				temp = temp->parent;
				if (temp == NULL)
				{
					knot = knot->left;
					return (*this);
				}
			}
			knot = knot->parent;
			return (*this);
		};

		const_iterator operator--(int)
		{
			const_iterator temp(knot);
			operator--();
			return (temp);
		};

		TreeNode		*getNode() const								{ return knot; }
		bool			operator==(const const_iterator &src) const		{ return knot == src.knot; };
		bool			operator!=(const const_iterator &src) const		{ return knot != src.knot; };
		bool			operator==(const iterator &src) const			{ return knot == src.getNode(); };
		bool			operator!=(const iterator &src) const			{ return knot != src.getNode(); };
		const_reference	operator*() const								{ return *(knot->data); };
		const_pointer	operator->() const								{ return knot->data; }

	private:
		TreeNode *getMinNode(TreeNode *node)
		{
			if (node->left != NULL)
				return (getMinNode(node->left));
			else
				return (node);
		}

		TreeNode *getMaxNode(TreeNode *node)
		{
			if (node->right != NULL)
				return (getMaxNode(node->right));
			else
				return (node);
		}
	};

	class reverse_iterator : public std::reverse_iterator<iterator>
	{
		private:
			TreeNode * knot;

		public:
			reverse_iterator(TreeNode * node = NULL): knot(node) {};
			~reverse_iterator() {};
			reverse_iterator(const reverse_iterator &src) { *this = src; };

			reverse_iterator &operator=(const reverse_iterator &src)
			{
				this->knot = src.knot;
				return (*this);
			};

		reverse_iterator &operator++()
		{
			if (knot->left != NULL)
			{
				knot = getMaxNode(knot->left);
				return (*this);
			}
			else if (knot->parent && knot->parent->right == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			TreeNode *temp = knot;
			while (temp->parent->left == temp)
				if ((temp = temp->parent) == NULL)
				{
					knot = temp->left;
					return (*this);
				}
			knot = temp->parent;
			return (*this);
		};

		reverse_iterator operator++(int)
		{
			reverse_iterator temp(knot);
			operator++();
			return (temp);

		};

		reverse_iterator &operator--()
		{
			if (knot->right != NULL)
			{
				knot = getMinNode(knot->right);
				return (*this);
			}
			else if (knot->parent && knot->parent->left == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			else if (knot->parent->right == knot)
				knot = knot->parent;
			TreeNode *temp = knot;
			while (temp->parent->right == temp)
			{
				temp = temp->parent;
				if (temp == NULL)
				{
					knot = knot->right;
					return (*this);
				}
			}
			knot = temp->parent;
			return (*this);
		};

		reverse_iterator operator--(int)
		{
			reverse_iterator temp(knot);
			operator--();
			return (temp);
		};

		bool				operator==(const reverse_iterator &src) const			{ return knot == src.knot; };
		bool				operator!=(const reverse_iterator &src) const			{ return knot != src.knot; };
		bool				operator==(const const_reverse_iterator &src) const		{ return knot == src.getNode(); };
		bool				operator!=(const const_reverse_iterator &src) const		{ return knot != src.getNode(); };
		const value_type	&operator*() const										{ return *(knot->data); };
		const value_type	*operator->() const										{ return knot->data; }
		TreeNode			*getNode() const										{ return knot; }

	private:
		TreeNode *getMinNode(TreeNode *node)
		{
			if (node->left != NULL)
				return (getMinNode(node->left));
			else
				return (node);
		}

		TreeNode *getMaxNode(TreeNode *node)
		{
			if (node->right != NULL)
				return (getMaxNode(node->right));
			else
				return (node);
		}
	};

	class const_reverse_iterator : public std::reverse_iterator<iterator>
	{
		private:
			TreeNode * knot;

		public:
			const_reverse_iterator(TreeNode* node = NULL): knot(node) {};
			~const_reverse_iterator() {};

			const_reverse_iterator &operator=(const const_reverse_iterator &src)
			{
				this->knot = src.knot;
				return (*this);
			};

			const_reverse_iterator &operator=(const reverse_iterator &src)
			{
				this->knot = src.getNode();
				return (*this);
			};

		const_reverse_iterator(const const_reverse_iterator &src)	{ *this = src; };
		const_reverse_iterator(const reverse_iterator &src)			{ *this = src; };

		const_reverse_iterator &operator++()
		{
			if (knot->left != NULL)
			{
				knot = getMaxNode(knot->left);
				return (*this);
			}
			else if (knot->parent && knot->parent->right == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			TreeNode *temp = knot;
			while (temp->parent->left == temp)
			{
				if ((temp = temp->parent) == NULL)
				{
					knot = temp->left;
					return (*this);
				}
			}
			knot = temp->parent;
			return (*this);
		};

		const_reverse_iterator operator++(int)
		{
			const_reverse_iterator tmp(knot);
			operator++();
			return (tmp);
		};

		const_reverse_iterator &operator--()
		{
			if (knot->right != NULL)
			{
				knot = getMinNode(knot->right);
				return (*this);
			}
			else if (knot->parent && knot->parent->left == knot)
			{
				knot = knot->parent;
				return (*this);
			}
			else if (knot->parent->right == knot)
				knot = knot->parent;
			TreeNode *temp = knot;
			while (temp->parent->right == temp)
			{
				temp = temp->parent;
				if (temp == NULL)
				{
					knot = knot->right;
					return (*this);
				}
			}
			knot = temp->parent;
			return (*this);
		};

		const_reverse_iterator operator--(int)
		{
			const_reverse_iterator tmp(knot);
			operator--();
			return (tmp);
		};

		bool			operator==(const const_reverse_iterator &src) const		{ return knot == src.knot; };
		bool			operator!=(const const_reverse_iterator &src) const		{ return knot != src.knot; };
		bool			operator==(const reverse_iterator &src) const			{ return knot == src.getNode(); };
		bool			operator!=(const reverse_iterator &src) const			{ return knot != src.getNode(); };
		const_reference	operator*() const										{ return *(this->knot->data); }
		const_pointer	operator->() const										{ return this->it->data; }
		TreeNode		*getNode() const										{ return knot; }

	private:
		TreeNode *getMinNode(TreeNode *node)
		{
			if (node->left)
				return (getMinNode(node->left));
			else
				return (node);
		}

		TreeNode *getMaxNode(TreeNode *node)
		{
			if (node->right)
				return (getMaxNode(node->right));
			else
				return (node);
		}
	};

	};
}

#endif

/***********************************************************************
 * Component:
 *    Assignment 10, Binary Search Tree (Map)
 *    Brother Kirby, CS 235
 * Author:
 *    Braden, David, Isabel
 * Summary:
 *    Create a Map
 ************************************************************************/

#ifndef MAP_H
#define MAP_H

// #include "bst.h"
#include "pair.h" 
using namespace std;
using namespace custom;

namespace custom
{
	template <class K, class V>
	class map
	{
	public:
		/*******************************************************
		 * Nested Binary tree class
		 *******************************************************/
		class BST
		{ 
		public:
		template <class T>
			class iterator
			{
			public:
				iterator()      : p(NULL)       {             }
				iterator(BNode * p) : p(p)  {             } 
				iterator(const iterator & rhs) { *this = rhs; }
				iterator & operator = (const iterator & rhs)
				{
					this->p = rhs.p;
					return *this;
				}
				
				// equals, not equals operator
				bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
				bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

				// dereference operator
				T & operator * ()       
				{
					return (*p).data; 
				}


				// prefix increment
				iterator & operator ++ ()
				{
					// do nothing if we have nothing
					if (NULL == p)
						return *this;

					// if there is a right node, take it
					if (NULL != p->pRight)
					{
						// go 
						p = p->pRight;

						// jig right - there might be more right-most children
						while (p->pLeft)
							p = p->pLeft;
						return *this;
					}

					// there are no left children, the right are done
					assert(NULL == p->pRight);
					BNode * pSave = p;

					// go up
					p = p->pParent;

					// if the parent is the NULL, we are done!
					if (NULL == p)
						return *this;

					// if we are the right-child, got to the parent.
					if (pSave == p->pLeft)
						return *this;

					// we are the left-child, go up as long as we are the left child!
					while (NULL != p && pSave == p->pRight)
					{
						pSave = p;
						p = p->pParent;
					}
					return *this;
				}

				// postfix increment
				iterator operator ++ (int postfix)
				{
					
					// do nothing if we have nothing
					if (NULL == p)
						return *this;

					// if there is a left node, take it
					if (NULL != p->pRight)
					{
						// go left
						p = p->pRight;

						// jig right - there might be more right-most children
						while (p->pLeft)
							p = p->pLeft;
						return *this;
					}

					// there are no left children, the right are done
					assert(NULL == p->pRight);
					BNode <T> * pSave = p;

					// go up
					p = p->pParent;

					// if the parent is the NULL, we are done!
					if (NULL == p)
						return *this;

					// if we are the right-child, got to the parent.
					if (pSave == p->pLeft)
						return *this;

					// we are the left-child, go up as long as we are the left child!
					while (NULL != p && pSave == p->pRight)
					{
						pSave = p;
						p = p->pParent;
					}
					return *this;
				}

				// prefix decrement
				iterator & operator -- ()
				{         
					// do nothing if we have nothing
					if (NULL == p)
						return *this;

					// if there is a left node, take it
					if (NULL != p->pLeft)
					{
						// go left
						p = p->pLeft;

						// jig right - there might be more right-most children
						while (p->pRight)
							p = p->pRight;
						return *this;
					}

					// there are no left children, the right are done
					assert(NULL == p->pLeft);
					BNode <T> * pSave = p;

					// go up
					p = p->pParent;

					// if the parent is the NULL, we are done!
					if (NULL == p)
						return *this;

					// if we are the right-child, got to the parent.
					if (pSave == p->pRight)
						return *this;

					// we are the left-child, go up as long as we are the left child!
					while (NULL != p && pSave == p->pLeft)
					{
						pSave = p;
						p = p->pParent;
					}

					return *this;
				}

				// postfix decrement
				iterator operator -- (int postfix)
				{
					// do nothing if we have nothing
					if (NULL == p)
						return *this;

					// if there is a left node, take it
					if (NULL != p->pLeft)
					{
						// go left
						p = p->pLeft;

						// jig right - there might be more right-most children
						while (p->pRight)
							p = p->pRight;
						return *this;
					}

					// there are no left children, the right are done
					assert(NULL == p->pLeft);
					BNode <T> * pSave = p;

					// go up
					p = p->pParent;

					// if the parent is the NULL, we are done!
					if (NULL == p)
						return *this;

					// if we are the right-child, got to the parent.
					if (pSave == p->pRight)
						return *this;

					// we are the left-child, go up as long as we are the left child!
					while (NULL != p && pSave == p->pLeft)
					{
						pSave = p;
						p = p->pParent;
					}
					return *this;
				}

				BNode <T> * getNode() { return p;}

			private:
				BNode <T> * p;
			};

			template <class T>
			class BNode
			{
				public:
				//node should use public variables
				T data;
				BNode * pLeft;
				BNode * pRight;
				BNode * pParent;
				bool isRed;

				// default constructor
				BNode(){ pParent = NULL; pRight = NULL; pLeft = NULL; data = NULL; isRed = true; }

				//non default constructor
				BNode(T newData)
				{
					pParent = NULL;
					pRight = NULL;
					pLeft = NULL;
					data = newData;
					isRed = true;
				}

				/****************************************************
				 * BINARY NODE :: FIND DEPTH
				 * Find the depth of the black nodes. This is useful for
				 * verifying that a given red-black tree is valid
				 * Author: Br. Helfrich
				 ****************************************************/
				bool findDepth() const // i'm not sure this should be a bool -Braden
				{
					// if there are no children, the depth is ourselves
					if (pRight == NULL && pLeft == NULL)
						return (isRed ? 0 : 1);

					// if there is a right child, go that way
					if (pRight != NULL)
						return (isRed ? 0 : 1) + pRight->findDepth();
					else
						return (isRed ? 0 : 1) + pLeft->findDepth();
				}

				/****************************************************
				 * BINARY NODE :: VERIFY RED BLACK
				 * Do all four red-black rules work here?
				 * Author: Br. Helfrich
				 ***************************************************/
				void verifyRedBlack(int depth) const
				{
					depth -= (isRed == false) ? 1 : 0;

					// Rule a) Every node is either red or black
					assert(isRed == true || isRed == false); // this feels silly

					// Rule b) The root is black
					if (pParent == NULL)
						assert(isRed == false);

					// Rule c) Red nodes have black children
					if (isRed == true)
					{
						if (pLeft != NULL)
							assert(pLeft->isRed == false);
						if (pRight != NULL)
							assert(pRight->isRed == false);
					}

					// Rule d) Every path from a leaf to the root has the same # of black nodes
					if (pLeft == NULL && pRight && NULL)
						assert(depth == 0);
					if (pLeft != NULL)
						pLeft->verifyRedBlack(depth);
					if (pRight != NULL)
						pRight->verifyRedBlack(depth);
				}

				/******************************************************
				 * VERIFY B TREE
				 * Verify that the tree is correctly formed
				 * Author: Br. Helfrich
				 ******************************************************/
				void verifyBTree() const
				{
					// check parent
					if (pParent)
						assert(pParent->pLeft == this || pParent->pRight == this);

					// check left
					if (pLeft)
					{
						assert(pLeft->data <= data);
						assert(pLeft->pParent == this);
						pLeft->verifyBTree();
					}

					// check right
					if (pRight)
					{
						assert(pRight->data >= data);
						assert(pRight->pParent == this);
						pRight->verifyBTree();
					}
				}

				private:
			}; 

			BST() { numElements = 0; root = NULL; };

			// copy constructor
			BST(const BST & rhs)
			{
				numElements = rhs.numElements;
				root = copyBTree(rhs.root);
			};

			// Destructor
			~BST() 
			{ 
				if (numElements != 0)
				{
					deleteBTree(root);
				}
				
			};

			BNode <pair <K,V>> * getRoot() { return root; }

			void clear() 
			{ 
				if(numElements > 0)
				{
					deleteBTree(root);                 
				}   
				root = NULL;     
				numElements = 0;
				return; 
			};

			iterator <pair <K,V>> begin()   
			{
				if (root == NULL)
				{   
					return iterator(NULL);
				}
				
				BNode <pair <K,V>> * left = root;
				while (left->pLeft != NULL)
				{
					left = left->pLeft;
				}
				return iterator(left);
			}

			iterator <pair <K,V>> end()
			{
				return iterator(NULL);
			}

			iterator <pair <K,V>> rbegin()
			{
				if (root == NULL)
				{
					return iterator(NULL);
				}
				
				BNode <pair <K,V>> * right = root;
				while (right->pRight != NULL)
				{
					right = right->pRight;
				}
				return iterator(right);
			}

			iterator <pair <K,V>> rend()
			{
				return iterator(NULL);
			}

			int size()   
			{ return numElements; };

			bool empty()
			{ 
				if (numElements == 0)
					return true;

				return false;
			};

			void insert(K data)
			{
				if (root == NULL)
				{
					root = new BNode (data);
					numElements++; 
					root->isRed = false;
					return;
				}

				// if the new data is less than current, go left
				// else go right 
				BNode <pair <K,V>> * pRef = root;
				while(pRef)
				{
					BNode <pair <K,V>> * newNode = new BNode (data);
					if (data <= pRef->data)
					{
						if (pRef->pLeft == NULL)
						{
							pRef->pLeft = newNode;
							newNode->pParent = pRef;
							newNode->pParent->pLeft = newNode;
							pRef = NULL;
						}
						else
						{
							pRef = pRef->pLeft;
						}
					}
					else
					{
						if(pRef->pRight == NULL)
						{
							pRef->pRight = newNode;
							newNode->pParent = pRef;
							pRef = NULL;
						}
						else
						{
							pRef = pRef->pRight;
						}
					}   
				} 
				// new data should be inserted in the correct location
				numElements++;
			};

			// Assignment operator 
			BST & operator = (const BST & rhs)
			{
				numElements = rhs.numElements;
				root = copyBTree(rhs.root);
				return *this;
			}

			// erase function
			void erase(iterator & it)
			{
				BNode <pair <K,V>> * p = it.getNode();
				// delete a child node
				if (p->pLeft == NULL && p->pRight == NULL)
				{
					if (p->data == p->pParent->pLeft->data)
					{
						p->pParent->pLeft = NULL;
						delete p;
					}
					else
					{
						p->pParent->pRight = NULL;
						delete p;
					}
					return; // we return so that we dont do the other ifs
				}

				// second case is if the node has two children
				if (p->pLeft != NULL && p->pRight != NULL)
				{
					T saveData = *(it++);
					erase(it);
					p->data = saveData;
					return;
				}

				// third case is if there are one children
				// check left
				if (p->pLeft != NULL || p->pRight != NULL)
				{      
					if (p->pLeft != NULL) // check to see if there is a left child
					{
						if(p->pParent->pLeft != NULL) // check to see if we are the left child
						{  
							p->pLeft->pParent = p->pParent;
							p->pParent->pLeft = p->pLeft;
							delete p;
							return;
						}
						else // when p->data == p->pParent->pRight
						{
							p->pLeft->pParent = p->pParent;
							p->pParent->pRight = p->pLeft;
							delete p;
							return;
						}
					} 
					else // There is a right child
					{
						if (p->data == p->pParent->pLeft->data)
						{
							p->pRight->pParent = p->pParent;
							p->pParent->pLeft = p->pRight;
							delete p;
							return;
						}
						else
						{
							p->pRight->pParent = p->pParent;
							p->pParent->pRight = p->pRight;
							delete p;
							return;
						}
					}
				}
				
				return;
			}

			// find function
			iterator find(const K & searchThing) 
			{
				iterator it;
				for (it = begin(); it != end(); it++)
				{
					if (*it == searchThing)
					{
						return it;
					}
					
				}
				return iterator(NULL);
			}

			void deleteBTree(BNode <pair <K,V>> * pRef)
			{
				if (pRef != NULL)
				{
					if (pRef->pLeft != NULL)
						deleteBTree(pRef->pLeft);
					if (pRef->pRight != NULL)
						deleteBTree(pRef->pRight);
					delete pRef;
					return;
				}

				return;
			};

			BNode <pair <K,V>> * copyBTree(const BNode * pRef)
			{
				if(pRef == NULL)
				{
					return NULL;
				}

				BNode <pair <K,V>> * tempNode = new BNode (pRef->data);

				tempNode->pLeft = copyBTree(pRef->pLeft);
				if (tempNode->pLeft != NULL)
				{
					tempNode->pLeft->pParent = tempNode;
				}

				tempNode->pRight = copyBTree(pRef->pRight);
				if (tempNode->pRight != NULL)
				{
					tempNode->pRight->pParent = tempNode;
				}     
				return tempNode;
			}

			// make the tree be balanced
			void balance(BNode <pair <K,V>> * pRef)
			{
				// root is black
				if (pRef == root)
				{
					pRef->isRed = false;
					return;
				}

				BNode <pair <K,V>> * uncle;
				// change the color of the node
				// case 1

			}

			private:
			BNode <pair <K,V>> * root;
			int numElements;
			
		};
		/*****************************************************
		* Class: iterator
		* Description: the iterator class for the map
		*****************************************************/
		class iterator
		{

		private:

			// We are just using the BST iterator but because BST::iterator is a nested class we need to put
			// typename so the compiler knows that this is a type and not a static member of BST
			typename BST < pair <K, V> > ::iterator it;

		public:

			//Constructors
			iterator() : it() {}
			iterator(const typename BST < pair <K, V> >::iterator & rhs)
			{
				it = rhs;
			}
			iterator(const iterator & rhs)
			{
				it = rhs.it;
			}

			//Assignment operator, can be assigned to a map iterator
			iterator & operator = (const iterator & rhs)
			{
				it = rhs.it;
				return *this;
			}

			// Uses the equality functions of the BST class
			bool operator == (const iterator & rhs) { return (it == rhs.it); }
			bool operator != (const iterator & rhs) { return (it != rhs.it); }

		// increment and decrement use the increment and decrement from the bst iterator
			// increment
			iterator & operator ++ () { it++; return *this; };
			iterator & operator ++ (int postfix) { ++it; return *this; };
			iterator & operator -- () { it--; return *this; };
			iterator & operator -- (int postfix) { --it; return *this; };
			// decrement
			
			// Dereference operator uses the derefernce code of the BST class
			pair<K, V> & operator * ()
			{
				return *it;
			}

		};


		// default and copy constructor uses BST code
		map() : bst() {}
		map(const map<K, V> & rhs) //throw (const char *)
		{
			bst = rhs.bst;
		}

		// copy the values, assignment operator uses BST code
		map <K, V> & operator = (const map <K, V> & rhs)
		{
			bst = rhs.bst;
			return *this;
		}


		// access operators, returns values by reference 
		V & operator [] (K key) // throw (const char *)
		{
			iterator temp(find(key));

			//If the specified key is not there, then add it
			if (temp == end())
			{
				pair<K, V> tempPair(key, V());
				insert(tempPair);
				temp = find(key);
			}
			return (*temp).second;
		}

		// access operator for const values, does not allow changing values 
        // calls this one when getting a value that doesn't
		// TODO: we will figure this out later -Braden
		const V & operator [] (K key) const
		{
			iterator temp(find(key));

			//If the specified key is not there, then return default value for V
			if (temp == end())
			{
				return V();
			}

			V tempThing = (*temp).second;

			return tempThing;
		}

		// Use code from BST for the rest of the class, only new code is in find()
		bool empty() { return bst.empty(); }
		int size() { return bst.size(); }
		void clear() { bst.clear(); }
		void insert(K key, V value)
		{
			pair<K, V> pair(key, value);
			bst.insert(pair);
		}
		void insert(pair<K, V> pair) { bst.insert(pair); }

		// We need it to return a map::iterator so we have to set it to BST::iterator
		// that is returned from the BST find() method 
        // Goes into the pair and looks for the value 
		iterator find(K key)
		{
			pair<K, V> tempPair(key, V());
			iterator it(bst.find(tempPair));
			iterator temp(it);
			return temp;
		}
		iterator begin()
		{
			return bst.begin();
		}
		iterator end()
		{
			iterator temp(nullptr);
			return temp;
		}

	private:

		// Since the map class is so similar to a Binary search tree, we just need a BST of type pair<K, V>
		BST < pair <K, V> > bst;
	};
	// map class
} // namespace custom

#endif // MAP_H
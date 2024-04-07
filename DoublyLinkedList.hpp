#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


#include <iostream>
#include <stdlib.h>
#include <stdexcept>


namespace CPSC131::DoublyLinkedList
{
	template <class T>
	class DoublyLinkedList
	{
		public:
			
			class Node
			{
				public:
					
					Node() : prev_(nullptr), next_(nullptr) {}
					Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
					Node(T element, Node* prev, Node* next) : element_(element), prev_(prev), next_(next){}
					
					
					void setPrevious(Node* prev) {prev_ = prev;}
					
					
					void setPrev(Node* prev) {prev_ = prev;}
					
					
					Node* getPrevious() {return prev_;}
					
					
					Node* getPrev() {return prev_;}
					
					
					void setNext(Node* next) {next_ = next;}
					
					
					Node* getNext() {return next_;}
					
					
					void setElement(T element) {element_ = element;}
					
					
					T& getElement() { return this->element_; }
					
					T& operator*() { return this->element_; }
					
				private:
					T element_;
					Node* prev_;
					Node* next_;
			};
			
		
			class Iterator
			{
				public:
					
					
					Iterator()
					{
						
					}
					
				
					Iterator(Node* head, Node* tail) : head_(head), tail_(tail)
					{
						this->cursor_ = this->end();	
					}
					
				
					Iterator(Node* head, Node* tail, Node* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
					

					Node* begin()
					{
						
						return head_;
					}
					
		
					Node* end()
					{
						return nullptr;
					}
					
			
					Node* getCursor()
					{
						return cursor_;
					}
					
					bool isAtEnd()
					{
						return this->cursor_ == nullptr;
					}
					
					Iterator& operator=(const Iterator& other)
					{
						if (this != &other) {
							head_ = other.head_;
							tail_ = other.tail_;
							cursor_ = other.cursor_;
								}

								return *this;
					}
					
			
					bool operator==(const Iterator& other)
					{
						return (cursor_ == other.cursor_);
					}
			
					bool operator!=(const Iterator& other)
					{
						return cursor_ != other.cursor_;
					}
					

					Iterator operator +(size_t add)
					{
						Iterator temp = *this;
						size_t count = 0;
						while (count < add && temp.cursor_ != nullptr)
						{
							temp.cursor_ = temp.cursor_ -> getNext();
							count++;
						}
						return temp;
					}
					
		
					Iterator operator -(size_t subtract)
					{
						Iterator temp = *this;
						size_t count = 0;
   						 while (count < subtract && temp.cursor_ != nullptr)
						{
							temp.cursor_ = temp.cursor_ -> getPrevious();
							count++;
						}
						return temp;

					}
					
	
					Iterator& operator++()
					{
						if (cursor_ != nullptr)
							{
									cursor_ = cursor_ -> getNext();
							}		
						return *this;
					}
					
		
					Iterator operator++(int)
					{
						Iterator temp(*this);
						if (cursor_ != nullptr)		
						{
							cursor_ = cursor_->getNext();
						}	
							return temp;
					}
					
		
					Iterator& operator--()
					{
						if (cursor_ != nullptr)
						{
							cursor_ = cursor_ -> getPrevious();
						}
						return *this;
					}
					

					Iterator operator--(int)
					{
						Iterator temp(*this);
						if (cursor_ != nullptr)	
							{
								cursor_ = cursor_ -> getPrevious();
							}
							return temp;
					}
					
			
					Iterator operator +=(size_t add)
					{
						for (size_t i = 0; i < add && cursor_ != nullptr; ++i)	
						{
							cursor_ = cursor_ -> getNext();
						}
						return *this;
					}
				
					Iterator operator -=(size_t subtract )
					{
						for (size_t i = 0; i < subtract && cursor_ != nullptr; ++i)
						{
							cursor_ = cursor_ -> getPrev();
						}
						return *this;
					}
					
		
					Iterator operator +=(int add)
					{
						if (add >= 0)				
						{
							for (int i = 0; i < add && cursor_ != nullptr; ++i)
							{
								cursor_ = cursor_ -> getNext();
							}
						}
						else if (add <= 0)
						{
							for (int i = 0; i > add && cursor_ != nullptr; --i)
							{
								cursor_ = cursor_ -> getPrevious();
							}
						}
						return *this;
					}
					

					Iterator operator -=(int subtract)
					{
						if (subtract >= 0)				
						{
							for (int i = 0; i < subtract && cursor_ != nullptr; ++i)
							{
								cursor_ = cursor_ -> getPrev();
							}
						}
						else 
						{
							for (int i = 0; i > subtract && cursor_ != nullptr; --i)
							{
								cursor_ = cursor_ -> getNext();
							}
						}
						return *this;
					}
					
				
					T& operator*()
					{
						return cursor_ -> getElement();	
					}
				
				private:
					
				
					Node* head_ = nullptr;
					
					
					Node* tail_ = nullptr;
					
				
					Node* cursor_ = nullptr;
				
				friend class DoublyLinkedList;
			};
			
		
			DoublyLinkedList()
			{
				head_ = nullptr;	
				tail_ = nullptr;
				size_ = 0;
			}
			
		
			DoublyLinkedList(DoublyLinkedList& other)
			{
				head_ = nullptr;	
				tail_ = nullptr;
				size_ = 0;

				for (auto it = other.begin(); it != other.end(); ++it) 
				{
					this->push_back(*it);
				}
				}
			

			~DoublyLinkedList()
			{
				this->clear();
			}
			

			void assign(size_t count, const T& value)
			{
				this->clear();

				for (size_t i = 0; i < count; ++i)
				{
					push_back(value);
				}
			}
			
			void assign(Iterator first, Iterator last)
			{
				clear();	
				while (first != last && first.getCursor() != nullptr)
				{
					push_back(*first);
					++first;
				}
				if (first.getCursor() != nullptr)
				{
					push_back(*first);
				}
			}
			
		
			Node* head() const
			{
				return head_;	
			}
			
		
			Node* tail() const
			{
				return tail_;	
			}
			
	
			Iterator begin() const
			{
				return Iterator(head_, tail_, head_);	
			}
			
	
			Iterator last() const
			{
				return Iterator(head_,tail_,tail_);	
			}
			

			Iterator end() const
			{
				return Iterator(nullptr,nullptr,nullptr);		
			}
			

			bool empty() const
			{
				return size_ == 0;	
			}
			
	
			size_t size() const
			{
				return size_;	
			}
			
		
			void clear()
			{
				
				while (head_ != nullptr)
				{
					Node* temp = head_;
					head_ = head_ ->getNext();
					delete temp;
				}
				head_ = nullptr;
				tail_ = nullptr;
				size_ = 0;
			}
			
			Iterator insert_after(Iterator pos, const T& value) 
			{
    			if (pos == end() || size_ == 0) 
				{
        			return push_back(value);
    			} 
				else 
				{
        		Node* current = pos.getCursor();
        		Node* newNode = new Node(value);
				newNode->setPrev(current);
        		newNode->setNext(current->getNext());
        		

        		if (current->getNext()) 
				{
            		current->getNext()->setPrev(newNode);
        		} 
					else 
				{
            		tail_ = newNode;
        		}
        			current->setNext(newNode);
        			++size_;
        			return Iterator(head_, tail_, newNode);
    		}
		}



			Iterator insert_after(size_t pos, const T& value)
			{
				if (pos > size())	
				{
					return push_back(value);
				}
				else
				{
				Iterator it = begin();
				for (size_t i = 0; i < pos; ++i)
				{
					++it;
				}
				
				return insert_after(it, value);
				}
			}
			

			Iterator erase(Iterator pos)
			{
				if (pos.getCursor() == nullptr)	//	TODO: Your code here
				{
				throw std::range_error("The iterator is invalid");
				}
				Node* current = pos.getCursor();
				Node* prev1 = current -> getPrev();
				Node* next1 = current -> getNext();

				if (prev1 != nullptr)
				{

				prev1 -> setNext(next1);
				}
				else
				{
					head_ = next1;
				}

				if (next1 != nullptr)
				{
					next1 -> setPrev(prev1);
				}

				else
				{
					tail_ = prev1;
				}

				delete current;
				--size_;

				return Iterator (head_,tail_,next1);
			}
			

			Iterator push_after(Iterator pos, const T& value)
			{
				if (size_ == 0 && pos == end())	
				{
					return push_back(value);
				}
				else
				{
					return insert_after(pos, value);
				}
				
				
			}
			
			void push_front(const T& value)
			{
				Node* newNode = new Node(value);	

				if (size_ == 0)
				{
					head_ = newNode;
					tail_ = newNode;
				}
				else 
				{
					newNode -> setNext(head_);
					head_ -> setPrev(newNode);
					head_ = newNode;
				}
				size_++;
			}
			

			Iterator push_back(const T& value)
			{
				Node* newNode = new Node(value);	

				if (tail_ == 0)
				{
					head_ = newNode;
					tail_ = newNode;
				}
				else 
				{
					tail_ -> setNext(newNode);
					newNode -> setPrev(tail_);
					tail_ = newNode;
				}
				size_++;

				return Iterator(newNode,head_,tail_);
			}
			

			void pop_front()
			{
				if (size_ == 0)
				{
					throw std::out_of_range("The list can't pop because it's empty");
				}
				Node* removedNode = head_;
				head_ = removedNode -> getNext();

				if (head_ != nullptr)
				{
					head_->setPrev(nullptr);
				}

				else
				{
					tail_ = nullptr;
				}

				delete removedNode;
				size_ --;
			}
			

			void pop_back()
			{
				if (size_ == 0)	
				{
					throw std::out_of_range("The list can't pop because it's empty");
				}
				Node* removedNode = tail_;
				tail_ = removedNode -> getPrev();

				if (tail_ != nullptr)
				{
					tail_ -> setNext(nullptr);
				}
				else
				{
					head_ = nullptr;
				}
				delete removedNode;
				size_ --;
			
			}
			

			T& front()
			{
				if (size_ == 0)	
				{
					throw std::out_of_range("The list is empty");
				}
				return head_ -> getElement();
			}
			
	
			T& back()
			{
				if (size_ == 0)	
				{
					throw std::underflow_error("The list is empty");
				}
				return tail_ -> getElement();
			}
			
			T& at(size_t index)
			{
				if (index >= size_ || index < 0)
				{
					throw std::range_error("The index is out of bounds");
				}
				Node* currentNode = head_;
				for (size_t i = 0; i < index; i++)
				{
					currentNode = currentNode-> getNext();
				}
				return currentNode -> getElement();
			}
			

			void reverse()
			{
				if (size_ > 1)
				{
					Node* currentList = head_;
					Node* temp = nullptr;

					while (currentList != nullptr)
					{
						temp = currentList -> getPrev();
						currentList -> setPrev(currentList -> getNext());
						currentList -> setNext(temp);
						currentList = currentList -> getPrev();
					}

					temp = head_;
					head_ = tail_;
					tail_ = temp;

				}
			}
		
			void sort()
			{
				
			}
			

			DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
			{
				if (this != &other)
				{
					clear();
				
				for (auto iterator = other.begin(); iterator != other.end(); ++iterator)
				{
					push_back(*iterator);
				}
			}
			return *this;
			}
	
			bool operator ==(DoublyLinkedList<T>& other)
			{
				if (size_ != other.size())
				{
					return false;
				}

				auto Iterator1 = begin();
				auto Iterator2 = other.begin();

				while (Iterator1 != end())
				{
					if (*Iterator1 != *Iterator2)
					{
						return false;
					}
					++Iterator1;
					++Iterator2;
				}
				return true;
			}
			

			bool operator !=(DoublyLinkedList<T>& other)
			{
				return !(*this == other);
			}
			
		private:
			
			
			Node* head_ = nullptr;
			Node* tail_ = nullptr;
			size_t size_ = 0;
	};
}

#endif

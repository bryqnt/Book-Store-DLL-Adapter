#include "BookStore.hpp"
#include <iostream>
#include <sstream>
#include <string>


using std::cout, std::cin, std::endl;
using std::string, std::to_string;
using std::stringstream;



namespace CPSC131::BookStore
{

	
	BookStore::BookStore() {}
	
	
	void BookStore::adjustAccountBalance(int adjustment)
	{
		account_balance_ += adjustment;
	}
	
	int BookStore::getAccountBalance() const
	{
		return account_balance_;
	}
	

	DoublyLinkedList::DoublyLinkedList<Book>::Iterator BookStore::findBook(std::string isbn) const
	{
		auto iterator1 = bookList.begin();

		while (iterator1 != bookList.end())
		{
			Book& currentBook = *iterator1;

			if (currentBook.getIsbn() == isbn)
			{
				return iterator1;
			}
			iterator1++;
		}
		
		return bookList.end();
	}
	
	bool BookStore::bookExists(std::string isbn) const
	{
		return findBook(isbn) != bookList.end();
	}
	
	size_t BookStore::getBookStockAvailable(std::string isbn) const
	{
		auto iterator2 = findBook(isbn);

		if (iterator2 != bookList.end())
		{
			const Book& book = *iterator2;
			return book.getStockAvailable();
		}
		
		return 0;
	}
	
	Book& BookStore::getBook(std::string isbn) const
	{
		auto iterator3 = findBook(isbn);

		if (iterator3 == bookList.end())
		{
			throw std::runtime_error("The book doesn't exist");
		}
		return *iterator3;
	}
	
	void BookStore::purchaseInventory(const Book& book)
	{
		auto iterator4 = findBook(book.getIsbn());

		if (iterator4 != bookList.end())
		{
			iterator4.getCursor()-> getElement().adjustStockAvailable(book.getStockAvailable());
		}
		else
		{
			bookList.push_back(book);
		}
		adjustAccountBalance(-1 * (book.getPriceCents() * book.getStockAvailable()));
	}
	
	void BookStore::purchaseInventory(
		std::string title, std::string author, std::string isbn,
		size_t price_cents,
		size_t unit_count
	)
	{
		Book book(title, author, isbn, price_cents, unit_count);
		purchaseInventory(book);
	}
	
	void BookStore::printInventory() const
	{
		std::cout << "*** Book Store Inventory ***" << std::endl;	

		for (auto iterator5 = bookList.begin(); iterator5 != bookList.end(); iterator5++)
		{
			const Book& book = *iterator5;
			std::cout << "\"" << book.getTitle() << "\", by " << book.getAuthor() << " [" << book.getIsbn() << "] (" << book.getStockAvailable() << " in stock)" << std::endl;

		}
	}
	
	void BookStore::sellToCustomer(std::string isbn, size_t price_cents, size_t quantity)
	{
		auto iterator6 = findBook(isbn);	

		if (iterator6 != bookList.end())
		{
			Book& book = *iterator6;
			
			if (book.getStockAvailable() < quantity)
			{
				throw std::runtime_error("Not enough stock is available");
			}
			int Cost = price_cents * quantity;
			adjustAccountBalance(Cost);

		}
	
	}
	

	void BookStore::sellToCustomer(Book& book, size_t price_cents, size_t quantity)
	{
		if (book.getStockAvailable() < quantity)
		{
			throw std::range_error("We don't have enough of this book in stock.");
		}

		int Cost = price_cents * quantity;
		adjustAccountBalance(Cost);
		book.adjustStockAvailable(book.getStockAvailable() - quantity);

	}
}

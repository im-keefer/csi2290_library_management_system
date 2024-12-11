#pragma once

#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <queue>
// Global counter for the amount of registered books
int numBooks = 0;

struct Book {
	std::string title;
	std::string author;
	std::string isbn;
	struct Person* borrower;
	std::queue<Person*> waitlist;
	int _id; // Internal, mainly used when pointer propogation will break
	Book(std::string title_in, std::string author_in, std::string isbn_in)
		: title(title_in), author(author_in), isbn(isbn_in)
	{
		_id = numBooks++;
		borrower = nullptr;
	};
	Book()
	{
		_id = numBooks++;
		borrower = nullptr;
	};
	bool operator==(const Book& other)
	{
		if (this->_id == other._id)
			return true;
		return false;
	}
};
#endif
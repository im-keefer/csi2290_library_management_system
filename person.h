#pragma once
#include <string>
#include <vector>
#ifndef PERSON_H
#define PERSON_H

#include "book.h"
struct Person {
	std::string name;
	Person(std::string person_name)
		: name(person_name)
	{
	};
	Person() {};
	std::vector<Book*> borrowed;
	std::vector<Book*> waitlisted;
};
#endif
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "book.h"



Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string ISBN) : Product(category, name, price, qty)
{
    author_ = author;
    ISBN_ = ISBN;

}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> nameKeywords;
    std::set<std::string> authorKeywords;
    nameKeywords = parseStringToWords(name_);
    authorKeywords = parseStringToWords(author_);
    keywords = setUnion(nameKeywords,authorKeywords);
    keywords.insert(ISBN_);
    return keywords;

}

std::string Book::displayString() const
{
    std::stringstream ss;
    std::string stringPrice;
    ss << std::setprecision(2) << std::fixed << price_;
    ss >> stringPrice;
    return name_  + "\n" +
    "Author: " + author_ + " " +
    + "ISBN: " + ISBN_ + "\n" +
    std::to_string(price_) + " " + std::to_string(qty_) + " left.\n";




}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::setprecision(2) << std::fixed << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << std::endl;
}
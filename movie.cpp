#include "movie.h"
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}
std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keywords;
    keywords = parseStringToWords(name_);
    keywords.insert(convToLower(genre_));
    return keywords;

}

std::string Movie::displayString() const
{
    std::stringstream ss;
    std::string stringPrice;
    ss << std::setprecision(2) << std::fixed << price_;
    ss >> stringPrice;
    return name_  + "\n" +
    "Genre: " + genre_ +
    + " Rating: " + rating_ + "\n" +
    stringPrice + " " + std::to_string(qty_) + " left.\n" ;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::setprecision(2) << std::fixed << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}
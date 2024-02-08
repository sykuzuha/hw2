#include <string>
#include <set>
#include <vector>
#include "clothing.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}
std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> nameKeywords;
    std::set<std::string> brandKeywords;
    nameKeywords = parseStringToWords(name_);
    nameKeywords = parseStringToWords(brand_);
    keywords = setUnion(nameKeywords,brandKeywords);
    return keywords;

}

std::string Clothing::displayString() const
{
    return "Name: " + name_  + "\n" +
    "Size: " + size_ + " " +
    + "Brand: " + brand_ + "\n" +
    std::to_string(price_) + " " + std::to_string(qty_) + " left.\n";
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}


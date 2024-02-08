#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>
#include <set>
#include <queue>
#include "mydatastore.h"
#include "util.h"
#include "product.h"

class MyDataStore : public DataStore{
    public:
        MyDataStore();
        
        void addProduct(Product* p);

        void addUser(User* u);

        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        void dump(std::ostream& ofile);

        void addToCart(std::string uname, Product* p);

        void viewCart(std::string uname);

        void buyCart(std::string uname);


    private:
        std::map<std::string, std::set<Product*>> keyProducts;

        std::map<std::string, User*> users;
        std::map<std::string, Product*> products;
        std::map<User*, std::vector<Product*>> carts;


};
#endif
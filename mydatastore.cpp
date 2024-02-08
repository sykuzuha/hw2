#include "mydatastore.h"
#include "util.h"
#include "product.h"
using namespace std;

MyDataStore::MyDataStore()
{

}
        
void MyDataStore::addProduct(Product* p)
{
    //products.insert(std::make_pair(p->getName(),p));
    std::set<std::string> keys;
    keys = p->keywords();
    for(std::set<string>::iterator it=keys.begin(); it != keys.end(); ++it)
    {
        keyProducts[*it].insert(p);
    }

    products.insert(std::make_pair(p->getName(),p));
    

}

void MyDataStore::addUser(User* u)
{
    users.insert(std::make_pair(u->getName(),u));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    //AND is 0
    //OR is 1
    std::set<Product*> searched_products;
    if(terms.size() == 0)
    {
        std::vector<Product*> empty;
        return empty;
    }
    if(type == 0)
    {
        for(int i = 1; i < terms.size(); i++)
        {
            searched_products = setIntersection(searched_products, keyProducts[terms[i]]);
        }   
    }
    else if(type == 1)
    {
        for(int i = 1; i < terms.size(); i++)
        {
            searched_products = setUnion(searched_products, keyProducts[terms[i]]);
        }   
    }
    vector<Product*> returnProducts(searched_products.begin(), searched_products.end());
    return returnProducts;
}

void MyDataStore::dump(std::ostream& ofile)
{
    std::map<std::string, User*>::iterator it;
    for(it = users.begin(); it != users.end(); ++it)
    {
        it->second->dump(ofile);
    }

    std::map<std::string, Product*>::iterator it2;
    for(it2 = products.begin(); it2 != products.end(); ++it)
    {
        it2->second->dump(ofile);
    }
}

void MyDataStore::addToCart(std::string uname, Product* p)
{
    carts[users[uname]].push_back(p);
}

void MyDataStore::viewCart(std::string uname)
{
    std::vector<Product*> cart = carts[users[uname]];
    for(int i = 0; i < cart.size(); i++)
    {
        cout << cart[i]->displayString();
    }
}

void MyDataStore::buyCart(std::string uname)
{
    std::vector<Product*> cart = carts[users[uname]];
    if(cart.size() > 0) 
    {
        for(int i = 0; i < cart.size(); i++)
        {
            Product* p = cart[i];
            if((p->getQty() > 0) && (users[uname]->getBalance() >= p->getPrice()))
            {
                users[uname]->deductAmount(p->getPrice());
                p->subtractQty(1);
                cart.erase(cart.begin() + i);
        
                

            }
        }
    }   
}



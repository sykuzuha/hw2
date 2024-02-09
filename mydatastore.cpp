#include "mydatastore.h"
#include "util.h"
#include "product.h"
#include <iostream>
#include <map>
#include <iomanip>


using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    std::map<std::string, Product*>::iterator it;
    for(it = products.begin(); it != products.end(); ++it)
    {
      delete it->second;
    } 
    std::map<std::string, User*>::iterator it2;
    for(it2 = users.begin(); it2 != users.end(); ++it2)
    {
      delete it2->second;
    } 
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
        searched_products = keyProducts[terms[0]];
        
        for(unsigned int i = 1; i < terms.size(); i++)
        {
            searched_products = setIntersection(searched_products, keyProducts[terms[i]]);
        }   
    }
    else if(type == 1)
    {
        searched_products = keyProducts[terms[0]];
        for(unsigned int i = 1; i < terms.size(); i++)
        {
            searched_products = setUnion(searched_products, keyProducts[terms[i]]);
        }   
    }
    vector<Product*> returnProducts(searched_products.begin(), searched_products.end());
    return returnProducts;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    std::map<std::string, Product*>::iterator it2;
    for(it2 = products.begin(); it2 != products.end(); ++it2)
    {
        it2->second->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    std::map<std::string, User*>::iterator it;
    for(it = users.begin(); it != users.end(); ++it)
    {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;

  
}

void MyDataStore::addToCart(std::string uname, Product* p)
{
    std::map<std::string, User*>::iterator it = users.find(uname);
    if (it != users.end())
    {
      carts[users[uname]].push_back(p);
    }
    else{
      cout << "Invalid request";
      return;
    }
    
}

void MyDataStore::viewCart(std::string uname)
{
    std::map<std::string, User*>::iterator it = users.find(uname);
    if (it != users.end()){
        for(unsigned int i = 0; i < carts[users[uname]].size(); i++)
        {   
            cout << "Item " << i + 1 << endl;
            cout << carts[users[uname]][i]->displayString() << endl;
        }
    }
    else{
      cout << "Invalid username";
      return;
    }
}

void MyDataStore::buyCart(std::string uname)
{
    if (users.find(uname) == users.end()){
      std::cout << "Invalid username" << std::endl;
      return;   
    }
    std::vector<Product*>& cart = carts[users[uname]]; 
    std::vector<Product*> new_cart;
    for(unsigned int i = 0; i < cart.size(); i++)
    {
      Product* p = cart[i];
      if((p->getQty() > 0) && (users[uname]->getBalance() >= p->getPrice()))
      {
        users[uname]->deductAmount(p->getPrice());
        p->subtractQty(1);
            

      }
      else{
        new_cart.push_back(p);
      }
    }
    cart = new_cart; 
    
    
    
}


#include <iostream>
#include <map>
#include <vector>

class Product {
private:
    int price;
    std::string description;
public:
    Product(int price, std::string description) {
        this->price = price;
        this->description = description;
    }

    int GetPrice() { return price; }

    std::string GetDescription() { return description; }

    void SetDescription(std::string description) {
        this->description = description;
    }
};

class Burger {
};

class Wrap {
};

class FriedPotatoes {
};

class Sauce {
};

class Beverage {
};

class Salad {
};

class Hamburger : public Burger {
};

class Cheeseburger : public Burger {
};

class BigMac : public Burger {
};

class McRoyal : public Burger {
};

class BigTasty : public Burger {
};

class CrispyChickenMcWrap : public Wrap {
};

class GrilledChickenMcWrap : public Wrap {
};

class SnackWrap : public Wrap {
};

class RanchSalad : public Salad {
};

class SideSalad : public Salad {
};

class SweetAndSourSauce : public Sauce {
};

class Ketchup : public Sauce {
};

class Mayonnaise : public Sauce {
};

class LatteCoffee : public Beverage {
};

class MochaCoffee : public Beverage {
};

class Fanta : public Beverage {
};

class CocaCola : public Beverage {
};

class Tea : public Beverage {
};

class Water : public Beverage {
};

class OrderObserver {
public:
    virtual void UpdateOrder() = 0;
};

// Using pattern MVC

class DisplayModelInterface {
public:

    virtual void Initialize() = 0;

    virtual void OrderProduct(Product *product, int count) = 0;

    virtual void CancelProduct(Product *product) = 0;

    virtual void IncreaseCountByOne(Product *product) = 0;

    virtual void DecreaseCountByOne(Product *product) = 0;

    virtual void RegisterObserver(OrderObserver *observer) = 0;

    virtual void RemoveObserver(OrderObserver *observer) = 0;

    virtual void NotifyObservers() = 0;

};

class DisplayModel : public DisplayModelInterface {
private:
    std::map<Product *, int> orderedProducts;
    std::vector<OrderObserver *> orderObservers;
    int totalPrice;
public:
    void Initialize() override {
        totalPrice = 0;
    }

    void OrderProduct(Product *product, int count) override {
        //key already exists
        if (!orderedProducts.insert(std::make_pair(product, count)).second) {
            orderedProducts[product] += count;
        } else {
            orderedProducts.insert(std::make_pair(product, count));
        }
        totalPrice += count * product->GetPrice();
    }

    void CancelProduct(Product *product) override {
        totalPrice -= orderedProducts[product] * product->GetPrice();
        orderedProducts.erase(product);
    }

    void IncreaseCountByOne(Product *product) override {
        auto lb = orderedProducts.lower_bound(product);

        if (lb != orderedProducts.end() && !(orderedProducts.key_comp()(product, lb->first))) {
            // key already exists
            orderedProducts[product]++;
        } else {
            // the key does not exist in the map
            orderedProducts.insert(lb, std::make_pair(product, 1));
        }
    }

    void DecreaseCountByOne(Product *product) override {
        auto lb = orderedProducts.lower_bound(product);

        if (lb != orderedProducts.end() && !(orderedProducts.key_comp()(product, lb->first))) {
            // key already exists
            if (orderedProducts[product] == 0) {
                orderedProducts[product]--;
            } else {
                /*
             !!!MUST BE EXCEPTION!!!
             */
                std::cout << "Negative count of product!!!" << std::endl;
            }
        } else {
            // the key does not exist in the map

            /*
             !!!MUST BE EXCEPTION!!!
             */
            std::cout << "Negative count of product!!!" << std::endl;
        }
    }

    void RegisterObserver(OrderObserver *observer) override {
        orderObservers.push_back(observer);
    }

    void RemoveObserver(OrderObserver *observer) override {
        for (auto it = orderObservers.begin(); it != orderObservers.end(); ++it) {
            if (*it == observer) {
                orderObservers.erase(it);
            }
        }
    }

    void NotifyObservers() override {
        for (auto &orderObserver : orderObservers) {
            orderObserver->UpdateOrder();
        }
    }
};

class DisplayControllerInterface{

};

//Сlient

int main() {
    return 0;
}
#include <iostream>
#include <string>

class Animal {
public:
    virtual void speak() = 0;
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        std::cout << "Meow!" << std::endl;
    }
};

int main() {
    Dog dog;
    Cat cat;

    Animal* animal1 = &dog;
    Animal* animal2 = &cat;

    animal1->speak();
    animal2->speak();

    return 0;
}

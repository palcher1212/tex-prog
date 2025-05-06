#include <iostream>
#include <string>

//класс Animal
class Animal {
protected:
    std::string name;
    int age;

public:
    Animal(const std::string& name, int age) : name(name), age(age) {}

    //получение информации об животном
    virtual void info() const {
        std::cout << "Name: " << name << ", Age: " << age << " years" << std::endl;
    }

    //виртуальный метод для издавания звука
    virtual void makeSound() const {
        std::cout << name << " makes a sound." << std::endl;
    }

    // деструктор 
    virtual ~Animal() {}
};

//класс Dog
class Dog : public Animal {
public:
    Dog(const std::string& name, int age) : Animal(name, age) {}

    void bark() const {
        std::cout << name << " barks: Woof!" << std::endl;
    }

    void fetch() const {
        std::cout << name << " is fetching the ball." << std::endl;
    }
};

//класс Cat
class Cat : public Animal {
public:
    Cat(const std::string& name, int age) : Animal(name, age) {}

    void meow() const {
        std::cout << name << " meows: Meow!" << std::endl;
    }

    void scratch() const {
        std::cout << name << " is scratching the furniture." << std::endl;
    }
};

//класс Bird
class Bird : public Animal {
public:
    Bird(const std::string& name, int age) : Animal(name, age) {}

    void sing() const {
        std::cout << name << " sings: Kewa!" << std::endl;
    }

    void fly() const {
        std::cout << name << " is flying." << std::endl;
    }
};

// сценарий 
int main() {
    Dog myDog("Xacki", 3);
    Cat myCat("Basik", 5);
    Bird myBird("Kewa", 2);

    myDog.info();
    myDog.makeSound();
    myDog.bark();
    myDog.fetch();

    std::cout << std::endl;

    myCat.info();
    myCat.makeSound();
    myCat.meow();
    myCat.scratch();

    std::cout << std::endl;

    myBird.info();
    myBird.makeSound();
    myBird.sing();
    myBird.fly();

    return 0;
}

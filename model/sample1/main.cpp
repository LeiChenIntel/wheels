#include <iostream>

// Abstract base class
class Base {
public:
    void normalShow() {
        std::cout << "Base class normal show function called." << std::endl;
    }
    virtual void virtualShow() {
        std::cout << "Base class virtual show function called." << std::endl;
    }
    virtual void pureVirtualShow() = 0;  // Pure virtual function makes this an abstract class
};

class DerivedA : public Base {
public:
    void normalShow() {
        std::cout << "DerivedA class normal show function called." << std::endl;
    }
    void virtualShow() override {
        std::cout << "DerivedA class virtual show function called." << std::endl;
    }
    void pureVirtualShow() override {
        std::cout << "DerivedA class implementation of pure virtual function." << std::endl;
    }
    int dataA = 11;
};

class DerivedB : public Base {
public:
    void normalShow() {
        std::cout << "DerivedB class normal show function called." << std::endl;
    }
    void virtualShow() override {
        std::cout << "DerivedB class virtual show function called." << std::endl;
    }
    void pureVirtualShow() override {
        std::cout << "DerivedB class implementation of pure virtual function." << std::endl;
    }
    int dataB = 13;
};

class Base2 {
public:
    void normalShow() {
        std::cout << "Base2 class normal show function called." << std::endl;
    }

    virtual void virtualShow() {
        std::cout << "Base2 class virtual show function called." << std::endl;
    }
    int dataD = 19;
};

class Derived2 : public Base2 {
public:
    void normalShow() {
        std::cout << "Derived2 class normal show function called." << std::endl;
    }
    int dataD = 17;
};

int main() {
    Base* objA = new DerivedA();
    Base* objB = new DerivedB();

    std::cout << "Calling functions on DerivedA object:" << std::endl;
    objA->normalShow();       // Calls Base class version
    objA->virtualShow();      // Calls DerivedA class version
    objA->pureVirtualShow();  // Calls DerivedA class version

    std::cout << "Calling functions on DerivedB object:" << std::endl;
    objB->normalShow();       // Calls Base class version
    objB->virtualShow();      // Calls DerivedB class version
    objB->pureVirtualShow();  // Calls DerivedB class version

    auto* objA2 = new DerivedA();
    std::cout << "Calling functions on DerivedA object:" << std::endl;
    objA2->normalShow();       // Calls Base class version
    objA2->virtualShow();      // Calls DerivedA class version
    objA2->pureVirtualShow();  // Calls DerivedA class version

    // DerivedB* objA3 = new DerivedA(); // This line would cause a compile-time error

    auto* objB2 = new Base2();
    objB2->normalShow();                           // Calls Base2 class version
    auto* objD2 = dynamic_cast<Derived2*>(objB2);  // dynamic_cast can only be applied to polymorphic types
    objD2->normalShow();
    std::cout << objB2->dataD << std::endl;
    std::cout << objD2->dataD << std::endl;
    auto* objD3 = dynamic_cast<DerivedA*>(objA);
    objD3->normalShow();

    delete objA;
    delete objB;
    delete objA2;
    delete objD2;
    return 0;
}

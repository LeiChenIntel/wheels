### This sample is to test virtual functions and inheritance in C++.

### Why std::cout << objD2->dataD << std::endl has a Segmentation fault (core dumped) issue at runtime?

The segmentation fault occurs because objD2 is a null pointer when you try to access objD2->dataD.
Here's what happens:

* objB2 is created as a Base2* pointing to a Base2 object
* dynamic_cast<Derived2*>(objB2) attempts to cast objB2 to Derived2*
* Since objB2 actually points to a Base2 object (not a Derived2 object), the dynamic_cast fails and returns nullptr
* objD2 becomes nullptr
* When you try to access objD2->dataD, you're dereferencing a null pointer, causing a segmentation fault

The fix is to check if the dynamic_cast succeeded before using the pointer:

```c++
auto* objD2 = dynamic_cast<Derived2*>(objB2);
if (objD2 != nullptr) {
    objD2->normalShow();
    std::cout << objD2->dataD << std::endl;
} else {
    std::cout << "dynamic_cast failed - objB2 is not a Derived2 object" << std::endl;
}
```

Alternatively, if you want objD2 to actually point to a Derived2 object, create it properly:

```c++
auto* objD2 = new Derived2();  // Create actual Derived2 object
objD2->normalShow();
std::cout << objD2->dataD << std::endl;
```

### If objD2 is a nullptr, then why objD2->normalShow(); works?

The reason objD2->normalShow(); works despite objD2 being nullptr is because normalShow() is declared as a static
function in the Derived2 class.

When you call a static member function through an object pointer (even a null pointer), the compiler resolves the
function call at compile time based on the pointer's type. Since static functions don't operate on specific object
instances and don't access member variables, dereferencing the null pointer doesn't actually occur.

Here's what happens:

* objD2->normalShow() is equivalent to Derived2::normalShow() because normalShow() is static
* The compiler translates this to a direct function call that doesn't require dereferencing the pointer
* No actual memory access through the null pointer occurs

However, when you try objD2->dataD, this attempts to access instance member data, which requires dereferencing the null
pointer and causes the segmentation fault.

To verify this behavior, you can replace the static call with the explicit syntax:

```c++
if (objD2 != nullptr) {
    objD2->normalShow();  // Works even if objD2 is null (static function)
    std::cout << objD2->dataD << std::endl;  // Segfault - accesses instance data
} else {
    Derived2::normalShow();  // Equivalent to objD2->normalShow() when static
    std::cout << "objD2 is null" << std::endl;
}
```

This is undefined behavior in C++ - calling member functions on null pointers should be avoided even if they happen to
work with static functions.

### Only the pointer is actually for a derived class, and it is cased by the base. the downcasting can work. but if the
pointer is a the one for base class, the downcasting can be failed is it right?

Yes, you're absolutely correct! That's exactly how dynamic_cast works for downcasting.

Here's the key principle:

dynamic_cast succeeds only when the object being pointed to is actually of the target type (or derived from it).

From your code:

1. When downcasting succeeds:

```c++
Base* objA = new DerivedA();  // objA points to a DerivedA object
auto* objD3 = dynamic_cast<DerivedA*>(objA);  // ✅ Succeeds - returns valid pointer
```

This works because objA actually points to a DerivedA object, even though it's stored as a Base*.

2. When downcasting fails:

```c++
auto* objB2 = new Base2();  // objB2 points to a Base2 object
auto* objD2 = dynamic_cast<Derived2*>(objB2);  // ❌ Fails - returns nullptr
```

This fails because objB2 points to a Base2 object, not a Derived2 object.

The dynamic_cast performs a runtime type check using RTTI (Run-Time Type Information). It checks if the actual object
type matches or is compatible with the target cast type.

Important note: For dynamic_cast to work, the base class must have at least one virtual function (making it
polymorphic). In your Base2 class, you have virtual void virtualShow(), which enables RTTI and allows dynamic_cast to
work.

If you removed the virtual function from Base2, the dynamic_cast would result in a compile-time error.

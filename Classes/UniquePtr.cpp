#include <iostream>

template <typename T> class uniquePtr
{
private:
    T* resource;
public:
    uniquePtr()
    {
        resource = nullptr;
        std::cout << "ctor\n";
    }

    ~uniquePtr()
    {
        delete resource;
        resource = nullptr;
        std::cout << "Destructor\n";
    }

    uniquePtr(T* val)
    {
        if (resource != nullptr)
        {
            resource = nullptr;
        }
        resource = val;
        std::cout << "Param ctor\n";
    }

    uniquePtr(uniquePtr& uptr) = delete;

    uniquePtr& operator = (uniquePtr& uptr) = delete;

    uniquePtr(uniquePtr&& uptr)
    {
        std::cout << "Move ctor\n";
        resource = uptr.resource;
        uptr.resource = nullptr;
    }
    uniquePtr& operator = (uniquePtr&& uptr)
    {
        std::cout << "Move assignment operator\n";
        if (this != &uptr)
        {
            if (resource != nullptr)
            {
                resource = nullptr;
            }
            resource = uptr.resource;
        }
        uptr.resource = nullptr;
        return *this;
    }

    T* operator -> () {
        return resource;
    }

    T& operator * () {
        return *resource;
    }
};

int main()
{
    uniquePtr<int> uptr1; // Default Ctor
    uniquePtr<int> uptr2(new int(3)); // Param Ctor
    uniquePtr<int> uptr3 = new int(4); // Param Ctor
    uniquePtr<int> uptr4 = std::move(uptr3); // Move ctor
    uptr3 = std::move(uptr2); // Move assignment operator
    std::cout << *uptr3;
}
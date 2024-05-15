#include <iostream>
#include <cstring>

class String
{
private:
    char* resource;
    unsigned int len;
public:
    String() : resource(nullptr), len(0)
    {
        std::cout << "Default Ctor\n";
    }

    String(const char* str)
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            len++;
        }
        resource = new char[len + 1];
        memcpy(resource, str, len + 1);
        //std::cout << resource << "*******\n";
        std::cout << "Parameterized Ctor\n";
    }

    String(const String& str)
    {
        if (this != &str)
        {
            if (this->resource != nullptr)
            {
                this->resource = nullptr;
            }
            this->len = str.len;
            this->resource = new char[str.len + 1];
            memcpy(this->resource, str.resource, this->len + 1);
        }
        //std::cout << resource << "*******\n";
        std::cout << "Copy Ctor\n";
    }

    String& operator = (const String& str)
    {
        if (this != &str)
        {
            if (this->resource != nullptr)
            {
                this->resource = nullptr;
            }
            this->len = str.len;
            this->resource = new char[len + 1];
            memcpy(this->resource, str.resource, str.len + 1);
        }
        //std::cout << resource << "*******\n";
        std::cout << "Copy Assignment Operator\n";
        return *this;
    }

    String(String&& str)
    {
        if (this != &str)
        {
            this->resource = str.resource;
            this->len = str.len;
            str.resource = nullptr;
            str.len = 0;
        }

        std::cout << "Move Constructor\n";
    }

    String& operator = (String&& str)
    {
        if (this != &str)
        {
            this->resource = str.resource;
            this->len = str.len;
            str.resource = nullptr;
            str.len = 0;
        }

        std::cout << "Move Assignment Operator\n";
        return *this;
    }

    unsigned int length()
    {
        return this->len;
    }

    friend std::istream& operator >> (std::istream& cin, String& str);
    friend std::ostream& operator <<  (std::ostream& cout, String& str);
};

std::istream& operator >> (std::istream& cin, String& str)
{
    /* with c++17 it should work fine.*/
    std::cin >> str.resource;
    return cin;
}
std::ostream& operator <<  (std::ostream& cout, String& str)
{
    /* with c++17 it should work fine.*/
    std::cout << str.resource;
    return cout;
}

int main()
{
    String str1; // Default Ctor
    String str2("String 2"); // Parameterized Ctor
    String str3 = "String 3"; // Parameterized Ctor
    String str4 = str2; // Copy Contructor
    String str5(str2); // Copy Contructor
    str1 = str2; // Copy Assignment operator
    String str6 = std::move(str2); //Move Ctor
    str1 = std::move(str3); //Move Assignment Operator
    std::cout << str1.length() << std::endl; // Length
    std::cout << str1; // Operator Overload
    return 0;
}
#include <iostream>
#include <cstring>
#define MAX_VECTOR_SIZE 100

template <typename T> class vector
{
private:
    T* resource;
    int front;
    int back;
public:
    vector() : resource(nullptr), front(0), back(0)
    {
        std::cout << "default Constructor\n";
    }
    vector(T value, unsigned int size)
    {
        std::cout << "parameterised constructor\n";
        this->resource = new T[size];
        for (int i = 0; i < size; i++)
        {
            this->resource[i] = value;
            this->front++;
        }

    }
    vector(const vector<T>& vec)
    {
        if (this != &vec)
        {
            if (this->resource != nullptr)
            {
                this->resource = nullptr;
            }
            int size = vec.front - vec.back;
            this->resource = new T[size];
            for (int i = 0; i < size; i++)
            {
                this->resource[i] = vec.resource[i];
            }
        }
        std::cout << "copy constructor\n";
    }

    vector<T>& operator = (vector<T>& vec)
    {

        if (this != &vec)
        {
            if (this->resource != nullptr)
            {
                this->resource = nullptr;
            }
            int size = vec.front - vec.back;
            this->resource = new T[size];
            for (int i = 0; i < size; i++)
            {
                this->resource[i] = vec.resource[i];
            }
            this->front = vec.front;
            this->back = vec.back;
        }
        std::cout << "Copy Assignment Operator\n";
        return *this;
    }

    vector(vector<T>&& vec)
    {
        this->resource = vec.resource;
        this->front = vec.front;
        this->back = vec.back;
        vec.resource = nullptr;
        vec.front = 0;
        vec.back = 0;
        std::cout << "move constructor\n";
    }
    vector<T>& operator = (vector<T>&& vec)
    {
        if (this != &vec)
        {
            if (this->resource != nullptr)
            {
                this->resource = nullptr;
            }
            this->resource = vec.resource;
            this->front = vec.front;
            this->back = vec.back;
            vec.resource = nullptr;
            vec.front = 0;
            vec.back = 0;
        }
        std::cout << "move assignment operator\n";
        return *this;
    }

    unsigned int size()
    {
        return front - back;
    }

};

int main()
{
    vector<int> vec1; /* Default ctor */
    vector<int> vec2(10, 5); /* Param ctor */
    vector<int> vec3 = vec2; /* Copy ctor */
    vec3 = vec2; /* copy assignment operator */
    vector<int> vec4 = std::move(vec3); /* Move ctor */
    vec3 = std::move(vec4); /* Move assignment operator */
    return 0;
}
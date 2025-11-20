#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class Stack {
public:
    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
    ~Stack();

    bool empty() const noexcept;
    std::size_t size() const noexcept;

    // вершина стека 
    const std::string* peek() const noexcept; // nullptr, если стек пуст
    std::string*       peek() noexcept;

    void push(const std::string& v);                 // добавить на вершину
    bool pop(std::string* out = nullptr);            // снять вершину

    void clear() noexcept;                          

    void print(std::ostream& os) const;              // печать сверху вниз: i) value
    bool save_to_file(const std::string& filename) const; // низ -> верх, как в S_save
    bool load_from_file(const std::string& filename);     // низ -> верх, как в S_load

private:
    struct Node {
        std::string person;
        Node* next;
    };

    Node* top_;          // вершина стека
    std::size_t size_;   // количество элементов

    static Node* new_node(const std::string& v, Node* next = nullptr);
    void copy_from(const Stack& other);
};

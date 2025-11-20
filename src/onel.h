#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList& other);           
    LinkedList(LinkedList&& other) noexcept;       
    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;
    ~LinkedList();

    bool empty() const noexcept;
    std::size_t size() const noexcept;

    const std::string* front() const noexcept;      // nullptr, если пусто
    std::string*       front() noexcept;

    const std::string* back() const noexcept;
    std::string*       back() noexcept;

    const std::string* at(std::size_t index) const; // nullptr, если за границами
    std::string*       at(std::size_t index);


    void push_front(const std::string& v);          // в голову
    void push_back(const std::string& v);           // в хвост

    bool pop_front();                             
    bool pop_back();

    // вставка по индексу
    bool insert_after(std::size_t index, const std::string& v);  // после index
    bool insert_before(std::size_t index, const std::string& v); // перед index

    bool erase_after(std::size_t index);            // удалить узел после index
    bool erase_before_tail();                       // удалить предпоследний

    int  index_of(const std::string& x) const;      // индекс первого вхождения, -1 если нет
    bool erase_first(const std::string& x);         // удалить первое вхождение
    int  erase_all(const std::string& x);           // удалить все, вернуть кол-во

    void clear() noexcept;                         

    void print(std::ostream& os) const;            
    bool save_to_file(const std::string& filename) const;
    bool load_from_file(const std::string& filename);

private:
    struct Node {
        std::string person;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    static Node* new_node(const std::string& v, Node* next = nullptr);
    Node* node_at(std::size_t index) const;
    void  copy_from(const LinkedList& other);
};

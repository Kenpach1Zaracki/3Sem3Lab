#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class DLinkedList {
public:
    DLinkedList();
    DLinkedList(const DLinkedList& other);
    DLinkedList(DLinkedList&& other) noexcept;
    DLinkedList& operator=(const DLinkedList& other);
    DLinkedList& operator=(DLinkedList&& other) noexcept;
    ~DLinkedList();

    bool empty() const noexcept;
    std::size_t size() const noexcept;

    // доступ к элементам
    const std::string* front() const noexcept;
    std::string*       front() noexcept;

    const std::string* back() const noexcept;
    std::string*       back() noexcept;

    const std::string* at(std::size_t index) const;
    std::string*       at(std::size_t index);

    void push_front(const std::string& v);
    void push_back(const std::string& v);

    bool pop_front();
    bool pop_back();

    // вставка по индексу
    bool insert_after(std::size_t index, const std::string& v);   // после index
    bool insert_before(std::size_t index, const std::string& v);  // перед index

    // удаление по индексу 
    bool erase_after(std::size_t index);   // удалить узел сразу после index
    bool erase_before(std::size_t index);  // удалить узел сразу перед index

    // поиск / удаление по значению
    int  index_of(const std::string& x) const;
    bool erase_first(const std::string& x);
    int  erase_all(const std::string& x);

    void clear() noexcept;

    void print(std::ostream& os) const;
    bool save_to_file(const std::string& filename) const;
    bool load_from_file(const std::string& filename);

private:
    struct Node {
        std::string person;
        Node* prev;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    static Node* new_node(const std::string& v, Node* p = nullptr, Node* n = nullptr);
    Node* node_at(std::size_t index) const;
    void  copy_from(const DLinkedList& other);
};

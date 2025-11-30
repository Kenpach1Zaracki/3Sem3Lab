#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class Queue {
public:
    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    ~Queue();

    bool empty() const noexcept;
    std::size_t size() const noexcept;

    const std::string* front() const noexcept; // nullptr, если пусто
    std::string*       front() noexcept;

    const std::string* back() const noexcept;  // nullptr, если пусто
    std::string*       back() noexcept;

    void push(const std::string& v);           // enqueue
    bool pop(std::string* out = nullptr);      // dequeue, true если удалось

    void clear() noexcept;

    void print(std::ostream& os) const;     
    bool save_to_file(const std::string& filename) const;
    bool load_from_file(const std::string& filename);

    bool save_to_binary(const std::string& filename) const;
    bool load_from_binary(const std::string& filename);

private:
    struct Node {
        std::string person;
        Node* next;
    };

    Node* head_;
    Node* tail_;
    std::size_t size_;

    static Node* new_node(const std::string& v, Node* next = nullptr);
    void copy_from(const Queue& other);
};

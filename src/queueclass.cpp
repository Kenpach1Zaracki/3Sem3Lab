#include "queue.h"

#include <fstream>
#include <ostream>


Queue::Node* Queue::new_node(const std::string& v, Node* next) {
    Node* n = new Node;
    n->person = v;
    n->next   = next;
    return n;
}

void Queue::copy_from(const Queue& other) {
    Node* cur = other.head_;
    while (cur) {
        push(cur->person);
        cur = cur->next;
    }
}

Queue::Queue()
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {
}

Queue::Queue(const Queue& other)
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {
    copy_from(other);
}

Queue::Queue(Queue&& other) noexcept
    : head_(other.head_)
    , tail_(other.tail_)
    , size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

Queue& Queue::operator=(Queue&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

Queue::~Queue() {
    clear();
}


bool Queue::empty() const noexcept {
    return size_ == 0;
}

std::size_t Queue::size() const noexcept {
    return size_;
}


const std::string* Queue::front() const noexcept {
    return head_ ? &head_->person : nullptr;
}

std::string* Queue::front() noexcept {
    return head_ ? &head_->person : nullptr;
}

const std::string* Queue::back() const noexcept {
    return tail_ ? &tail_->person : nullptr;
}

std::string* Queue::back() noexcept {
    return tail_ ? &tail_->person : nullptr;
}


void Queue::push(const std::string& v) {
    Node* n = new_node(v);
    if (tail_) {
        tail_->next = n;
        tail_ = n;
    } else {
        head_ = tail_ = n;
    }
    ++size_;
}

bool Queue::pop(std::string* out) {
    if (!head_) return false;
    Node* t = head_;
    if (out) {
        *out = t->person;
    }
    head_ = head_->next;
    if (!head_) {
        tail_ = nullptr;
    }
    delete t;
    --size_;
    return true;
}

void Queue::clear() noexcept {
    while (head_) {
        Node* t = head_;
        head_ = head_->next;
        delete t;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
}


void Queue::print(std::ostream& os) const {
    int i = 0;
    for (Node* cur = head_; cur; cur = cur->next, ++i) {
        os << i << ") " << cur->person << '\n';
    }
}

bool Queue::save_to_file(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    for (Node* cur = head_; cur; cur = cur->next) {
        f << cur->person << '\n';
    }
    return true;
}

bool Queue::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    clear();
    std::string line;
    while (std::getline(f, line)) {
        push(line);
    }
    return true;
}

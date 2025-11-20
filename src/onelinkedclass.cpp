#include "onel.h"
#include <fstream>
#include <ostream>

LinkedList::Node* LinkedList::new_node(const std::string& v, Node* next) {
    Node* n = new Node;
    n->person = v;
    n->next   = next;
    return n;
}

LinkedList::Node* LinkedList::node_at(std::size_t index) const {
    Node* cur = head_;
    while (cur && index--) {
        cur = cur->next;
    }
    return cur;
}

void LinkedList::copy_from(const LinkedList& other) {
    Node* cur = other.head_;
    while (cur) {
        push_back(cur->person);
        cur = cur->next;
    }
}

LinkedList::LinkedList()
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {
}

LinkedList::LinkedList(const LinkedList& other)
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {
    copy_from(other);
}

LinkedList::LinkedList(LinkedList&& other) noexcept
    : head_(other.head_)
    , tail_(other.tail_)
    , size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
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

LinkedList::~LinkedList() {
    clear();
}


bool LinkedList::empty() const noexcept {
    return size_ == 0;
}

std::size_t LinkedList::size() const noexcept {
    return size_;
}


const std::string* LinkedList::front() const noexcept {
    return head_ ? &head_->person : nullptr;
}

std::string* LinkedList::front() noexcept {
    return head_ ? &head_->person : nullptr;
}

const std::string* LinkedList::back() const noexcept {
    return tail_ ? &tail_->person : nullptr;
}

std::string* LinkedList::back() noexcept {
    return tail_ ? &tail_->person : nullptr;
}

const std::string* LinkedList::at(std::size_t index) const {
    Node* n = node_at(index);
    return n ? &n->person : nullptr;
}

std::string* LinkedList::at(std::size_t index) {
    Node* n = node_at(index);
    return n ? &n->person : nullptr;
}


void LinkedList::push_front(const std::string& v) {
    Node* n = new_node(v, head_);
    head_ = n;
    if (!tail_) {
        tail_ = n;
    }
    ++size_;
}

void LinkedList::push_back(const std::string& v) {
    Node* n = new_node(v, nullptr);
    if (!tail_) {
        head_ = tail_ = n;
    } else {
        tail_->next = n;
        tail_ = n;
    }
    ++size_;
}

bool LinkedList::pop_front() {
    if (!head_) return false;
    Node* t = head_;
    head_ = head_->next;
    if (!head_) {
        tail_ = nullptr;
    }
    delete t;
    --size_;
    return true;
}

bool LinkedList::pop_back() {
    if (!head_) return false;
    if (!head_->next) { 
        delete head_;
        head_ = tail_ = nullptr;
        size_ = 0;
        return true;
    }
    Node* prev = head_;
    while (prev->next && prev->next->next) {
        prev = prev->next;
    }
    delete prev->next;
    prev->next = nullptr;
    tail_ = prev;
    --size_;
    return true;
}

bool LinkedList::insert_after(std::size_t index, const std::string& v) {
    Node* pos = node_at(index);
    if (!pos) return false;
    Node* n = new_node(v, pos->next);
    pos->next = n;
    if (pos == tail_) {
        tail_ = n;
    }
    ++size_;
    return true;
}

bool LinkedList::insert_before(std::size_t index, const std::string& v) {
    if (index == 0) {
        push_front(v);
        return true;
    }
    Node* prev = node_at(index - 1);
    if (!prev) return false;
    Node* n = new_node(v, prev->next);
    prev->next = n;
    if (prev == tail_) {
        tail_ = n;
    }
    ++size_;
    return true;
}

bool LinkedList::erase_after(std::size_t index) {
    Node* pos = node_at(index);
    if (!pos || !pos->next) return false;
    Node* t = pos->next;
    pos->next = t->next;
    if (t == tail_) {
        tail_ = pos;
    }
    delete t;
    --size_;
    return true;
}

bool LinkedList::erase_before_tail() {
    if (!head_ || !head_->next) return false; // 0 или 1 элемент
    if (head_->next == tail_) {
        // два элемента -> удалить голову
        return pop_front();
    }
    Node* prev = head_;
    while (prev->next && prev->next->next != tail_) {
        prev = prev->next;
    }
    Node* t = prev->next; // узел перед хвостом
    prev->next = t->next;
    delete t;
    --size_;
    return true;
}

int LinkedList::index_of(const std::string& x) const {
    int idx = 0;
    for (Node* cur = head_; cur; cur = cur->next, ++idx) {
        if (cur->person == x) return idx;
    }
    return -1;
}

bool LinkedList::erase_first(const std::string& x) {
    if (!head_) return false;

    if (head_->person == x) {
        return pop_front();
    }

    Node* prev = head_;
    while (prev->next && prev->next->person != x) {
        prev = prev->next;
    }
    if (!prev->next) return false;

    Node* t = prev->next;
    prev->next = t->next;
    if (t == tail_) {
        tail_ = prev;
    }
    delete t;
    --size_;
    return true;
}

int LinkedList::erase_all(const std::string& x) {
    int cnt = 0;
    while (head_ && head_->person == x) {
        pop_front();
        ++cnt;
    }
    if (!head_) return cnt;

    Node* cur = head_;
    while (cur->next) {
        if (cur->next->person == x) {
            Node* t = cur->next;
            cur->next = t->next;
            if (t == tail_) {
                tail_ = cur;
            }
            delete t;
            --size_;
            ++cnt;
        } else {
            cur = cur->next;
        }
    }
    return cnt;
}

void LinkedList::clear() noexcept {
    while (head_) {
        Node* t = head_;
        head_ = head_->next;
        delete t;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
}

void LinkedList::print(std::ostream& os) const {
    bool first = true;
    for (Node* cur = head_; cur; cur = cur->next) {
        if (!first) os << ' ';
        os << cur->person;
        first = false;
    }
}

bool LinkedList::save_to_file(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    for (Node* cur = head_; cur; cur = cur->next) {
        f << cur->person << '\n';
    }
    return true;
}

bool LinkedList::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    clear();
    std::string line;
    while (std::getline(f, line)) {
        push_back(line);
    }
    return true;
}

#include "twolink.h"

#include <fstream>
#include <ostream>


DLinkedList::Node* DLinkedList::new_node(const std::string& v, Node* p, Node* n) {
    Node* node = new Node;
    node->person = v;
    node->prev   = p;
    node->next   = n;
    return node;
}

DLinkedList::Node* DLinkedList::node_at(std::size_t index) const {
    Node* cur = head_;
    while (cur && index--) {
        cur = cur->next;
    }
    return cur;
}

void DLinkedList::copy_from(const DLinkedList& other) {
    Node* cur = other.head_;
    while (cur) {
        push_back(cur->person);
        cur = cur->next;
    }
}

DLinkedList::DLinkedList()
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {
}

DLinkedList::DLinkedList(const DLinkedList& other)
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {
    copy_from(other);
}

DLinkedList::DLinkedList(DLinkedList&& other) noexcept
    : head_(other.head_)
    , tail_(other.tail_)
    , size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

DLinkedList& DLinkedList::operator=(const DLinkedList& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

DLinkedList& DLinkedList::operator=(DLinkedList&& other) noexcept {
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

DLinkedList::~DLinkedList() {
    clear();
}


bool DLinkedList::empty() const noexcept {
    return size_ == 0;
}

std::size_t DLinkedList::size() const noexcept {
    return size_;
}


const std::string* DLinkedList::front() const noexcept {
    return head_ ? &head_->person : nullptr;
}

std::string* DLinkedList::front() noexcept {
    return head_ ? &head_->person : nullptr;
}

const std::string* DLinkedList::back() const noexcept {
    return tail_ ? &tail_->person : nullptr;
}

std::string* DLinkedList::back() noexcept {
    return tail_ ? &tail_->person : nullptr;
}

const std::string* DLinkedList::at(std::size_t index) const {
    Node* n = node_at(index);
    return n ? &n->person : nullptr;
}

std::string* DLinkedList::at(std::size_t index) {
    Node* n = node_at(index);
    return n ? &n->person : nullptr;
}


void DLinkedList::push_front(const std::string& v) {
    Node* n = new_node(v, nullptr, head_);
    if (head_) {
        head_->prev = n;
    } else {
        tail_ = n;
    }
    head_ = n;
    ++size_;
}

void DLinkedList::push_back(const std::string& v) {
    Node* n = new_node(v, tail_, nullptr);
    if (tail_) {
        tail_->next = n;
        tail_ = n;
    } else {
        head_ = tail_ = n;
    }
    ++size_;
}

bool DLinkedList::pop_front() {
    if (!head_) return false;
    Node* t = head_;
    head_ = head_->next;
    if (head_) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }
    delete t;
    --size_;
    return true;
}

bool DLinkedList::pop_back() {
    if (!tail_) return false;
    Node* t = tail_;
    tail_ = tail_->prev;
    if (tail_) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }
    delete t;
    --size_;
    return true;
}

bool DLinkedList::insert_after(std::size_t index, const std::string& v) {
    Node* pos = node_at(index);
    if (!pos) return false;
    Node* n = new_node(v, pos, pos->next);
    if (pos->next) {
        pos->next->prev = n;
    } else {
        tail_ = n;
    }
    pos->next = n;
    ++size_;
    return true;
}

bool DLinkedList::insert_before(std::size_t index, const std::string& v) {
    Node* pos = node_at(index);
    if (!pos) return false;
    if (pos == head_) {
        push_front(v);
        return true;
    }
    Node* n = new_node(v, pos->prev, pos);
    pos->prev->next = n;
    pos->prev = n;
    ++size_;
    return true;
}

bool DLinkedList::erase_after(std::size_t index) {
    Node* pos = node_at(index);
    if (!pos || !pos->next) return false;
    Node* t = pos->next;
    pos->next = t->next;
    if (t->next) {
        t->next->prev = pos;
    } else {
        tail_ = pos;
    }
    delete t;
    --size_;
    return true;
}

bool DLinkedList::erase_before(std::size_t index) {
    Node* pos = node_at(index);
    if (!pos || !pos->prev) return false;
    Node* t = pos->prev;
    if (t->prev) {
        t->prev->next = pos;
        pos->prev = t->prev;
    } else {
        // t был головой
        head_ = pos;
        pos->prev = nullptr;
    }
    delete t;
    --size_;
    return true;
}


int DLinkedList::index_of(const std::string& x) const {
    int idx = 0;
    for (Node* cur = head_; cur; cur = cur->next, ++idx) {
        if (cur->person == x) return idx;
    }
    return -1;
}

bool DLinkedList::erase_first(const std::string& x) {
    Node* cur = head_;
    while (cur && cur->person != x) {
        cur = cur->next;
    }
    if (!cur) return false;

    if (cur->prev) cur->prev->next = cur->next;
    else head_ = cur->next;

    if (cur->next) cur->next->prev = cur->prev;
    else tail_ = cur->prev;

    delete cur;
    --size_;
    return true;
}

int DLinkedList::erase_all(const std::string& x) {
    int cnt = 0;
    Node* cur = head_;
    while (cur) {
        if (cur->person == x) {
            Node* del = cur;
            cur = cur->next;

            if (del->prev) del->prev->next = del->next;
            else head_ = del->next;

            if (del->next) del->next->prev = del->prev;
            else tail_ = del->prev;

            delete del;
            --size_;
            ++cnt;
        } else {
            cur = cur->next;
        }
    }
    return cnt;
}


void DLinkedList::clear() noexcept {
    while (head_) {
        Node* t = head_;
        head_ = head_->next;
        delete t;
    }
    head_ = tail_ = nullptr;
    size_ = 0;
}


void DLinkedList::print(std::ostream& os) const {
    int i = 0;
    for (Node* cur = head_; cur; cur = cur->next, ++i) {
        os << i << ") " << cur->person << '\n';
    }
}

bool DLinkedList::save_to_file(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    for (Node* cur = head_; cur; cur = cur->next) {
        f << cur->person << '\n';
    }
    return true;
}

bool DLinkedList::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    clear();
    std::string s;
    while (std::getline(f, s)) {
        push_back(s);
    }
    return true;
}

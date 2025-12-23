#include "stack.h"

#include <fstream>
#include <ostream>
#include <vector>



Stack::Node* Stack::new_node(const std::string& v, Node* next) {
    Node* n = new Node;
    n->person = v;
    n->next   = next;
    return n;
}

// аккуратное копирование с сохранением порядка (низ -> верх такой же)
void Stack::copy_from(const Stack& other) {
    std::vector<std::string> buf;
    for (Node* p = other.top_; p; p = p->next) {
        buf.push_back(p->person);
    }
    for (auto it = buf.rbegin(); it != buf.rend(); ++it) {
        push(*it);
    }
}


Stack::Stack()
    : top_(nullptr)
    , size_(0) {
}

Stack::Stack(const Stack& other)
    : top_(nullptr)
    , size_(0) {
    copy_from(other);
}

Stack::Stack(Stack&& other) noexcept
    : top_(other.top_)
    , size_(other.size_) {
    other.top_ = nullptr;
    other.size_ = 0;
}

Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

Stack& Stack::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();
        top_ = other.top_;
        size_ = other.size_;
        other.top_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

Stack::~Stack() {
    clear();
}

bool Stack::empty() const noexcept {
    return size_ == 0;
}

std::size_t Stack::size() const noexcept {
    return size_;
}

const std::string* Stack::peek() const noexcept {
    return top_ ? &top_->person : nullptr;
}

std::string* Stack::peek() noexcept {
    return top_ ? &top_->person : nullptr;
}


void Stack::push(const std::string& v) {
    Node* n = new_node(v, top_);
    top_ = n;
    ++size_;
}

bool Stack::pop(std::string* out) {
    if (!top_) return false;
    Node* t = top_;
    if (out) {
        *out = t->person;
    }
    top_ = top_->next;
    delete t;
    --size_;
    return true;
}

void Stack::clear() noexcept {
    while (top_) {
        Node* t = top_;
        top_ = top_->next;
        delete t;
    }
    size_ = 0;
}


void Stack::print(std::ostream& os) const {
    int i = 0;
    for (Node* p = top_; p; p = p->next, ++i) {
        os << i << ") " << p->person << '\n';
    }
}

// сохраняем элементы в порядке "низ -> верх"
bool Stack::save_to_file(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;

    std::vector<std::string> buf;
    for (Node* p = top_; p; p = p->next) {
        buf.push_back(p->person);
    }
    // в buf[0] — вершина, в buf[last] — низ
    // пишем в файл в обратном порядке: низ -> верх
    for (int i = static_cast<int>(buf.size()) - 1; i >= 0; --i) {
        f << buf[static_cast<std::size_t>(i)] << '\n';
    }
    return true;
}

bool Stack::save_to_binary(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    if (!f.is_open()) return false;

    f.write(reinterpret_cast<const char*>(&size_), sizeof(size_));

    std::vector<std::string> buf;
    for (Node* p = top_; p; p = p->next) {
        buf.push_back(p->person);
    }
    // buf[0] is top, buf[last] is bottom.
    // We want to save bottom -> top.
    for (int i = static_cast<int>(buf.size()) - 1; i >= 0; --i) {
        const std::string& s = buf[static_cast<std::size_t>(i)];
        size_t len = s.size();
        f.write(reinterpret_cast<const char*>(&len), sizeof(len));
        f.write(s.data(), len);
    }
    return true;
}


// читаем файл строками и пушим в стек по очереди
// (при условии, что файл был сохранён save_to_file, порядок восстановится)
bool Stack::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;

    clear();
    std::string s;
    while (std::getline(f, s)) {
        // читаем низ->верх и пушим в таком порядке
        push(s);
    }
    return true;
}

bool Stack::load_from_binary(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f.is_open()) return false;

    clear();

    size_t count = 0;
    f.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        size_t len = 0;
        f.read(reinterpret_cast<char*>(&len), sizeof(len));
        
        std::string s;
        s.resize(len);
        f.read(&s[0], len);

        push(s);
    }
    return true;
}

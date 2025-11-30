#include "massive.h"

#include <fstream>
#include <ostream>

unsigned long HashSet::hash_func(const std::string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned long>(c); // hash * 33 + c
    }
    return hash;
}

void HashSet::init_buckets(std::size_t tableSize) {
    tableSize_ = tableSize;
    size_ = 0;
    buckets_ = new Node*[tableSize_];
    for (std::size_t i = 0; i < tableSize_; ++i) {
        buckets_[i] = nullptr;
    }
}

void HashSet::free_buckets() noexcept {
    if (!buckets_) return;
    for (std::size_t i = 0; i < tableSize_; ++i) {
        Node* curr = buckets_[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }
    delete[] buckets_;
    buckets_ = nullptr;
    tableSize_ = 0;
    size_ = 0;
}

void HashSet::copy_from(const HashSet& other) {
    init_buckets(other.tableSize_);
    for (std::size_t i = 0; i < other.tableSize_; ++i) {
        Node* curr = other.buckets_[i];
        Node* prevNew = nullptr;
        while (curr) {
            Node* newNode = new Node{curr->val, nullptr};
            if (!buckets_[i]) {
                buckets_[i] = newNode;
            } else {
                prevNew->next = newNode;
            }
            prevNew = newNode;
            curr = curr->next;
            ++size_;
        }
    }
}

HashSet::HashSet(std::size_t tableSize)
    : buckets_(nullptr)
    , tableSize_(0)
    , size_(0) {
    init_buckets(tableSize);
}

HashSet::HashSet(const HashSet& other)
    : buckets_(nullptr)
    , tableSize_(0)
    , size_(0) {
    copy_from(other);
}

HashSet::HashSet(HashSet&& other) noexcept
    : buckets_(other.buckets_)
    , tableSize_(other.tableSize_)
    , size_(other.size_) {
    other.buckets_ = nullptr;
    other.tableSize_ = 0;
    other.size_ = 0;
}

HashSet& HashSet::operator=(const HashSet& other) {
    if (this != &other) {
        free_buckets();
        copy_from(other);
    }
    return *this;
}

HashSet& HashSet::operator=(HashSet&& other) noexcept {
    if (this != &other) {
        free_buckets();
        buckets_ = other.buckets_;
        tableSize_ = other.tableSize_;
        size_ = other.size_;
        other.buckets_ = nullptr;
        other.tableSize_ = 0;
        other.size_ = 0;
    }
    return *this;
}

HashSet::~HashSet() {
    free_buckets();
}


bool HashSet::empty() const noexcept {
    return size_ == 0;
}

std::size_t HashSet::size() const noexcept {
    return size_;
}

std::size_t HashSet::table_size() const noexcept {
    return tableSize_;
}


bool HashSet::contains(const std::string& elem) const {
    if (!buckets_ || tableSize_ == 0) return false;
    std::size_t idx = hash_func(elem) % tableSize_;
    Node* curr = buckets_[idx];
    while (curr) {
        if (curr->val == elem) return true;
        curr = curr->next;
    }
    return false;
}

bool HashSet::insert(const std::string& elem) {
    if (!buckets_ || tableSize_ == 0) return false;

    std::size_t idx = hash_func(elem) % tableSize_;
    Node* curr = buckets_[idx];
    while (curr) {
        if (curr->val == elem) {
            // уже есть
            return false;
        }
        curr = curr->next;
    }
    Node* newNode = new Node{elem, buckets_[idx]};
    buckets_[idx] = newNode;
    ++size_;
    return true;
}

bool HashSet::erase(const std::string& elem) {
    if (!buckets_ || tableSize_ == 0) return false;

    std::size_t idx = hash_func(elem) % tableSize_;
    Node* curr = buckets_[idx];
    Node* prev = nullptr;

    while (curr) {
        if (curr->val == elem) {
            if (prev) {
                prev->next = curr->next;
            } else {
                buckets_[idx] = curr->next;
            }
            delete curr;
            --size_;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void HashSet::clear() noexcept {
    free_buckets();
    // пересоздаём бакеты с тем же размером
    if (tableSize_ == 0) {
        // на всякий случай, но обычно сюда не попадём
        init_buckets(1009);
    } else {
        init_buckets(tableSize_);
    }
}


void HashSet::print(std::ostream& os) const {
    bool emptyFlag = true;
    for (std::size_t i = 0; i < tableSize_; ++i) {
        Node* curr = buckets_[i];
        while (curr) {
            os << "  • " << curr->val << '\n';
            curr = curr->next;
            emptyFlag = false;
        }
    }
    if (emptyFlag) {
        os << "(пусто)\n";
    }
}

bool HashSet::load_from_file(const std::string& path) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        return false;
    }
    clear();
    std::string word;
    while (fin >> word) {
        insert(word);
    }
    return true;
}

bool HashSet::save_to_file(const std::string& path) const {
    std::ofstream fout(path);
    if (!fout.is_open()) {
        return false;
    }
    for (std::size_t i = 0; i < tableSize_; ++i) {
        Node* curr = buckets_[i];
        while (curr) {
            fout << curr->val << '\n';
            curr = curr->next;
        }
    }
    return true;
}

bool HashSet::save_to_binary(const std::string& path) const {
    std::ofstream f(path, std::ios::binary);
    if (!f.is_open()) return false;

    f.write(reinterpret_cast<const char*>(&size_), sizeof(size_));

    for (std::size_t i = 0; i < tableSize_; ++i) {
        Node* curr = buckets_[i];
        while (curr) {
            size_t len = curr->val.size();
            f.write(reinterpret_cast<const char*>(&len), sizeof(len));
            f.write(curr->val.data(), len);
            curr = curr->next;
        }
    }
    return true;
}

bool HashSet::load_from_binary(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
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

        insert(s);
    }
    return true;
}

#include "hash.h"

#include <fstream>
#include <ostream>

std::size_t HashMap::hash_str(const std::string& s, std::size_t bucketCount) {
    unsigned int h = 0;
    for (char c : s) {
        h = h * 131u + static_cast<unsigned char>(c);
    }
    return static_cast<std::size_t>(h % static_cast<unsigned int>(bucketCount));
}
void HashMap::init_buckets(std::size_t bucketCount) {
    bucketCount_ = bucketCount;
    size_ = 0;
    buckets_ = new Node*[bucketCount_];
    for (std::size_t i = 0; i < bucketCount_; ++i) {
        buckets_[i] = nullptr;
    }
}

void HashMap::free_buckets() noexcept {
    if (!buckets_) return;
    for (std::size_t i = 0; i < bucketCount_; ++i) {
        Node* cur = buckets_[i];
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        buckets_[i] = nullptr;
    }
    delete[] buckets_;
    buckets_ = nullptr;
    bucketCount_ = 0;
    size_ = 0;
}

void HashMap::copy_from(const HashMap& other) {
    init_buckets(other.bucketCount_);
    for (std::size_t i = 0; i < other.bucketCount_; ++i) {
        Node* src = other.buckets_[i];
        Node* prevNew = nullptr;
        while (src) {
            Node* n = new Node{src->key, src->value, nullptr};
            if (!buckets_[i]) {
                buckets_[i] = n;
            } else {
                prevNew->next = n;
            }
            prevNew = n;
            src = src->next;
            ++size_;
        }
    }
}

HashMap::HashMap(std::size_t bucketCount)
    : buckets_(nullptr)
    , bucketCount_(0)
    , size_(0) {
    if (bucketCount == 0) bucketCount = 1;
    init_buckets(bucketCount);
}

HashMap::HashMap(const HashMap& other)
    : buckets_(nullptr)
    , bucketCount_(0)
    , size_(0) {
    copy_from(other);
}

HashMap::HashMap(HashMap&& other) noexcept
    : buckets_(other.buckets_)
    , bucketCount_(other.bucketCount_)
    , size_(other.size_) {
    other.buckets_ = nullptr;
    other.bucketCount_ = 0;
    other.size_ = 0;
}

HashMap& HashMap::operator=(const HashMap& other) {
    if (this != &other) {
        free_buckets();
        copy_from(other);
    }
    return *this;
}

HashMap& HashMap::operator=(HashMap&& other) noexcept {
    if (this != &other) {
        free_buckets();
        buckets_ = other.buckets_;
        bucketCount_ = other.bucketCount_;
        size_ = other.size_;
        other.buckets_ = nullptr;
        other.bucketCount_ = 0;
        other.size_ = 0;
    }
    return *this;
}

HashMap::~HashMap() {
    free_buckets();
}

bool HashMap::empty() const noexcept {
    return size_ == 0;
}

std::size_t HashMap::size() const noexcept {
    return size_;
}

std::size_t HashMap::bucket_count() const noexcept {
    return bucketCount_;
}


bool HashMap::contains(const std::string& key) const {
    if (!buckets_ || bucketCount_ == 0) return false;
    std::size_t idx = hash_str(key, bucketCount_);
    Node* cur = buckets_[idx];
    while (cur) {
        if (cur->key == key) return true;
        cur = cur->next;
    }
    return false;
}

void HashMap::set(const std::string& key, const std::string& val) {
    if (!buckets_ || bucketCount_ == 0) return;

    std::size_t idx = hash_str(key, bucketCount_);
    Node* cur = buckets_[idx];

    // если нашли ключ — обновляем значение
    while (cur) {
        if (cur->key == key) {
            cur->value = val;
            return;
        }
        cur = cur->next;
    }

    // не нашли — вставляем новый в голову цепочки
    Node* node = new Node{key, val, buckets_[idx]};
    buckets_[idx] = node;
    ++size_;
}

bool HashMap::get(const std::string& key, std::string& outVal) const {
    if (!buckets_ || bucketCount_ == 0) return false;
    std::size_t idx = hash_str(key, bucketCount_);
    Node* cur = buckets_[idx];
    while (cur) {
        if (cur->key == key) {
            outVal = cur->value;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool HashMap::erase(const std::string& key) {
    if (!buckets_ || bucketCount_ == 0) return false;
    std::size_t idx = hash_str(key, bucketCount_);
    Node* cur = buckets_[idx];
    Node* prev = nullptr;

    while (cur) {
        if (cur->key == key) {
            if (prev) {
                prev->next = cur->next;
            } else {
                buckets_[idx] = cur->next;
            }
            delete cur;
            --size_;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void HashMap::clear() noexcept {
    free_buckets();
    if (bucketCount_ == 0) {
        init_buckets(1024); // чтобы не остаться с нулём
    } else {
        init_buckets(bucketCount_);
    }
}


void HashMap::print(std::ostream& os) const {
    for (std::size_t i = 0; i < bucketCount_; ++i) {
        Node* cur = buckets_[i];
        while (cur) {
            os << cur->key << " => " << cur->value << '\n';
            cur = cur->next;
        }
    }
}

bool HashMap::save_to_file(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    // простой текстовый формат key value на строку
    for (std::size_t i = 0; i < bucketCount_; ++i) {
        Node* cur = buckets_[i];
        while (cur) {
            f << cur->key << ' ' << cur->value << '\n';
            cur = cur->next;
        }
    }
    return true;
}

bool HashMap::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    clear();
    std::string key, value;
    while (f >> key >> value) {
        set(key, value);
    }
    return true;
}

bool HashMap::save_to_binary(const std::string& filename) const {
    std::ofstream f(filename, std::ios::binary);
    if (!f.is_open()) return false;

    f.write(reinterpret_cast<const char*>(&size_), sizeof(size_));

    for (std::size_t i = 0; i < bucketCount_; ++i) {
        Node* cur = buckets_[i];
        while (cur) {
            size_t klen = cur->key.size();
            f.write(reinterpret_cast<const char*>(&klen), sizeof(klen));
            f.write(cur->key.data(), klen);

            size_t vlen = cur->value.size();
            f.write(reinterpret_cast<const char*>(&vlen), sizeof(vlen));
            f.write(cur->value.data(), vlen);

            cur = cur->next;
        }
    }
    return true;
}

bool HashMap::load_from_binary(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f.is_open()) return false;

    clear();

    size_t count = 0;
    f.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        size_t klen = 0;
        f.read(reinterpret_cast<char*>(&klen), sizeof(klen));
        std::string key;
        key.resize(klen);
        f.read(&key[0], klen);

        size_t vlen = 0;
        f.read(reinterpret_cast<char*>(&vlen), sizeof(vlen));
        std::string val;
        val.resize(vlen);
        f.read(&val[0], vlen);

        set(key, val);
    }
    return true;
}

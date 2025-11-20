#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class HashMap {
public:
    explicit HashMap(std::size_t bucketCount = 1024);

    HashMap(const HashMap& other);
    HashMap(HashMap&& other) noexcept;
    HashMap& operator=(const HashMap& other);
    HashMap& operator=(HashMap&& other) noexcept;
    ~HashMap();

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    std::size_t bucket_count() const noexcept;
    bool contains(const std::string& key) const;
    void set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& outVal) const;
    bool erase(const std::string& key);
    void clear() noexcept;
    void print(std::ostream& os) const;
    bool save_to_file(const std::string& filename) const;
    bool load_from_file(const std::string& filename);

private:
    struct Node {
        std::string key;
        std::string value;
        Node* next;
    };

    Node**      buckets_;      // массив списков
    std::size_t bucketCount_;  // число бакетов
    std::size_t size_;         // количество пар (элементов) в таблице

    // хеш-функция по строке
    static std::size_t hash_str(const std::string& s, std::size_t bucketCount);

    void init_buckets(std::size_t bucketCount);
    void free_buckets() noexcept;
    void copy_from(const HashMap& other);
};

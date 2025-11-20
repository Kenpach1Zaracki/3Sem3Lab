#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class HashSet {
public:
    explicit HashSet(std::size_t tableSize = 1009);

    HashSet(const HashSet& other);             // глубокое копирование
    HashSet(HashSet&& other) noexcept;         // перемещение
    HashSet& operator=(const HashSet& other);  // копирующее присваивание
    HashSet& operator=(HashSet&& other) noexcept; // перемещающее
    ~HashSet();

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    std::size_t table_size() const noexcept;

    bool contains(const std::string& elem) const; // проверка наличия (SET_AT)
    bool insert(const std::string& elem);         // добавить, true если добавлен
    bool erase(const std::string& elem);          // удалить, true если был

    void clear() noexcept;                        

    void print(std::ostream& os) const;           



    bool load_from_file(const std::string& path);

    bool save_to_file(const std::string& path) const;

private:
    struct Node {
        std::string val;
        Node* next;
    };

    Node** buckets_;         
    std::size_t tableSize_;  
    std::size_t size_;       

    static unsigned long hash_func(const std::string& str);

    void init_buckets(std::size_t tableSize);
    void free_buckets() noexcept;
    void copy_from(const HashSet& other);
};

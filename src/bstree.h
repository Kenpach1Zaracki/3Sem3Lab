#pragma once

#include <string>
#include <cstddef>
#include <iosfwd>

class BSTree {
public:
    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;
    ~BSTree();

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    int height() const noexcept; // высота дерева (для интереса/тестов)


    bool insert(const std::string& value);
    bool contains(const std::string& value) const;
    bool erase(const std::string& value);
    const std::string* min_value() const;
    const std::string* max_value() const;

    void clear() noexcept;

    // симметричный обход (in-order), по одному элементу в строке — дерево как отсортированный список
    void print_inorder(std::ostream& os) const;

    void print_structure(std::ostream& os) const;

    // сохраняем дерево в текстовый файл (in-order, по строке на элемент)
    bool save_to_file(const std::string& filename) const;

    // читаем файл (по строке = одно значение) и добавляем в дерево
    bool load_from_file(const std::string& filename);

private:
    struct Node {
        std::string value;
        Node* left;
        Node* right;
    };

    Node* root_;
    std::size_t size_;

    static Node* new_node(const std::string& v);
    static void  delete_subtree(Node* node);

    static Node* copy_subtree(const Node* node);

    static std::size_t calc_size(const Node* node);
    static int calc_height(const Node* node);

    static bool insert_rec(Node*& node, const std::string& value);
    static bool contains_rec(const Node* node, const std::string& value);
    static bool erase_rec(Node*& node, const std::string& value);

    static Node* find_min_node(Node* node);
    static const Node* find_min_node(const Node* node);
    static const Node* find_max_node(const Node* node);

    static void print_inorder_rec(const Node* node, std::ostream& os);
    static void print_structure_rec(const Node* node, std::ostream& os, int depth);
};

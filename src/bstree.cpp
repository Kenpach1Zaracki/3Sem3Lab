#include "bstree.h"

#include <fstream>
#include <ostream>


BSTree::Node* BSTree::new_node(const std::string& v) {
    Node* n = new Node;
    n->value = v;
    n->left  = nullptr;
    n->right = nullptr;
    return n;
}

void BSTree::delete_subtree(Node* node) {
    if (!node) return;
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

BSTree::Node* BSTree::copy_subtree(const Node* node) {
    if (!node) return nullptr;
    Node* n = new Node;
    n->value = node->value;
    n->left  = copy_subtree(node->left);
    n->right = copy_subtree(node->right);
    return n;
}

std::size_t BSTree::calc_size(const Node* node) {
    if (!node) return 0;
    return 1 + calc_size(node->left) + calc_size(node->right);
}

int BSTree::calc_height(const Node* node) {
    if (!node) return 0;
    int hl = calc_height(node->left);
    int hr = calc_height(node->right);
    return 1 + (hl > hr ? hl : hr);
}

// вставка: возвращает true, если реально добавили новый узел
bool BSTree::insert_rec(Node*& node, const std::string& value) {
    if (!node) {
        node = new_node(value);
        return true;
    }
    if (value < node->value) {
        return insert_rec(node->left, value);
    } else if (value > node->value) {
        return insert_rec(node->right, value);
    } else {
        // уже есть
        return false;
    }
}

bool BSTree::contains_rec(const Node* node, const std::string& value) {
    if (!node) return false;
    if (value < node->value) {
        return contains_rec(node->left, value);
    } else if (value > node->value) {
        return contains_rec(node->right, value);
    } else {
        return true;
    }
}

// поиск минимального узла в поддереве
BSTree::Node* BSTree::find_min_node(Node* node) {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}
const BSTree::Node* BSTree::find_min_node(const Node* node) {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}
const BSTree::Node* BSTree::find_max_node(const Node* node) {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    return node;
}

// удаление узла по значению
bool BSTree::erase_rec(Node*& node, const std::string& value) {
    if (!node) return false;

    if (value < node->value) {
        return erase_rec(node->left, value);
    } else if (value > node->value) {
        return erase_rec(node->right, value);
    } else {
        // нашли
        // 1) нет детей
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        }
        // 2) только правый
        else if (!node->left) {
            Node* tmp = node;
            node = node->right;
            delete tmp;
        }
        // 3) только левый
        else if (!node->right) {
            Node* tmp = node;
            node = node->left;
            delete tmp;
        }
        // 4) два ребёнка: берём минимальный элемент из правого поддерева
        else {
            Node* minRight = find_min_node(node->right);
            node->value = minRight->value;               // копируем значение
            erase_rec(node->right, minRight->value);     // удаляем дубль ниже
        }
        return true;
    }
}

void BSTree::print_inorder_rec(const Node* node, std::ostream& os) {
    if (!node) return;
    print_inorder_rec(node->left, os);
    os << node->value << '\n';
    print_inorder_rec(node->right, os);
}

void BSTree::print_structure_rec(const Node* node, std::ostream& os, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) os << "  ";
    os << node->value << '\n';
    print_structure_rec(node->left, os, depth + 1);
    print_structure_rec(node->right, os, depth + 1);
}


BSTree::BSTree()
    : root_(nullptr)
    , size_(0) {
}

BSTree::BSTree(const BSTree& other)
    : root_(nullptr)
    , size_(0) {
    root_ = copy_subtree(other.root_);
    size_ = calc_size(root_);
}

BSTree::BSTree(BSTree&& other) noexcept
    : root_(other.root_)
    , size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
}

BSTree& BSTree::operator=(const BSTree& other) {
    if (this != &other) {
        clear();
        root_ = copy_subtree(other.root_);
        size_ = calc_size(root_);
    }
    return *this;
}

BSTree& BSTree::operator=(BSTree&& other) noexcept {
    if (this != &other) {
        clear();
        root_ = other.root_;
        size_ = other.size_;
        other.root_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

BSTree::~BSTree() {
    clear();
}


bool BSTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BSTree::size() const noexcept {
    return size_;
}

int BSTree::height() const noexcept {
    return calc_height(root_);
}


bool BSTree::insert(const std::string& value) {
    bool added = insert_rec(root_, value);
    if (added) ++size_;
    return added;
}

bool BSTree::contains(const std::string& value) const {
    return contains_rec(root_, value);
}

bool BSTree::erase(const std::string& value) {
    bool removed = erase_rec(root_, value);
    if (removed) {
        size_ = calc_size(root_);
    }
    return removed;
}

const std::string* BSTree::min_value() const {
    const Node* n = find_min_node(root_);
    return n ? &n->value : nullptr;
}

const std::string* BSTree::max_value() const {
    const Node* n = find_max_node(root_);
    return n ? &n->value : nullptr;
}

void BSTree::clear() noexcept {
    delete_subtree(root_);
    root_ = nullptr;
    size_ = 0;
}


void BSTree::print_inorder(std::ostream& os) const {
    print_inorder_rec(root_, os);
}

void BSTree::print_structure(std::ostream& os) const {
    print_structure_rec(root_, os, 0);
}

bool BSTree::save_to_file(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    print_inorder_rec(root_, f);
    return true;
}

bool BSTree::load_from_file(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    clear();
    std::string line;
    while (std::getline(f, line)) {
        if (!line.empty())
            insert(line);
    }
    return true;
}

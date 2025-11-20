// main.cpp
#include <iostream>
#include <string>

#include "onel.h"       // LinkedList
#include "twolink.h"    // DLinkedList
#include "queue.h"      // Queue
#include "stack.h"      // Stack
#include "massive.h"    // HashSet (множество)
#include "hash.h"       // HashMap (ключ -> значение)
#include "bstree.h"     // BSTree

using std::cout;
using std::cin;
using std::string;

// ---------- МЕНЮ ОДНОСВЯЗНОГО СПИСКА ----------
void menu_linked_list(LinkedList& list) {
    while (true) {
        cout << "\n=== ОДНОСВЯЗНЫЙ СПИСОК ===\n"
             << "1) Добавить в НАЧАЛО\n"
             << "2) Добавить в КОНЕЦ\n"
             << "3) Вставить ПОСЛЕ индекса\n"
             << "4) Вставить ПЕРЕД индексом\n"
             << "5) Удалить ПЕРВЫЙ элемент\n"
             << "6) Удалить ПОСЛЕДНИЙ элемент\n"
             << "7) Удалить элемент ПОСЛЕ индекса\n"
             << "8) Удалить ПРЕДПОСЛЕДНИЙ элемент\n"
             << "9) Удалить ПЕРВОЕ вхождение значения\n"
             << "10) Удалить ВСЕ вхождения значения\n"
             << "11) Показать элементы списка\n"
             << "12) Загрузить из файла\n"
             << "13) Сохранить в файл\n"
             << "14) Показать размер и пустоту\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string val, filename;
        std::size_t idx;

        switch (cmd) {
            case 1:
                cout << "Значение: ";
                cin >> val;
                list.push_front(val);
                break;
            case 2:
                cout << "Значение: ";
                cin >> val;
                list.push_back(val);
                break;
            case 3:
                cout << "Индекс: ";
                cin >> idx;
                cout << "Значение: ";
                cin >> val;
                if (!list.insert_after(idx, val))
                    cout << "Ошибка: индекс вне диапазона.\n";
                break;
            case 4:
                cout << "Индекс: ";
                cin >> idx;
                cout << "Значение: ";
                cin >> val;
                if (!list.insert_before(idx, val))
                    cout << "Ошибка: индекс вне диапазона.\n";
                break;
            case 5:
                if (!list.pop_front())
                    cout << "Список пуст.\n";
                break;
            case 6:
                if (!list.pop_back())
                    cout << "Список пуст.\n";
                break;
            case 7:
                cout << "Индекс: ";
                cin >> idx;
                if (!list.erase_after(idx))
                    cout << "Ошибка: нельзя удалить элемент после этого индекса.\n";
                break;
            case 8:
                if (!list.erase_before_tail())
                    cout << "Ошибка: в списке слишком мало элементов.\n";
                break;
            case 9:
                cout << "Значение: ";
                cin >> val;
                if (!list.erase_first(val))
                    cout << "Такого значения нет.\n";
                break;
            case 10:
                cout << "Значение: ";
                cin >> val;
                cout << "Удалено элементов: " << list.erase_all(val) << "\n";
                break;
            case 11:
                cout << "Список:\n";
                list.print(std::cout);
                cout << "\n";
                break;
            case 12:
                cout << "Файл: ";
                cin >> filename;
                if (!list.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 13:
                cout << "Файл: ";
                cin >> filename;
                if (!list.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 14:
                cout << "Размер: " << list.size()
                     << ", список " << (list.empty() ? "ПУСТОЙ" : "НЕ пустой") << "\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}

// ---------- МЕНЮ ДВУСВЯЗНОГО СПИСКА ----------
void menu_dlinked_list(DLinkedList& list) {
    while (true) {
        cout << "\n=== ДВУСВЯЗНЫЙ СПИСОК ===\n"
             << "1) Добавить в НАЧАЛО\n"
             << "2) Добавить в КОНЕЦ\n"
             << "3) Вставить ПОСЛЕ индекса\n"
             << "4) Вставить ПЕРЕД индексом\n"
             << "5) Удалить ПЕРВЫЙ элемент\n"
             << "6) Удалить ПОСЛЕДНИЙ элемент\n"
             << "7) Удалить элемент ПОСЛЕ индекса\n"
             << "8) Удалить элемент ПЕРЕД индексом\n"
             << "9) Удалить ПЕРВОЕ вхождение значения\n"
             << "10) Удалить ВСЕ вхождения значения\n"
             << "11) Показать элементы списка\n"
             << "12) Загрузить из файла\n"
             << "13) Сохранить в файл\n"
             << "14) Показать размер и пустоту\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string val, filename;
        std::size_t idx;

        switch (cmd) {
            case 1:
                cout << "Значение: ";
                cin >> val;
                list.push_front(val);
                break;
            case 2:
                cout << "Значение: ";
                cin >> val;
                list.push_back(val);
                break;
            case 3:
                cout << "Индекс: ";
                cin >> idx;
                cout << "Значение: ";
                cin >> val;
                if (!list.insert_after(idx, val))
                    cout << "Ошибка: индекс вне диапазона.\n";
                break;
            case 4:
                cout << "Индекс: ";
                cin >> idx;
                cout << "Значение: ";
                cin >> val;
                if (!list.insert_before(idx, val))
                    cout << "Ошибка: индекс вне диапазона.\n";
                break;
            case 5:
                if (!list.pop_front())
                    cout << "Список пуст.\n";
                break;
            case 6:
                if (!list.pop_back())
                    cout << "Список пуст.\n";
                break;
            case 7:
                cout << "Индекс: ";
                cin >> idx;
                if (!list.erase_after(idx))
                    cout << "Ошибка удаления.\n";
                break;
            case 8:
                cout << "Индекс: ";
                cin >> idx;
                if (!list.erase_before(idx))
                    cout << "Ошибка удаления.\n";
                break;
            case 9:
                cout << "Значение: ";
                cin >> val;
                if (!list.erase_first(val))
                    cout << "Такого значения нет.\n";
                break;
            case 10:
                cout << "Значение: ";
                cin >> val;
                cout << "Удалено элементов: " << list.erase_all(val) << "\n";
                break;
            case 11:
                cout << "Список:\n";
                list.print(std::cout);
                break;
            case 12:
                cout << "Файл: ";
                cin >> filename;
                if (!list.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 13:
                cout << "Файл: ";
                cin >> filename;
                if (!list.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 14:
                cout << "Размер: " << list.size()
                     << ", список " << (list.empty() ? "ПУСТОЙ" : "НЕ пустой") << "\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}

// ---------- МЕНЮ ОЧЕРЕДИ ----------
void menu_queue(Queue& q) {
    while (true) {
        cout << "\n=== ОЧЕРЕДЬ ===\n"
             << "1) Добавить в КОНЕЦ очереди\n"
             << "2) Удалить из НАЧАЛА очереди\n"
             << "3) Показать ПЕРВЫЙ и ПОСЛЕДНИЙ элемент\n"
             << "4) Показать все элементы очереди\n"
             << "5) Загрузить очередь из файла\n"
             << "6) Сохранить очередь в файл\n"
             << "7) Показать размер и пустоту\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string val, filename;

        switch (cmd) {
            case 1:
                cout << "Значение: ";
                cin >> val;
                q.push(val);
                break;
            case 2:
                if (q.pop(&val))
                    cout << "Удалён элемент: " << val << "\n";
                else
                    cout << "Очередь пуста.\n";
                break;
            case 3: {
                const string* f = q.front();
                const string* b = q.back();
                cout << "Первый: "  << (f ? *f : "нет")
                     << ", последний: " << (b ? *b : "нет") << "\n";
                break;
            }
            case 4:
                cout << "Очередь:\n";
                q.print(std::cout);
                break;
            case 5:
                cout << "Файл: ";
                cin >> filename;
                if (!q.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 6:
                cout << "Файл: ";
                cin >> filename;
                if (!q.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 7:
                cout << "Размер: " << q.size()
                     << ", очередь " << (q.empty() ? "ПУСТАЯ" : "НЕ пустая") << "\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}

// ---------- МЕНЮ СТЕКА ----------
void menu_stack(Stack& st) {
    while (true) {
        cout << "\n=== СТЕК ===\n"
             << "1) Положить элемент на вершину\n"
             << "2) Снять элемент с вершины\n"
             << "3) Показать элемент на вершине\n"
             << "4) Показать все элементы стека\n"
             << "5) Загрузить стек из файла\n"
             << "6) Сохранить стек в файл\n"
             << "7) Показать размер и пустоту\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string val, filename;

        switch (cmd) {
            case 1:
                cout << "Значение: ";
                cin >> val;
                st.push(val);
                break;
            case 2:
                if (st.pop(&val))
                    cout << "Снято: " << val << "\n";
                else
                    cout << "Стек пуст.\n";
                break;
            case 3: {
                const string* p = st.peek();
                cout << "Вершина: " << (p ? *p : "нет элементов") << "\n";
                break;
            }
            case 4:
                cout << "Стек (сверху вниз):\n";
                st.print(std::cout);
                break;
            case 5:
                cout << "Файл: ";
                cin >> filename;
                if (!st.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 6:
                cout << "Файл: ";
                cin >> filename;
                if (!st.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 7:
                cout << "Размер: " << st.size()
                     << ", стек " << (st.empty() ? "ПУСТОЙ" : "НЕ пустой") << "\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}

// ---------- МЕНЮ МНОЖЕСТВА (HashSet из massive.h) ----------
void menu_hashset(HashSet& set) {
    while (true) {
        cout << "\n=== МНОЖЕСТВО (HashSet) ===\n"
             << "1) Добавить элемент в множество\n"
             << "2) Удалить элемент из множества\n"
             << "3) Проверить, есть ли элемент\n"
             << "4) Показать все элементы множества\n"
             << "5) Загрузить множество из файла\n"
             << "6) Сохранить множество в файл\n"
             << "7) Показать размер, пустоту и размер таблицы\n"
             << "8) Очистить множество\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string val, filename;

        switch (cmd) {
            case 1:
                cout << "Элемент: ";
                cin >> val;
                if (set.insert(val))
                    cout << "Элемент добавлен.\n";
                else
                    cout << "Такой элемент уже есть.\n";
                break;
            case 2:
                cout << "Элемент: ";
                cin >> val;
                if (set.erase(val))
                    cout << "Элемент удалён.\n";
                else
                    cout << "Такого элемента нет.\n";
                break;
            case 3:
                cout << "Элемент: ";
                cin >> val;
                cout << (set.contains(val)
                         ? "Элемент ЕСТЬ в множестве.\n"
                         : "Элемента НЕТ в множестве.\n");
                break;
            case 4:
                cout << "Множество:\n";
                set.print(std::cout);
                break;
            case 5:
                cout << "Файл: ";
                cin >> filename;
                if (!set.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 6:
                cout << "Файл: ";
                cin >> filename;
                if (!set.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 7:
                cout << "Элементов: " << set.size()
                     << ", множество " << (set.empty() ? "ПУСТОЕ" : "НЕ пустое")
                     << ", размер хеш-таблицы: " << set.table_size() << "\n";
                break;
            case 8:
                set.clear();
                cout << "Множество очищено.\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}

// ---------- МЕНЮ ХЕШ-КАРТЫ (HashMap) ----------
void menu_hashmap(HashMap& map) {
    while (true) {
        cout << "\n=== ХЕШ-Таблица (HashMap: ключ -> значение) ===\n"
             << "1) Добавить/обновить пару (ключ, значение)\n"
             << "2) Получить значение по ключу\n"
             << "3) Удалить пару по ключу\n"
             << "4) Проверить наличие ключа\n"
             << "5) Показать все пары\n"
             << "6) Загрузить из файла\n"
             << "7) Сохранить в файл\n"
             << "8) Показать размер, пустоту и число бакетов\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string key, value, filename;

        switch (cmd) {
            case 1:
                cout << "Ключ: ";
                cin >> key;
                cout << "Значение: ";
                cin >> value;
                map.set(key, value);
                cout << "Пара сохранена.\n";
                break;
            case 2:
                cout << "Ключ: ";
                cin >> key;
                if (map.get(key, value))
                    cout << "Значение: " << value << "\n";
                else
                    cout << "Такого ключа нет.\n";
                break;
            case 3:
                cout << "Ключ: ";
                cin >> key;
                if (map.erase(key))
                    cout << "Пара удалена.\n";
                else
                    cout << "Такого ключа нет.\n";
                break;
            case 4:
                cout << "Ключ: ";
                cin >> key;
                cout << (map.contains(key)
                         ? "Ключ ЕСТЬ в таблице.\n"
                         : "Ключа НЕТ в таблице.\n");
                break;
            case 5:
                cout << "Содержимое таблицы:\n";
                map.print(std::cout);
                break;
            case 6:
                cout << "Файл: ";
                cin >> filename;
                if (!map.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 7:
                cout << "Файл: ";
                cin >> filename;
                if (!map.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 8:
                cout << "Элементов: " << map.size()
                     << ", таблица " << (map.empty() ? "ПУСТАЯ" : "НЕ пустая")
                     << ", бакетов: " << map.bucket_count() << "\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}

// ---------- МЕНЮ ДЕРЕВА ----------
void menu_bst(BSTree& tree) {
    while (true) {
        cout << "\n=== БИНАРНОЕ ДЕРЕВО ПОИСКА (BSTree) ===\n"
             << "1) Добавить значение\n"
             << "2) Удалить значение\n"
             << "3) Проверить наличие значения\n"
             << "4) Вывести значения по возрастанию\n"
             << "5) Показать структуру дерева\n"
             << "6) Показать минимум и максимум\n"
             << "7) Загрузить дерево из файла\n"
             << "8) Сохранить дерево в файл\n"
             << "9) Показать число узлов, высоту и пустоту\n"
             << "0) Назад\n"
             << "Ваш выбор: ";
        int cmd;
        if (!(cin >> cmd)) return;
        if (cmd == 0) break;

        string val, filename;

        switch (cmd) {
            case 1:
                cout << "Значение: ";
                cin >> val;
                if (tree.insert(val))
                    cout << "Добавлено.\n";
                else
                    cout << "Такое значение уже есть.\n";
                break;
            case 2:
                cout << "Значение: ";
                cin >> val;
                if (tree.erase(val))
                    cout << "Удалено.\n";
                else
                    cout << "Такого значения нет.\n";
                break;
            case 3:
                cout << "Значение: ";
                cin >> val;
                cout << (tree.contains(val)
                         ? "Значение ЕСТЬ в дереве.\n"
                         : "Значения НЕТ в дереве.\n");
                break;
            case 4:
                cout << "Дерево (отсортированный вывод):\n";
                tree.print_inorder(std::cout);
                break;
            case 5:
                cout << "Структура дерева:\n";
                tree.print_structure(std::cout);
                break;
            case 6: {
                const string* mn = tree.min_value();
                const string* mx = tree.max_value();
                cout << "Минимум: " << (mn ? *mn : "нет")
                     << ", максимум: " << (mx ? *mx : "нет") << "\n";
                break;
            }
            case 7:
                cout << "Файл: ";
                cin >> filename;
                if (!tree.load_from_file(filename))
                    cout << "Ошибка чтения файла.\n";
                break;
            case 8:
                cout << "Файл: ";
                cin >> filename;
                if (!tree.save_to_file(filename))
                    cout << "Ошибка записи файла.\n";
                break;
            case 9:
                cout << "Узлов: " << tree.size()
                     << ", высота: " << tree.height()
                     << ", дерево " << (tree.empty() ? "ПУСТОЕ" : "НЕ пустое") << "\n";
                break;
            default:
                cout << "Неизвестная команда.\n";
        }
    }
}


int main() {
    LinkedList  sList;
    DLinkedList dList;
    Queue       queue;
    Stack       stack;
    HashSet     hset;   // множество
    HashMap     hmap;   // ассоц. массив
    BSTree      bst;

    while (true) {
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n"
             << "1) Работа с ОДНОСВЯЗНЫМ списком\n"
             << "2) Работа с ДВУСВЯЗНЫМ списком\n"
             << "3) Работа с ОЧЕРЕДЬЮ\n"
             << "4) Работа со СТЕКОМ\n"
             << "5) Работа с МНОЖЕСТВОМ (HashSet)\n"
             << "6) Работа с ХЕШ-Таблицей (HashMap)\n"
             << "7) Работа с БИНАРНЫМ ДЕРЕВОМ ПОИСКА (BSTree)\n"
             << "0) Выход\n"
             << "Ваш выбор: ";

        int choice;
        if (!(cin >> choice)) break;

        switch (choice) {
            case 1: menu_linked_list(sList);  break;
            case 2: menu_dlinked_list(dList); break;
            case 3: menu_queue(queue);        break;
            case 4: menu_stack(stack);        break;
            case 5: menu_hashset(hset);       break;
            case 6: menu_hashmap(hmap);       break;
            case 7: menu_bst(bst);            break;
            case 0:
                cout << "Работа программы завершена.\n";
                return 0;
            default:
                cout << "Неизвестный пункт меню.\n";
        }
    }
    return 0;
}

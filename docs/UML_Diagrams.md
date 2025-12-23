# UML Диаграммы Классов - Структуры Данных

Для просмотра диаграмм:
1. Откройте этот файл на GitHub (диаграммы отобразятся автоматически)
2. Или скопируйте код диаграммы и вставьте на [mermaid.live](https://mermaid.live)
3. Или используйте расширение для браузера/редактора с поддержкой Mermaid

---

## 1. BSTree - Бинарное Дерево Поиска

```mermaid
classDiagram
    class BSTree {
        -Node* root_
        -size_t size_

        +BSTree()
        +BSTree(const BSTree& other)
        +BSTree(BSTree&& other)
        +operator=(const BSTree& other) BSTree&
        +operator=(BSTree&& other) BSTree&
        +~BSTree()

        +empty() bool
        +size() size_t
        +height() int

        +insert(value: string) bool
        +contains(value: string) bool
        +erase(value: string) bool
        +min_value() const string*
        +max_value() const string*
        +clear() void

        +print_inorder(os: ostream&) void
        +print_structure(os: ostream&) void
        +save_to_file(filename: string) bool
        +load_from_file(filename: string) bool
        +save_to_binary(filename: string) bool
        +load_from_binary(filename: string) bool

        -new_node(v: string)$ Node*
        -delete_subtree(node: Node*)$ void
        -copy_subtree(node: Node*)$ Node*
        -calc_size(node: Node*)$ size_t
        -calc_height(node: Node*)$ int
        -insert_rec(node: Node*&, value: string)$ bool
        -contains_rec(node: Node*, value: string)$ bool
        -erase_rec(node: Node*&, value: string)$ bool
        -find_min_node(node: Node*)$ Node*
        -find_max_node(node: Node*)$ const Node*
        -print_inorder_rec(node: Node*, os: ostream&)$ void
        -print_structure_rec(node: Node*, os: ostream&, depth: int)$ void
    }

    class Node {
        +string value
        +Node* left
        +Node* right
    }

    BSTree *-- Node : содержит
```

**Описание:**
- Бинарное дерево поиска с автоматическим балансированием
- Поддерживает операции вставки, поиска, удаления за O(log n) в среднем
- Имеет методы для сохранения/загрузки в текстовом и бинарном форматах

---

## 2. HashMap - Хеш-Таблица (Словарь)

```mermaid
classDiagram
    class HashMap {
        -Node** buckets_
        -size_t bucketCount_
        -size_t size_

        +HashMap(bucketCount: size_t = 1024)
        +HashMap(const HashMap& other)
        +HashMap(HashMap&& other)
        +operator=(const HashMap& other) HashMap&
        +operator=(HashMap&& other) HashMap&
        +~HashMap()

        +empty() bool
        +size() size_t
        +bucket_count() size_t
        +contains(key: string) bool
        +set(key: string, value: string) void
        +get(key: string, outVal: string&) bool
        +erase(key: string) bool
        +clear() void

        +print(os: ostream&) void
        +save_to_file(filename: string) bool
        +load_from_file(filename: string) bool
        +save_to_binary(filename: string) bool
        +load_from_binary(filename: string) bool

        -hash_str(s: string, bucketCount: size_t)$ size_t
        -init_buckets(bucketCount: size_t) void
        -free_buckets() void
        -copy_from(other: HashMap&) void
    }

    class Node {
        +string key
        +string value
        +Node* next
    }

    HashMap *-- Node : содержит
```

**Описание:**
- Хеш-таблица с методом цепочек для разрешения коллизий
- Хранит пары ключ-значение
- Средняя сложность операций O(1)

---

## 3. HashSet - Хеш-Множество

```mermaid
classDiagram
    class HashSet {
        -Node** buckets_
        -size_t tableSize_
        -size_t size_

        +HashSet(tableSize: size_t = 1009)
        +HashSet(const HashSet& other)
        +HashSet(HashSet&& other)
        +operator=(const HashSet& other) HashSet&
        +operator=(HashSet&& other) HashSet&
        +~HashSet()

        +empty() bool
        +size() size_t
        +table_size() size_t
        +contains(elem: string) bool
        +insert(elem: string) bool
        +erase(elem: string) bool
        +clear() void

        +print(os: ostream&) void
        +load_from_file(path: string) bool
        +save_to_file(path: string) bool
        +save_to_binary(path: string) bool
        +load_from_binary(path: string) bool

        -hash_func(str: string)$ unsigned long
        -init_buckets(tableSize: size_t) void
        -free_buckets() void
        -copy_from(other: HashSet&) void
    }

    class Node {
        +string val
        +Node* next
    }

    HashSet *-- Node : содержит
```

**Описание:**
- Хеш-множество для хранения уникальных значений
- Быстрая проверка наличия элемента
- Использует метод цепочек для коллизий

---

## 4. LinkedList - Односвязный Список

```mermaid
classDiagram
    class LinkedList {
        -Node* head_
        -Node* tail_
        -size_t size_

        +LinkedList()
        +LinkedList(const LinkedList& other)
        +LinkedList(LinkedList&& other)
        +operator=(const LinkedList& other) LinkedList&
        +operator=(LinkedList&& other) LinkedList&
        +~LinkedList()

        +empty() bool
        +size() size_t
        +front() const string*
        +front() string*
        +back() const string*
        +back() string*
        +at(index: size_t) const string*
        +at(index: size_t) string*

        +push_front(v: string) void
        +push_back(v: string) void
        +pop_front() bool
        +pop_back() bool
        +insert_after(index: size_t, v: string) bool
        +insert_before(index: size_t, v: string) bool
        +erase_after(index: size_t) bool
        +erase_before_tail() bool
        +index_of(x: string) int
        +erase_first(x: string) bool
        +erase_all(x: string) int
        +clear() void

        +print(os: ostream&) void
        +save_to_file(filename: string) bool
        +load_from_file(filename: string) bool
        +save_to_binary(filename: string) bool
        +load_from_binary(filename: string) bool

        -new_node(v: string, next: Node*)$ Node*
        -node_at(index: size_t) Node*
        -copy_from(other: LinkedList&) void
    }

    class Node {
        +string person
        +Node* next
    }

    LinkedList *-- Node : содержит
```

**Описание:**
- Односвязный список с указателями на голову и хвост
- Быстрая вставка в начало O(1)
- Доступ по индексу O(n)

---

## 5. DLinkedList - Двусвязный Список

```mermaid
classDiagram
    class DLinkedList {
        -Node* head_
        -Node* tail_
        -size_t size_

        +DLinkedList()
        +DLinkedList(const DLinkedList& other)
        +DLinkedList(DLinkedList&& other)
        +operator=(const DLinkedList& other) DLinkedList&
        +operator=(DLinkedList&& other) DLinkedList&
        +~DLinkedList()

        +empty() bool
        +size() size_t
        +front() const string*
        +front() string*
        +back() const string*
        +back() string*
        +at(index: size_t) const string*
        +at(index: size_t) string*

        +push_front(v: string) void
        +push_back(v: string) void
        +pop_front() bool
        +pop_back() bool
        +insert_after(index: size_t, v: string) bool
        +insert_before(index: size_t, v: string) bool
        +erase_after(index: size_t) bool
        +erase_before(index: size_t) bool
        +index_of(x: string) int
        +erase_first(x: string) bool
        +erase_all(x: string) int
        +clear() void

        +print(os: ostream&) void
        +save_to_file(filename: string) bool
        +load_from_file(filename: string) bool
        +save_to_binary(filename: string) bool
        +load_from_binary(filename: string) bool

        -new_node(v: string, p: Node*, n: Node*)$ Node*
        -node_at(index: size_t) Node*
        -copy_from(other: DLinkedList&) void
    }

    class Node {
        +string person
        +Node* prev
        +Node* next
    }

    DLinkedList *-- Node : содержит
```

**Описание:**
- Двусвязный список с указателями вперед и назад
- Быстрая вставка/удаление в начале и конце O(1)
- Более гибкое удаление по сравнению с односвязным списком

---

## 6. Queue - Очередь (FIFO)

```mermaid
classDiagram
    class Queue {
        -Node* head_
        -Node* tail_
        -size_t size_

        +Queue()
        +Queue(const Queue& other)
        +Queue(Queue&& other)
        +operator=(const Queue& other) Queue&
        +operator=(Queue&& other) Queue&
        +~Queue()

        +empty() bool
        +size() size_t
        +front() const string*
        +front() string*
        +back() const string*
        +back() string*

        +push(v: string) void
        +pop(out: string*) bool
        +clear() void

        +print(os: ostream&) void
        +save_to_file(filename: string) bool
        +load_from_file(filename: string) bool
        +save_to_binary(filename: string) bool
        +load_from_binary(filename: string) bool

        -new_node(v: string, next: Node*)$ Node*
        -copy_from(other: Queue&) void
    }

    class Node {
        +string person
        +Node* next
    }

    Queue *-- Node : содержит
```

**Описание:**
- FIFO (First In First Out) - первым пришел, первым вышел
- Вставка в конец, удаление из начала
- Все операции O(1)

---

## 7. Stack - Стек (LIFO)

```mermaid
classDiagram
    class Stack {
        -Node* top_
        -size_t size_

        +Stack()
        +Stack(const Stack& other)
        +Stack(Stack&& other)
        +operator=(const Stack& other) Stack&
        +operator=(Stack&& other) Stack&
        +~Stack()

        +empty() bool
        +size() size_t
        +peek() const string*
        +peek() string*

        +push(v: string) void
        +pop(out: string*) bool
        +clear() void

        +print(os: ostream&) void
        +save_to_file(filename: string) bool
        +load_from_file(filename: string) bool
        +save_to_binary(filename: string) bool
        +load_from_binary(filename: string) bool

        -new_node(v: string, next: Node*)$ Node*
        -copy_from(other: Stack&) void
    }

    class Node {
        +string person
        +Node* next
    }

    Stack *-- Node : содержит
```

**Описание:**
- LIFO (Last In First Out) - последним пришел, первым вышел
- Вставка и удаление только с вершины
- Все операции O(1)

---

## Сводная Таблица Сложности Операций

| Структура | Вставка | Поиск | Удаление | Доступ по индексу |
|-----------|---------|-------|----------|-------------------|
| BSTree | O(log n) | O(log n) | O(log n) | - |
| HashMap | O(1) сред. | O(1) сред. | O(1) сред. | - |
| HashSet | O(1) сред. | O(1) сред. | O(1) сред. | - |
| LinkedList | O(1) начало<br>O(n) середина | O(n) | O(1) начало<br>O(n) середина | O(n) |
| DLinkedList | O(1) начало/конец<br>O(n) середина | O(n) | O(1) начало/конец<br>O(n) середина | O(n) |
| Queue | O(1) | - | O(1) | - |
| Stack | O(1) | - | O(1) | - |

---

## Использование

### Как просмотреть диаграммы:

1. **GitHub**: Просто откройте этот файл на GitHub - диаграммы отобразятся автоматически

2. **Mermaid Live Editor**:
   - Перейдите на https://mermaid.live
   - Скопируйте код диаграммы (блок между \`\`\`mermaid и \`\`\`)
   - Вставьте в редактор
   - Скачайте как PNG/SVG

3. **VS Code**:
   - Установите расширение "Markdown Preview Mermaid Support"
   - Откройте этот файл и нажмите Ctrl+Shift+V

4. **Командная строка** (если установлен mermaid-cli):
   ```bash
   npm install -g @mermaid-js/mermaid-cli
   mmdc -i UML_Diagrams.md -o diagrams.png
   ```

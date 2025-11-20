package containers

type doublyNode struct {
	value string
	prev  *doublyNode
	next  *doublyNode
}

type DoublyList struct {
	head *doublyNode
	tail *doublyNode
	size int
}

func NewDoublyList() *DoublyList {
	return &DoublyList{}
}

func (l *DoublyList) Empty() bool {
	return l.size == 0
}

func (l *DoublyList) Size() int {
	return l.size
}

func (l *DoublyList) PushFront(v string) {
	node := &doublyNode{value: v, next: l.head}
	if l.head != nil {
		l.head.prev = node
	}
	l.head = node
	if l.tail == nil {
		l.tail = node
	}
	l.size++
}

func (l *DoublyList) PushBack(v string) {
	node := &doublyNode{value: v, prev: l.tail}
	if l.tail != nil {
		l.tail.next = node
	}
	l.tail = node
	if l.head == nil {
		l.head = node
	}
	l.size++
}

func (l *DoublyList) Front() (string, bool) {
	if l.head == nil {
		return "", false
	}
	return l.head.value, true
}

func (l *DoublyList) Back() (string, bool) {
	if l.tail == nil {
		return "", false
	}
	return l.tail.value, true
}

func (l *DoublyList) PopFront() (string, bool) {
	if l.head == nil {
		return "", false
	}
	v := l.head.value
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	l.size--
	return v, true
}

func (l *DoublyList) PopBack() (string, bool) {
	if l.tail == nil {
		return "", false
	}
	v := l.tail.value
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	l.size--
	return v, true
}

func (l *DoublyList) At(index int) (string, bool) {
	if index < 0 || index >= l.size {
		return "", false
	}
	if index < l.size/2 {
		cur := l.head
		for i := 0; i < index; i++ {
			cur = cur.next
		}
		return cur.value, true
	}
	cur := l.tail
	for i := l.size - 1; i > index; i-- {
		cur = cur.prev
	}
	return cur.value, true
}

func (l *DoublyList) InsertAt(index int, v string) bool {
	if index < 0 || index > l.size {
		return false
	}
	if index == 0 {
		l.PushFront(v)
		return true
	}
	if index == l.size {
		l.PushBack(v)
		return true
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	node := &doublyNode{value: v}
	prev := cur.prev

	node.prev = prev
	node.next = cur
	prev.next = node
	cur.prev = node

	l.size++
	return true
}

func (l *DoublyList) RemoveAt(index int) (string, bool) {
	if index < 0 || index >= l.size {
		return "", false
	}
	if index == 0 {
		return l.PopFront()
	}
	if index == l.size-1 {
		return l.PopBack()
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	prev := cur.prev
	next := cur.next

	prev.next = next
	next.prev = prev

	l.size--
	return cur.value, true
}

func (l *DoublyList) IndexOf(v string) int {
	cur := l.head
	idx := 0
	for cur != nil {
		if cur.value == v {
			return idx
		}
		cur = cur.next
		idx++
	}
	return -1
}

func (l *DoublyList) ToSlice() []string {
	res := make([]string, 0, l.size)
	cur := l.head
	for cur != nil {
		res = append(res, cur.value)
		cur = cur.next
	}
	return res
}

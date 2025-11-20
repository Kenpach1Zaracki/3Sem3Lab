package containers

type singlyNode struct {
	value string
	next  *singlyNode
}

type SinglyList struct {
	head *singlyNode
	tail *singlyNode
	size int
}

func NewSinglyList() *SinglyList {
	return &SinglyList{}
}

func (l *SinglyList) Empty() bool {
	return l.size == 0
}

func (l *SinglyList) Size() int {
	return l.size
}

func (l *SinglyList) PushFront(v string) {
	node := &singlyNode{value: v, next: l.head}
	l.head = node
	if l.tail == nil {
		l.tail = node
	}
	l.size++
}

func (l *SinglyList) PushBack(v string) {
	node := &singlyNode{value: v}
	if l.tail == nil {
		l.head = node
		l.tail = node
	} else {
		l.tail.next = node
		l.tail = node
	}
	l.size++
}

func (l *SinglyList) Front() (string, bool) {
	if l.head == nil {
		return "", false
	}
	return l.head.value, true
}

func (l *SinglyList) Back() (string, bool) {
	if l.tail == nil {
		return "", false
	}
	return l.tail.value, true
}

func (l *SinglyList) PopFront() (string, bool) {
	if l.head == nil {
		return "", false
	}
	v := l.head.value
	l.head = l.head.next
	if l.head == nil {
		l.tail = nil
	}
	l.size--
	return v, true
}

func (l *SinglyList) PopBack() (string, bool) {
	if l.tail == nil {
		return "", false
	}
	if l.head == l.tail {
		v := l.tail.value
		l.head = nil
		l.tail = nil
		l.size = 0
		return v, true
	}
	prev := l.head
	for prev.next != nil && prev.next != l.tail {
		prev = prev.next
	}
	v := l.tail.value
	prev.next = nil
	l.tail = prev
	l.size--
	return v, true
}

func (l *SinglyList) At(index int) (string, bool) {
	if index < 0 || index >= l.size {
		return "", false
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	return cur.value, true
}

func (l *SinglyList) InsertAt(index int, v string) bool {
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
	prev := l.head
	for i := 0; i < index-1; i++ {
		prev = prev.next
	}
	node := &singlyNode{value: v, next: prev.next}
	prev.next = node
	l.size++
	return true
}

func (l *SinglyList) RemoveAt(index int) (string, bool) {
	if index < 0 || index >= l.size {
		return "", false
	}
	if index == 0 {
		return l.PopFront()
	}
	prev := l.head
	for i := 0; i < index-1; i++ {
		prev = prev.next
	}
	target := prev.next
	prev.next = target.next
	if target == l.tail {
		l.tail = prev
	}
	l.size--
	return target.value, true
}

func (l *SinglyList) IndexOf(v string) int {
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

func (l *SinglyList) ToSlice() []string {
	res := make([]string, 0, l.size)
	cur := l.head
	for cur != nil {
		res = append(res, cur.value)
		cur = cur.next
	}
	return res
}

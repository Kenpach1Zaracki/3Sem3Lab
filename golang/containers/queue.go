package containers

type Queue struct {
	data []string
	head int
}

func NewQueue() *Queue {
	return &Queue{
		data: make([]string, 0),
		head: 0,
	}
}

func (q *Queue) Push(v string) {
	q.data = append(q.data, v)
}

func (q *Queue) Pop() (value string, ok bool) {
	if q.Empty() {
		return "", false
	}
	v := q.data[q.head]
	q.head++

	if q.head > 0 && q.head*2 >= len(q.data) {
		q.data = append([]string(nil), q.data[q.head:]...)
		q.head = 0
	}
	return v, true
}

func (q *Queue) Front() (value string, ok bool) {
	if q.Empty() {
		return "", false
	}
	return q.data[q.head], true
}

func (q *Queue) Back() (value string, ok bool) {
	if q.Empty() {
		return "", false
	}
	return q.data[len(q.data)-1], true
}

func (q *Queue) Size() int {
	return len(q.data) - q.head
}

func (q *Queue) Empty() bool {
	return q.Size() == 0
}

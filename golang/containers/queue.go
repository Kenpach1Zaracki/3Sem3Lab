package containers

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

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

func (q *Queue) toSlice() []string {
	if q.Empty() {
		return []string{}
	}
	return q.data[q.head:]
}

func (q *Queue) SaveToBinary(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	data := q.toSlice()
	enc := gob.NewEncoder(f)
	return enc.Encode(data)
}

func (q *Queue) LoadFromBinary(filename string) error {
	f, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	dec := gob.NewDecoder(f)
	var data []string
	if err := dec.Decode(&data); err != nil {
		return err
	}

	q.data = data
	q.head = 0
	return nil
}

func (q *Queue) SaveToText(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	data := q.toSlice()
	enc := json.NewEncoder(f)
	return enc.Encode(data)
}

func (q *Queue) LoadFromText(filename string) error {
	f, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	dec := json.NewDecoder(f)
	var data []string
	if err := dec.Decode(&data); err != nil {
		return err
	}

	q.data = data
	q.head = 0
	return nil
}

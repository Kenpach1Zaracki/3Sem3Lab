package containers

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

type Array struct {
	data []string
}

func NewArray() *Array {
	return &Array{
		data: make([]string, 0),
	}
}

func NewArrayWithCapacity(capacity int) *Array {
	if capacity < 0 {
		capacity = 0
	}
	return &Array{
		data: make([]string, 0, capacity),
	}
}

func (a *Array) Len() int {
	return len(a.data)
}

func (a *Array) Cap() int {
	return cap(a.data)
}

func (a *Array) Empty() bool {
	return len(a.data) == 0
}

func (a *Array) Get(index int) (string, bool) {
	if index < 0 || index >= len(a.data) {
		return "", false
	}
	return a.data[index], true
}

func (a *Array) Set(index int, v string) bool {
	if index < 0 || index >= len(a.data) {
		return false
	}
	a.data[index] = v
	return true
}

func (a *Array) PushBack(v string) {
	a.data = append(a.data, v)
}

func (a *Array) InsertAt(index int, v string) bool {
	if index < 0 || index > len(a.data) {
		return false
	}
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = v
	return true
}

func (a *Array) RemoveAt(index int) (string, bool) {
	if index < 0 || index >= len(a.data) {
		return "", false
	}
	v := a.data[index]
	copy(a.data[index:], a.data[index+1:])
	a.data = a.data[:len(a.data)-1]
	return v, true
}

func (a *Array) Clear() {
	a.data = a.data[:0]
}

func (a *Array) ToSlice() []string {
	res := make([]string, len(a.data))
	copy(res, a.data)
	return res
}

func (a *Array) SaveToBinary(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	enc := gob.NewEncoder(f)
	return enc.Encode(a.data)
}

func (a *Array) LoadFromBinary(filename string) error {
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
	a.data = data
	return nil
}

func (a *Array) SaveToText(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	enc := json.NewEncoder(f)
	return enc.Encode(a.data)
}

func (a *Array) LoadFromText(filename string) error {
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
	a.data = data
	return nil
}

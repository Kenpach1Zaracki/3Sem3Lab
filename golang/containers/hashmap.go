package containers

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

type hashEntry struct {
	key   string
	value string
}

type HashMap struct {
	buckets [][]hashEntry
	size    int
}

const defaultBucketCount = 16

func NewHashMap() *HashMap {
	return &HashMap{
		buckets: make([][]hashEntry, defaultBucketCount),
		size:    0,
	}
}

func (m *HashMap) Empty() bool {
	return m.size == 0
}

func (m *HashMap) Size() int {
	return m.size
}

func (m *HashMap) bucketCount() int {
	return len(m.buckets)
}

func hashString(s string) uint64 {
	var h uint64 = 5381
	for i := 0; i < len(s); i++ {
		h = ((h << 5) + h) + uint64(s[i])
	}
	return h
}

func (m *HashMap) indexFor(key string) int {
	h := hashString(key)
	return int(h % uint64(len(m.buckets)))
}

func (m *HashMap) Set(key, value string) {
	if key == "" {
	}
	if m.size > 0 && float64(m.size)/float64(len(m.buckets)) > 0.75 {
		m.rehash(len(m.buckets) * 2)
	}

	idx := m.indexFor(key)
	bucket := m.buckets[idx]

	for i := range bucket {
		if bucket[i].key == key {
			bucket[i].value = value
			m.buckets[idx] = bucket
			return
		}
	}

	bucket = append(bucket, hashEntry{key: key, value: value})
	m.buckets[idx] = bucket
	m.size++
}

func (m *HashMap) Get(key string) (string, bool) {
	idx := m.indexFor(key)
	bucket := m.buckets[idx]
	for i := range bucket {
		if bucket[i].key == key {
			return bucket[i].value, true
		}
	}
	return "", false
}

func (m *HashMap) Contains(key string) bool {
	_, ok := m.Get(key)
	return ok
}

func (m *HashMap) Delete(key string) bool {
	idx := m.indexFor(key)
	bucket := m.buckets[idx]
	for i := range bucket {
		if bucket[i].key == key {
			// удаляем из среза
			last := len(bucket) - 1
			bucket[i] = bucket[last]
			bucket = bucket[:last]
			m.buckets[idx] = bucket
			m.size--
			return true
		}
	}
	return false
}

func (m *HashMap) Clear() {
	m.buckets = make([][]hashEntry, defaultBucketCount)
	m.size = 0
}

func (m *HashMap) rehash(newBucketCount int) {
	if newBucketCount < 1 {
		return
	}
	oldBuckets := m.buckets
	m.buckets = make([][]hashEntry, newBucketCount)
	m.size = 0

	for _, bucket := range oldBuckets {
		for _, e := range bucket {
			m.Set(e.key, e.value)
		}
	}
}

func (m *HashMap) Keys() []string {
	res := make([]string, 0, m.size)
	for _, bucket := range m.buckets {
		for _, e := range bucket {
			res = append(res, e.key)
		}
	}
	return res
}

func (m *HashMap) toMap() map[string]string {
	res := make(map[string]string, m.size)
	for _, bucket := range m.buckets {
		for _, e := range bucket {
			res[e.key] = e.value
		}
	}
	return res
}

func (m *HashMap) SaveToBinary(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	data := m.toMap()
	enc := gob.NewEncoder(f)
	return enc.Encode(data)
}

func (m *HashMap) LoadFromBinary(filename string) error {
	f, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	dec := gob.NewDecoder(f)
	var data map[string]string
	if err := dec.Decode(&data); err != nil {
		return err
	}

	m.Clear()
	for k, v := range data {
		m.Set(k, v)
	}
	return nil
}

func (m *HashMap) SaveToText(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	data := m.toMap()
	enc := json.NewEncoder(f)
	return enc.Encode(data)
}

func (m *HashMap) LoadFromText(filename string) error {
	f, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	dec := json.NewDecoder(f)
	var data map[string]string
	if err := dec.Decode(&data); err != nil {
		return err
	}

	m.Clear()
	for k, v := range data {
		m.Set(k, v)
	}
	return nil
}

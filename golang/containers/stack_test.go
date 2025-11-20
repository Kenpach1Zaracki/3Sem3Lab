package containers

import "testing"

func TestStackBasic(t *testing.T) {
	s := NewStack()
	if !s.Empty() {
		t.Fatalf("новый стек должен быть пустым")
	}
	if s.Size() != 0 {
		t.Fatalf("размер нового стека должен быть 0, получено %d", s.Size())
	}

	s.Push("a")
	s.Push("b")
	s.Push("c")

	if s.Size() != 3 {
		t.Fatalf("размер стека должен быть 3, получено %d", s.Size())
	}

	if top, ok := s.Peek(); !ok || top != "c" {
		t.Fatalf("peek должен вернуть 'c', получено %q, ok=%v", top, ok)
	}

	if v, ok := s.Pop(); !ok || v != "c" {
		t.Fatalf("первый pop должен вернуть 'c', получено %q, ok=%v", v, ok)
	}
	if v, ok := s.Pop(); !ok || v != "b" {
		t.Fatalf("второй pop должен вернуть 'b', получено %q, ok=%v", v, ok)
	}
	if v, ok := s.Pop(); !ok || v != "a" {
		t.Fatalf("третий pop должен вернуть 'a', получено %q, ok=%v", v, ok)
	}

	if !s.Empty() {
		t.Fatalf("после трёх pop стек должен быть пустым")
	}
	if _, ok := s.Pop(); ok {
		t.Fatalf("pop из пустого стека должен возвращать ok=false")
	}
}

func TestStackPeekOnEmpty(t *testing.T) {
	s := NewStack()
	if _, ok := s.Peek(); ok {
		t.Fatalf("peek для пустого стека должен возвращать ok=false")
	}
}

func BenchmarkStackPushPop(b *testing.B) {
	for i := 0; i < b.N; i++ {
		s := NewStack()
		for j := 0; j < 1000; j++ {
			s.Push("value")
		}
		for !s.Empty() {
			s.Pop()
		}
	}
}

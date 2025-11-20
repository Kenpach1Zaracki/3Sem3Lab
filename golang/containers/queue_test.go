package containers

import "testing"

func TestQueueBasic(t *testing.T) {
	q := NewQueue()
	if !q.Empty() {
		t.Fatalf("новая очередь должна быть пустой")
	}
	if q.Size() != 0 {
		t.Fatalf("размер новой очереди должен быть 0, получено %d", q.Size())
	}

	q.Push("a")
	q.Push("b")
	q.Push("c")

	if q.Empty() {
		t.Fatalf("очередь не должна быть пустой после добавления элементов")
	}
	if q.Size() != 3 {
		t.Fatalf("размер очереди должен быть 3, получено %d", q.Size())
	}

	if v, ok := q.Front(); !ok || v != "a" {
		t.Fatalf("Front должен вернуть 'a', получено %q, ok=%v", v, ok)
	}
	if v, ok := q.Back(); !ok || v != "c" {
		t.Fatalf("Back должен вернуть 'c', получено %q, ok=%v", v, ok)
	}

	if v, ok := q.Pop(); !ok || v != "a" {
		t.Fatalf("первый Pop должен вернуть 'a', получено %q, ok=%v", v, ok)
	}
	if v, ok := q.Pop(); !ok || v != "b" {
		t.Fatalf("второй Pop должен вернуть 'b', получено %q, ok=%v", v, ok)
	}
	if v, ok := q.Pop(); !ok || v != "c" {
		t.Fatalf("третий Pop должен вернуть 'c', получено %q, ok=%v", v, ok)
	}
	if !q.Empty() {
		t.Fatalf("после трёх Pop очередь должна быть пустой")
	}
	if _, ok := q.Pop(); ok {
		t.Fatalf("Pop из пустой очереди должен возвращать ok=false")
	}
}

func TestQueueFrontBackOnEmpty(t *testing.T) {
	q := NewQueue()
	if _, ok := q.Front(); ok {
		t.Fatalf("Front для пустой очереди должен возвращать ok=false")
	}
	if _, ok := q.Back(); ok {
		t.Fatalf("Back для пустой очереди должен возвращать ok=false")
	}
}

func TestQueueInternalCompaction(t *testing.T) {
	q := NewQueue()
	for i := 0; i < 10; i++ {
		q.Push("x")
	}
	for i := 0; i < 7; i++ {
		if _, ok := q.Pop(); !ok {
			t.Fatalf("Pop %d должен проходить успешно", i)
		}
	}
	if q.Size() != 3 {
		t.Fatalf("после Pop размер очереди должен быть 3, получено %d", q.Size())
	}
	q.Push("y")
	if q.Size() != 4 {
		t.Fatalf("после дополнительного Push размер должен быть 4, получено %d", q.Size())
	}
}

func BenchmarkQueuePushPop(b *testing.B) {
	for i := 0; i < b.N; i++ {
		q := NewQueue()
		for j := 0; j < 1000; j++ {
			q.Push("value")
		}
		for !q.Empty() {
			q.Pop()
		}
	}
}

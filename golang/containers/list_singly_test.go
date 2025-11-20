package containers

import "testing"

func TestSinglyListBasic(t *testing.T) {
	l := NewSinglyList()
	if !l.Empty() {
		t.Fatalf("новый список должен быть пустым")
	}
	if l.Size() != 0 {
		t.Fatalf("size нового списка = %d, ожидалось 0", l.Size())
	}

	l.PushBack("b")
	l.PushFront("a")
	l.PushBack("c")

	if l.Empty() {
		t.Fatalf("список не должен быть пустым после вставок")
	}
	if l.Size() != 3 {
		t.Fatalf("ожидалось size=3, получили %d", l.Size())
	}

	if v, ok := l.Front(); !ok || v != "a" {
		t.Fatalf("Front должен быть 'a', получили %q, ok=%v", v, ok)
	}
	if v, ok := l.Back(); !ok || v != "c" {
		t.Fatalf("Back должен быть 'c', получили %q, ok=%v", v, ok)
	}

	if v, ok := l.At(1); !ok || v != "b" {
		t.Fatalf("At(1) должен быть 'b', получили %q, ok=%v", v, ok)
	}
	if _, ok := l.At(10); ok {
		t.Fatalf("At(10) для выхода за границы должен возвращать ok=false")
	}
}

func TestSinglyListInsertRemove(t *testing.T) {
	l := NewSinglyList()
	l.PushBack("a") // 0
	l.PushBack("c") // 1

	if !l.InsertAt(1, "b") { // a b c
		t.Fatalf("InsertAt(1) должен вернуть true")
	}
	if l.Size() != 3 {
		t.Fatalf("size должен быть 3, получили %d", l.Size())
	}
	if v, ok := l.At(1); !ok || v != "b" {
		t.Fatalf("после вставки элемент с индексом 1 должен быть 'b', получили %q", v)
	}

	if ok := l.InsertAt(0, "start"); !ok {
		t.Fatalf("InsertAt(0) должен вернуть true")
	}
	if v, ok := l.At(0); !ok || v != "start" {
		t.Fatalf("после InsertAt(0) первый элемент должен быть 'start', получили %q", v)
	}

	if ok := l.InsertAt(l.Size(), "end"); !ok {
		t.Fatalf("InsertAt(size) должен вернуть true")
	}
	if v, ok := l.Back(); !ok || v != "end" {
		t.Fatalf("последний элемент должен быть 'end', получили %q", v)
	}

	if ok := l.InsertAt(-1, "x"); ok {
		t.Fatalf("InsertAt(-1) должен вернуть false")
	}
	if ok := l.InsertAt(100, "y"); ok {
		t.Fatalf("InsertAt(100) должен вернуть false")
	}

	v, ok := l.RemoveAt(0)
	if !ok || v != "start" {
		t.Fatalf("RemoveAt(0) должен удалить 'start', получили %q, ok=%v", v, ok)
	}

	v, ok = l.RemoveAt(l.Size() - 1)
	if !ok || v != "end" {
		t.Fatalf("RemoveAt(last) должен удалить 'end', получили %q, ok=%v", v, ok)
	}

	idxB := l.IndexOf("b")
	if idxB == -1 {
		t.Fatalf("b должен присутствовать в списке")
	}
	v, ok = l.RemoveAt(idxB)
	if !ok || v != "b" {
		t.Fatalf("RemoveAt(indexOf(b)) должен удалить 'b', получили %q, ok=%v", v, ok)
	}
	if l.IndexOf("b") != -1 {
		t.Fatalf("после удаления 'b' не должен находиться в списке")
	}

	if _, ok := l.RemoveAt(100); ok {
		t.Fatalf("RemoveAt(100) должен вернуть ok=false")
	}
}

func TestSinglyListIndexOfAndToSlice(t *testing.T) {
	l := NewSinglyList()
	l.PushBack("x")
	l.PushBack("y")
	l.PushBack("z")
	l.PushBack("y")

	if idx := l.IndexOf("y"); idx != 1 {
		t.Fatalf("IndexOf('y') должен быть 1, получили %d", idx)
	}
	if idx := l.IndexOf("nope"); idx != -1 {
		t.Fatalf("IndexOf('nope') должен быть -1, получили %d", idx)
	}

	slice := l.ToSlice()
	if len(slice) != l.Size() {
		t.Fatalf("len(ToSlice()) должен совпадать с Size(), получили %d и %d", len(slice), l.Size())
	}
	if slice[0] != "x" || slice[1] != "y" || slice[2] != "z" || slice[3] != "y" {
		t.Fatalf("ожидался срез [x y z y], получили %#v", slice)
	}
}

func BenchmarkSinglyListPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		l := NewSinglyList()
		for j := 0; j < 1000; j++ {
			l.PushBack("value")
		}
	}
}
func TestSinglyListPopSingleElement(t *testing.T) {
	l := NewSinglyList()

	l.PushBack("one")
	v, ok := l.PopFront()
	if !ok || v != "one" {
		t.Fatalf("PopFront для списка из одного элемента должен вернуть 'one', получено %q, ok=%v", v, ok)
	}
	if !l.Empty() || l.Size() != 0 {
		t.Fatalf("после PopFront список должен быть пустым, size=%d", l.Size())
	}

	l.PushBack("only")
	v, ok = l.PopBack()
	if !ok || v != "only" {
		t.Fatalf("PopBack для списка из одного элемента должен вернуть 'only', получено %q, ok=%v", v, ok)
	}
	if !l.Empty() || l.Size() != 0 {
		t.Fatalf("после PopBack список должен быть пустым, size=%d", l.Size())
	}
}

func TestSinglyListEdgeCases(t *testing.T) {
	l := NewSinglyList()

	if idx := l.IndexOf("x"); idx != -1 {
		t.Fatalf("IndexOf по пустому списку должен возвращать -1, получили %d", idx)
	}

	if _, ok := l.At(-1); ok {
		t.Fatalf("At(-1) должен вернуть ok=false")
	}

	l.PushBack("elem")
	v, ok := l.RemoveAt(0)
	if !ok || v != "elem" {
		t.Fatalf("RemoveAt(0) для одноэлементного списка должен вернуть 'elem', получено %q, ok=%v", v, ok)
	}
	if !l.Empty() || l.Size() != 0 {
		t.Fatalf("после RemoveAt(0) список должен быть пустым, size=%d", l.Size())
	}
}

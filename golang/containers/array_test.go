package containers

import "testing"

func TestArrayBasic(t *testing.T) {
	a := NewArray()
	if !a.Empty() {
		t.Fatalf("новый массив должен быть пустым")
	}
	if a.Len() != 0 {
		t.Fatalf("Len нового массива = %d, ожидалось 0", a.Len())
	}

	a.PushBack("a")
	a.PushBack("b")
	a.PushBack("c")

	if a.Empty() {
		t.Fatalf("массив не должен быть пустым после вставок")
	}
	if a.Len() != 3 {
		t.Fatalf("ожидалось Len=3, получили %d", a.Len())
	}

	if v, ok := a.Get(0); !ok || v != "a" {
		t.Fatalf("Get(0) должен вернуть 'a', получили %q, ok=%v", v, ok)
	}
	if v, ok := a.Get(2); !ok || v != "c" {
		t.Fatalf("Get(2) должен вернуть 'c', получили %q, ok=%v", v, ok)
	}
	if _, ok := a.Get(10); ok {
		t.Fatalf("Get(10) должен вернуть ok=false (выход за границы)")
	}
}

func TestArraySetInsertRemove(t *testing.T) {
	a := NewArrayWithCapacity(4)
	a.PushBack("a") // 0
	a.PushBack("c") // 1

	if !a.Set(1, "x") {
		t.Fatalf("Set(1, 'x') должен вернуть true")
	}
	if v, ok := a.Get(1); !ok || v != "x" {
		t.Fatalf("после Set(1) значение должно быть 'x', получили %q", v)
	}
	if ok := a.Set(10, "no"); ok {
		t.Fatalf("Set(10) должен вернуть false")
	}

	// вставка в середину
	if !a.InsertAt(1, "b") {
		t.Fatalf("InsertAt(1) должен вернуть true")
	}
	if a.Len() != 3 {
		t.Fatalf("длина должна быть 3, получили %d", a.Len())
	}
	if s := a.ToSlice(); s[0] != "a" || s[1] != "b" || s[2] != "x" {
		t.Fatalf("после InsertAt(1) ожидали [a b x], получили %#v", s)
	}

	// вставка в конец
	if !a.InsertAt(a.Len(), "end") {
		t.Fatalf("InsertAt(Len) должен вернуть true")
	}
	if v, ok := a.Get(a.Len() - 1); !ok || v != "end" {
		t.Fatalf("последний элемент должен быть 'end', получили %q", v)
	}

	// некорректные вставки
	if ok := a.InsertAt(-1, "no"); ok {
		t.Fatalf("InsertAt(-1) должен вернуть false")
	}
	if ok := a.InsertAt(100, "no"); ok {
		t.Fatalf("InsertAt(100) должен вернуть false")
	}

	// удаление по индексу
	v, ok := a.RemoveAt(1)
	if !ok || v != "b" {
		t.Fatalf("RemoveAt(1) должен удалить 'b', получили %q, ok=%v", v, ok)
	}

	if _, ok := a.RemoveAt(100); ok {
		t.Fatalf("RemoveAt(100) должен вернуть ok=false")
	}
}

func TestArrayClearAndToSlice(t *testing.T) {
	a := NewArray()
	a.PushBack("x")
	a.PushBack("y")
	a.PushBack("z")

	s := a.ToSlice()
	if len(s) != 3 || s[0] != "x" || s[1] != "y" || s[2] != "z" {
		t.Fatalf("ToSlice должен вернуть [x y z], получили %#v", s)
	}

	a.Clear()
	if !a.Empty() || a.Len() != 0 {
		t.Fatalf("после Clear массив должен быть пустым")
	}
}

func BenchmarkArrayPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := NewArrayWithCapacity(1000)
		for j := 0; j < 1000; j++ {
			a.PushBack("value")
		}
	}
}

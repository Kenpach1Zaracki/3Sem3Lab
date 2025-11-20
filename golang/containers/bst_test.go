package containers

import "testing"

func TestBSTEmpty(t *testing.T) {
	t1 := NewBST()
	if !t1.Empty() {
		t.Fatalf("новое дерево должно быть пустым")
	}
	if t1.Size() != 0 {
		t.Fatalf("Size нового дерева = %d, ожидалось 0", t1.Size())
	}
	if _, ok := t1.Min(); ok {
		t.Fatalf("Min для пустого дерева должен возвращать ok=false")
	}
	if _, ok := t1.Max(); ok {
		t.Fatalf("Max для пустого дерева должен возвращать ok=false")
	}
	if h := t1.Height(); h != 0 {
		t.Fatalf("Height пустого дерева должен быть 0, получили %d", h)
	}
}

func TestBSTInsertAndContains(t *testing.T) {
	t1 := NewBST()
	values := []string{"b", "a", "c", "d", "e"}
	for _, v := range values {
		if !t1.Insert(v) {
			t.Fatalf("Insert('%s') должен вернуть true при первой вставке", v)
		}
	}
	if t1.Insert("b") {
		t.Fatalf("повторный Insert('b') должен вернуть false (дубликат)")
	}

	if t1.Size() != len(values) {
		t.Fatalf("Size должен быть %d, получили %d", len(values), t1.Size())
	}

	for _, v := range values {
		if !t1.Contains(v) {
			t.Fatalf("Contains('%s') должен быть true", v)
		}
	}
	if t1.Contains("nope") {
		t.Fatalf("Contains('nope') должен быть false")
	}

	min, ok := t1.Min()
	if !ok || min != "a" {
		t.Fatalf("Min должен быть 'a', получили %q, ok=%v", min, ok)
	}
	max, ok := t1.Max()
	if !ok || max != "e" {
		t.Fatalf("Max должен быть 'e', получили %q, ok=%v", max, ok)
	}

	if t1.Height() < 2 {
		t.Fatalf("высота дерева с несколькими элементами должна быть >=2, получили %d", t1.Height())
	}

	inOrder := t1.InOrder()
	expected := []string{"a", "b", "c", "d", "e"}
	if len(inOrder) != len(expected) {
		t.Fatalf("длина InOrder должна быть %d, получили %d", len(expected), len(inOrder))
	}
	for i, v := range expected {
		if inOrder[i] != v {
			t.Fatalf("InOrder[%d] = %q, ожидалось %q", i, inOrder[i], v)
		}
	}
}

func TestBSTDeleteCases(t *testing.T) {
	t1 := NewBST()
	for _, v := range []string{"d", "b", "f", "a", "c", "e", "g"} {
		t1.Insert(v)
	}

	if !t1.Delete("a") {
		t.Fatalf("Delete('a') должен вернуть true")
	}
	if t1.Contains("a") {
		t.Fatalf("после Delete('a') значение не должно содержаться в дереве")
	}

	if !t1.Delete("b") {
		t.Fatalf("Delete('b') должен вернуть true")
	}
	if t1.Contains("b") {
		t.Fatalf("после Delete('b') значение не должно содержаться в дереве")
	}

	if !t1.Delete("d") {
		t.Fatalf("Delete('d') должен вернуть true")
	}
	if t1.Contains("d") {
		t.Fatalf("после Delete('d') значение не должно содержаться в дереве")
	}

	if t1.Delete("nope") {
		t.Fatalf("Delete('nope') должен вернуть false (узла нет)")
	}

	inOrder := t1.InOrder()
	expected := []string{"c", "e", "f", "g"}
	if len(inOrder) != len(expected) {
		t.Fatalf("после удалений длина InOrder должна быть %d, получили %d", len(expected), len(inOrder))
	}
	for i, v := range expected {
		if inOrder[i] != v {
			t.Fatalf("после удалений InOrder[%d] = %q, ожидалось %q", i, inOrder[i], v)
		}
	}
}

func BenchmarkBSTInsert(b *testing.B) {
	for i := 0; i < b.N; i++ {
		t1 := NewBST()
		for j := 0; j < 1000; j++ {
			t1.Insert(string(rune('A' + (j % 26))))
		}
	}
}

func BenchmarkBSTContains(b *testing.B) {
	t1 := NewBST()
	for j := 0; j < 1000; j++ {
		t1.Insert(string(rune('A' + (j % 26))))
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = t1.Contains("A")
		_ = t1.Contains("Z")
		_ = t1.Contains("nope")
	}
}

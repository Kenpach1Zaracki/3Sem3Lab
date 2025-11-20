package containers

import "testing"

func TestHashMapBasic(t *testing.T) {
	m := NewHashMap()
	if !m.Empty() {
		t.Fatalf("новая HashMap должна быть пустой")
	}
	if m.Size() != 0 {
		t.Fatalf("Size новой HashMap = %d, ожидалось 0", m.Size())
	}

	m.Set("a", "1")
	m.Set("b", "2")
	m.Set("c", "3")

	if m.Empty() {
		t.Fatalf("после вставок HashMap не должна быть пустой")
	}
	if m.Size() != 3 {
		t.Fatalf("ожидалось Size=3, получили %d", m.Size())
	}

	if v, ok := m.Get("a"); !ok || v != "1" {
		t.Fatalf("Get('a') должно дать '1', получили %q, ok=%v", v, ok)
	}
	if v, ok := m.Get("c"); !ok || v != "3" {
		t.Fatalf("Get('c') должно дать '3', получили %q, ok=%v", v, ok)
	}
	if _, ok := m.Get("nope"); ok {
		t.Fatalf("Get('nope') должно вернуть ok=false")
	}

	if !m.Contains("b") {
		t.Fatalf("Contains('b') должно быть true")
	}
	if m.Contains("nope") {
		t.Fatalf("Contains('nope') должно быть false")
	}
}

func TestHashMapOverwriteAndDelete(t *testing.T) {
	m := NewHashMap()

	m.Set("key", "v1")
	if v, ok := m.Get("key"); !ok || v != "v1" {
		t.Fatalf("Get после первой вставки должно дать 'v1', получили %q, ok=%v", v, ok)
	}

	m.Set("key", "v2")
	if v, ok := m.Get("key"); !ok || v != "v2" {
		t.Fatalf("Get после перезаписи должно дать 'v2', получили %q, ok=%v", v, ok)
	}

	if !m.Delete("key") {
		t.Fatalf("Delete('key') должно вернуть true")
	}
	if m.Contains("key") {
		t.Fatalf("после Delete ключ не должен содержаться в HashMap")
	}
	if m.Delete("key") {
		t.Fatalf("повторный Delete('key') должен вернуть false")
	}
}

func TestHashMapRehash(t *testing.T) {
	m := NewHashMap()

	for i := 0; i < 100; i++ {
		m.Set(
			"key"+string(rune('A'+(i%26))),
			"value",
		)
	}

	if m.Size() == 0 {
		t.Fatalf("после вставок размер не должен быть 0")
	}

	m.Set("special", "42")
	if v, ok := m.Get("special"); !ok || v != "42" {
		t.Fatalf("после rehash Get('special') должно дать '42', получили %q, ok=%v", v, ok)
	}
}

func TestHashMapClearAndKeys(t *testing.T) {
	m := NewHashMap()
	m.Set("a", "1")
	m.Set("b", "2")
	m.Set("c", "3")

	keys := m.Keys()
	if len(keys) != m.Size() {
		t.Fatalf("len(Keys()) должен совпадать с Size(), получили %d и %d", len(keys), m.Size())
	}

	m.Clear()
	if !m.Empty() || m.Size() != 0 {
		t.Fatalf("после Clear HashMap должна быть пустой")
	}
	if len(m.Keys()) != 0 {
		t.Fatalf("после Clear Keys() должен быть пустым")
	}
}

func BenchmarkHashMapSet(b *testing.B) {
	for i := 0; i < b.N; i++ {
		m := NewHashMap()
		for j := 0; j < 1000; j++ {
			m.Set("key"+string(rune('A'+(j%26))), "value")
		}
	}
}

func BenchmarkHashMapGet(b *testing.B) {
	m := NewHashMap()
	for j := 0; j < 1000; j++ {
		m.Set("key"+string(rune('A'+(j%26))), "value")
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_, _ = m.Get("keyA")
		_, _ = m.Get("keyZ")
		_, _ = m.Get("nope")
	}
}

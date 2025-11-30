package containers

import (
	"encoding/gob"
	"encoding/json"
	"os"
)

type bstNode struct {
	value string
	left  *bstNode
	right *bstNode
}

type BST struct {
	root *bstNode
	size int
}

func NewBST() *BST {
	return &BST{}
}

func (t *BST) Empty() bool {
	return t.size == 0
}

func (t *BST) Size() int {
	return t.size
}

func (t *BST) Insert(v string) bool {
	inserted := false
	t.root, inserted = bstInsert(t.root, v)
	if inserted {
		t.size++
	}
	return inserted
}

func bstInsert(node *bstNode, v string) (*bstNode, bool) {
	if node == nil {
		return &bstNode{value: v}, true
	}
	if v == node.value {
		return node, false
	}
	if v < node.value {
		var inserted bool
		node.left, inserted = bstInsert(node.left, v)
		return node, inserted
	} else {
		var inserted bool
		node.right, inserted = bstInsert(node.right, v)
		return node, inserted
	}
}

func (t *BST) Contains(v string) bool {
	cur := t.root
	for cur != nil {
		if v == cur.value {
			return true
		}
		if v < cur.value {
			cur = cur.left
		} else {
			cur = cur.right
		}
	}
	return false
}

func (t *BST) Min() (string, bool) {
	if t.root == nil {
		return "", false
	}
	cur := t.root
	for cur.left != nil {
		cur = cur.left
	}
	return cur.value, true
}

func (t *BST) Max() (string, bool) {
	if t.root == nil {
		return "", false
	}
	cur := t.root
	for cur.right != nil {
		cur = cur.right
	}
	return cur.value, true
}

func (t *BST) Height() int {
	return bstHeight(t.root)
}

func bstHeight(node *bstNode) int {
	if node == nil {
		return 0
	}
	lh := bstHeight(node.left)
	rh := bstHeight(node.right)
	if lh > rh {
		return lh + 1
	}
	return rh + 1
}

func (t *BST) Delete(v string) bool {
	deleted := false
	t.root, deleted = bstDelete(t.root, v)
	if deleted {
		t.size--
	}
	return deleted
}

func bstDelete(node *bstNode, v string) (*bstNode, bool) {
	if node == nil {
		return nil, false
	}
	if v < node.value {
		var deleted bool
		node.left, deleted = bstDelete(node.left, v)
		return node, deleted
	}
	if v > node.value {
		var deleted bool
		node.right, deleted = bstDelete(node.right, v)
		return node, deleted
	}
	if node.left == nil && node.right == nil {
		return nil, true
	}
	if node.left == nil {
		return node.right, true
	}
	if node.right == nil {
		return node.left, true
	}
	successor := node.right
	for successor.left != nil {
		successor = successor.left
	}
	node.value = successor.value
	var deleted bool
	node.right, deleted = bstDelete(node.right, successor.value)
	return node, deleted
}

func (t *BST) InOrder() []string {
	res := make([]string, 0, t.size)
	bstInOrder(t.root, &res)
	return res
}

func bstInOrder(node *bstNode, out *[]string) {
	if node == nil {
		return
	}
	bstInOrder(node.left, out)
	*out = append(*out, node.value)
	bstInOrder(node.right, out)
}

func (t *BST) preOrder() []string {
	res := make([]string, 0, t.size)
	bstPreOrder(t.root, &res)
	return res
}

func bstPreOrder(node *bstNode, out *[]string) {
	if node == nil {
		return
	}
	*out = append(*out, node.value)
	bstPreOrder(node.left, out)
	bstPreOrder(node.right, out)
}

func (t *BST) SaveToBinary(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	data := t.preOrder()
	enc := gob.NewEncoder(f)
	return enc.Encode(data)
}

func (t *BST) LoadFromBinary(filename string) error {
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

	t.root = nil
	t.size = 0
	for _, v := range data {
		t.Insert(v)
	}
	return nil
}

func (t *BST) SaveToText(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	data := t.preOrder()
	enc := json.NewEncoder(f)
	return enc.Encode(data)
}

func (t *BST) LoadFromText(filename string) error {
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

	t.root = nil
	t.size = 0
	for _, v := range data {
		t.Insert(v)
	}
	return nil
}

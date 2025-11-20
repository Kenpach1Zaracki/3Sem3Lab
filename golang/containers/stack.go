package containers

type Stack struct {
	data []string
}

func NewStack() *Stack {
	return &Stack{data: make([]string, 0)}
}

func (s *Stack) Push(v string) {
	s.data = append(s.data, v)
}

func (s *Stack) Pop() (value string, ok bool) {
	if len(s.data) == 0 {
		return "", false
	}
	last := len(s.data) - 1
	v := s.data[last]
	s.data = s.data[:last]
	return v, true
}

func (s *Stack) Peek() (value string, ok bool) {
	if len(s.data) == 0 {
		return "", false
	}
	return s.data[len(s.data)-1], true
}

func (s *Stack) Size() int {
	return len(s.data)
}

func (s *Stack) Empty() bool {
	return len(s.data) == 0
}

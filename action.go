package main

// ActionFunc is a thing program can do, arg is argument
type ActionFunc func([]string) int

// Action is a thing that the program can do
type Action struct {
	Name      string
	Help      string
	Arguments []string
	Func      ActionFunc
}

package main

import (
	"fmt"
	"os"
	"time"
)

// Program is a representation of your program
type Program struct {
	Actions     []Action
	StartTime   time.Time
	Description string
}

// Execute runs programs then exits
func (p *Program) Execute() {
	if len(os.Args) <= 1 {
		fmt.Printf("You must specify a command\n")
		p.PrintHelp()
		os.Exit(1)
	}
	for _, a := range p.Actions {
		if a.Name == os.Args[1] {
			p.StartTime = time.Now()
			os.Exit(a.Func(os.Args[2:]))
		}
	}
	fmt.Printf("Invalid command '%s'\n", os.Args[1])
	p.PrintHelp()
	os.Exit(1)
}

// PrintHelp shows the help menu for all of the programs
func (p *Program) PrintHelp() {
	fmt.Println(p.Description)
	fmt.Println()
	for _, a := range p.Actions {
		fmt.Printf("%s [", a.Name)
		if a.Arguments != nil {
			for _, arg := range a.Arguments {
				fmt.Printf("%s, ", arg)
			}
		}
		fmt.Printf("] - %s\n", a.Help)
	}
}

package main

import (
	"fmt"
	"log"
)

var program Program

func onHelp(args []string) int {
	program.PrintHelp()
	return 0
}

func onList(args []string) int {
	curConfig := Config{}
	err := curConfig.ParseConfig()
	if err != nil {
		log.Println(err.Error())
		return 1
	}
	for _, b := range curConfig.Bins {
		fmt.Printf("%s -> %s\n", b.Name, b.Path)
	}
	return 0
}

func onRepair(args []string) int {
	curConfig := Config{}
	err := curConfig.ParseConfig()
	if err != nil {
		log.Println(err.Error())
		return 1
	}
	err = curConfig.RepairBins()
	if err != nil {
		log.Println(err.Error())
		return 1
	}
	return 0

}

func main() {
	program.Actions = []Action{
		Action{
			Name:      "help",
			Help:      "shows help menu",
			Arguments: nil,
			Func:      onHelp,
		},
		Action{
			Name:      "list",
			Help:      "lists all programs",
			Arguments: nil,
			Func:      onList,
		},
		Action{
			Name:      "repair",
			Help:      "repairs simlinks to programs in bins folder",
			Arguments: nil,
			Func:      onRepair,
		},
	}
	program.Description = "binmgr keeps track of all temporary bin files"
	program.Execute()
	panic(0)
}

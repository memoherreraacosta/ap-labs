package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	mapita := make(map[string]int)
	splited := strings.Split(s, " ")

	for i := 0; i < len(splited); i++ {
		mapita[splited[i]] = 0
	}
	for i := 0; i < len(splited); i++ {
		mapita[splited[i]] = mapita[splited[i]] + 1
	}

	return mapita
}

func main() {
	wc.Test(WordCount)
}

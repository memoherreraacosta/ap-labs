// Ekaterina Chumakova A01223041
// Guillermo Herrera A01400835

package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"

	"gopl.io/ch5/links"
)

var tokens = make(chan struct{}, 20)

type nameTree struct {
	Level    int
	Name     string
	Parent   string
	Children []nameTree
}

func crawl(url string) []string {
	tokens <- struct{}{} // acquire a token
	list, err := links.Extract(url)
	<-tokens // release the token

	if err != nil {
		log.Print(err)
	}
	return list
}

func next_name(iniurl string, Tree *nameTree, depth int) {
	var i int
	var count int

	if Tree.Level == depth {
		return
	}

	Tree.Name = iniurl
	Tree.Children = []nameTree{}

	list := crawl(Tree.Name)

	count = len(list)
	if count > 10 {
		count = 10
	}

	for i = 0; i < count; i++ {
		ch := nameTree{Level: Tree.Level + 1,
			Name:     list[i],
			Parent:   Tree.Name,
			Children: []nameTree{},
		}
		Tree.Children = append(Tree.Children, ch)

		next_name(list[i], &Tree.Children[i], depth)
	}
}

func main() {
	iniurl := os.Args[2]
	var Tree nameTree
	Tree.Level = 0
	depth := flag.Int("depth", 1, "")
	flag.Parse()
	Tree.Parent = "null"
	next_name(iniurl, &Tree, *depth)

	b, err := json.Marshal(&Tree)
	if err != nil {
		fmt.Println(err)
		return
	}

	s := string(b)
	s = strings.Replace(s, "Name", "name", -1)
	s = strings.Replace(s, "Parent", "parent", -1)
	s = strings.Replace(s, "Children", "children", -1)

	s = "[" + s + "]"
	fmt.Println(s)
}

package main

import (
	"fmt"
	"os"
	"io/ioutil"
)

// scanDir stands for the directory scanning implementation
func scanDir(dirPath string) error {

	files , err := ioutil.ReadDir(dirPath)
	total := len(files)
	dir := 0
	sLin := 0
	otros := 0

	for err, fil := range files {
		if fil.Mode()&os.ModeDir != 0 {
			dir++
		} else if fil.Mode()&os.ModeSymlink != 0 {
			sLin++
		} else {
			otros++
		}
	}
	
	fmt.Printf("+----------------+------+")
	fmt.Printf("| Path:          |  %s  |", dirPath)
	fmt.Printf("+----------------+------+")
	fmt.Printf("| Directories    |  %d  |\n", dir))
	fmt.Printf("| Symbolic Links |  %d  |\n", sLink)
	fmt.Printf("| Other files    |  %d  |\n", other)
	fmt.Printf("+----------------+------+")

	return nil
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}

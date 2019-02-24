package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

// scanDir stands for the directory scanning implementation
func scanDir(dirPath string) error {

	files, _ := ioutil.ReadDir(dirPath)
	dir := 0
	sLin := 0
	otros := 0

	for _, fil := range files {
		if fil.Mode()&os.ModeDir != 0 {
			dir++
		} else if fil.Mode()&os.ModeSymlink != 0 {
			sLin++
		} else {
			otros++
		}
	}

	fmt.Printf("\n+----------------+------+\n")
	fmt.Printf("| Path:          |  %s  |\n", dirPath)
	fmt.Printf("+----------------+------+\n")
	fmt.Printf("| Directories    |  %d  |\n", dir)
	fmt.Printf("| Symbolic Links |  %d  |\n", sLin)
	fmt.Printf("| Other files    |  %d  |\n", otros)
	fmt.Printf("+----------------+------+\n")

	return nil
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}

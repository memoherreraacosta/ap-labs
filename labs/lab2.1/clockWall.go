package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func main() {
	//There are 3 args

	for i := 1; i < len(os.Args); i++ {

		split := strings.Split(os.Args[i], "=")

		fmt.Printf("%s: %s\n ", split[0], split[1])
		con, er := net.Dial("tcp", split[1])

		if er != nil {
			log.Fatal(er)
		}

		defer con.Close()

		go copyFun(con, os.Stdout)
	}
	for true {
	}
}

func copyFun(src io.Reader, des io.Writer) {
	if _, er := io.Copy(des, src); er != nil {
		log.Fatal(er)
	}
}

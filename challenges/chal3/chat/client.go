// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 227.

// Netcat is a simple read/write client for TCP servers.
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

//!+
func main() {

	// Check args
	if (len(os.Args) != 5) ||
		(strings.Compare(os.Args[1], "-user") != 0) ||
		(strings.Compare(os.Args[3], "-server") != 0) {
		log.Printf("Error in arguments\n ")
		return
	}

	uName := os.Args[2] // User name
	uDir := os.Args[4]  // Server dir
	// Conexion
	conn, err := net.Dial("tcp", uDir)
	if err != nil {
		log.Fatal(err)
	}

	// Client body
	done := make(chan struct{})
	go func() {
		fmt.Fprintf(conn, uName)
		io.Copy(os.Stdout, conn) // NOTE: ignoring errors
		log.Println("done")
		done <- struct{}{} // signal the main goroutine
	}()
	mustCopy(conn, os.Stdin)
	conn.Close()
	<-done // wait for background goroutine to finish
}

//!-
func mustCopy(dst io.Writer, src io.Reader) {
	if _, err := io.Copy(dst, src); err != nil {
		log.Fatal(err)
	}
}

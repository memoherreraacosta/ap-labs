package main

import (
	"fmt"
	"os"
	"strconv"
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

const (
	screenWidth  = 600
	screenHeight = 800
	framePerSec  = 60
)

var delta float64

type vector struct {
	x float64
	y float64
}

func divmod(numerator, denominator int) (quotient, remainder int) {
	quotient = numerator / denominator
	remainder = numerator % denominator
	return
}

func main() {

	if err := sdl.Init(sdl.INIT_EVERYTHING); err != nil {
		fmt.Println("initializing SDL:", err)
		return
	}

	window, err := sdl.CreateWindow(
		"Gaming in Go Episode 2",
		sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		sdl.WINDOW_OPENGL)
	if err != nil {
		fmt.Println("initializing window:", err)
		return
	}
	defer window.Destroy()

	renderer, err := sdl.CreateRenderer(window, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		fmt.Println("initializing renderer:", err)
		return
	}
	defer renderer.Destroy()

	elements = append(elements, newPlayer(renderer))

	// Initialize enemies
	numEnemies, err := strconv.Atoi(os.Args[1])

	if err != nil {
		//fmt.Println(err)
		numEnemies = 30
	}

	nRow := 4 // Number of row STATIC
	nCol, res := divmod(numEnemies, nRow)

	// Case number of enemies modify number of rows and columns
	if res != 0 {
		nCol++
		for i := 0; i < nCol; i++ {
			for j := 0; j < nRow-1; j++ {
				x := (float64(i)/float64(nCol))*screenWidth + (basicEnemySize / 2.0)
				y := float64(j)*basicEnemySize + (basicEnemySize / 2.0)
				go newBasicEnemy(renderer, x, y)

			}
		}
		nCol--
		for i := 0; i < res; i++ {
			j := nRow - 1
			x := (float64(i)/float64(nCol))*screenWidth + (basicEnemySize / 2.0)
			y := float64(j)*basicEnemySize + (basicEnemySize / 2.0)
			go newBasicEnemy(renderer, x, y)
		
		}

	} else {
		for i := 0; i < nCol; i++ {
			for j := 0; j < nRow; j++ {
				x := (float64(i)/float64(nCol))*screenWidth + (basicEnemySize / 2.0)
				y := float64(j)*basicEnemySize + (basicEnemySize / 2.0)
				go newBasicEnemy(renderer, x, y)
		
			}
		}
	}

	initBulletPool(renderer)

	for {
		iniST := time.Now()

		for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
			switch event.(type) {
			case *sdl.QuitEvent:
				return
			}
		}

		renderer.SetDrawColor(0, 0, 0, 0)
		renderer.Clear()

		for _, elem := range elements {
			if elem.active {
				err = elem.update()
				if err != nil {
					fmt.Println("updating element:", err)
					return
				}
				err = elem.draw(renderer)
				if err != nil {
					fmt.Println("drawing element:", err)
				}
			}
		}

		if err := checkCollisions(); err != nil {
			fmt.Println("checking collisions:", err)
			return
		}

		renderer.Present()

		delta = time.Since(iniST).Seconds() * framePerSec
	}
}

package main

import (
	"fmt"
	"os"
	"strconv"
	"time"

	"github.com/veandco/go-sdl2/sdl"
	"github.com/veandco/go-sdl2/ttf"
)

const (
	screenWidth  = 600
	screenHeight = 800
	framePerSec  = 60
)

var (
	delta        float64
	score        int
	totalEnemies int
	lives        = 10
	eK           = 0 // Enemies Killed
)

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

	if err := ttf.Init(); err != nil {
		fmt.Println("initializing ttf:", err)
		return
	}

	window, err := sdl.CreateWindow(
		"Space Invaders",
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

	font, _ := ttf.OpenFont("Arial.ttf", 18)
	elements = append(elements, newPlayer(renderer))

	// Initialize enemies
	totalEnemies, err := strconv.Atoi(os.Args[1])

	if err != nil {
		fmt.Println(err)
	}

	nRow, resi := divmod(totalEnemies, 12)
	if resi != 0 {
		nRow++
	}

	// Number of row STATIC
	nCol, res := divmod(totalEnemies, nRow)

	// Case number of enemies modify number of rows and columns

	for i := 0; i < nCol; i++ {
		for j := 0; j < nRow; j++ {
			x := (float64(i)/float64(nCol))*screenWidth + (basicEnemySize / 2.0)
			y := float64(j)*basicEnemySize + (basicEnemySize / 2.0)
			if j%3 == 0 {
				go newBasicEnemy(renderer, x, y, 1)
			} else if j%2 == 0 {
				go newBasicEnemy(renderer, x, y, 2)
			} else {
				go newBasicEnemy(renderer, x, y, 3)
			}
		}
	}
	for i := 0; i < res; i++ {
		j := nRow
		x := (float64(i)/float64(res))*screenWidth + (basicEnemySize / 2.0)
		y := float64(j)*basicEnemySize + (basicEnemySize / 2.0)
		if j == 1 {
			go newBasicEnemy(renderer, x, y, 1)
		} else if j == 2 {
			go newBasicEnemy(renderer, x, y, 2)
		} else {
			go newBasicEnemy(renderer, x, y, 3)
		}
	}

	initBulletPool(renderer)
	initBulletPoolEnemy(renderer)

	for totalEnemies > 0 {

		iniST := time.Now()

		for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
			switch event.(type) {
			case *sdl.QuitEvent:
				return
			}
		}

		solidSurface, _ := font.RenderUTF8Solid("Score: "+strconv.Itoa(score), sdl.Color{255, 255, 255, 255})
		solidSurface2, _ := font.RenderUTF8Solid("Lives: "+strconv.Itoa(lives), sdl.Color{255, 255, 255, 255})
		solidTexture, _ := renderer.CreateTextureFromSurface(solidSurface)
		solidTexture2, _ := renderer.CreateTextureFromSurface(solidSurface2)
		solidSurface.Free()
		solidSurface2.Free()

		renderer.SetDrawColor(0, 0, 0, 0)
		renderer.Clear()

		renderer.Copy(solidTexture, nil, &sdl.Rect{10, screenHeight - 70, 190, 50})
		renderer.Copy(solidTexture2, nil, &sdl.Rect{400, screenHeight - 70, 190, 50})

		// Case you lose
		if lives <= 0 {
			for _, elem := range elements {
				elem.active = false
			}
			renderer.Clear()
			solidSurface3, _ := font.RenderUTF8Solid("GAME OVER", sdl.Color{255, 255, 255, 255})
			solidTexture3, _ := renderer.CreateTextureFromSurface(solidSurface3)
			solidSurface3.Free()

			renderer.SetDrawColor(1, 0, 0, 0)

			renderer.Copy(solidTexture3, nil, &sdl.Rect{150, screenHeight - 500, 300, 100})
			//renderer.Copy(solidTexture, nil, &sdl.Rect{10, screenHeight - 70, 190, 50})
		}

		// Case you win
		if (score / 20) == totalEnemies {
			for _, elem := range elements {
				elem.active = false
			}
			renderer.Clear()
			solidSurface3, _ := font.RenderUTF8Solid("YOU WIN", sdl.Color{255, 255, 255, 255})
			solidTexture3, _ := renderer.CreateTextureFromSurface(solidSurface3)
			solidSurface3.Free()

			renderer.SetDrawColor(1, 0, 0, 0)

			renderer.Copy(solidTexture3, nil, &sdl.Rect{150, screenHeight - 500, 300, 100})
		}

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

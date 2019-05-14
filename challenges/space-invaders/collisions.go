package main
import (
	"math"
	//"fmt"
)


type circle struct {
	center vector
	radius float64
}

func collides(c1, c2 circle) bool {
	dist := math.Sqrt(math.Pow(c2.center.x-c1.center.x, 2) +
		math.Pow(c2.center.y-c1.center.y, 2))

	return dist <= c1.radius+c2.radius
}

func checkCollisions() error {
	for i := 0; i < len(elements)-1; i++ {
		for j := i + 1; j < len(elements); j++ {
			var colCheck = true
			if (elements[i].tag == "enemy") && (elements[j].tag == "bullet_enemy"){
				colCheck = false
			} else if (elements[i].tag == "player") && (elements[j].tag == "bullet"){
				colCheck = false
			}
			if colCheck{
				for _, c1 := range elements[i].collisions {
					for _, c2 := range elements[j].collisions {
						if collides(c1, c2) && elements[i].active && elements[j].active {
							err := elements[i].collision(elements[j])
							if err != nil {
								return err
							}
							err = elements[j].collision(elements[i])
							if err != nil {
								return err
							}
						}
					}
				}
			}


		}
	}

	return nil
}

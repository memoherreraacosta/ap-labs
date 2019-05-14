package main

import (
	"math"

	"github.com/veandco/go-sdl2/sdl"
)

type bulletMoverEnemy struct {
	container *element
	speed     float64
}

func newbulletMoverEnemy(container *element) *bulletMoverEnemy {
	return &bulletMoverEnemy{container: container}
}

func (mover *bulletMoverEnemy) onDraw(renderer *sdl.Renderer) error {
	return nil
}

func (mover *bulletMoverEnemy) onUpdate() error {
	c := mover.container

	c.position.x += bulletSpeed * math.Cos(c.rotation) * delta
	c.position.y += bulletSpeed * math.Sin(c.rotation) * delta

	if c.position.x > screenWidth || c.position.x < 0 ||
		c.position.y > screenHeight-100 || c.position.y < 0 {
		c.active = false
	}

	c.collisions[0].center = c.position

	return nil

}

func (mover *bulletMoverEnemy) onCollision(other *element) error {
	mover.container.active = false
	if other.tag == "player"{
		lives -= 1
	}
	return nil
}

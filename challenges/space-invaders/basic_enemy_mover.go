package main

import (
	"math"
	"math/rand"
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

type enemyMover struct {
	container *element
	speed     float64
}

type enemyShooter struct {
	container *element
	cooldown  time.Duration
	lastShot  time.Time
}

const (
	enemyShotCooldown = time.Millisecond * 1000
)

var direction = 1.0
var enemySpeed = 1.0

func newEnemyMover(container *element) *enemyMover {
	return &enemyMover{container: container}
}

func (mover *enemyMover) onDraw(renderer *sdl.Renderer) error {
	return nil
}

func (mover *enemyMover) onUpdate() error {
	c := mover.container
	c.position.x += direction * enemySpeed * math.Cos(c.rotation) * delta
	c.position.y += 0.05 * enemySpeed * math.Cos(c.rotation) * delta

	if c.position.x > (screenWidth-10) || c.position.x < 10 {
		direction = -1.0 * direction
	}
	c.collisions[0].center = c.position
	return nil
}

func (mover *enemyMover) onCollision(other *element) error {
	//mover.container.active = false
	return nil
}

func newEnemyShooter(container *element, cooldown time.Duration) *enemyShooter {
	return &enemyShooter{
		container: container,
		cooldown:  cooldown}
}

func (shooter *enemyShooter) onDraw(renderer *sdl.Renderer) error {
	return nil
}

func (shooter *enemyShooter) onUpdate() error {
	pos := shooter.container.position
	r := float64(rand.Intn(100))
	ra := rand.Intn(2000)
	if ra == 1 {
		if time.Since(shooter.lastShot) >= shooter.cooldown {
			shooter.shoot(pos.x, pos.y+r)
			shooter.lastShot = time.Now()
		}
	}
	return nil
}

func (shooter *enemyShooter) shoot(x, y float64) {
	if bul, ok := bulletFromEnemyPool(); ok {
		bul.active = true
		bul.position.x = x
		bul.position.y = y
		bul.rotation = 90 * (math.Pi / 180)
	}
}

func (shooter *enemyShooter) onCollision(other *element) error {

	return nil
}

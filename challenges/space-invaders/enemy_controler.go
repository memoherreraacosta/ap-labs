package main

import (
	"math"
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

type enemyMover struct {
	container *element
	speed     float64
	sr *spriteRenderer
}

type enemyShooter struct {
	container *element
	cooldown  time.Duration
	lastShot  time.Time
}


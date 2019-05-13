package main

import (
	"time"

	"github.com/veandco/go-sdl2/sdl"
)

const (
	playerSize = 105
	playerShotCooldown = time.Millisecond * 250
	scoreSpace = 50
)

func newPlayer(renderer *sdl.Renderer) *element {
	player := &element{}

	player.position = vector{
		x: screenWidth / 2.0,
		y: screenHeight - playerSize/2.0 - scoreSpace}

	sr := newSpriteRenderer(player, renderer, "sprites/Nave.png")
	player.addComponent(sr)

	mover := newKeyboardMover(player, 5)
	player.addComponent(mover)

	shooter := newKeyboardShooter(player, playerShotCooldown)
	player.addComponent(shooter)

	player.active = true

	return player
}

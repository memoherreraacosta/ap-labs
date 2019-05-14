package main

import (
	"github.com/veandco/go-sdl2/sdl"
)

const basicEnemySize = 25

func newBasicEnemy(renderer *sdl.Renderer, x, y float64, image int) {
	basicEnemy := &element{}

	basicEnemy.position = vector{x: x, y: y}
	basicEnemy.rotation = 0

	if image == 1 {
		sr := newSpriteRenderer(basicEnemy, renderer, "sprites/Alien1-1.png")
		basicEnemy.addComponent(sr)
	} else if image == 2 {
		sr := newSpriteRenderer(basicEnemy, renderer, "sprites/Alien2-1.png")
		basicEnemy.addComponent(sr)
	} else if image == 3 {
		sr := newSpriteRenderer(basicEnemy, renderer, "sprites/Alien3-1.png")
		basicEnemy.addComponent(sr)
	}

	vtb := newVulnerableToBullets(basicEnemy)
	basicEnemy.addComponent(vtb)

	col := circle{
		center: basicEnemy.position,
		radius: 20,
	}
	basicEnemy.collisions = append(basicEnemy.collisions, col)
	basicEnemy.tag = "enemy"

	basicEnemy.active = true

	mover := newEnemyMover(basicEnemy)
	basicEnemy.addComponent(mover)

	shooter := newEnemyShooter(basicEnemy, enemyShotCooldown)
	basicEnemy.addComponent(shooter)

	elements = append(elements, basicEnemy)
	//return basicEnemy
}

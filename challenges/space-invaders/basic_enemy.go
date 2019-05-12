package main

import (
	"github.com/veandco/go-sdl2/sdl"
)

const basicEnemySize = 105

func newBasicEnemy(renderer *sdl.Renderer, x, y float64){
	basicEnemy := &element{}

	basicEnemy.position = vector{x: x, y: y}
	basicEnemy.rotation = 0

	sr := newSpriteRenderer(basicEnemy, renderer, "sprites/Alien1.1.png")
	basicEnemy.addComponent(sr)

	vtb := newVulnerableToBullets(basicEnemy)
	basicEnemy.addComponent(vtb)

	col := circle{
		center: basicEnemy.position,
		radius: 38,
	}
	basicEnemy.collisions = append(basicEnemy.collisions, col)

	basicEnemy.active = true

	elements = append(elements,basicEnemy)
	//return basicEnemy
}

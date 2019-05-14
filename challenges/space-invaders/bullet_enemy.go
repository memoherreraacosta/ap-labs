package main

import (
	"github.com/veandco/go-sdl2/sdl"
)

func newBulletEnemy(renderer *sdl.Renderer, tag string) *element {
	bullet := &element{}

	sr := newSpriteRenderer(bullet, renderer, "sprites/"+tag+".png")
	bullet.addComponent(sr)
	mover := newbulletMoverEnemy(bullet)
	bullet.addComponent(mover)

	col := circle{
		center: bullet.position,
		radius: 8,
	}
	bullet.collisions = append(bullet.collisions, col)
	bullet.tag = tag

	return bullet
}

var bulletPoolEnemy []*element

func initBulletPoolEnemy(renderer *sdl.Renderer) {
	for i := 0; i < 50; i++ {
		bul := newBulletEnemy(renderer, "bullet_enemy")
		bulletPoolEnemy = append(bulletPoolEnemy, bul)
		elements = append(elements, bul)
	}
}

func bulletFromEnemyPool() (*element, bool) {
	for _, bul := range bulletPoolEnemy {
		if !bul.active {
			return bul, true
		}
	}
	return nil, false
}

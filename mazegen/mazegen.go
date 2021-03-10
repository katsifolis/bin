package main

import (
	"math/rand"
	"os"
	"strconv"
	"time"
)

var r rand.Source = rand.New(rand.NewSource(time.Now().Unix()))
var n, s, e, w int = 1, 2, 4, 8
var dx = map[int]int{e: 1, w: -1, n: 0, s: 0}
var dy = map[int]int{e: 0, w: 0, n: -1, s: 1}
var opposite = map[int]int{e: w, w: e, n: s, s: n}

func ascii(matrix [][]int) {

	print(" ")
	for z := 0; z < len(matrix[0])*2-1; z++ {
		print("_")
	}

	println()
	for i := 0; i < len(matrix[0]); i++ {
		print("|")
		for j := 0; j < len(matrix); j++ {
			if matrix[i][j]&s != 0 {
				print(" ")
			} else {
				print("_")
			}
			if matrix[i][j]&e != 0 {
				if (matrix[i][j]|matrix[i][j+1])&s != 0 {
					print(" ")
				} else {
					print("_")
				}
			} else {
				print("|")
			}
		}
		println()
	}
}

func backtracer(cx, cy int, m [][]int) {

	dir := []int{n, s, e, w}
	rand.Shuffle(len(dir), func(i, j int) { dir[i], dir[j] = dir[j], dir[i] })

	for _, direction := range dir {
		nx := cx + dx[direction]
		ny := cy + dy[direction]

		if (ny >= 0 && ny < len(m)) && (nx >= 0 && nx < len(m[0])) && (m[ny][nx] == 0) {
			m[cy][cx] |= direction
			m[ny][nx] |= opposite[direction]
			backtracer(nx, ny, m)
		}

	}
}

func main() {
	if len(os.Args) < 3 {
		println("Parameters not given")
		os.Exit(0)
	}
	x, _ := strconv.Atoi(os.Args[1])
	y, _ := strconv.Atoi(os.Args[2])

	rand.Seed(time.Now().UTC().UnixNano())
	matrix := make([][]int, y)
	for i := 0; i < y; i++ {
		matrix[i] = make([]int, x)
	}

	backtracer(0, 0, matrix)

	ascii(matrix)
	println()

}

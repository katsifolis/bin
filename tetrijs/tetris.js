// Tetris in JS //
const canvas    = document.getElementById('canvas')
const ctx       = canvas.getContext('2d'); ctx.scale(16, 16)
const log       = console.log
const _columns  = 10
const _lines    = 20
const _landing  = _lines - 4
var dt          = 0
var start       = 0
var runtime     = 0
var speed       = 300
var p           = undefined
var saved       = []
var matrix      = []

for (i = 0; i < 20; i++) { 
  matrix[i] = [] 
  for (j=0; j<10;j++) {
    matrix[i][j] = 0 
  } 
}

var I = [ [0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 1, 0], ]
var O = [ [0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 0], [0, 1, 1, 0], ]
var T = [ [0, 0, 0, 0], [0, 1, 1, 1], [0, 0, 1, 0], [0, 0, 1, 0], ]
var S = [ [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 1, 1], [0, 1, 1, 0], ]
var Z = [ [0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 0], [0, 0, 1, 1], ]
var J = [ [0, 0, 0, 0], [0, 0, 1, 0], [0, 0, 1, 0], [0, 1, 1, 0], ]
var L = [ [0, 0, 0, 0], [0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 1, 1], ]

function new_piece() {

  let piece = { shape: 0, color: 0, pos: { x: 0, y: 0}}
  choice = Math.floor(Math.random() * 7)
  piece.pos.y = _columns / 2
  piece.pos.x = -5
  
  switch (choice) {
  case 0:
    piece.shape = I
    piece.color = 'red'
    break 
  case 1:
    piece.shape = O
    piece.color = 'yellow'
    break
  case 2:
    piece.shape = T
    piece.color = 'purple'
    break
  case 3:
    piece.shape = S
    piece.color = 'green'
    break
  case 4:
    piece.shape = Z
    piece.color = 'red'
    break
  case 5:
    piece.shape = J
    piece.color = 'blue'
    break
  case 6:
    piece.shape = L
    piece.color = 'orange'
    break
  }
  return piece
}



function input(event) {
  document.addEventListener('keydown', (event) => {
    const keyName = event.key;
    switch (keyName) {
    case "ArrowLeft":
      p.pos.y--
     // if (out_of_bounds(p))
        //  p.pos.y++
      render_piece(p)
      break
    case "ArrowRight":
      p.pos.y++

      //if (out_of_bounds(p))
       //   p.pos.y--

      render_piece(p)
      break
    case "u":
      speed = speed - 20
      break
    case "j":
      speed = speed + 20
      break
    }
  });
}

function out_of_bounds(piece) {
  for (i = 0; i < 4; ++i) { 
    for (j = 0; j < 4; ++j) {
        return true
    }
  }
}

function render_piece(piece) {
  ctx.fillStyle = 'black'
  ctx.fillRect(0, 0, canvas.width, canvas.height)
  ctx.fillStyle = piece.color
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (piece.shape[i][j] == 1) {
        ctx.fillRect(piece.pos.y + j, piece.pos.x + i, 1, 1)
      }
    }
  }
}


function render_matrix() {
  for (x = 0; x < saved.length; x++) {
    ctx.fillStyle = 'black'
    ctx.fillRect(0, 0, canvas.width, canvas.height)
    ctx.fillStyle = saved[x].color
    let pos = saved[x].pos
    let shape = saved[x].shape
    for (i = 0; i < 20; i++) {
      for (j = 0; j < 10; j++) {
        if (matrix[i][j] == 1) 
          ctx.fillRect(pos.y + j, pos.x + i, 1, 1)
      }
    }
  }
}

function update_matrix(piece) {
  saved.push(piece)
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (piece.shape[i][j] == 1) 
        matrix[piece.pos.x][piece.pos.y] = 1
    }
  }
}

function update(dt) {

  if (p === undefined) { p = new_piece() }
  runtime = dt - start

  if (runtime > speed) {
    start = dt
    runtime = 0
    
    render_matrix()
    render_piece(p)
    p.pos.x++
    if (p.pos.x > _landing) {
      update_matrix(p)
      p = new_piece()
    }
  }
  
  requestAnimationFrame(update)
}


(() => {
  input(event)
  update()
})()

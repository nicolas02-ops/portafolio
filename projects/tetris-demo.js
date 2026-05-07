const terminal = document.getElementById("tetris-terminal");
const widthInput = document.getElementById("board-width");
const heightInput = document.getElementById("board-height");
const startButton = document.getElementById("tetris-start");
const resetButton = document.getElementById("tetris-reset");
const actionButtons = document.querySelectorAll("[data-action]");

const pieces = [
  [[1, 1, 1, 1]],
  [[1, 1], [1, 1]],
  [[0, 1, 0], [1, 1, 1]],
  [[1, 0, 0], [1, 1, 1]],
  [[0, 0, 1], [1, 1, 1]],
  [[0, 1, 1], [1, 1, 0]],
  [[1, 1, 0], [0, 1, 1]]
];

let board = [];
let currentPiece = null;
let width = 8;
let height = 16;
let gameStarted = false;
let gameOver = false;
let exitRequested = false;
let lines = 0;
let logLines = [];

function normalizeWidth(value) {
  const parsed = Number.parseInt(value, 10);
  if (!Number.isFinite(parsed) || parsed < 8) return 8;
  return Math.max(8, parsed - (parsed % 8));
}

function normalizeHeight(value) {
  const parsed = Number.parseInt(value, 10);
  if (!Number.isFinite(parsed) || parsed < 8) return 16;
  return parsed;
}

function createBoard() {
  board = Array.from({ length: height }, () => Array(width).fill(0));
}

function cloneShape(shape) {
  return shape.map((row) => row.slice());
}

function randomPiece() {
  const shape = cloneShape(pieces[Math.floor(Math.random() * pieces.length)]);
  return {
    shape,
    x: Math.floor((width - shape[0].length) / 2),
    y: 0
  };
}

function canPlace(piece) {
  for (let row = 0; row < piece.shape.length; row += 1) {
    for (let col = 0; col < piece.shape[row].length; col += 1) {
      if (!piece.shape[row][col]) continue;
      const x = piece.x + col;
      const y = piece.y + row;
      if (x < 0 || x >= width || y < 0 || y >= height) return false;
      if (board[y][x]) return false;
    }
  }
  return true;
}

function mergePiece() {
  currentPiece.shape.forEach((row, pieceY) => {
    row.forEach((value, pieceX) => {
      if (value) {
        board[currentPiece.y + pieceY][currentPiece.x + pieceX] = 1;
      }
    });
  });
}

function clearCompleteLines() {
  const remainingRows = board.filter((row) => !row.every(Boolean));
  const cleared = height - remainingRows.length;
  while (remainingRows.length < height) remainingRows.unshift(Array(width).fill(0));
  board = remainingRows;
  if (cleared > 0) {
    lines += cleared;
    logLines.push(`Lineas limpiadas: ${cleared}`);
  }
}

function rotateShape(shape) {
  return shape[0].map((_, index) => shape.map((row) => row[index]).reverse());
}

function spawnPiece() {
  currentPiece = randomPiece();
  if (!canPlace(currentPiece)) {
    gameOver = true;
    logLines.push("GAME OVER!");
  }
}

function move(dx, dy) {
  const next = { ...currentPiece, x: currentPiece.x + dx, y: currentPiece.y + dy };
  if (canPlace(next)) {
    currentPiece = next;
    return true;
  }
  return false;
}

function stepDown() {
  if (!move(0, 1)) {
    mergePiece();
    clearCompleteLines();
    spawnPiece();
  }
}

function rotatePiece() {
  const next = { ...currentPiece, shape: rotateShape(currentPiece.shape) };
  if (canPlace(next)) currentPiece = next;
}

function boardWithPiece() {
  const output = board.map((row) => row.slice());
  if (!currentPiece) return output;
  currentPiece.shape.forEach((row, pieceY) => {
    row.forEach((value, pieceX) => {
      const x = currentPiece.x + pieceX;
      const y = currentPiece.y + pieceY;
      if (value && y >= 0 && y < height && x >= 0 && x < width) {
        output[y][x] = 2;
      }
    });
  });
  return output;
}

function renderBoard() {
  const rows = boardWithPiece().map((row) => {
    const cells = row.map((value) => {
      if (value === 2) return "@";
      if (value === 1) return "#";
      return ".";
    }).join("");
    return `|${cells}|`;
  });
  return [`+${"-".repeat(width)}+`, ...rows, `+${"-".repeat(width)}+`].join("\n");
}

function render() {
  const header = [
    "=========================================================",
    "    TETRIS By  nicolas anacona",
    "=========================================================",
    "",
    `Tablero: ${width}x${height}`,
    `Lineas: ${lines}`,
    ""
  ];

  const footer = gameStarted
    ? ["", "Accion (a=izq, d=der, s=bajar, w=rotar, q=salir):"]
    : ["", "Ingrese ancho del tablero (multiplo de 8, minimo 8) y alto (minimo 8).", "Presione Iniciar."];

  terminal.textContent = [
    ...header,
    gameStarted ? renderBoard() : "+--------+\n|........|\n|........|\n|........|\n+--------+",
    ...footer,
    ...logLines.slice(-5).map((line) => `> ${line}`)
  ].join("\n");
}

function startGame() {
  width = normalizeWidth(widthInput.value);
  height = normalizeHeight(heightInput.value);
  widthInput.value = width;
  heightInput.value = height;
  lines = 0;
  gameStarted = true;
  gameOver = false;
  exitRequested = false;
  logLines = [`Tablero creado: ${width}x${height}`];
  createBoard();
  spawnPiece();
  render();
}

function resetGame() {
  gameStarted = false;
  gameOver = false;
  exitRequested = false;
  lines = 0;
  logLines = [];
  createBoard();
  currentPiece = null;
  render();
}

function handleAction(action) {
  if (!gameStarted || gameOver || exitRequested) return;
  logLines.push(action);
  if (action === "a") move(-1, 0);
  if (action === "d") move(1, 0);
  if (action === "s") stepDown();
  if (action === "w") rotatePiece();
  if (action === "q") {
    exitRequested = true;
    logLines.push("Gracias por jugar!");
  }
  render();
}

startButton.addEventListener("click", startGame);
resetButton.addEventListener("click", resetGame);
actionButtons.forEach((button) => {
  button.addEventListener("click", () => handleAction(button.dataset.action));
});

document.addEventListener("keydown", (event) => {
  const key = event.key.toLowerCase();
  if (["a", "d", "s", "w", "q"].includes(key)) {
    event.preventDefault();
    handleAction(key);
  }
});

resetGame();

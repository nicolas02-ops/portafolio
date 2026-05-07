const terminal = document.getElementById("triqui-terminal");
const letterInput = document.getElementById("player-letter");
const startButton = document.getElementById("triqui-start");
const resetButton = document.getElementById("triqui-reset");
const moveButtons = document.querySelectorAll("[data-move]");

let board = "         ".split("");
let player = "X";
let computer = "O";
let turn = "Usuario";
let playing = false;
let output = [];

function drawBoard() {
  return [
    "------------------------------------",
    ` ${board[6]} | ${board[7]} | ${board[8]}`,
    "-----------",
    ` ${board[3]} | ${board[4]} | ${board[5]}`,
    "-----------",
    ` ${board[0]} | ${board[1]} | ${board[2]}`,
    "------------------------------------"
  ].join("\n");
}

function isWinner(letter) {
  const wins = [[6, 7, 8], [3, 4, 5], [0, 1, 2], [6, 3, 0], [7, 4, 1], [8, 5, 2], [6, 4, 2], [8, 4, 0]];
  return wins.some((combo) => combo.every((index) => board[index] === letter));
}

function isFull() {
  return board.every((cell) => cell !== " ");
}

function availableMoves() {
  return board.map((cell, index) => cell === " " ? index + 1 : null).filter(Boolean);
}

function testMove(letter, move) {
  const copy = board.slice();
  copy[move - 1] = letter;
  const wins = [[6, 7, 8], [3, 4, 5], [0, 1, 2], [6, 3, 0], [7, 4, 1], [8, 5, 2], [6, 4, 2], [8, 4, 0]];
  return wins.some((combo) => combo.every((index) => copy[index] === letter));
}

function chooseComputerMove() {
  for (const move of availableMoves()) if (testMove(computer, move)) return move;
  for (const move of availableMoves()) if (testMove(player, move)) return move;
  for (const move of [1, 3, 7, 9]) if (board[move - 1] === " ") return move;
  if (board[4] === " ") return 5;
  return availableMoves()[0];
}

function render() {
  terminal.textContent = [
    "==============================",
    "            TRIQUI",
    "==============================",
    "",
    ...output.slice(-10),
    drawBoard(),
    "",
    playing ? "Ingresa tu siguiente movimiento (1-9):" : "Elige X u O y presiona Iniciar."
  ].join("\n");
}

function finishIfNeeded(letter) {
  if (isWinner(letter)) {
    output.push(letter === player ? "Felicidades! Has ganado el Triqui!" : "La computadora te ha ganado. Has perdido.");
    playing = false;
    return true;
  }
  if (isFull()) {
    output.push("El juego ha quedado empatado!");
    playing = false;
    return true;
  }
  return false;
}

function computerTurn() {
  const move = chooseComputerMove();
  if (!move) return;
  board[move - 1] = computer;
  output.push(`Computadora juega: ${move}`);
  finishIfNeeded(computer);
}

function startGame() {
  player = letterInput.value.trim().toUpperCase() === "O" ? "O" : "X";
  computer = player === "X" ? "O" : "X";
  board = "         ".split("");
  playing = true;
  output = [`Usuario es: ${player}. Computadora es: ${computer}.`, "Usuario ira primero!"];
  render();
}

function playMove(move) {
  if (!playing) return;
  const index = move - 1;
  output.push(`Usuario juega: ${move}`);
  if (move < 1 || move > 9 || board[index] !== " ") {
    output.push("Esa casilla no esta disponible.");
    render();
    return;
  }
  board[index] = player;
  if (!finishIfNeeded(player)) computerTurn();
  render();
}

startButton.addEventListener("click", startGame);
resetButton.addEventListener("click", startGame);
moveButtons.forEach((button) => button.addEventListener("click", () => playMove(Number(button.dataset.move))));
document.addEventListener("keydown", (event) => {
  const move = Number(event.key);
  if (move >= 1 && move <= 9) playMove(move);
});
render();

"""
Laboratorio 4
Kevin Santiago Mesa Urrego
Nicolas Anacona
Grupo 03
"""
import random
import sys
# Mostrar mensaje de inicio
def printIntro(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            print(file.read())
    except UnicodeEncodeError:
        print("=========== TRIQUI ===========")
    except FileNotFoundError:
        print("No se encontro el archivo de introduccion:", filename)
    print("___________________________________________\n")
# Decidir quien va ser X y O
def inputPlayerletter():
    letter = ''
    while not (letter == 'X' or letter == 'O'):
        print('¿Quieres ser X o O?')
        choice = input().upper()
        if choice in ('X', 'O'):
            letter = choice
    if letter == 'X':
        return 'X', 'O'
    else:
        return 'O', 'X'

def inputPlayerLetter():
    return inputPlayerletter()
# Decidir quien va primero
def whoGoesFirst():
    if random.randint(0, 1) == 0:
        return 'Computadora'
    else:
        return 'Usuario'
# Crear nuevo tablero vacio
def createNewBoard():
    return '         '
# Imprime el estado actual del tablero
def drawBoard(board):
    print("------------------------------------")
    print(f' {board[6]} | {board[7]} | {board[8]}')
    print('-----------')
    print(f' {board[3]} | {board[4]} | {board[5]}')
    print('-----------')
    print(f' {board[0]} | {board[1]} | {board[2]}')
    print("------------------------------------")
# Verifica si esta vacio el espacio
def isSpaceFree(board, move):
    return board[move - 1] == ' '

# Hace el movimiento modificando la cadena
def makeMove(board, letter, move):
    posicion = move - 1
    return board[:posicion] + letter + board[posicion+1:]

# Verifica si se gana
def isWinner(board, letter):
    letra = letter 
    # Se verifica cada combinación ganadora usando indexación directa:
    return (
        # Filas
        (board[6] == letra and board[7] == letra and board[8] == letra) or 
        (board[3] == letra and board[4] == letra and board[5] == letra) or 
        (board[0] == letra and board[1] == letra and board[2] == letra) or 
        # Columnas
        (board[6] == letra and board[3] == letra and board[0] == letra) or 
        (board[7] == letra and board[4] == letra and board[1] == letra) or 
        (board[8] == letra and board[5] == letra and board[2] == letra) or 
        # Diagonales
        (board[6] == letra and board[4] == letra and board[2] == letra) or 
        (board[8] == letra and board[4] == letra and board[0] == letra)
    )
# Verifica si el tablero esta lleno
def isBoardFull(board):
    return ' ' not in board
# Pide al usuario jugar 
def getPlayerMove(board):
    while True:
        print('Ingresa tu siguiente movimiento (1-9):')
        try:
            move = int(input())
            if 1 <= move <= 9:
                if isSpaceFree(board, move):
                    return move
                else:
                    print('¡Esa casilla ya está ocupada! Ingresa un número de casilla vacía.')
            else:
                print('Ingresa un número válido entre 1 y 9.')
        except ValueError:
            print('¡Entrada inválida! Ingresa solo números.')

# Ayuda para movimiento de la IA
def chooseRandomMoveFromList(board, move1=None, move2=None, move3=None, move4=None):    
    available_moves_str = ""
    count = 0
    if move1 is not None and isSpaceFree(board, move1):
        available_moves_str += str(move1)
        count += 1
    if move2 is not None and isSpaceFree(board, move2):
        available_moves_str += str(move2)
        count += 1
    if move3 is not None and isSpaceFree(board, move3):
        available_moves_str += str(move3)
        count += 1
    if move4 is not None and isSpaceFree(board, move4):
        available_moves_str += str(move4)
        count += 1

    if count > 0:
        # Elegimos una posición aleatoria dentro de la cadena de movimientos libres
        random_index = random.randint(0, count - 1)
        # Retornamos el entero de esa posición
        return int(available_moves_str[random_index])
    else:
        return None
# Pasos de la IA
def getComputerMove(board, computerletter):

    playerletter = 'X' if computerletter == 'O' else 'O'
    # Verificar si se puede ganar 
    def check_winning_or_blocking(check_letter):
        for move in range(1, 10):
            if isSpaceFree(board, move):
                # Simula el movimiento creando una NUEVA cadena
                temp_board = makeMove(board, check_letter, move)
                if isWinner(temp_board, check_letter):
                    return move # Retorna el movimiento ganador o bloqueador
        return None

    # Intenta ganar
    move = check_winning_or_blocking(computerletter)
    if move is not None:
        return move

    # Intenta bloquear al usuario
    move = check_winning_or_blocking(playerletter)
    if move is not None:
        return move
        
    # Toma una esquina (1, 3, 7, 9)
    move = chooseRandomMoveFromList(board, 1, 3, 7, 9)
    if move is not None:
        return move

    # Toma el centro (5)
    if isSpaceFree(board, 5):
        return 5

    # Toma un lado (2, 4, 6, 8)
    move = chooseRandomMoveFromList(board, 2, 4, 6, 8) 
    if move is not None:
        return move
    return None

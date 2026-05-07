"""
Nicolas Anacona
Grupo 03
"""
import triqui
import sys

def main():

    triqui.printIntro("intro.txt")

    while True: 

        playerLetter, computerLetter = triqui.inputPlayerletter()
        print(f"Usuario es: {playerLetter}. Computadora es: {computerLetter}.")
        

        theBoard = triqui.createNewBoard()
        
   
        turn = triqui.whoGoesFirst()
        print(f"\n¡{turn} irá primero!")
        gameIsPlaying = True

        while gameIsPlaying:
            
            if turn == 'Usuario':

                triqui.drawBoard(theBoard) 
                move = triqui.getPlayerMove(theBoard) 
    
                theBoard = triqui.makeMove(theBoard, playerLetter, move)
                

                if triqui.isWinner(theBoard, playerLetter): 
                    triqui.drawBoard(theBoard)
                    print('¡Felicidades! ¡Has ganado el Triqui!')
                    gameIsPlaying = False
                elif triqui.isBoardFull(theBoard): 
                    triqui.drawBoard(theBoard)
                    print('¡El juego ha quedado empatado!')
                    gameIsPlaying = False
                else:
                    turn = 'Computadora'
            
            else:
                move = triqui.getComputerMove(theBoard, computerLetter) 
                
  
                theBoard = triqui.makeMove(theBoard, computerLetter, move)

                if triqui.isWinner(theBoard, computerLetter): 
                    triqui.drawBoard(theBoard)
                    print('¡La computadora te ha ganado! Has perdido.')
                    gameIsPlaying = False
                elif triqui.isBoardFull(theBoard): 
                    triqui.drawBoard(theBoard)
                    print('¡El juego ha quedado empatado!')
                    gameIsPlaying = False
                else:
                    turn = 'Usuario'
        print('\n¿Quieres jugar otra vez? (sí)')
        respuesta = input().strip().lower()
        if not respuesta.startswith('s'):
            sys.exit() 

if __name__ == '__main__':
    main()

from cargar_datos import cargar_datos_estudiantes
from funciones_notas import * 
from proyec import mostrar_grafica
lista_Cursos , lista_ID, matriz_Notas = cargar_datos_estudiantes("notas_estudiantes.csv")
while True:
    print("=============================================================")
    print("                  MENU UNIVERSIDAD")
    print(("============================================================="))
    print(" 1 - Elimnar Estudiante")
    print(" 2 - Mayor Nota estudiante")
    print(" 3 - Promedio estudiantes")
    print(" 4 - Estudiantes por curso")
    print(" 5 - Mostrar grafica ")
    print(" 0 - Salir ")
    opcion_principal = input("Seleccione una opción [1, 2, 3, 4, 5, 0]: ").strip()
    # Salida
    if opcion_principal == "0":
        print("\n Gracias por usar el sistema Saliendo...")
        break
    # Generales
    elif opcion_principal == "1":
        print("Elimnar Estudiante")
        eliminar_estudiante(lista_ID,matriz_Notas)
    elif opcion_principal == "2":
        print("Mayor Nota estudiante")
        mayor_nota_estudiante(lista_Cursos,lista_ID,matriz_Notas)
    elif opcion_principal == "3":
        print("Promedio estudiantes")
        promedio_estudiantes(lista_ID, matriz_Notas)
    elif opcion_principal == "4":
        estudiantes_por_cursos(lista_ID,matriz_Notas)
        print("Estudiantes por curso")
    elif opcion_principal == "5":
        print("Mostrar grafica")
        mostrar_grafica()
    else:
        print("\n Opción no válida. Intente de nuevo.")

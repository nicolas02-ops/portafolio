from cargar_datos import *
from funciones_notas import *
#plot_data(data=[[1900,20],[1901,30],[1902,40]], regression_line=[10,20,30],years=[1900,1901,1902])
lista_Cursos , lista_ID, matriz_Notas =cargar_datos_estudiantes("notas_estudiantes.csv")
#eliminar_estudiante(lista_ID,matriz_Notas)
#mayor_nota_estudiante(lista_Cursos,lista_ID,matriz_Notas)
#promedio_estudiantes(lista_ID, matriz_Notas)
estudiantes_por_cursos(lista_ID,matriz_Notas)
def eliminar_estudiante(lista_ID,matriz_Notas):
    """" elimina un estudiante segun su documento
    entrada: documento del estudiante a eliminar
    lista de estudiantes
    matriz de notas
    salida : mensaje de eliminacion """
    ID=str(input("ingrese el numero de documento del estudiante a eliminar: "))
    if ID in lista_ID:
        borrar= lista_ID.index(ID)
        lista_ID.pop(borrar)
        matriz_Notas.pop(borrar)
        print("se elimino el estudiante:",ID,"con sus notas")
    else:
        print("el numero de documento del estudiante no se encuentra")
def mayor_nota_estudiante(lista_Cursos,lista_ID,matriz_Notas):
    """
    muestra la nota mas alta de un estudiante y el curso de esa nota
    entrada: documento del estudiante para saber su nota mas alta y el cusro de la nota.
    lista de cursos
    lista de estudiantes
    matriz de notas
    salida:muesta el estudiante el curso en la que saco mayor nota
    """
    ID=str(input("ingrese el numero de documento del estudiante para ver su mayor nota y el curso: "))
    nota_alta= 0
    if ID in lista_ID:
        notas = lista_ID.index(ID)
        for elemento in matriz_Notas[notas]:
            if nota_alta < elemento:
                nota_alta = elemento
        fila=matriz_Notas[notas]
        curso=fila.index(nota_alta)
        print(lista_Cursos[curso])
        print("el estudiante con el ID",ID,"tiene la mayor nota en el curso ",lista_Cursos[curso],"con la nota",nota_alta)
    else:
        print("el numero de documento del estudiante no se encuentra")
def promedio_estudiantes(lista_ID,matriz_Notas):
    """
    muestra la nota mas alta de un estudiante y el curso de esa nota
    entrada:
    lista de estudiantes
    matriz de notas
    salida:muestra una lista ordenada de menor a mayor los estudiantes segun la cantidad de cursos
    """
    lista_resultado=[]
    lista_promedio=[]
    for estudiante in lista_ID:
        notas_index=lista_ID.index(estudiante)
        promedio=0
        divido=0 
        for notas in matriz_Notas[notas_index]:
            if notas !=-1 and notas !=-2:
                promedio=notas+promedio
                divido=divido+1
        promedio=promedio/divido
        lista_promedio=[estudiante,promedio]
        lista_resultado.append(lista_promedio)
    reccorrido_resultado=len(lista_resultado)
    for i in range(1,reccorrido_resultado):
        for j in range(0,reccorrido_resultado-1):
            if lista_resultado[j][1]<lista_resultado[j+1][1]:
                temporal=lista_resultado[j] 
                lista_resultado[j]=lista_resultado[j+1]
                lista_resultado[j+1] =temporal 
    print(lista_resultado)
def estudiantes_por_cursos(lista_ID,matriz_Notas):
    """
    muestra la nota mas alta de un estudiante y el curso de esa nota
    entrada:
    lista de estudiantes
    matriz de notas
    salida:muestra una lista ordenada de mayor a menor del promedio de los estudiantes
    """
    lista_materias=[]
    lista_resultado=[]
    for estudiante in lista_ID:
        notas_index=lista_ID.index(estudiante)
        materias_cursadas=0
        for nota in matriz_Notas[notas_index]:
            if nota !=-1 and nota !=-2:
                materias_cursadas=materias_cursadas+1
        lista_materias=[estudiante, materias_cursadas]
        lista_resultado.append(lista_materias)
    reccorrido_resultado=len(lista_resultado)
    for i in range(reccorrido_resultado-1):
        indice_minimo=i
        for j in range(i+1,reccorrido_resultado):
            if lista_resultado[j][1] < lista_resultado[indice_minimo][1]:
                indice_minimo = j
        if indice_minimo != i:
            auxiliar = lista_resultado[i]
            lista_resultado[i] = lista_resultado[indice_minimo]
            lista_resultado[indice_minimo] = auxiliar
    print(lista_resultado)
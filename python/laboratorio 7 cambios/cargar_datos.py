def cargar_datos_estudiantes(nombre_archivo):
    """Carga los datos de estudiantes, cursos y notas del archivo CSV."""
    lista_Cursos = []
    lista_ID = []
    matriz_Notas= []

    with open(nombre_archivo, 'r', encoding="utf-8") as archivo:
        lineas = archivo.readlines()
        linea_Curso= lineas[0].strip()
        elemento_cursos=linea_Curso.split(',')
        for elemento in elemento_cursos:
            lista_Cursos.append(elemento)
        linea_Curso= lineas[1].strip()
        elemento_ID=linea_Curso.split(',')
        for elemento in elemento_ID:
            lista_ID.append(elemento)    
        for indice in range(2, len(lineas)):
            linea_Notas = lineas[indice].strip()
            elementos_notas = linea_Notas.split(',')  
            fila_notas = []
            for elemento in elementos_notas:
                fila_notas.append(float(elemento))
            matriz_Notas.append(fila_notas)
    return (lista_Cursos,lista_ID,matriz_Notas)
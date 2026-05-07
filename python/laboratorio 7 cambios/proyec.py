import math 
import plots 

def cargar_datos_historicos(nombre_archivo):
    """Carga los datos históricos (años como x y estudiantes como y)."""
    años_lista = []
    estudiantes_lista = []
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
        if len(lineas) <= 1:
            return [], []        
        for i in range(1, len(lineas)):
            fila = lineas[i].strip()
            if not fila:
                continue
            datos_fila = fila.split(',')
            if len(datos_fila) >= 2:
                año = int(datos_fila[0].strip())
                estudiantes = int(datos_fila[1].strip())
                años_lista.append(año)
                estudiantes_lista.append(estudiantes)

    return años_lista, estudiantes_lista

def predecir_estudiantes(lista_x, a, b):
    """Calcula la lista de valores estimados (y) usando la función y = ax + b.
    Retorna la lista de las 'Y's (estudiantes estimados).
    """
    lista_y_estimada = []    
    for x in lista_x:
        y_estimada = a * x + b
        lista_y_estimada.append(y_estimada)
        
    return lista_y_estimada

def calcular_mae(lista_y_real, lista_y_estimada):
    if not lista_y_real:
        return 0.0
    
    n = len(lista_y_real)
    suma_error_abs = 0 
    
    for indice in range(n):
        error_absoluto = abs(lista_y_real[indice] - lista_y_estimada[indice])
        suma_error_abs = suma_error_abs + error_absoluto
        
    return suma_error_abs / n
    
def encontrar_mejores_parametros(lista_x, lista_y):
    """Busca la mejor línea (a, b) que minimiza el MAE, probando una línea
    generada por CADA PAR de puntos (x1, y1) y (x2, y2) en el hits.
    """
    n = len(lista_x)    
    mejor_a = 0.0
    mejor_b = 0.0
    min_mae = 0.0     
    primera_linea_encontrada = False    
    if n < 2:
        return 0.0, 0.0, 0.0
    i = 0
    while i < n:
        x1 = lista_x[i]
        y1 = lista_y[i]        
        j = 0
        while j < n:
            if i != j: 
                x2 = lista_x[j]
                y2 = lista_y[j]
                denominador_a = x2 - x1
                if denominador_a == 0:
                    j = j + 1
                    continue 
                a = (y2 - y1) / denominador_a
                b = y1 - (a * x1)
                y_estimada = predecir_estudiantes(lista_x, a, b)
                error_actual = calcular_mae(lista_y, y_estimada)
                if not primera_linea_encontrada:
                    min_mae = error_actual
                    mejor_a = a
                    mejor_b = b
                    primera_linea_encontrada = True
                elif error_actual < min_mae:
                    min_mae = error_actual
                    mejor_a = a
                    mejor_b = b
            j = j + 1
        i = i + 1
    return mejor_a, mejor_b, min_mae

def generar_datos_grafica(años, estudiantes):
    datos_para_plot = []   
    for indice in range(len(años)):
        valor_año = años[indice]
        valor_estudiante = estudiantes[indice]
        coordenada_punto = [valor_año, valor_estudiante]
        datos_para_plot.append(coordenada_punto)
    return datos_para_plot
    
def exportar_grafica_prediccion(datos_para_plot, linea_regresion, años, año_prediccion, estudiantes_predichos):
    print("\n Grafica exportada: \n")
    tupla_prediccion = (año_prediccion, int(round(estudiantes_predichos))) 
    print("La predicción (Año, Estudiantes) ha sido conceptualmente añadida al gráfico: " + str(tupla_prediccion))
    plots.plot_data(datos_para_plot, linea_regresion, años)
    
def mostrar_grafica():
    datos_cargados = cargar_datos_historicos("hist_matriculados.csv")
    hist_años = datos_cargados[0]
    hist_estudiantes = datos_cargados[1]
    a, b, mae_minimo = encontrar_mejores_parametros(hist_años, hist_estudiantes)
    año_prediccion_str = input("Ingrese el año futuro para ver la predicción gráfica (ejemplo: 2028): ")
    año_prediccion = int(año_prediccion_str)
    lista_un_año = [año_prediccion]
    resultado_prediccion = predecir_estudiantes(lista_un_año, a, b)
    prediccion_final = resultado_prediccion[0]
    primer_año_hist = hist_años[0]
    final_rango = año_prediccion + 1
    años_para_grafica = []
    contador_año = primer_año_hist
    while contador_año < final_rango:
        años_para_grafica.append(contador_año)
        contador_año = contador_año + 1
    linea_regresion_extendida = predecir_estudiantes(años_para_grafica, a, b)
    datos_para_plot = generar_datos_grafica(hist_años, hist_estudiantes)
    exportar_grafica_prediccion(datos_para_plot, linea_regresion_extendida, años_para_grafica, año_prediccion, prediccion_final)

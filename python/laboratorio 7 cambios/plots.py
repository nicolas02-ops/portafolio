def plot_data(data, regression_line, years):
  '''
  Grafica los datos y la Regresión Lineal
  Parametros:
    data (list): Lista bidimensional con datos historicos de acuerdo al archivo csv
                 de la forma [[año1, #estudiantes], [año2, #estudiantes]...]
    regression_line(list): Lista de los valores y para la regresión lineal.
    years(list): Lista de años entre 1980 y 2024
  
  Para usarla es necesario usar las librerías numpy y matplotlib.pyplot
  Revise que las librerías se encuentren instaladas en su entorno de trabajo.
  '''
  try:
    import numpy as np
    import matplotlib.pyplot as plt
  except ModuleNotFoundError as error:
    print("No se pudo mostrar la grafica porque falta una dependencia:", error.name)
    print("Instale las librerias necesarias con: pip install numpy matplotlib")
    return

  data = np.array(data)

  plt.figure(figsize=(10, 6))
  plt.plot(data[:, 0], data[:, 1], 'o', label='Data Points')
  plt.plot(years, regression_line, 'r', label='Linear Regression')
  plt.grid(True)
  plt.legend()
  plt.title('Historical Data and Linear Regression')
  plt.xlabel('Year')
  plt.ylabel('Students Enrolled')
  plt.show()

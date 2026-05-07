const terminal = document.getElementById("notas-terminal");
const studentInput = document.getElementById("student-id");
const predictionInput = document.getElementById("prediction-year");
const buttons = document.querySelectorAll("[data-notas-action]");

const courses = ["Curso1", "Curso2", "Curso3", "Curso4", "Curso5"];
let ids = ["1033492448", "1032090603", "1002152167", "1028854736", "1014191590", "1024351175", "1036351870"];
let grades = [
  [-1, 1.1, 4.8, 4.2, 1.5],
  [0.4, 4.4, -1, 4.5, 3.3],
  [2.1, 3.1, 2.5, 1.8, 2.8],
  [3.4, 3.7, 4.2, -2, 3.4],
  [4.6, 4.9, 4.4, 1.6, 3.2],
  [4, 2.4, 2.3, 0.1, 4.1],
  [3.1, 3.7, 2.9, 3.8, 4.8]
];
const historyYears = [1980, 1981, 1982, 1983, 1984, 1985, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2003, 2005, 2006, 2007, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2017, 2018, 2019, 2020, 2022, 2023, 2024];
const historyStudents = [11, 12, 24, 16, 19, 24, 23, 25, 28, 29, 48, 36, 38, 37, 52, 43, 60, 46, 48, 52, 55, 59, 60, 61, 61, 67, 85, 68, 71, 72, 78, 83, 85, 83, 89, 89, 90, 89];
let output = [];

function menu() {
  return [
    "=============================================================",
    "                  MENU UNIVERSIDAD",
    "=============================================================",
    " 1 - Elimnar Estudiante",
    " 2 - Mayor Nota estudiante",
    " 3 - Promedio estudiantes",
    " 4 - Estudiantes por curso",
    " 5 - Mostrar grafica ",
    " 0 - Salir ",
    "Seleccione una opcion [1, 2, 3, 4, 5, 0]:"
  ].join("\n");
}

function render() {
  terminal.textContent = [menu(), ...output].join("\n");
  terminal.scrollTop = terminal.scrollHeight;
}

function findStudent() {
  const id = studentInput.value.trim();
  return { id, index: ids.indexOf(id) };
}

function pythonList(value) {
  if (Array.isArray(value)) {
    return `[${value.map(pythonList).join(", ")}]`;
  }
  if (typeof value === "string") {
    return `'${value}'`;
  }
  return String(value);
}

function calcularMae(real, estimated) {
  let sum = 0;
  for (let index = 0; index < real.length; index += 1) {
    sum += Math.abs(real[index] - estimated[index]);
  }
  return real.length ? sum / real.length : 0.0;
}

function predecirEstudiantes(xs, a, b) {
  const estimated = [];
  for (const x of xs) {
    estimated.push((a * x) + b);
  }
  return estimated;
}

function encontrarMejoresParametros(xs, ys) {
  let bestA = 0.0;
  let bestB = 0.0;
  let minMae = 0.0;
  let firstLine = false;

  if (xs.length < 2) return [0.0, 0.0, 0.0];

  let i = 0;
  while (i < xs.length) {
    const x1 = xs[i];
    const y1 = ys[i];
    let j = 0;
    while (j < xs.length) {
      if (i !== j) {
        const x2 = xs[j];
        const y2 = ys[j];
        const denominatorA = x2 - x1;
        if (denominatorA === 0) {
          j += 1;
          continue;
        }
        const a = (y2 - y1) / denominatorA;
        const b = y1 - (a * x1);
        const yEstimated = predecirEstudiantes(xs, a, b);
        const currentError = calcularMae(ys, yEstimated);
        if (!firstLine) {
          minMae = currentError;
          bestA = a;
          bestB = b;
          firstLine = true;
        } else if (currentError < minMae) {
          minMae = currentError;
          bestA = a;
          bestB = b;
        }
      }
      j += 1;
    }
    i += 1;
  }
  return [bestA, bestB, minMae];
}

function promedioEstudiantes() {
  const result = [];
  for (const student of ids) {
    const notasIndex = ids.indexOf(student);
    let promedio = 0;
    let divido = 0;
    for (const note of grades[notasIndex]) {
      if (note !== -1 && note !== -2) {
        promedio = note + promedio;
        divido = divido + 1;
      }
    }
    promedio = promedio / divido;
    result.push([student, promedio]);
  }
  const recorridoResultado = result.length;
  for (let i = 1; i < recorridoResultado; i += 1) {
    for (let j = 0; j < recorridoResultado - 1; j += 1) {
      if (result[j][1] < result[j + 1][1]) {
        const temporal = result[j];
        result[j] = result[j + 1];
        result[j + 1] = temporal;
      }
    }
  }
  return result;
}

function estudiantesPorCursos() {
  const result = [];
  for (const student of ids) {
    const notasIndex = ids.indexOf(student);
    let materiasCursadas = 0;
    for (const note of grades[notasIndex]) {
      if (note !== -1 && note !== -2) {
        materiasCursadas = materiasCursadas + 1;
      }
    }
    result.push([student, materiasCursadas]);
  }
  const recorridoResultado = result.length;
  for (let i = 0; i < recorridoResultado - 1; i += 1) {
    let indiceMinimo = i;
    for (let j = i + 1; j < recorridoResultado; j += 1) {
      if (result[j][1] < result[indiceMinimo][1]) {
        indiceMinimo = j;
      }
    }
    if (indiceMinimo !== i) {
      const auxiliar = result[i];
      result[i] = result[indiceMinimo];
      result[indiceMinimo] = auxiliar;
    }
  }
  return result;
}

function handleAction(action) {
  output.push(`Seleccione una opcion [1, 2, 3, 4, 5, 0]: ${action}`);
  const student = findStudent();

  if (action === "0") {
    output.push("");
    output.push(" Gracias por usar el sistema Saliendo...");
  }

  if (action === "1") {
    output.push("Elimnar Estudiante");
    output.push(`ingrese el numero de documento del estudiante a eliminar: ${student.id}`);
    if (student.index >= 0) {
      ids.splice(student.index, 1);
      grades.splice(student.index, 1);
      output.push(`se elimino el estudiante: ${student.id} con sus notas`);
    } else {
      output.push("el numero de documento del estudiante no se encuentra");
    }
  }

  if (action === "2") {
    output.push("Mayor Nota estudiante");
    output.push(`ingrese el numero de documento del estudiante para ver su mayor nota y el curso: ${student.id}`);
    if (student.index >= 0) {
      const row = grades[student.index];
      const maxGrade = Math.max(...row);
      const course = courses[row.indexOf(maxGrade)];
      output.push(course);
      output.push(`el estudiante con el ID ${student.id} tiene la mayor nota en el curso  ${course} con la nota ${maxGrade}`);
    } else {
      output.push("el numero de documento del estudiante no se encuentra");
    }
  }

  if (action === "3") {
    output.push("Promedio estudiantes");
    output.push(pythonList(promedioEstudiantes()));
  }

  if (action === "4") {
    output.push(pythonList(estudiantesPorCursos()));
    output.push("Estudiantes por curso");
  }

  if (action === "5") {
    output.push("Mostrar grafica");
    const year = Number.parseInt(predictionInput.value, 10) || 2028;
    output.push(`Ingrese el ano futuro para ver la prediccion grafica (ejemplo: 2028): ${year}`);
    const [a, b] = encontrarMejoresParametros(historyYears, historyStudents);
    const prediction = predecirEstudiantes([year], a, b)[0];
    output.push("");
    output.push(" Grafica exportada: ");
    output.push("");
    output.push(`La prediccion (Ano, Estudiantes) ha sido conceptualmente anadida al grafico: (${year}, ${Math.round(prediction)})`);
    output.push("No se pudo mostrar la grafica porque falta una dependencia: matplotlib");
    output.push("Instale las librerias necesarias con: pip install numpy matplotlib");
  }

  if (!["0", "1", "2", "3", "4", "5"].includes(action)) {
    output.push("");
    output.push(" Opcion no valida. Intente de nuevo.");
  }

  render();
}

buttons.forEach((button) => button.addEventListener("click", () => handleAction(button.dataset.notasAction)));
render();

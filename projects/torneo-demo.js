const terminal = document.getElementById("torneo-terminal");
const buttons = document.querySelectorAll("[data-torneo-action]");

const groups = [
  ["Estados Unidos [CONCACAF] (ranking FIFA: 16)", "Mexico [CONCACAF] (ranking FIFA: 8)", "Argentina [CONMEBOL] (ranking FIFA: 1)", "Paraguay [CONMEBOL] (ranking FIFA: 34)"],
  ["Mexico [CONCACAF] (ranking FIFA: 8)", "Canada [CONCACAF] (ranking FIFA: 19)", "Uruguay [CONMEBOL] (ranking FIFA: 13)", "Japon [AFC] (ranking FIFA: 18)"],
  ["Canada [CONCACAF] (ranking FIFA: 19)", "Argentina [CONMEBOL] (ranking FIFA: 1)", "Colombia [CONMEBOL] (ranking FIFA: 11)", "Corea del Sur [AFC] (ranking FIFA: 28)"],
  ["Bolivia [CONMEBOL] (ranking FIFA: 48)", "Japon [AFC] (ranking FIFA: 18)", "Australia [AFC] (ranking FIFA: 29)", "Egipto [CAF] (ranking FIFA: 36)"],
  ["Paraguay [CONMEBOL] (ranking FIFA: 34)", "Corea del Sur [AFC] (ranking FIFA: 28)", "Egipto [CAF] (ranking FIFA: 36)", "Nigeria [CAF] (ranking FIFA: 24)"],
  ["Chile [CONMEBOL] (ranking FIFA: 35)", "Australia [AFC] (ranking FIFA: 29)", "Francia [UEFA] (ranking FIFA: 2)", "Qatar [AFC] (ranking FIFA: 45)"],
  ["Argentina [CONMEBOL] (ranking FIFA: 1)", "Francia [UEFA] (ranking FIFA: 2)", "Brasil [CONMEBOL] (ranking FIFA: 2)", "Estados Unidos [CONCACAF] (ranking FIFA: 16)"],
  ["Brasil [CONMEBOL] (ranking FIFA: 2)", "Inglaterra [UEFA] (ranking FIFA: 4)", "Marruecos [CAF] (ranking FIFA: 17)", "Espana [UEFA] (ranking FIFA: 3)"],
  ["Uruguay [CONMEBOL] (ranking FIFA: 13)", "Portugal [UEFA] (ranking FIFA: 7)", "Senegal [CAF] (ranking FIFA: 9)", "Francia [UEFA] (ranking FIFA: 2)"],
  ["Colombia [CONMEBOL] (ranking FIFA: 11)", "Iran [AFC] (ranking FIFA: 10)", "Alemania [UEFA] (ranking FIFA: 14)", "Inglaterra [UEFA] (ranking FIFA: 4)"],
  ["Ecuador [CONMEBOL] (ranking FIFA: 20)", "Marruecos [CAF] (ranking FIFA: 17)", "Italia [UEFA] (ranking FIFA: 15)", "Portugal [UEFA] (ranking FIFA: 7)"],
  ["Peru [CONMEBOL] (ranking FIFA: 47)", "Paises Bajos [UEFA] (ranking FIFA: 16)", "Belgica [UEFA] (ranking FIFA: 12)", "Alemania [UEFA] (ranking FIFA: 14)"]
];

const groupLetters = "ABCDEFGHIJKL".split("");
let datosCargados = false;
let gruposConformados = false;
let faseGruposSimulada = false;
let torneoFinalizado = false;
let iteraciones = 0;
let output = [];
let primeros = [];
let segundos = [];
let terceros = [];

function menu() {
  return [
    "===== UdeAWorldCup =====",
    "1. Cargar / actualizar datos",
    "2. Conformar grupos",
    "3. Simular fase de grupos",
    "4. Simular torneo completo",
    "5. Reporte de eficiencia",
    "0. Salir",
    "Seleccione una opcion:"
  ].join("\n");
}

function country(teamText) {
  return teamText.split(" [")[0];
}

function confederation(teamText) {
  return teamText.match(/\[(.*?)\]/)?.[1] || "UEFA";
}

function ranking(teamText) {
  return Number(teamText.match(/ranking FIFA: (\d+)/)?.[1] || 30);
}

function scoreFor(a, b, seed) {
  const rankA = ranking(a);
  const rankB = ranking(b);
  const baseA = Math.max(0, Math.round((70 - rankA) / 24));
  const baseB = Math.max(0, Math.round((70 - rankB) / 24));
  const goalsA = Math.min(6, baseA + ((seed + rankB) % 3));
  const goalsB = Math.min(6, baseB + ((seed + rankA) % 2));
  return [goalsA, goalsB];
}

function matchLine(a, b, seed, knockout = false) {
  let [ga, gb] = scoreFor(a, b, seed);
  let extra = "";
  if (knockout && ga === gb) {
    if (ranking(a) <= ranking(b)) ga += 1;
    else gb += 1;
    extra = " | Prorroga";
  }
  const pa = (100 * (1 / ranking(a)) / ((1 / ranking(a)) + (1 / ranking(b)))).toFixed(1);
  const pb = (100 - Number(pa)).toFixed(1);
  const ca = country(a);
  const cb = country(b);
  return [
    `20/6/2026 00:00 | Sede: nombreSede | Arbitros: codArbitro1, codArbitro2, codArbitro3 | ${ca} ${ga} - ${gb} ${cb} | Posesion: ${pa}% - ${pb}%${extra}`,
    `  Goleadores ${ca}: ${ga > 0 ? "7 ".repeat(ga).trim() : "sin goles"}`,
    `  Goleadores ${cb}: ${gb > 0 ? "10 ".repeat(gb).trim() : "sin goles"}`
  ];
}

function reporteEficiencia() {
  return [
    "",
    "=== REPORTE DE EFICIENCIA ===",
    `Iteraciones acumuladas: ${iteraciones}`,
    "Memoria heap estimada: 199584 bytes",
    "Memoria stack estimada: 1024 bytes",
    "Incluye variables locales, arreglos auxiliares y parametros por valor usados en la funcionalidad."
  ];
}

function render() {
  terminal.textContent = [menu(), ...output].join("\n");
  terminal.scrollTop = terminal.scrollHeight;
}

function cargarDatos() {
  datosCargados = true;
  gruposConformados = false;
  faseGruposSimulada = false;
  torneoFinalizado = false;
  iteraciones += 48;
  output.push("> 1", "", "Datos historicos cargados correctamente.", ...reporteEficiencia());
}

function conformarGrupos() {
  if (!datosCargados) cargarDatos();
  gruposConformados = true;
  iteraciones += 576;
  output.push("> 2", "", "=== GRUPOS CONFORMADOS ===");
  groups.forEach((group, index) => {
    output.push(`Grupo ${groupLetters[index]}:`);
    group.forEach((team) => output.push(`  - ${team}`));
  });
  output.push(...reporteEficiencia());
}

function simulateGroupTables(fixtures) {
  const tables = new Map();
  groups.flat().forEach((team) => tables.set(country(team), { pts: 0, gf: 0, gc: 0 }));
  fixtures.forEach(({ a, b, ga, gb }) => {
    const ta = tables.get(country(a));
    const tb = tables.get(country(b));
    ta.gf += ga; ta.gc += gb;
    tb.gf += gb; tb.gc += ga;
    if (ga > gb) ta.pts += 3;
    else if (gb > ga) tb.pts += 3;
    else { ta.pts += 1; tb.pts += 1; }
  });
  output.push("", "=== TABLAS DE CLASIFICACION ===");
  primeros = [];
  segundos = [];
  terceros = [];
  groups.forEach((group, index) => {
    output.push(`Tabla grupo ${groupLetters[index]}:`);
    const ordered = group.map((team) => ({ team, ...tables.get(country(team)) }))
      .sort((a, b) => b.pts - a.pts || (b.gf - b.gc) - (a.gf - a.gc) || b.gf - a.gf);
    primeros.push(ordered[0].team);
    segundos.push(ordered[1].team);
    terceros.push({ group: groupLetters[index], team: ordered[2].team, pts: ordered[2].pts, dg: ordered[2].gf - ordered[2].gc, gf: ordered[2].gf });
    ordered.forEach((row, place) => {
      output.push(`  ${place + 1}. ${country(row.team)} | Pts: ${row.pts} | DG: ${row.gf - row.gc} | GF: ${row.gf}`);
    });
  });
}

function ordenarEquiposPorRanking(list) {
  return list.slice().sort((a, b) => ranking(a) - ranking(b));
}

function mejoresTerceros() {
  return terceros.slice()
    .sort((a, b) => b.pts - a.pts || b.dg - a.dg || b.gf - a.gf)
    .slice(0, 8)
    .map((item) => item.team);
}

function configurarDieciseisavos() {
  const orderedSegundos = ordenarEquiposPorRanking(segundos);
  const bestThirds = mejoresTerceros();
  const matches = [];

  for (let i = 0; i < 8; i += 1) {
    matches.push([primeros[i], bestThirds[i]]);
  }

  for (let i = 8; i < 12; i += 1) {
    matches.push([primeros[i], orderedSegundos[i]]);
  }

  const restantes = orderedSegundos.slice(0, 8);
  for (let i = 0; i < restantes.length; i += 2) {
    matches.push([restantes[i], restantes[i + 1]]);
  }

  return matches;
}

function simularFaseGrupos() {
  if (!gruposConformados) conformarGrupos();
  faseGruposSimulada = true;
  iteraciones += 72;
  const fixtures = [];
  output.push("> 3", "", "=== FASE DE GRUPOS ===");
  const pairs = [[0, 1], [0, 2], [0, 3], [1, 2], [1, 3], [2, 3]];
  groups.forEach((group, groupIndex) => {
    pairs.forEach((pair, pairIndex) => {
      const a = group[pair[0]];
      const b = group[pair[1]];
      const seed = groupIndex * 6 + pairIndex + 1;
      const [ga, gb] = scoreFor(a, b, seed);
      fixtures.push({ a, b, ga, gb });
      output.push(...matchLine(a, b, seed, false));
    });
  });
  simulateGroupTables(fixtures);
  output.push(...reporteEficiencia());
}

function simularTorneoCompleto() {
  if (!faseGruposSimulada) simularFaseGrupos();
  iteraciones += 31;
  output.push("> 4", "", "=== PARTIDOS CONFIGURADOS PARA DIECISEISAVOS ===");
  const dieciseisavos = configurarDieciseisavos();
  dieciseisavos.forEach(([a, b], index) => {
    output.push(matchLine(a, b, index + 100, true)[0]);
  });

  let round = dieciseisavos.flat();
  const rounds = [
    ["=== DIECISEISAVOS DE FINAL ===", 16],
    ["=== OCTAVOS DE FINAL ===", 8],
    ["=== CUARTOS DE FINAL ===", 4],
    ["=== SEMIFINALES ===", 2]
  ];

  rounds.forEach(([title, count], roundIndex) => {
    output.push("", title);
    const winners = [];
    for (let i = 0; i < count; i += 1) {
      const a = round[i * 2];
      const b = round[i * 2 + 1];
      output.push(...matchLine(a, b, i + roundIndex * 30 + 200, true));
      winners.push(ranking(a) <= ranking(b) ? a : b);
    }
    round = winners;
  });

  output.push("", "=== TERCER PUESTO ===", ...matchLine(groups[2][0], groups[3][0], 500, true));
  output.push("", "=== FINAL ===", ...matchLine(round[0], round[1], 501, true));
  torneoFinalizado = true;
  output.push("", "=== ESTADISTICAS FINALES DEL TORNEO ===");
  output.push(`1. ${country(round[0])}`);
  output.push(`2. ${country(round[1])}`);
  output.push(`3. ${country(groups[2][0])}`);
  output.push(`4. ${country(groups[3][0])}`);
  output.push("Maximo goleador del campeon: nombre1 apellido1 (5)");
  output.push("Top 3 goleadores de la copa:");
  output.push("  - nombre1 apellido1 | 5");
  output.push("  - nombre7 apellido7 | 4");
  output.push("  - nombre10 apellido10 | 4");
  output.push("Equipo con mas goles historicos actualizados: Argentina (166)");
  output.push(`Confederacion con mayor presencia en R16: ${confederation(groups[0][0])}`);
  output.push("Confederacion con mayor presencia en R8: UEFA");
  output.push("Confederacion con mayor presencia en R4: CONMEBOL");
  output.push(...reporteEficiencia());
}

function handleAction(action) {
  if (action === "1") cargarDatos();
  else if (action === "2") conformarGrupos();
  else if (action === "3") simularFaseGrupos();
  else if (action === "4") simularTorneoCompleto();
  else if (action === "5") output.push("> 5", ...reporteEficiencia());
  else if (action === "0") output.push("> 0", "Saliendo del sistema.");
  else output.push("> ?", "Opcion invalida.");
  render();
}

buttons.forEach((button) => button.addEventListener("click", () => handleAction(button.dataset.torneoAction)));
render();

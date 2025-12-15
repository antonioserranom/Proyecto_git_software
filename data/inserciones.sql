BEGIN TRANSACTION;

-- ==========================================================
-- 1. COORDINADORES (5)
-- ==========================================================
INSERT OR IGNORE INTO COORDINADOR (id, nombre, email, facultad, responsabilidades) VALUES
('90000000R', 'Roberto Jefe', 'coord1@uco.es', 'Escuela Politécnica', 'Planificación Anual'),
('90000001W', 'Laura Mando', 'coord2@uco.es', 'Facultad de Ciencias', 'Asignación de Tutores'),
('90000002A', 'Carlos Director', 'coord3@uco.es', 'Derecho', 'Gestión de Incidencias'),
('90000003G', 'Ana Supervisora', 'coord4@uco.es', 'Medicina', 'Calidad Académica'),
('90000004M', 'Luis Gestor', 'coord5@uco.es', 'Filosofía', 'Relaciones Externas');

-- ==========================================================
-- 2. TUTORES (10)
-- ==========================================================
INSERT OR IGNORE INTO TUTOR (id, nombre, email, horario, area_conocimiento, facultad) VALUES
('80000000H', 'Dr. Gregorio House', 'tutor1@uco.es', 'Lunes 10:00-14:00', 'Diagnóstico', 'Medicina'),
('80000001L', 'Alan Turing', 'tutor2@uco.es', 'Martes 09:00-11:00', 'Inteligencia Artificial', 'Politécnica'),
('80000002C', 'Ada Lovelace', 'tutor3@uco.es', 'Miércoles 16:00-18:00', 'Programación', 'Politécnica'),
('80000003K', 'Marie Curie', 'tutor4@uco.es', 'Jueves 10:00-12:00', 'Física Nuclear', 'Ciencias'),
('80000004E', 'Isaac Newton', 'tutor5@uco.es', 'Viernes 11:00-13:00', 'Física Clásica', 'Ciencias'),
('80000005T', 'Sigmund Freud', 'tutor6@uco.es', 'Lunes 16:00-20:00', 'Psicología', 'Medicina'),
('80000006R', 'Grace Hopper', 'tutor7@uco.es', 'Martes 12:00-14:00', 'Sistemas Operativos', 'Politécnica'),
('80000007W', 'Albert Einstein', 'tutor8@uco.es', 'Miércoles 09:00-13:00', 'Relatividad', 'Ciencias'),
('80000008A', 'Nikola Tesla', 'tutor9@uco.es', 'Jueves 17:00-19:00', 'Electrónica', 'Politécnica'),
('80000009G', 'Charles Darwin', 'tutor10@uco.es', 'Viernes 10:00-12:00', 'Biología', 'Ciencias');

-- ==========================================================
-- 3. ESTUDIANTES (50) - TODOS SIN TUTOR (NULL)
-- ==========================================================

-- Grupo Medicina (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000000D', 'Alumno Uno', 'alu1@uco.es', 'Grado Medicina', 'Residencia', 'Adecuado', NULL),
('70000001X', 'Alumno Dos', 'alu2@uco.es', 'Grado Medicina', 'Piso', 'Riesgo', NULL),
('70000002B', 'Alumno Tres', 'alu3@uco.es', 'Grado Medicina', 'Casa', 'Excelente', NULL),
('70000003N', 'Alumno Cuatro', 'alu4@uco.es', 'Grado Medicina', 'Residencia', 'Adecuado', NULL),
('70000004J', 'Alumno Cinco', 'alu5@uco.es', 'Grado Medicina', 'Piso', 'Adecuado', NULL);

-- Grupo Informática (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000005Z', 'Alumno Seis', 'alu6@uco.es', 'Ing. Informática', 'Casa', 'Adecuado', NULL),
('70000006S', 'Alumno Siete', 'alu7@uco.es', 'Ing. Informática', 'Residencia', 'Riesgo', NULL),
('70000007Q', 'Alumno Ocho', 'alu8@uco.es', 'Ing. Informática', 'Piso', 'Excelente', NULL),
('70000008V', 'Alumno Nueve', 'alu9@uco.es', 'Ing. Informática', 'Casa', 'Adecuado', NULL),
('70000009H', 'Alumno Diez', 'alu10@uco.es', 'Ing. Informática', 'Piso', 'Adecuado', NULL);

-- Grupo Software (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000010L', 'Alumno Once', 'alu11@uco.es', 'Ing. Software', 'Residencia', 'Adecuado', NULL),
('70000011C', 'Alumno Doce', 'alu12@uco.es', 'Ing. Software', 'Piso', 'Adecuado', NULL),
('70000012K', 'Alumno Trece', 'alu13@uco.es', 'Ing. Software', 'Casa', 'Adecuado', NULL),
('70000013E', 'Alumno Catorce', 'alu14@uco.es', 'Ing. Software', 'Residencia', 'Riesgo', NULL),
('70000014T', 'Alumno Quince', 'alu15@uco.es', 'Ing. Software', 'Piso', 'Excelente', NULL);

-- Grupo Interés IA (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000015R', 'Alumno Dieciseis', 'alu16@uco.es', 'Interés en Inteligencia Artificial', 'Casa', 'Adecuado', NULL),
('70000016W', 'Alumno Diecisiete', 'alu17@uco.es', 'Interés en Inteligencia Artificial', 'Residencia', 'Adecuado', NULL),
('70000017A', 'Alumno Dieciocho', 'alu18@uco.es', 'Interés en Inteligencia Artificial', 'Piso', 'Riesgo', NULL),
('70000018G', 'Alumno Diecinueve', 'alu19@uco.es', 'Interés en Inteligencia Artificial', 'Casa', 'Excelente', NULL),
('70000019M', 'Alumno Veinte', 'alu20@uco.es', 'Interés en Inteligencia Artificial', 'Piso', 'Adecuado', NULL);

-- Grupo Física (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000020Y', 'Alumno Veintiuno', 'alu21@uco.es', 'Física Teórica', 'Residencia', 'Adecuado', NULL),
('70000021F', 'Alumno Veintidos', 'alu22@uco.es', 'Física Teórica', 'Piso', 'Adecuado', NULL),
('70000022P', 'Alumno Veintitres', 'alu23@uco.es', 'Física Teórica', 'Casa', 'Adecuado', NULL),
('70000023D', 'Alumno Veinticuatro', 'alu24@uco.es', 'Física Teórica', 'Residencia', 'Riesgo', NULL),
('70000024X', 'Alumno Veinticinco', 'alu25@uco.es', 'Física Teórica', 'Piso', 'Excelente', NULL);

-- Grupo Historia (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000025B', 'Alumno Veintiseis', 'alu26@uco.es', 'Grado Historia', 'Casa', 'Adecuado', NULL),
('70000026N', 'Alumno Veintisiete', 'alu27@uco.es', 'Grado Historia', 'Residencia', 'Adecuado', NULL),
('70000027J', 'Alumno Veintiocho', 'alu28@uco.es', 'Grado Historia', 'Piso', 'Adecuado', NULL),
('70000028Z', 'Alumno Veintinueve', 'alu29@uco.es', 'Grado Historia', 'Casa', 'Adecuado', NULL),
('70000029S', 'Alumno Treinta', 'alu30@uco.es', 'Grado Historia', 'Piso', 'Adecuado', NULL);

-- Grupo Psicología (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000030Q', 'Alumno TreintaUno', 'alu31@uco.es', 'Psicología Clínica', 'Residencia', 'Adecuado', NULL),
('70000031V', 'Alumno TreintaDos', 'alu32@uco.es', 'Psicología Clínica', 'Piso', 'Adecuado', NULL),
('70000032H', 'Alumno TreintaTres', 'alu33@uco.es', 'Medicina Interna', 'Casa', 'Adecuado', NULL),
('70000033L', 'Alumno TreintaCuatro', 'alu34@uco.es', 'Medicina Interna', 'Residencia', 'Riesgo', NULL),
('70000034C', 'Alumno TreintaCinco', 'alu35@uco.es', 'Medicina Interna', 'Piso', 'Excelente', NULL);

-- Grupo Ing. Eléctrica (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000035K', 'Alumno TreintaSeis', 'alu36@uco.es', 'Ing. Eléctrica', 'Casa', 'Adecuado', NULL),
('70000036E', 'Alumno TreintaSiete', 'alu37@uco.es', 'Ing. Eléctrica', 'Residencia', 'Adecuado', NULL),
('70000037T', 'Alumno TreintaOcho', 'alu38@uco.es', 'Ing. Eléctrica', 'Piso', 'Adecuado', NULL),
('70000038R', 'Alumno TreintaNueve', 'alu39@uco.es', 'Ing. Eléctrica', 'Casa', 'Adecuado', NULL),
('70000039W', 'Alumno Cuarenta', 'alu40@uco.es', 'Ing. Eléctrica', 'Piso', 'Adecuado', NULL);

-- Grupo Biología (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000040A', 'Alumno CuarentaUno', 'alu41@uco.es', 'Biología', 'Residencia', 'Adecuado', NULL),
('70000041G', 'Alumno CuarentaDos', 'alu42@uco.es', 'Biología', 'Piso', 'Adecuado', NULL),
('70000042M', 'Alumno CuarentaTres', 'alu43@uco.es', 'Biología', 'Casa', 'Adecuado', NULL),
('70000043Y', 'Alumno CuarentaCuatro', 'alu44@uco.es', 'Biología', 'Residencia', 'Adecuado', NULL),
('70000044F', 'Alumno CuarentaCinco', 'alu45@uco.es', 'Biología', 'Piso', 'Adecuado', NULL);

-- Grupo General (Sin asignar)
INSERT OR IGNORE INTO ESTUDIANTE (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('70000045P', 'Alumno CuarentaSeis', 'alu46@uco.es', 'General', 'Casa', 'Adecuado', NULL),
('70000046D', 'Alumno CuarentaSiete', 'alu47@uco.es', 'General', 'Residencia', 'Adecuado', NULL),
('70000047X', 'Alumno CuarentaOcho', 'alu48@uco.es', 'General', 'Piso', 'Adecuado', NULL),
('70000048B', 'Alumno CuarentaNueve', 'alu49@uco.es', 'General', 'Casa', 'Adecuado', NULL),
('70000049N', 'Alumno Cincuenta', 'alu50@uco.es', 'General', 'Piso', 'Adecuado', NULL);

COMMIT;

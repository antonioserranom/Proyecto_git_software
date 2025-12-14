INSERT INTO Coordinador (id, nombre, email, facultad, responsabilidades) VALUES
('00000001A', 'Admin Principal', 'admin@uco.es', 'Escuela Politécnica Superior', 'Gestión Total'),
('11111111H', 'Laura García', 'cc1gacal@uco.es', 'Facultad de Ciencias', 'Coordinación de Primero');

INSERT INTO Tutor (id, nombre, email, horario, area_conocimiento, facultad) VALUES
('22222222J', 'Dr. Antonio Pérez', 'antonio.perez@uco.es', 'Lunes 10:00-12:00', 'Ingeniería Software', 'EPS'),
('33333333P', 'Dra. Marta López', 'marta.lopez@uco.es', 'Martes 16:00-18:00', 'Matemáticas', 'Ciencias'),
('44444444D', 'Prof. Juan Ruiz', 'juan.ruiz@uco.es', 'Jueves 11:00-13:00', 'Física', 'Ciencias');

INSERT INTO Estudiante (id, nombre, email, informacion_academica, alojamiento, progreso, id_tutor) VALUES
('55555555K', 'Carlos Perez', 'carlos.per@uco.es', 'Grado Ing. Informática', 'Residencia', 'Adecuado', '22222222J'),
('66666666L', 'Ana Sánchez', 'ana.san@uco.es', 'Grado Matemáticas', 'Piso compartido', 'Riesgo', '33333333P'),
('77777777M', 'Luis Serrano', 'luis.ser@uco.es', 'Grado Física', 'Domicilio familiar', 'Adecuado', NULL);

INSERT INTO Chat (id_estudiante, id_tutor, fecha_creacion) VALUES
('55555555K', '22222222J', '2024-09-15 09:00:00');

INSERT INTO Mensaje (id_chat, id_emisor, contenido, fecha_envio) VALUES
(1, '55555555K', 'Hola profesor, ¿cuándo puedo ir a revisión?', '2024-09-15 09:05:00'),
(1, '22222222J', 'Hola Carlos, pásate el lunes en mi horario.', '2024-09-15 10:00:00');

INSERT INTO Alerta (id_estudiante, motivo, estado, comentarios, fecha) VALUES
('66666666L', 'Bajo rendimiento en Cálculo', 'En seguimiento', 'Se ha contactado con el alumno, pendiente de reunión', '2024-10-01 12:00:00'),
('66666666L', 'Faltas de asistencia reiteradas', 'Pendiente', '', '2024-10-05 09:30:00');

INSERT INTO Asignaciones (estudiante_id, tutor_id, criterios, fecha_asignacion) VALUES
('55555555K', '22222222J', 'Asignación Manual', '2024-09-01 10:00:00'),
('66666666L', '33333333P', 'Asignación Automática', '2024-09-15 09:05:00');

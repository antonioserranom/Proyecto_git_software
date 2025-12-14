
Create table TUTOR(
	id VARCHAR(9) primary key,
	nombre VARCHAR(100) NOT NULL,
	email VARCHAR(100) NOT NULL,
	horario VARCHAR(50),
	area_conocimiento VARCHAR(100),
	facultad VARCHAR(100)
);

Create table ESTUDIANTE(
	id VARCHAR(9) primary key,
	nombre VARCHAR(100),
	email VARCHAR(100),
	informacion_academica VARCHAR(255),
	alojamiento VARCHAR(100),
	progreso VARCHAR(50),
	id_tutor VARCHAR (9),
	FOREIGN KEY (id_tutor) REFERENCES TUTOR(id)
);

Create table COORDINADOR(
	id VARCHAR(9) primary key,
	nombre VARCHAR(100),
	email VARCHAR(100),
	facultad VARCHAR(100),
	responsabilidades VARCHAR(255)
);

Create table ALERTA(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	id_estudiante VARCHAR(9) NOT NULL,
	motivo VARCHAR(255),
	fecha DATETIME DEFAULT CURRENT_TIMESTAMP,
	Estado VARCHAR(20) DEFAULT 'Pendiente',
	Comentarios VARCHAR(255),
	
	FOREIGN KEY (id_estudiante) REFERENCES ESTUDIANTE(id),
	CONSTRAINT CHK_EstadoValido CHECK (
        Estado IN ('En seguimiento', 'Pendiente', 'Resuelta')
    )
);

Create Table CHAT(
    id_chat INTEGER PRIMARY KEY AUTOINCREMENT,
    id_estudiante VARCHAR(9) NOT NULL,
    id_tutor VARCHAR(9) NOT NULL,
    fecha_creacion DATETIME DEFAULT CURRENT_TIMESTAMP,
	UNIQUE(id_estudiante, id_tutor),
	FOREIGN KEY (id_estudiante) REFERENCES Estudiante(id),
	FOREIGN KEY (id_tutor) REFERENCES Tutor(id)
);

CREATE TABLE MENSAJE(
    id_mensaje INTEGER PRIMARY KEY AUTOINCREMENT,
    id_chat INTEGER NOT NULL,
	id_emisor VARCHAR(9) NOT NULL,
    contenido TEXT NOT NULL,
    fecha_envio DATETIME DEFAULT CURRENT_TIMESTAMP,

	FOREIGN KEY (id_chat) REFERENCES Chat(id_chat) ON DELETE CASCADE
);


CREATE TABLE ASIGNACIONES(
    id INTEGER PRIMARY KEY AUTOINCREMENT,

    estudiante_id VARCHAR(9) NOT NULL,
    tutor_id VARCHAR(9) NOT NULL,
    criterios TEXT,
    fecha_asignacion DATETIME DEFAULT CURRENT_TIMESTAMP,

    modificaciones TEXT, 

	FOREIGN KEY (estudiante_id) REFERENCES Estudiante(id),
	FOREIGN KEY (tutor_id) REFERENCES Tutor(id)
);

Create table TUTOR(
	id VARCHAR(9) primary key,
	nombre VARCHAR(100),
	email VARCHAR(100),
	horario VARCHAR(50),
	facultad VARCHAR(100)
);

Create table ESTUDIANTE(
	id VARCHAR(9) primary key,
	nombre VARCHAR(100),
	email VARCHAR(100),
	informacion_academica VARCHAR(255),
	id_tutor VARCHAR (9),
	
	foreign KEY (id_tutor) REFERENCES TUTOR(id)
);

Create table COORDINADOR(
	id VARCHAR(9) primary key,
	nombre VARCHAR(100),
	email VARCHAR(100),
	facultad VARCHAR(100),
	responsabilidades VARCHAR(255),
)

Create table Alerta(
	id_estudiante VARCHAR(9),
	motivo VARCHAR(255),
	fecha DATE,
	Estado VARCHAR(20),
	Comentarios VARCHAR(255),
	
	PRIMARY KEY (id_estudiante, fecha),
	foreign KEY (id_estudiante) REFERENCES ESTUDIANTE(id),
	CONSTRAINT CHK_EstadoValido CHECK (
        Estado IN ('en seguimiento', 'pendiente', 'resuelta')
    )
);

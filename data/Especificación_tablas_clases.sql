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

Create Table Chat (
    id_chat INT PRIMARY KEY,
    id_estudiante VARCHAR(20) NOT NULL,
    id_tutor VARCHAR(20) NOT NULL,
    fecha_creacion DATETIME DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_chat_estudiante FOREIGN KEY (id_estudiante) REFERENCES Estudiante(id_usuario),
    CONSTRAINT fk_chat_tutor FOREIGN KEY (id_tutor) REFERENCES Tutor(id_usuario)
);

CREATE TABLE Mensaje (
    id_mensaje INT PRIMARY KEY,
    id_chat INT NOT NULL,
    contenido TEXT NOT NULL,
    fecha_envio DATETIME DEFAULT
    
    enviado_por_estudiante BOOLEAN NOT NULL,

    CONSTRAINT fk_mensaje_chat FOREIGN KEY (id_chat) REFERENCES Chat(id_chat) ON DELETE CASCADE
);


CREATE TABLE Asignaciones (
    id INT PRIMARY KEY,

    estudiante_id INT NOT NULL,
    tutor_id INT NOT NULL,
    
    criterios TEXT,
    fecha_asignacion DATETIME DEFAULT CURRENT_TIMESTAMP,

    modificaciones TEXT, 

    CONSTRAINT fk_estudiante FOREIGN KEY (estudiante_id) REFERENCES Estudiantes(id),
    CONSTRAINT fk_tutor FOREIGN KEY (tutor_id) REFERENCES Tutores(id)
);

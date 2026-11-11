Algoritmo proyectox
	Definir uNombre, uMatricula, uCorreo, uTelefono Como Caracter
	Definir uActivo Como Entero
	Dimension uNombre[100], uMatricula[100], uCorreo[100], uTelefono[100], uActivo[100]
	
	Definir lTitulo, lEditorial, lAutor, lAnio, lCategoria Como Caracter
	Definir lDisp, lVeces, lActivo Como Entero
	Dimension lTitulo[500], lEditorial[500], lAutor[500], lAnio[500], lCategoria[500]
	Dimension lDisp[500], lVeces[500], lActivo[500]
	
	Definir pFechaP, pFechaD Como Caracter
	Definir pUsuario, pLibro, pActivo Como Entero
	Dimension pUsuario[1000], pLibro[1000], pFechaP[1000], pFechaD[1000], pActivo[1000]
	
	Definir mFecha Como Caracter
	Definir mTipo, mUsuario, mLibro Como Entero
	Dimension mTipo[2000], mUsuario[2000], mLibro[2000], mFecha[2000]
	
	Definir orden Como Entero
	Dimension orden[500]
	Definir nU, nL, nP, nM Como Entero
	Definir op, opU, opL, opP, opD, opR, opE Como Entero
	Definir id, idU, idL, pos, i, j, total, encontrados, yaVista, limite, aux, lb, cont Como Entero
	Definir texto, buscado, campo, tmp, resp, nombre, titulo, estado, pausa Como Caracter
	Definir salir, coincide Como Logico
	
	nU = 0
	nL = 0
	nP = 0
	nM = 0
	salir <- Falso
	
	Mientras salir = Falso Hacer
		Limpiar Pantalla
		Mostrar "Bienvenido a su biblioteca virtual"
		Mostrar "Por favor, elija una opcion"
		Mostrar "1.-Administrar usuarios"
		Mostrar "2.-Administrar libros"
		Mostrar "3.-Prestamos"
		Mostrar "4.-Devoluciones"
		Mostrar "5.-Reportes"
		Mostrar "0.-Salir"
		Leer op
		Limpiar Pantalla
		
		Segun op Hacer
			
			1:
				opU <- -1
				Mientras opU <> 0 Hacer
					Limpiar Pantalla
					Mostrar "Que desea hacer"
					Mostrar "1.-Registrar informacion"
					Mostrar "2.-Modificar informacion"
					Mostrar "3.-Eliminar usuarios"
					Mostrar "4.-Buscar usuarios"
					Mostrar "5.-Consultar usuarios registrados"
					Mostrar "6.-Consultar historial de un usuario"
					Mostrar "0.-Regresar al menu principal"
					Leer opU
					Limpiar Pantalla
					
					Segun opU Hacer
						1:
							Si nU >= 100 Entonces
								Mostrar "Se alcanzo el limite de usuarios."
							SiNo
								nU <- nU + 1
								Mostrar "Ingrese su nombre completo"
								Leer uNombre[nU]
								Mostrar "Ingrese su correo"
								Leer uCorreo[nU]
								Mostrar "Ingrese su matricula"
								Leer uMatricula[nU]
								Mostrar "Ingrese su telefono"
								Leer uTelefono[nU]
								uActivo[nU] <- 1
								Mostrar ""
								Mostrar "Usuario registrado con ID: ", nU
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						2:
							Mostrar "Ingrese el ID del usuario a modificar"
							Leer id
							Si id >= 1 Y id <= nU Entonces
								Si uActivo[id] = 1 Entonces
									Mostrar "Usuario: ", uNombre[id]
									Mostrar "Que desea editar?"
									Mostrar "1.-Editar nombre"
									Mostrar "2.-Editar correo"
									Mostrar "3.-Editar matricula"
									Mostrar "4.-Editar telefono"
									Leer opE
									Segun opE Hacer
										1:
											Mostrar "Nuevo nombre:"
											Leer uNombre[id]
											Mostrar "Dato actualizado."
										2:
											Mostrar "Nuevo correo:"
											Leer uCorreo[id]
											Mostrar "Dato actualizado."
										3:
											Mostrar "Nueva matricula:"
											Leer uMatricula[id]
											Mostrar "Dato actualizado."
										4:
											Mostrar "Nuevo telefono:"
											Leer uTelefono[id]
											Mostrar "Dato actualizado."
										De Otro Modo:
											Mostrar "Decision invalida"
									FinSegun
								SiNo
									Mostrar "Usuario no encontrado."
								FinSi
							SiNo
								Mostrar "Usuario no encontrado."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						3:
							Mostrar "Ingrese el ID del usuario a eliminar"
							Leer id
							Si id >= 1 Y id <= nU Entonces
								Si uActivo[id] = 1 Entonces
									cont <- 0
									Para i <- 1 Hasta nP Con Paso 1 Hacer
										Si pActivo[i] = 1 Y pUsuario[i] = id Entonces
											cont <- cont + 1
										FinSi
									FinPara
									Si cont > 0 Entonces
										Mostrar "No se puede eliminar: el usuario tiene prestamos activos."
									SiNo
										Mostrar "Usuario: ", uNombre[id]
										Mostrar "Confirmar borrar usuario (s/n)"
										Leer resp
										Si Minusculas(resp) = "s" Entonces
											uActivo[id] <- 0
											Mostrar "Usuario eliminado."
										SiNo
											Mostrar "Operacion cancelada."
										FinSi
									FinSi
								SiNo
									Mostrar "Usuario no encontrado."
								FinSi
							SiNo
								Mostrar "Usuario no encontrado."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						4:
							Mostrar "Ingrese el nombre o matricula del usuario"
							Leer texto
							buscado <- Minusculas(texto)
							lb <- Longitud(buscado)
							encontrados <- 0
							Mostrar ""
							Para i <- 1 Hasta nU Con Paso 1 Hacer
								Si uActivo[i] = 1 Entonces
									campo <- Minusculas(uNombre[i] + " " + uMatricula[i])
									coincide <- Falso
									Si lb > 0 Y lb <= Longitud(campo) Entonces
										Para j <- 0 Hasta Longitud(campo) - lb Con Paso 1 Hacer
											Si Subcadena(campo, j, j + lb - 1) = buscado Entonces
												coincide <- Verdadero
											FinSi
										FinPara
									FinSi
									Si coincide = Verdadero Entonces
										Mostrar "ID: ", i, " | ", uNombre[i], " | ", uMatricula[i], " | ", uTelefono[i]
										encontrados <- encontrados + 1
									FinSi
								FinSi
							FinPara
							Si encontrados = 0 Entonces
								Mostrar "Sin resultados."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						5:
							Mostrar "Usuarios registrados:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nU Con Paso 1 Hacer
								Si uActivo[i] = 1 Entonces
									Mostrar "ID: ", i, " | ", uNombre[i], " | ", uMatricula[i], " | ", uCorreo[i]
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " usuario(s)"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						6:
							Mostrar "Ingrese el ID del usuario"
							Leer id
							Si id >= 1 Y id <= nU Entonces
								Si uActivo[id] = 1 Entonces
									Mostrar "Historial de: ", uNombre[id]
									Mostrar ""
									total <- 0
									Para i <- 1 Hasta nM Con Paso 1 Hacer
										Si mUsuario[i] = id Entonces
											titulo <- "(libro eliminado)"
											Si mLibro[i] >= 1 Y mLibro[i] <= nL Entonces
												Si lActivo[mLibro[i]] = 1 Entonces
													titulo <- lTitulo[mLibro[i]]
												FinSi
											FinSi
											Si mTipo[i] = 1 Entonces
												tmp <- "Prestamo"
											SiNo
												tmp <- "Devolucion"
											FinSi
											Mostrar mFecha[i], " | ", tmp, " | Libro ", mLibro[i], ": ", titulo
											total <- total + 1
										FinSi
									FinPara
									Si total = 0 Entonces
										Mostrar "Sin movimientos."
									FinSi
								SiNo
									Mostrar "Usuario no encontrado."
								FinSi
							SiNo
								Mostrar "Usuario no encontrado."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						0:
							Mostrar ""
						De Otro Modo:
							Mostrar "Decision invalida"
							Esperar Tecla
					FinSegun
				FinMientras
				
			
			2:
				opL <- -1
				Mientras opL <> 0 Hacer
					Limpiar Pantalla
					Mostrar "Elija una opcion:"
					Mostrar "1.-Registrar libros"
					Mostrar "2.-Modificar libros"
					Mostrar "3.-Eliminar libros"
					Mostrar "4.-Buscar libros"
					Mostrar "5.-Consultar disponibilidad"
					Mostrar "6.-Clasificar libros por categoria"
					Mostrar "0.-Regresar al menu principal"
					Leer opL
					Limpiar Pantalla
					
					Segun opL Hacer
						1:
							Si nL >= 500 Entonces
								Mostrar "Se alcanzo el limite de libros."
							SiNo
								nL <- nL + 1
								Mostrar "Ingrese el nombre del libro"
								Leer lTitulo[nL]
								Mostrar "Ingrese editorial"
								Leer lEditorial[nL]
								Mostrar "Ingrese autor"
								Leer lAutor[nL]
								Mostrar "Ingrese anio de la publicacion"
								Leer lAnio[nL]
								Mostrar "Ingrese categoria (Ej. Ciencia, Novela, Historia)"
								Leer lCategoria[nL]
								lDisp[nL] <- 1
								lVeces[nL] <- 0
								lActivo[nL] <- 1
								Mostrar ""
								Mostrar "Libro registrado con ID: ", nL
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						2:
							Mostrar "Ingrese el ID del libro a modificar"
							Leer id
							Si id >= 1 Y id <= nL Entonces
								Si lActivo[id] = 1 Entonces
									Mostrar "Libro: ", lTitulo[id]
									Mostrar "Que desea editar?"
									Mostrar "1.-Editar nombre del libro"
									Mostrar "2.-Editar editorial"
									Mostrar "3.-Editar autor"
									Mostrar "4.-Editar anio de publicacion"
									Mostrar "5.-Editar categoria"
									Leer opE
									Segun opE Hacer
										1:
											Mostrar "Nuevo nombre:"
											Leer lTitulo[id]
											Mostrar "Dato actualizado."
										2:
											Mostrar "Nueva editorial:"
											Leer lEditorial[id]
											Mostrar "Dato actualizado."
										3:
											Mostrar "Nuevo autor:"
											Leer lAutor[id]
											Mostrar "Dato actualizado."
										4:
											Mostrar "Nuevo anio:"
											Leer lAnio[id]
											Mostrar "Dato actualizado."
										5:
											Mostrar "Nueva categoria:"
											Leer lCategoria[id]
											Mostrar "Dato actualizado."
										De Otro Modo:
											Mostrar "Decision invalida"
									FinSegun
								SiNo
									Mostrar "Libro no encontrado."
								FinSi
							SiNo
								Mostrar "Libro no encontrado."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						3:
							Mostrar "Ingrese el ID del libro a eliminar"
							Leer id
							Si id >= 1 Y id <= nL Entonces
								Si lActivo[id] = 1 Entonces
									Si lDisp[id] = 0 Entonces
										Mostrar "No se puede eliminar: el libro esta prestado actualmente."
									SiNo
										Mostrar "Libro: ", lTitulo[id]
										Mostrar "Desea eliminar (s/n)"
										Leer resp
										Si Minusculas(resp) = "s" Entonces
											lActivo[id] <- 0
											Mostrar "Libro eliminado."
										SiNo
											Mostrar "Operacion cancelada."
										FinSi
									FinSi
								SiNo
									Mostrar "Libro no encontrado."
								FinSi
							SiNo
								Mostrar "Libro no encontrado."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						4:
							Mostrar "Ingrese nombre, autor o categoria del libro"
							Leer texto
							buscado <- Minusculas(texto)
							lb <- Longitud(buscado)
							encontrados <- 0
							Mostrar ""
							Para i <- 1 Hasta nL Con Paso 1 Hacer
								Si lActivo[i] = 1 Entonces
									campo <- Minusculas(lTitulo[i] + " " + lAutor[i] + " " + lCategoria[i])
									coincide <- Falso
									Si lb > 0 Y lb <= Longitud(campo) Entonces
										Para j <- 0 Hasta Longitud(campo) - lb Con Paso 1 Hacer
											Si Subcadena(campo, j, j + lb - 1) = buscado Entonces
												coincide <- Verdadero
											FinSi
										FinPara
									FinSi
									Si coincide = Verdadero Entonces
										Si lDisp[i] = 1 Entonces
											estado <- "Disponible"
										SiNo
											estado <- "Prestado"
										FinSi
										Mostrar "ID: ", i, " | ", lTitulo[i], " | ", lAutor[i], " | ", lCategoria[i], " | ", estado
										encontrados <- encontrados + 1
									FinSi
								FinSi
							FinPara
							Si encontrados = 0 Entonces
								Mostrar "Sin resultados."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						5:
							Mostrar "Ingrese el ID del libro"
							Leer id
							Si id >= 1 Y id <= nL Entonces
								Si lActivo[id] = 1 Entonces
									Mostrar ""
									Mostrar "Libro:     ", lTitulo[id]
									Mostrar "Autor:     ", lAutor[id]
									Mostrar "Editorial: ", lEditorial[id]
									Mostrar "Anio:      ", lAnio[id]
									Mostrar "Categoria: ", lCategoria[id]
									Si lDisp[id] = 1 Entonces
										Mostrar "Estado:    DISPONIBLE"
									SiNo
										Mostrar "Estado:    PRESTADO"
										pos <- 0
										Para i <- 1 Hasta nP Con Paso 1 Hacer
											Si pActivo[i] = 1 Y pLibro[i] = id Entonces
												pos <- i
											FinSi
										FinPara
										Si pos > 0 Entonces
											Si uActivo[pUsuario[pos]] = 1 Entonces
												Mostrar "Prestado a: ", uNombre[pUsuario[pos]], " desde ", pFechaP[pos]
											FinSi
										FinSi
									FinSi
								SiNo
									Mostrar "Libro no encontrado."
								FinSi
							SiNo
								Mostrar "Libro no encontrado."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						6:
							Mostrar "Libros por categoria:"
							total <- 0
							Para i <- 1 Hasta nL Con Paso 1 Hacer
								Si lActivo[i] = 1 Entonces
									yaVista <- 0
									Para j <- 1 Hasta i - 1 Con Paso 1 Hacer
										Si lActivo[j] = 1 Y lCategoria[j] = lCategoria[i] Entonces
											yaVista <- 1
										FinSi
									FinPara
									Si yaVista = 0 Entonces
										Mostrar ""
										Mostrar "[ ", lCategoria[i], " ]"
										Para j <- 1 Hasta nL Con Paso 1 Hacer
											Si lActivo[j] = 1 Y lCategoria[j] = lCategoria[i] Entonces
												Si lDisp[j] = 1 Entonces
													estado <- "Disponible"
												SiNo
													estado <- "Prestado"
												FinSi
												Mostrar "   ID: ", j, " | ", lTitulo[j], " | ", lAutor[j], " | ", estado
											FinSi
										FinPara
									FinSi
									total <- total + 1
								FinSi
							FinPara
							Si total = 0 Entonces
								Mostrar "No hay libros registrados."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						0:
							Mostrar ""
						De Otro Modo:
							Mostrar "Decision invalida"
							Esperar Tecla
					FinSegun
				FinMientras
				
			
			3:
				opP <- -1
				Mientras opP <> 0 Hacer
					Limpiar Pantalla
					Mostrar "Elija una opcion"
					Mostrar "1.-Registrar prestamo"
					Mostrar "2.-Consultar prestamos activos"
					Mostrar "0.-Regresar al menu principal"
					Leer opP
					Limpiar Pantalla
					
					Segun opP Hacer
						1:
							Mostrar "Ingrese el ID del usuario"
							Leer idU
							coincide <- Falso
							Si idU >= 1 Y idU <= nU Entonces
								Si uActivo[idU] = 1 Entonces
									coincide <- Verdadero
								FinSi
							FinSi
							Si coincide = Falso Entonces
								Mostrar "Usuario no encontrado."
							SiNo
								Mostrar "Usuario: ", uNombre[idU]
								cont <- 0
								Para i <- 1 Hasta nP Con Paso 1 Hacer
									Si pActivo[i] = 1 Y pUsuario[i] = idU Entonces
										cont <- cont + 1
									FinSi
								FinPara
								Si cont >= 3 Entonces
									Mostrar "El usuario ya tiene 3 prestamos activos (maximo permitido)."
								SiNo
									Mostrar "Ingrese el ID del libro"
									Leer idL
									coincide <- Falso
									Si idL >= 1 Y idL <= nL Entonces
										Si lActivo[idL] = 1 Entonces
											coincide <- Verdadero
										FinSi
									FinSi
									Si coincide = Falso Entonces
										Mostrar "Libro no encontrado."
									SiNo
										Mostrar "Libro: ", lTitulo[idL]
										Si lDisp[idL] = 0 Entonces
											Mostrar "El libro NO esta disponible (ya esta prestado)."
										SiNo
											Si nP >= 1000 O nM >= 2000 Entonces
												Mostrar "Se alcanzo el limite de registros."
											SiNo
												Mostrar "Ingrese la fecha del prestamo (ej. 2026-11-10)"
												Leer texto
												nP <- nP + 1
												pUsuario[nP] <- idU
												pLibro[nP] <- idL
												pFechaP[nP] <- texto
												pFechaD[nP] <- "-"
												pActivo[nP] <- 1
												lDisp[idL] <- 0
												lVeces[idL] <- lVeces[idL] + 1
												nM <- nM + 1
												mTipo[nM] <- 1
												mUsuario[nM] <- idU
												mLibro[nM] <- idL
												mFecha[nM] <- texto
												Mostrar ""
												Mostrar "Prestamo registrado correctamente."
											FinSi
										FinSi
									FinSi
								FinSi
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						2:
							Mostrar "Prestamos activos:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nP Con Paso 1 Hacer
								Si pActivo[i] = 1 Entonces
									nombre <- "(eliminado)"
									titulo <- "(eliminado)"
									Si uActivo[pUsuario[i]] = 1 Entonces
										nombre <- uNombre[pUsuario[i]]
									FinSi
									Si lActivo[pLibro[i]] = 1 Entonces
										titulo <- lTitulo[pLibro[i]]
									FinSi
									Mostrar pFechaP[i], " | ", nombre, " | ", titulo
									total <- total + 1
								FinSi
							FinPara
							Si total = 0 Entonces
								Mostrar "No hay prestamos activos."
							SiNo
								Mostrar ""
								Mostrar "Total: ", total, " prestamo(s) activo(s)"
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						0:
							Mostrar ""
						De Otro Modo:
							Mostrar "Decision invalida"
							Esperar Tecla
					FinSegun
				FinMientras
				
			
			4:
				opD <- -1
				Mientras opD <> 0 Hacer
					Limpiar Pantalla
					Mostrar "Elija una opcion"
					Mostrar "1.-Registrar la devolucion"
					Mostrar "2.-Consultar devoluciones (historial)"
					Mostrar "0.-Regresar al menu principal"
					Leer opD
					Limpiar Pantalla
					
					Segun opD Hacer
						1:
							Mostrar "Ingrese el ID del libro"
							Leer idL
							coincide <- Falso
							Si idL >= 1 Y idL <= nL Entonces
								Si lActivo[idL] = 1 Entonces
									coincide <- Verdadero
								FinSi
							FinSi
							Si coincide = Falso Entonces
								Mostrar "Libro no encontrado."
							SiNo
								Mostrar "Libro: ", lTitulo[idL]
								pos <- 0
								Para i <- 1 Hasta nP Con Paso 1 Hacer
									Si pActivo[i] = 1 Y pLibro[i] = idL Entonces
										pos <- i
									FinSi
								FinPara
								Si lDisp[idL] = 1 O pos = 0 Entonces
									Mostrar "Este libro no tiene un prestamo activo."
								Sino
									Si nM >= 2000 Entonces
										Mostrar "Historial lleno: no se puede registrar la devolucion."
									SiNo
										Mostrar "Prestado a: ", uNombre[pUsuario[pos]], " (desde ", pFechaP[pos], ")"
										Mostrar "Ingrese la fecha de devolucion (ej. 2026-11-10)"
										Leer texto
										pFechaD[pos] <- texto
										pActivo[pos] <- 0
										lDisp[idL] <- 1
										nM <- nM + 1
										mTipo[nM] <- 2
										mUsuario[nM] <- pUsuario[pos]
										mLibro[nM] <- idL
										mFecha[nM] <- texto
										Mostrar ""
										Mostrar "Devolucion registrada. Disponibilidad actualizada e historial guardado."
									FinSi
								FinSi
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						2:
							Mostrar "Historial de devoluciones:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nM Con Paso 1 Hacer
								Si mTipo[i] = 2 Entonces
									nombre <- "(eliminado)"
									titulo <- "(eliminado)"
									Si uActivo[mUsuario[i]] = 1 Entonces
										nombre <- uNombre[mUsuario[i]]
									FinSi
									Si lActivo[mLibro[i]] = 1 Entonces
										titulo <- lTitulo[mLibro[i]]
									FinSi
									Mostrar mFecha[i], " | ", nombre, " | ", titulo
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " devolucion(es)"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						0:
							Mostrar ""
						De Otro Modo:
							Mostrar "Decision invalida"
							Esperar Tecla
					FinSegun
				FinMientras
				
			
			5:
				opR <- -1
				Mientras opR <> 0 Hacer
					Limpiar Pantalla
					Mostrar "Elija una opcion:"
					Mostrar "1.-Libros disponibles"
					Mostrar "2.-Libros prestados"
					Mostrar "3.-Libros registrados"
					Mostrar "4.-Historial de prestamos"
					Mostrar "5.-Historial de devoluciones"
					Mostrar "6.-Libros con mayor numero de prestamos"
					Mostrar "7.-Usuarios con prestamos activos"
					Mostrar "0.-Regresar al menu principal"
					Leer opR
					Limpiar Pantalla
					
					Segun opR Hacer
						1:
							Mostrar "Libros disponibles:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nL Con Paso 1 Hacer
								Si lActivo[i] = 1 Y lDisp[i] = 1 Entonces
									Mostrar "ID: ", i, " | ", lTitulo[i], " | ", lAutor[i], " | ", lCategoria[i]
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " libro(s) disponible(s)"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						2:
							Mostrar "Libros prestados:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nL Con Paso 1 Hacer
								Si lActivo[i] = 1 Y lDisp[i] = 0 Entonces
									nombre <- "(desconocido)"
									tmp <- "-"
									pos <- 0
									Para j <- 1 Hasta nP Con Paso 1 Hacer
										Si pActivo[j] = 1 Y pLibro[j] = i Entonces
											pos <- j
										FinSi
									FinPara
									Si pos > 0 Entonces
										tmp <- pFechaP[pos]
										Si uActivo[pUsuario[pos]] = 1 Entonces
											nombre <- uNombre[pUsuario[pos]]
										SiNo
											nombre <- "(eliminado)"
										FinSi
									FinSi
									Mostrar "ID: ", i, " | ", lTitulo[i], " | ", nombre, " | desde ", tmp
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " libro(s) prestado(s)"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						3:
							Mostrar "Libros registrados:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nL Con Paso 1 Hacer
								Si lActivo[i] = 1 Entonces
									Si lDisp[i] = 1 Entonces
										estado <- "Disponible"
									SiNo
										estado <- "Prestado"
									FinSi
									Mostrar "ID: ", i, " | ", lTitulo[i], " | ", lAutor[i], " | ", lEditorial[i], " | ", lAnio[i], " | ", estado
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " libro(s)"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						4:
							Mostrar "Historial de prestamos:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nM Con Paso 1 Hacer
								Si mTipo[i] = 1 Entonces
									nombre <- "(eliminado)"
									titulo <- "(eliminado)"
									Si uActivo[mUsuario[i]] = 1 Entonces
										nombre <- uNombre[mUsuario[i]]
									FinSi
									Si lActivo[mLibro[i]] = 1 Entonces
										titulo <- lTitulo[mLibro[i]]
									FinSi
									Mostrar mFecha[i], " | ", nombre, " | ", titulo
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " prestamo(s) registrado(s)"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						5:
							Mostrar "Historial de devoluciones:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nM Con Paso 1 Hacer
								Si mTipo[i] = 2 Entonces
									nombre <- "(eliminado)"
									titulo <- "(eliminado)"
									Si uActivo[mUsuario[i]] = 1 Entonces
										nombre <- uNombre[mUsuario[i]]
									FinSi
									Si lActivo[mLibro[i]] = 1 Entonces
										titulo <- lTitulo[mLibro[i]]
									FinSi
									Mostrar mFecha[i], " | ", nombre, " | ", titulo
									total <- total + 1
								FinSi
							FinPara
							Mostrar ""
							Mostrar "Total: ", total, " devolucione registradas"
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						6:
							Mostrar "Libros con mayor numero de prestamos:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nL Con Paso 1 Hacer
								Si lActivo[i] = 1 Entonces
									total <- total + 1
									orden[total] <- i
								FinSi
							FinPara
							Si total = 0 Entonces
								Mostrar "No hay libros registrados."
							SiNo
								Para i <- 1 Hasta total - 1 Con Paso 1 Hacer
									Para j <- 1 Hasta total - i Con Paso 1 Hacer
										Si lVeces[orden[j]] < lVeces[orden[j + 1]] Entonces
											aux <- orden[j]
											orden[j] <- orden[j + 1]
											orden[j + 1] <- aux
										FinSi
									FinPara
								FinPara
								Si total < 10 Entonces
									limite <- total
								SiNo
									limite <- 10
								FinSi
								Para i <- 1 Hasta limite Con Paso 1 Hacer
									Mostrar i, ". ID ", orden[i], " | ", lTitulo[orden[i]], " | ", lVeces[orden[i]], " prestamos"
								FinPara
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						7:
							Mostrar "Usuarios con prestamos activos:"
							Mostrar ""
							total <- 0
							Para i <- 1 Hasta nU Con Paso 1 Hacer
								Si uActivo[i] = 1 Entonces
									cont <- 0
									Para j <- 1 Hasta nP Con Paso 1 Hacer
										Si pActivo[j] = 1 Y pUsuario[j] = i Entonces
											cont <- cont + 1
										FinSi
									FinPara
									Si cont > 0 Entonces
										Mostrar "ID: ", i, " | ", uNombre[i], " | ", cont, " activo(s)"
										total <- total + 1
									FinSi
								FinSi
							FinPara
							Si total = 0 Entonces
								Mostrar "Ningun usuario tiene prestamos activos."
							FinSi
							Mostrar ""
							Mostrar "Presione una tecla para continuar..."
							Esperar Tecla
						0:
							Mostrar ""
						De Otro Modo:
							Mostrar "Decision invalida"
							Esperar Tecla
					FinSegun
				FinMientras
				
			0:
				salir <- Verdadero
				
			De Otro Modo:
				Mostrar "Decision invalida"
				Esperar Tecla
		FinSegun
	FinMientras
	
	Mostrar "Hasta luego."
FinAlgoritmo

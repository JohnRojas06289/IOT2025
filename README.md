# 🌊 **Sistema de Monitorización de Crecidas en Tiempo Real usando IoT**

## Resumen General
> **Colombia enfrenta desafíos recurrentes debido a las crecidas de ríos**, especialmente durante la temporada de lluvias y fenómenos climáticos como *La Niña*. Estas inundaciones han causado daños significativos a infraestructuras y han afectado a numerosas comunidades.
>
> Este proyecto presenta el desarrollo de un **prototipo funcional de un sistema IoT** diseñado para monitorear en tiempo real los niveles de agua y las precipitaciones en ríos colombianos, con el objetivo de detectar crecidas y notificar *in situ* a las autoridades locales.

---

## Motivación y Justificación
> **Las inundaciones en Colombia han tenido un impacto devastador** en diversas regiones.
> 
> *Ejemplo:* En noviembre de 2024, el departamento del **Chocó** sufrió inundaciones que afectaron al 85% de su territorio, dejando a más de 100,000 personas damnificadas (*Fuente: FRANCE24.COM*).
>
> La detección temprana de crecidas es **esencial para minimizar daños** y proteger tanto a las comunidades como a la infraestructura.
>
> Un **sistema IoT** ofrece una solución eficiente y rentable para el monitoreo en tiempo real, permitiendo a las autoridades locales tomar decisiones informadas y oportunas.

---

## 📁 Estructura de la Documentación
<details>
  <summary>Índice de Contenidos</summary>
  
1. [Solución Propuesta](#solución-propuesta)
2. [Restricciones de Diseño](#restricciones-de-diseño)
3. [Arquitectura Propuesta](#arquitectura-propuesta)
4. [Desarrollo Teórico Modular](#desarrollo-teórico-modular)
5. [Configuración Experimental, Resultados y Análisis](#configuración-experimental-resultados-y-análisis)
6. [Autoevaluación del Protocolo de Pruebas](#autoevaluación-del-protocolo-de-pruebas)
7. [Conclusiones, Retos y Trabajo Futuro](#conclusiones-retos-y-trabajo-futuro)
8. [Anexos](#anexos)
</details>

---

## ⚙️ **Solución Propuesta**

En busca de abordar la necesidad del monitoreo de crecientes mediante sensores, se propone implementar un sistema modular en **Arduino**, el cual sea capaz de detectar de manera eficaz las crecidas y la presencia de lluvias, generando alertas tempranas e informando en tiempo real. Este prototipo está compuesto por un **módulo de sensores** que recopila los datos del entorno a través del uso del sensor HC-SR04(ultrasonido) para medir la distancia a la cual estarían los rios de su nivel adecuado, un sensor de lluvia , un módulo de procesamiento basado en arduino que analiza la información y alerta dependiendo la situación y un módulo de salido que genera respuestas mediante la implementación de un **buzzer** que funciona como alarma sonora y una pantalla **lcd** para la visualización de los datos.

### **Restricciones de Diseño**
<details>
  <summary>Más detalles aquí</summary>
  
#### Técnicas:
- Uso de microcontroladores como **Arduino o ESP32**.
- Sensores de nivel de agua y de precipitación compatibles.
- **Sistema autónomo** con bajo consumo energético.

#### Económicas:
- **Presupuesto limitado** para componentes.
- Selección de **hardware rentable**.

#### Regulatorias:
- **Cumplimiento con normativas locales** de instalación de dispositivos en cuerpos de agua.

#### Espacio:
- Instalación en **áreas remotas** con infraestructura limitada.

#### Escalabilidad:
- Posibilidad de **ampliar el sistema** a múltiples ubicaciones.

#### Temporales:
- Implementación **antes de la próxima temporada de lluvias**.
</details>

---

## **Arquitectura Propuesta**

El sistema se compone de **módulos de hardware y software** integrados para monitorear y alertar sobre crecidas en ríos.

### **Diagrama de Componentes del Sistema**
```mermaid
graph TD;
    A[Arduino] -->|Trig/Echo| B[HC-SR04 Sensor Ultrasónico]
    A -->|Visualización| C[Leds]
    A -->|Señal| D[Buzzer]
    A -->|sensor| F[tMP36gz]
    A -->|I2C o Paralelo| E[Pantalla LCD]

```

### Diagrama de Clases
```mermaid

classDiagram
    class Sensor {
        +leerDatos(): float
    }
    
    class HC_SR04 {
        +distancia: float
        +leerDistancia(): float
    }

    class TMP36GZ {
        +temperatura: float
        +leerTemperatura(): float
    }
    
    class Arduino {
        +procesarDatos(): void
        +enviarSeñal(): void
    }
    
    class Buzzer {
        +activar(): void
    }
    
    class PantallaLCD {
        +mostrarDatos(): void
    }
    
    Sensor <|-- HC_SR04
    Sensor <|-- TMP36GZ
    HC_SR04 --> Arduino : Enviar distancia
    TMP36GZ --> Arduino : Enviar temperatura
    Arduino --> Buzzer : Activar alarma
    Arduino --> PantallaLCD : Mostrar información


```

### Diagrama de Secuencias
```mermaid
sequenceDiagram
    participant Usuario
    participant HC_SR04 as Sensor Ultrasónico
    participant Arduino
    participant Buzzer
    participant LCD

    Usuario->>HC_SR04: Activar sensor
    HC_SR04-->>Arduino: Enviar distancia

    Arduino->>Arduino: Procesar datos
    alt Distancia crítica detectada
        Arduino->>Buzzer: Activar alarma sonora
    end

    Arduino->>LCD: Mostrar distancia y estado del sistema

```



### **Tecnologías Utilizadas**
- **Microcontroladores**: Arduino.
- **Sensores**: Ultrasónico,tmp36GZ.
- **Actuadores**: Leds, buzzer, lcdI2C.
---

## *Desarollo Teórico Modular* 📕🎯
### 1. Módulos del sistema  

#### 1.1 Módulo de procesamiento  🧑‍💻
**Función:** Recibe los datos de los sensores para procesamiento y toma de decisiones.  

- Interpreta la información obtenida por los sensores.  
- Activa las salidas en función de los valores detectados.  

#### 1.2 Módulo de sensores 🔔 
**Función:** Captura datos del entorno y los envía al procesador.  

- **Sensor Ultrasónico HC-SR04:** Mide la distancia a objetos cercanos.
  
![Sensor Ultrasónico HC-SR04](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/sensor-ultrasonico.jpg)
- **Sensor de temperatura:** Detecta la temperatura actual.
  
![Sensor de lluvia](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/sensor-temperatura.gif)

#### 1.3 Módulo de actuadores
**Funcioón:** Genera respuestas físicas en funcion de las decisiones del procesador.

-**Buzzer**: Alarma sonora que se adctiva inmediatamente se detecta cercanía rítica de la precipitación del agua.

![Buzzer](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/buzzer.png)

-**Pantalla LCD**: Muestra en tiempo real la información de la distancia y que triage tiene la cercania. 

## 🧪 Configuración Experimental, Resultados y Análisis  

### 🔧 **Configuración Experimental**  
Para evaluar el rendimiento del sistema de detección de distancias, se realizaron pruebas en diferentes escenarios con el sensor ultrasónico **HC-SR04**.  

#### 📌 **Condiciones de prueba:**  
1. **Entorno controlado:** Se realizaron mediciones en un espacio cerrado con objetos de diferentes materiales y superficies.  
2. **Variación de distancias:** Se colocaron obstáculos a **5 cm, 15 cm, 25 cm y 40 cm** para comprobar los cambios de estado.  
3. **Verificación del LCD y LEDs:** Se observó si la pantalla mostraba los valores correctos y los LEDs respondían adecuadamente.  
4. **Buzzer:** Se verificó la activación del buzzer en los estados *WARNING* y *CRITICAL*.  

---

### 📊 **Resultados**  

| Distancia (cm) | Estado Detectado | LED Encendido | Buzzer |
|---------------|----------------|--------------|--------|
| + 31 cm        | NORMAL         | Verde       | ❌ Apagado |
| 30 cm        | CAUTION        | Verde + Amarillo | 🔉 Suave  |
| 20 cm        | WARNING        | Amarillo    | 🔔 Intermitente  |
| 10 cm         | CRITICAL       | Rojo        | 🚨 Intermitente |

- 📌 **El sistema respondió correctamente** a los cambios de distancia, activando los LEDs y el buzzer según la tabla.  
- 📌 **Las mediciones fueron consistentes** en todas las pruebas, con una desviación mínima de ±1 cm.  
- 📌 **La pantalla LCD mostró correctamente los valores de distancia y estado.**  

---

### 📈 **Análisis**  

- **Precisión del sensor:** El sensor **HC-SR04** mostró lecturas estables en distancias entre **5 cm y 100 cm**, pero comenzó a mostrar fluctuaciones leves en valores superiores a **300 cm**.  
- **Retraso en la actualización:** Debido al uso del buffer de promedios, los cambios de estado no fueron instantáneos, sino que tomaron **500 ms** para estabilizarse.  
- **Interferencia del entorno:** Superficies irregulares o materiales absorbentes de sonido (como tela o espuma) afectaron la precisión de las mediciones.  

### 📌 **Mejoras Propuestas**  

✅ Implementar un filtro para eliminar lecturas erróneas en distancias extremas.  
✅ Ajustar el intervalo de actualización del buzzer para reducir interferencias.  
✅ Explorar el uso de sensores adicionales para mejorar la precisión en entornos complejos.  

---

📌 **Conclusión:** El sistema demostró ser **efectivo y confiable** en la detección de obstáculos dentro del rango de operación del sensor ultrasónico, con una correcta activación de las señales visuales y auditivas.  

---

### 📝 **Autoevaluación del Protocolo de Pruebas** 

#### ✅ **1. Cobertura de Pruebas**
- Se han probado todos los estados del sistema ( estado normal, estado Caution, Estado Critical).
- Se han verificado que las distancias que mmide el sensor ultrasonico sean correctas.
- Se verificó la respuesta del buzzer y los leds ante el cambio de estado.
- Se revisó la información presentada en la pantalla LCD.

#### 🛠 **2. Precisión y Reproducibilidad** 
- Se realizaron múltiples mediciones a la misma distancia para validar la consistencia de los resultados.  

#### 🛑 **4. Identificación de Problemas Potenciales**  
❗ En algunas pruebas, el sensor HC-SR04 mostró pequeñas fluctuaciones en la lectura.  
❗ El buzzer podría requerir ajustes en su intensidad para mejorar la percepción del usuario.  


---
## Galería

![Buzzer](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/diagonal.jpg)

![Buzzer](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/superior.jpg)

![Buzzer](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/estado-critico.jpg)

![Buzzer](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/img/estado-normal.jpg)


## Funcionamiento

<video width="320" height="240" controls>
  <source src="https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/video/funcionamiento.mp4" type="video/mp4">
  Tu navegador no soporta el elemento video.
</video>

## Contribuciones

Si deseas contribuir a este proyecto, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una nueva rama (`git checkout -b feature/nueva-caracteristica`).
3. Realiza tus cambios y haz commit (`git commit -m 'Añadida nueva característica'`).
4. Empuja los cambios a tu rama (`git push origin feature/nueva-caracteristica`).
5. Crea un Pull Request.

---

## Referencias

1. **SunFounder** - Documentación oficial Kit V2 para Raspberry Pi: [SunFounder](https://docs.sunfounder.com/projects/sensorkit-v2-pi/en/latest//)

---

## 📎 **Anexos**

1. **Tinkercad** - Prototipado solución oficial: [Tinkercad](https://www.tinkercad.com/things/4sTa2o4PWZS/editel?sharecode=EIeFWOFX5DRneI9MpJu-DYvjm1JOlZI5UsiC8KP1DZc)
2. **Video** - Video de funcionamiento: [Video funcionamiento](https://unisabanaedu-my.sharepoint.com/:v:/g/personal/johnrove_unisabana_edu_co/EbKH4edEi4ZMiHfLPR-a3_wBw8cd4eqP4fy7lcsYe58xOQ?e=Y46gva)
3. **Código** - Código fuente: [Código](https://raw.githubusercontent.com/JohnRojas06289/IOT2025/main/resources/code.c)


---

🚀 *Este proyecto fue desarrollado para la universidad de La Sabana. ¡Contribuciones y sugerencias son bienvenidas!*

### INTEGRANTES 
John Jairo Rojas Vergara

Oscar David Vergara Moreno

Santiago Gavilán Paez


```mermaid
gantt
    title Cronograma del Proyecto de Automatización de T-Alem

    dateFormat  YYYY-MM-DD
    axisFormat  %m-%d


    section Levantamiento de Información (Entrega 1: 19 de febrero)
    Reunión inicial del equipo                : a1, 2024-01-22, 1d
    Visita a la empresa y recolección datos   : a2, after a1, 3d
    Análisis procesos (inventario y calidad) : a3, after a2, 5d
    Identificación del problema y necesidad     : a4, after a3, 3d
    Definición de objetivos SMART              : a5, after a4, 3d
    Definición de la metodología              : a6, after a5, 3d
    Elaboración del cronograma                 : a7, after a6, 3d
    Definición de alcance y riesgos           : a8, after a7, 3d
    Revisión preliminar grupal (fase 1)       : a9, after a8, 2d
    Entrega 1: Documentación y anexos          : a10, after a9, 3d
    Reunión con validador (fábrica)          : a11, after a10, 2d
    Reunión con validador (profesor)          : a12, after a11, 2d
    Ajustes finales y envío del documento      : a13, after a12, 2d

    section Anteproyecto (Entrega 2: 2 de abril)
    Reunión inicial del equipo (fase 2)       : b1, 2024-02-20, 1d
    Resumen de hallazgos (fase 1)             : b2, after b1, 2d
    Restricciones de diseño                  : b3, after b2, 4d
    Revisión y análisis de antecedentes      : b4, after b3, 5d
    Revisión preliminar grupal (fase 2)       : b5, after b4, 2d
    Entrega 2: Documento anteproyecto        : b6, after b5, 4d
    Reunión con validador (fábrica)          : b7, after b6, 2d
    Reunión con validador (profesor)          : b8, after b7, 2d
    Ajustes finales y envío del documento      : b9, after b8, 2d
    Preparación de la presentación           : b10, after b9, 3d
    Presentación y sustentación              : b11, after b10, 1d

    section Proyecto (Entrega 3: 14 de mayo)
    Reunión inicial del equipo (fase 3)       : c1, 2024-04-03, 1d
    Desarrollo del sistema de automatización  : c2, after c1, 25d
    Pruebas internas del equipo               : c3, after c2, 5d
    Revisión preliminar grupal (fase 3)       : c4, after c3, 2d
    Entrega 3: Documentación del proyecto     : c5, after c4, 4d
    Reunión con validador (fábrica)          : c6, after c5, 2d
    Reunión con validador (profesor)          : c7, after c6, 2d
    Ajustes finales y envío del documento      : c8, after c7, 2d
    Evaluación de resultados y análisis      : c9, after c8, 5d
    Informe final y presentación              : c10, after c9, 3d

    section Recursos Humanos
    John                                     : after a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10
    Santiago                                 : after a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10
    Oscar                                    : after a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10

    section Recursos Materiales
    Computadoras y software                  : after a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10
    Cámara para visita a la empresa           : after a2
    Software de gestión de proyectos (opcional): after a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10

```

## Hola

```mermaid
gantt
    title Cronograma Detallado del Proyecto de Automatización de T-Alem

    dateFormat  YYYY-MM-DD
    axisFormat  %m-%d

    section LevantamientodeInformación(Entrega1:19defebrero)
    Reunióninicialdelequipo:a1,2025-01-22,1d
    Visitaalaempresayrecoleccióndedatos:a2,aftera1,3d
    Análisisprocesos(inventarioycalidad):a3,aftera2,5d
    Identificacióndelproblemaynecesidad:a4,aftera3,3d
    DefinicióndeproyectoyobjetivosSMART:a5,aftera4,3d
    Definicióndela metodología:a6,aftera5,3d
    Elaboracióndelcronograma:a7,aftera6,3d
    Definicióndelealcancelyriesgos:a8,aftera7,3d
    Revisiónpreliminargrupal(fase1):a9,aftera8,2d
    Entrega1:Documentaciónyanexos:a10,aftera9,3d
    Reuniónconvalidador(fábrica):a11,aftera10,2d
    Reuniónconvalidador(profesor):a12,aftera11,2d
    Ajustesfinalesyenviódeldocumento:a13,aftera12,2d

    section Anteproyecto(Entrega2:2deabril)
    Reunióninicialdelequipo(fase2):b1,2025-02-20,1d
    Resumendehallazgos(fase1):b2,afterb1,2d
    Restriccionesdediseño:b3,afterb2,4d
    Revisiónyanálisisdeantecedentes:b4,afterb3,5d
    Revisiónpreliminargrupal(fase2):b5,afterb4,2d
    Entrega2:Documentoanteproyecto:b6,afterb5,4d
    Reuniónconvalidador(fábrica):b7,afterb6,2d
    Reuniónconvalidador(profesor):b8,afterb7,2d
    Ajustesfinalesyenviódeldocumento:b9,afterb8,2d
    Preparacióndelapresentación:b10,afterb9,3d
    Presentaciónysustentación:b11,afterb10,1d

    section Proyecto(Entrega3:14demayo)
    Reunióninicialdelequipo(fase3):c1,2025-04-03,1d
    Desarrollodeldesarrollodelautoma:c2,afterc1,25d
    Pruebasinternasdelequipo:c3,afterc2,5d
    Revisiónpreliminargrupal(fase3):c4,afterc3,2d
    Entrega3:Documentacióndelproyecto:c5,afterc4,4d
    Reuniónconvalidador(fábrica):c6,afterc5,2d
    Reuniónconvalidador(profesor):c7,afterc6,2d
    Ajustesfinalesyenviódeldocumento:c8,afterc7,2d
    Evaluaciónderesultadosyanálisis:c9,afterc8,5d
    Informefinalypresentación:c10,afterc9,3d

    section RecursosHumanos
    John:aftera1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10
    Santiago:aftera1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10
    Oscar:aftera1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10

    section RecursosMateriales
    Computadoraysoftware:aftera1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10
    Cámaraparavisitaalaempresa:aftera2
    Softwaredegestióndeproyectos(opcional):aftera1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10
  ```

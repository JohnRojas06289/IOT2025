# Sistema de monitorización de crecidas en tiempo real usando IOT 

## Resumen General  
Colombia enfrenta desafíos recurrentes debido a las crecidas de ríos, especialmente durante la temporada de lluvias y fenómenos climáticos como *La Niña*. Estas inundaciones han causado daños significativos a infraestructuras y han afectado a numerosas comunidades. Este proyecto presenta el desarrollo de un prototipo funcional de un sistema IoT diseñado para monitorear en tiempo real los niveles de agua y las precipitaciones en ríos colombianos, con el objetivo de detectar crecidas y notificar *in situ* a las autoridades locales.

---

## Motivación y Justificación  
Las inundaciones en Colombia han tenido un impacto devastador en diversas regiones. Por ejemplo, en noviembre de 2024, el departamento del Chocó sufrió inundaciones que afectaron al 85% de su territorio, dejando a más de 100,000 personas damnificadas (*FRANCE24.COM*). La detección temprana de crecidas es esencial para minimizar daños y proteger tanto a las comunidades como a la infraestructura. Un sistema IoT ofrece una solución eficiente y rentable para el monitoreo en tiempo real, permitiendo a las autoridades locales tomar decisiones informadas y oportunas.

---

## Estructura de la Documentación  
1. **Solución Propuesta**  
2. **Restricciones de Diseño**  
3. **Arquitectura Propuesta**  
4. **Desarrollo Teórico Modular**  
5. **Configuración Experimental, Resultados y Análisis**  
6. **Autoevaluación del Protocolo de Pruebas**  
7. **Conclusiones, Retos y Trabajo Futuro**  
8. **Anexos**  

---

## Solución Propuesta  

### Restricciones de Diseño  
- **Técnicas**:  
  - Uso de microcontroladores como Arduino o ESP32.  
  - Sensores de nivel de agua y de precipitación compatibles.  
  - Sistema autónomo con bajo consumo energético.  
- **Económicas**:  
  - Presupuesto limitado para componentes.  
  - Selección de hardware rentable.  
- **Regulatorias**:  
  - Cumplimiento con normativas locales de instalación de dispositivos en cuerpos de agua.  
- **Espacio**:  
  - Instalación en áreas remotas con infraestructura limitada.  
- **Escalabilidad**:  
  - Posibilidad de ampliar el sistema a múltiples ubicaciones.  
- **Temporales**:  
  - Implementación antes de la próxima temporada de lluvias.  

---

## Arquitectura Propuesta  
El sistema se compone de módulos de hardware y software integrados para monitorear y alertar sobre crecidas en ríos.  

### Diagrama de Bloques del Sistema  
```plaintext
[Sensor de Nivel de Agua] ---> [Microcontrolador] ---> [Alarma Visual y Sonora]  
[Sensor de Precipitación] ---> [Microcontrolador] ---> [Pantalla de Visualización]  

# TO DO:
* Hacer un algoritmo que dibuje el mismo pixel en pantalla a full screen hasta encontrar la mejor performance
* Crear un array con la info del dibujo (cada lado tamaño TILE_SIZE)
* Crear funcion scan(), lo que hace es scan_x y scan_y lo divide por SCAN_SUB_SIZE y ese numero entero es el que toma para obtener el pixel de referencia. Seria mejor en lugar de dividir, solo tomar los primeros X digitos. Ver bit shifting
* Algoritmo de dibujo:
 * Las teclas deben aumentar scan_step
   * Variable scan_x se va moviendo en loop partiendo desde 0 y sumando el scan_step. A cada step se va encontrando qué pixel corresponde a esa ubicacion de scan_x y scan_y. En cada step draw_x se suma en 1
   * Cuando draw_x llega al limite de SCREEN_SIZE_X, suma un step en scan_y, suma 1 en draw_y, resetea scan_x y resetea draw_x
   * Vuelve a iniciar el proceso de buscar los pixeles step por step
   * Finaliza cuando draw_y supera a SCREEN_Y
   * PRUEBA!
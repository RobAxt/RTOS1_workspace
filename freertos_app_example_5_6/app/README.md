# Comportamiento observado:
Se crean tres semáforos para cada juego de tareas task_button y task_led. Ya que hay que diferenciar que semáforo ha de usarse en cada llamada de las tareas, los mismos deben ser pasados por parámetros. 
Cuando el botón es presionado y se pasa al estado **BLINKING** la tarea task_button debe enviar la señal (*xSemaphoreGive*) continuamente para evitar que la tarea task_led se bloque por el semáforo. En esta condición el único bloqueo que presenta la tarea task_led se debe al *vTaskDelayUntil*.
Cuando el botón es presionado y se pasa al estado **NOT_BLINKING** la tarea task_button deja de enviar la señal (*xSemaphoreGive*) provocando que la tarea se bloqué en el wait del semáforo (*xSemaphoreTake*).

La tarea task_button se ejecuta cada 250ms (en este caso 1 tick = 1ms) y con la misma prioridad que task_led. Tendiendo esto en cuenta, lo que se está dejando al azar es la sincronización de la tarea task_button con respecto a la ejecución de la tarea task_led. Pero el enunciado no especificaba la creación de un segundo semáforo en la tarea task_led para que controle la tarea task_button. Pero se debería garantizar (usando un segundo semáforo) que luego de la ejecucion de la tarea task_led se ejecute la tarea task_button para que se garantice que se envía la señal (estando en modo **BLINKING**) para que en el siguiente llamado a la tarea task_led, el semáforo haya sido dado. Hay que tener cuidado que este segundo semáforo no bloque la tarea task_button y por ende evite la captura de los eventos de cambio de estado de botón.
# Uso de static dentro de la funcion task_button:
Dentro de la tarea task_button se crea la variable led_flag que va a indicar si la tarea task_led debe parpadear o no.
Se observa que al ser declarada como static, no importa cual de las tres tareas task_button reconozca el cambio de estado del boton, todos los led comenzaban a parpadear.
```C
static led_flag_t led_flag = NOT_BLINKING;
LOGGER_LOG("  Address of led_flag - 0x%08lx\r\n", (uint32_t) &led_flag);
```
Entonces se decidio verificar que dirección de memoria tomaba la variable led_flag en cada una las llamas a la tarea task_button. Se observa que en las tres instancias la dirección es la misma, por lo cual tiene sentido el comportamiento que los tres leds parpaden al unisono.
> app_init is running - Tick [mS] = 0
> 
>  RTOS - Event-Triggered Systems (ETS)
>  freertos_app_example_5_6: Demo Code
> 
>   Address of led_flag - 0x20000048
> 
>   Task CC is running - Task BUTTON - Demo Code
> 
>   Task A is running - Task LED - Demo Code
> 
>   Address of led_flag - 0x20000048
> 
>   Task AA is running - Task BUTTON - Demo Code
> 
>   Task B is running - Task LED - Demo Code
> 
>   Address of led_flag - 0x20000048
> 
>   Task BB is running - Task BUTTON - Demo Code
> 
>   Task C is running - Task LED - Demo Code
***
Se procede a realizar la misma prueba pero sin usar la variable led_flag como static
```C
led_flag_t led_flag = NOT_BLINKING;
LOGGER_LOG("  Address of led_flag - 0x%08lx\r\n", (uint32_t) &led_flag);
 ```
En es caso se observa que en cada instancia la variable led_flag toma direcciones de memoria distintas y esto concuerda con las observaciones del comportamiento de los leds. El parpadeo de los leds dejo de ser sincronizado y depende que tarea task_button haya capturado la pulsación del botón.
>  app_init is running - Tick [mS] = 0
> 
> RTOS - Event-Triggered Systems (ETS)
> 
> freertos_app_example_5_6: Demo Code
> 
>  Address of led_flag - 0x200025B7
> 
>  Task CC is running - Task BUTTON - Demo Code
> 
>  Task A is running - Task LED - Demo Code
> 
>  Address of led_flag - 0x200013D7
> 
>  Task AA is running - Task BUTTON - Demo Code
> 
>  Task B is running - Task LED - Demo Code
> 
>  Address of led_flag - 0x20001CC7
> 
>  Task BB is running - Task BUTTON - Demo Code
> 
>  Task C is running - Task LED - Demo Code
***
# Mejoras al contar con un único botón en la placa:
En caso de usar la variable led_flag como static, una optimización sería crear una única tarea para la captura del botón y que la misma le envíe la señal a los tres semáforos. La tarea task_button al usar los tres semaforos, no sería necesario que sean pasados por parámetros, sino que podría usar las instancias globales. En cambio las tareas task_led, si deberían seguir recibiendo sus semaforos por parámetro.

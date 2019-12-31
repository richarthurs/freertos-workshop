/*
   Arduino FreeRTOS blink example.

   This example blinks the built-in LED on an arduino using a FreeRTOS
   task at 1 Hz.

   This example requires the Arduino FreeRTOS library: https://github.com/feilipu/Arduino_FreeRTOS_Library

   The repository for this example can be found at: https://github.com/richarthurs/freertos-workshop
*/

#include <Arduino_FreeRTOS.h>

/**
   Setup() runs before the RTOS begins running.

   Here, we create the tasks that the RTOS should run.
*/
void setup() {
  Serial.begin(9600);

  /**
     xTaskCreate will create a task, which allows the RTOS to run it.
  */
  if (!xTaskCreate(blinkTask,      // Function that the task will run
                   "Blink",        // Human-readable task name
                   128,            // Stack size
                   NULL,           // Parameters for the task, none are required.
                   1,              // Task priority
                   NULL )) {       // Task handle, can be set to NULL.

    // If we get here, the task could not be created for some reason.
    Serial.println("Blink task could not be created");
  }


}


/**
   The loop function is executed by the the FreeRTOS idle 
   task in this port.

   This code runs automatically if none of the other tasks 
   need to run. This can be useful for power saving, for example.
*/
void loop() {
}


/*
   Blink task, blinks an LED at 1 Hz.

   pvParameters can be used to pass arbitrary
   data into a task during task creation. Here,
   it was set to NULL because we aren't using it.
*/
void blinkTask(void *pvParameters) {
  /**
     When a task is created, the code before the
     while(true) loop will run once. This is used in
     the same way to arduino's setup() function, to
     initialize pins and variables that are needed in
     the loop.
  */
  (void) pvParameters;
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Blinky task started.");

  /**
     This forever loop is the bulk of the task's implementation.
     Here, we can do things periodically, wait on events to
     occur, and more.
  */     
  while (true) {
    digitalWrite(LED_BUILTIN, HIGH);

    /**
     * The pdMS_TO_TICKS macro converts a duration in milliseconds
     * to a number of FreeRTOS ticks. 
     * 
     * The FreeRTOS arduino port uses a tick period of 15 ms by default.
     * Since 500 ms is not evenly divisible by the tick period, our delays
     * will be slightly longer than 500 ms, resulting in a slightly slower
     * than 1 Hz blink.
     * 
     * Note: long delays (more than ~1000 ms) and short delays (less than ~75 ms)
     * may not work correctly.
     */
    vTaskDelay(pdMS_TO_TICKS(150));
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(150));
  }
}

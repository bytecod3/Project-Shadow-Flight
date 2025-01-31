#include "main_app.h"

/*
 * private variables
 */
char msg_buffer[50];

/* function prototypes */
static void xTestTask(void* pvParameters);

/*
 * Function definitions
 */
static void xTestTask(void* pvParameters) {

    // function variables here

    while(1) {

    }

}

/*
 * Main function
 */
int mainapp() {

    /* create task to test setup */
    BaseType_t status;

    status = xTaskCreate(xTestTask, "xTestTask", 1024, NULL, 1, NULL);

    if(status == pdPASS) {
        sprintf(msg_buffer, "TASK CREATED OK!\n");
    } else {
        sprintf(msg_buffer, "TASK FAILED!\n");
    }

    /* start the scheduler */
    vTaskStartScheduler();

	while(1) {

	}
}

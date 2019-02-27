#ifndef ACCEL_H
#define ACCEL_H


//Pin 27 og 28 er ACC INT1 og ACC INT2 (akselerometer)
//Pin 0 og 30 er SCL og SDA
void accel_init();

void accel_read_x_y_z(int * data_buffer);

#endif

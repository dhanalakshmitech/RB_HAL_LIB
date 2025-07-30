#ifndef RB_I2C_H
#define RB_I2C_H

#include <stdint.h>
#include <stddef.h>

int rb_i2c_open(const char *dev, uint8_t addr);
void rb_i2c_close(int fd);

int rb_i2c_write_byte(int fd, uint8_t data);
int rb_i2c_read_byte(int fd, uint8_t *data);

int rb_i2c_write_buf(int fd, const uint8_t *buf, size_t len);
int rb_i2c_read_buf(int fd, uint8_t *buf, size_t len);

int rb_i2c_write_reg(int fd, uint8_t reg, uint8_t data);
int rb_i2c_read_reg(int fd, uint8_t reg, uint8_t *data);

#endif // RB_I2C_H


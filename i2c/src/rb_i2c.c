#include "rb_i2c.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <errno.h>

int rb_i2c_open(const char *dev, uint8_t addr) {
    int fd = open(dev, O_RDWR);
    if (fd < 0) {
        perror("rb_i2c_open: Failed to open device");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("rb_i2c_open: Failed to set I2C address");
        close(fd);
        return -1;
    }
    return fd;
}

void rb_i2c_close(int fd) {
    if (fd >= 0) close(fd);
}

int rb_i2c_write_byte(int fd, uint8_t data) {
    if (write(fd, &data, 1) != 1) {
        perror("rb_i2c_write_byte");
        return -1;
    }
    return 0;
}

int rb_i2c_read_byte(int fd, uint8_t *data) {
    if (read(fd, data, 1) != 1) {
        perror("rb_i2c_read_byte");
        return -1;
    }
    return 0;
}

int rb_i2c_write_buf(int fd, const uint8_t *buf, size_t len) {
    if (write(fd, buf, len) != (ssize_t)len) {
        perror("rb_i2c_write_buf");
        return -1;
    }
    return 0;
}

int rb_i2c_read_buf(int fd, uint8_t *buf, size_t len) {
    if (read(fd, buf, len) != (ssize_t)len) {
        perror("rb_i2c_read_buf");
        return -1;
    }
    return 0;
}

int rb_i2c_write_reg(int fd, uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    if (write(fd, buf, 2) != 2) {
        perror("rb_i2c_write_reg");
        return -1;
    }
    return 0;
}

int rb_i2c_read_reg(int fd, uint8_t reg, uint8_t *data) {
    if (write(fd, &reg, 1) != 1) {
        perror("rb_i2c_read_reg: write reg");
        return -1;
    }
    if (read(fd, data, 1) != 1) {
        perror("rb_i2c_read_reg: read data");
        return -1;
    }
    return 0;
}


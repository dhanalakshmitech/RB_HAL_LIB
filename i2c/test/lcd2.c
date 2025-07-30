#include "rb_i2c.h"
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define I2C_DEV "/dev/i2c-0"
#define LCD_ADDR 0x27

#define ENABLE 0x04
#define READ_WRITE 0x02
#define REGISTER_SELECT 0x01
#define BACKLIGHT 0x08

int fd;

// Send 4 bits to LCD
void lcd_write_4bits(uint8_t data) {
    rb_i2c_write_byte(fd, data | BACKLIGHT);         // Send with backlight
    rb_i2c_write_byte(fd, data | ENABLE | BACKLIGHT); // Enable high
    usleep(1);
    rb_i2c_write_byte(fd, (data & ~ENABLE) | BACKLIGHT); // Enable low
    usleep(50);
}

// Send command to LCD
void lcd_send_cmd(uint8_t cmd) {
    lcd_write_4bits((cmd & 0xF0) | 0x00);  // upper nibble, RS=0
    lcd_write_4bits(((cmd << 4) & 0xF0) | 0x00);  // lower nibble
}

// Send data (character) to LCD
void lcd_send_data(uint8_t data) {
    lcd_write_4bits((data & 0xF0) | REGISTER_SELECT);  // RS=1
    lcd_write_4bits(((data << 4) & 0xF0) | REGISTER_SELECT);
}

// Initialize LCD
void lcd_init() {
    usleep(50000);  // wait >40ms

    lcd_write_4bits(0x30);
    usleep(4500);
    lcd_write_4bits(0x30);
    usleep(4500);
    lcd_write_4bits(0x30);
    usleep(150);
    lcd_write_4bits(0x20);  // 4-bit mode

    lcd_send_cmd(0x28);  // 4-bit, 2 line, 5x8 dots
    lcd_send_cmd(0x0C);  // display ON, cursor OFF
    lcd_send_cmd(0x06);  // auto increment
    lcd_send_cmd(0x01);  // clear display
    usleep(2000);
}

// Set cursor to position
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_send_cmd(0x80 | (col + row_offsets[row]));
}

// Print string
void lcd_print(const char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

int main() {
    fd = rb_i2c_open(I2C_DEV, LCD_ADDR);
    if (fd < 0) {
        printf("Failed to open I2C device\n");
        return 1;
    }

    lcd_init();
    lcd_set_cursor(0, 0);
    lcd_print("Hello, dhanam");

    lcd_set_cursor(1, 0);
    lcd_print("I2C LCD Working!");

    rb_i2c_close(fd);
    return 0;
}


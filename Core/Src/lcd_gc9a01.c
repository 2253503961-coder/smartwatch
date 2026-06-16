#include "lcd_gc9a01.h"

extern SPI_HandleTypeDef hspi1;

static void LCD_WriteByte(uint8_t data)
{
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

static void LCD_WriteReg(uint8_t reg)
{
    LCD_DC_L();
    LCD_CS_L();
    LCD_WriteByte(reg);
    LCD_CS_H();
}

static void LCD_WriteData(uint8_t data)
{
    LCD_DC_H();
    LCD_CS_L();
    LCD_WriteByte(data);
    LCD_CS_H();
}

static void LCD_WriteData16(uint16_t data)
{
    LCD_DC_H();
    LCD_CS_L();
    LCD_WriteByte(data >> 8);
    LCD_WriteByte(data & 0xFF);
    LCD_CS_H();
}

void LCD_GPIO_Init(void)
{
    LCD_CS_H();
    LCD_DC_H();
    LCD_RST_H();
}

void LCD_Init(void)
{
    LCD_GPIO_Init();

    LCD_RST_L();
    osDelay(100);
    LCD_RST_H();
    osDelay(100);

    LCD_WriteReg(0xEF);
    LCD_WriteReg(0xEB);
    LCD_WriteData(0x14);

    LCD_WriteReg(0xFE);
    LCD_WriteReg(0xEF);

    LCD_WriteReg(0xEB);
    LCD_WriteData(0x14);

    LCD_WriteReg(0x84);
    LCD_WriteData(0x40);

    LCD_WriteReg(0x85);
    LCD_WriteData(0xFF);

    LCD_WriteReg(0x86);
    LCD_WriteData(0xFF);

    LCD_WriteReg(0x87);
    LCD_WriteData(0xFF);

    LCD_WriteReg(0x88);
    LCD_WriteData(0x0A);

    LCD_WriteReg(0x89);
    LCD_WriteData(0x21);

    LCD_WriteReg(0x8A);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x8B);
    LCD_WriteData(0x80);

    LCD_WriteReg(0x8C);
    LCD_WriteData(0x01);

    LCD_WriteReg(0x8D);
    LCD_WriteData(0x01);

    LCD_WriteReg(0x8E);
    LCD_WriteData(0xFF);

    LCD_WriteReg(0x8F);
    LCD_WriteData(0xFF);

    LCD_WriteReg(0xB6);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x3A);
    LCD_WriteData(0x05);

    LCD_WriteReg(0x90);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);

    LCD_WriteReg(0xBD);
    LCD_WriteData(0x06);

    LCD_WriteReg(0xBC);
    LCD_WriteData(0x00);

    LCD_WriteReg(0xFF);
    LCD_WriteData(0x60);
    LCD_WriteData(0x01);
    LCD_WriteData(0x04);

    LCD_WriteReg(0xC3);
    LCD_WriteData(0x13);
    LCD_WriteReg(0xC4);
    LCD_WriteData(0x13);

    LCD_WriteReg(0xC9);
    LCD_WriteData(0x22);

    LCD_WriteReg(0xBE);
    LCD_WriteData(0x11);

    LCD_WriteReg(0xE1);
    LCD_WriteData(0x10);
    LCD_WriteData(0x0E);

    LCD_WriteReg(0xDF);
    LCD_WriteData(0x21);
    LCD_WriteData(0x0c);
    LCD_WriteData(0x02);

    LCD_WriteReg(0xF0);
    LCD_WriteData(0x45);
    LCD_WriteData(0x09);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);
    LCD_WriteData(0x26);
    LCD_WriteData(0x2A);

    LCD_WriteReg(0xF1);
    LCD_WriteData(0x43);
    LCD_WriteData(0x70);
    LCD_WriteData(0x72);
    LCD_WriteData(0x36);
    LCD_WriteData(0x37);
    LCD_WriteData(0x6F);

    LCD_WriteReg(0xF2);
    LCD_WriteData(0x45);
    LCD_WriteData(0x09);
    LCD_WriteData(0x08);
    LCD_WriteData(0x08);
    LCD_WriteData(0x26);
    LCD_WriteData(0x2A);

    LCD_WriteReg(0xF3);
    LCD_WriteData(0x43);
    LCD_WriteData(0x70);
    LCD_WriteData(0x72);
    LCD_WriteData(0x36);
    LCD_WriteData(0x37);
    LCD_WriteData(0x6F);

    LCD_WriteReg(0xED);
    LCD_WriteData(0x1B);
    LCD_WriteData(0x0B);

    LCD_WriteReg(0xAE);
    LCD_WriteData(0x77);

    LCD_WriteReg(0xCD);
    LCD_WriteData(0x63);

    LCD_WriteReg(0x70);
    LCD_WriteData(0x07);
    LCD_WriteData(0x07);
    LCD_WriteData(0x04);
    LCD_WriteData(0x0E);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x09);
    LCD_WriteData(0x07);
    LCD_WriteData(0x08);
    LCD_WriteData(0x03);

    LCD_WriteReg(0xE8);
    LCD_WriteData(0x34);

    LCD_WriteReg(0x62);
    LCD_WriteData(0x18);
    LCD_WriteData(0x0D);
    LCD_WriteData(0x71);
    LCD_WriteData(0xED);
    LCD_WriteData(0x70);
    LCD_WriteData(0x70);
    LCD_WriteData(0x18);
    LCD_WriteData(0x0F);
    LCD_WriteData(0x71);
    LCD_WriteData(0xEF);
    LCD_WriteData(0x70);
    LCD_WriteData(0x70);

    LCD_WriteReg(0x63);
    LCD_WriteData(0x18);
    LCD_WriteData(0x11);
    LCD_WriteData(0x71);
    LCD_WriteData(0xF1);
    LCD_WriteData(0x70);
    LCD_WriteData(0x70);
    LCD_WriteData(0x18);
    LCD_WriteData(0x13);
    LCD_WriteData(0x71);
    LCD_WriteData(0xF3);
    LCD_WriteData(0x70);
    LCD_WriteData(0x70);

    LCD_WriteReg(0x64);
    LCD_WriteData(0x28);
    LCD_WriteData(0x29);
    LCD_WriteData(0xF1);
    LCD_WriteData(0x01);
    LCD_WriteData(0xF1);
    LCD_WriteData(0x00);
    LCD_WriteData(0x07);

    LCD_WriteReg(0x66);
    LCD_WriteData(0x3C);
    LCD_WriteData(0x00);
    LCD_WriteData(0xCD);
    LCD_WriteData(0x67);
    LCD_WriteData(0x45);
    LCD_WriteData(0x45);
    LCD_WriteData(0x10);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x67);
    LCD_WriteData(0x00);
    LCD_WriteData(0x3C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x54);
    LCD_WriteData(0x10);
    LCD_WriteData(0x32);
    LCD_WriteData(0x98);

    LCD_WriteReg(0x74);
    LCD_WriteData(0x10);
    LCD_WriteData(0x85);
    LCD_WriteData(0x80);
    LCD_WriteData(0x00);
    LCD_WriteData(0x00);
    LCD_WriteData(0x4E);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x98);
    LCD_WriteData(0x3e);
    LCD_WriteData(0x07);

    LCD_WriteReg(0x35);
    LCD_WriteData(0x00);

    LCD_WriteReg(0x36);
    LCD_WriteData(0x48);

    LCD_WriteReg(0x21);

    LCD_WriteReg(0x11);
    osDelay(120);
    LCD_WriteReg(0x29);
    osDelay(20);
}

void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_WriteReg(0x2A);
    LCD_WriteData16(x1);
    LCD_WriteData16(x2);

    LCD_WriteReg(0x2B);
    LCD_WriteData16(y1);
    LCD_WriteData16(y2);

    LCD_WriteReg(0x2C);
}

void LCD_SendPixels(uint16_t *data, uint32_t len)
{
    LCD_DC_H();
    LCD_CS_L();

    uint8_t *pData = (uint8_t *)data;
    HAL_SPI_Transmit(&hspi1, pData, len * 2, HAL_MAX_DELAY);

    LCD_CS_H();
}

void LCD_Clear(uint16_t color)
{
    uint16_t buf[LCD_W];
    for(int i = 0; i < LCD_W; i++) buf[i] = color;

    LCD_Address_Set(0, 0, LCD_W - 1, LCD_H - 1);

    LCD_DC_H();
    LCD_CS_L();

    for(int y = 0; y < LCD_H; y++)
    {
        HAL_SPI_Transmit(&hspi1, (uint8_t*)buf, LCD_W * 2, HAL_MAX_DELAY);
    }

    LCD_CS_H();
}

void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Address_Set(x, y, x, y);
    LCD_WriteData16(color);
}

void LCD_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint32_t len = (x2 - x1 + 1) * (y2 - y1 + 1);
    LCD_Address_Set(x1, y1, x2, y2);

    LCD_DC_H();
    LCD_CS_L();

    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    uint8_t buf[2] = {hi, lo};

    for(uint32_t i = 0; i < len; i++)
    {
        HAL_SPI_Transmit(&hspi1, buf, 2, HAL_MAX_DELAY);
    }

    LCD_CS_H();
}

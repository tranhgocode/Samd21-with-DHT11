#include <asf.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct usart_module usart_instance;

#define DHT11_pin 21
uint8_t c = 0,
I_RH,
D_RH,
I_temp,
D_temp,
Check_sum;

void configure_usart(void);
void usart_putc(char ch);
void usart_print(const char *str);
void Start(void);
void Response(void);
uint8_t Receive_data(void);

int main(void)
{
	// Khoi tao he thong va delay
	SystemInit();
	delay_init(); // Khoi tao delay voi tan so CPU

	configure_usart();

	usart_print("Bat dau chuong trinh\r\n");
	while (1) {
		Start();
		Response();

		// ?oc 5 byte data (DHT11 gui 40 bit)
		uint8_t data[5];
		for (int i = 0; i < 5; i++)
		{
			data[i] = Receive_data();
		}

		I_RH = data[0];
		D_RH = data[1];
		I_temp = data[2];
		D_temp = data[3];
		Check_sum = data[4];

		// Dung buffer ?e luu chuoi roi gui qua USART
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "Humidity: %d.%d%%\n", I_RH, D_RH);
		usart_print(buffer);
		snprintf(buffer, sizeof(buffer), "Temperature: %d.%dC\n", I_temp, D_temp);
		usart_print(buffer);
		snprintf(buffer, sizeof(buffer), "Checksum: %d\n", Check_sum);
		usart_print(buffer);

		if (Check_sum == (I_RH + D_RH + I_temp + D_temp))
		{
			usart_print("check sum true\n");
		}
		else
		{
			usart_print("check sum false\n");
		}
		delay_ms(2000); // Delay 2 giây gi?a các l?n ??c
	}
}

void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 9600;
	config_usart.mux_setting = USART_RX_2_TX_0_XCK_1;
	config_usart.pinmux_pad0 = PINMUX_PA22D_SERCOM5_PAD0; // PA22: TX
	config_usart.pinmux_pad1 = PINMUX_UNUSED;
	config_usart.pinmux_pad2 = PINMUX_PB22D_SERCOM5_PAD2; // PB22: RX
	config_usart.pinmux_pad3 = PINMUX_UNUSED;

	while (usart_init(&usart_instance, SERCOM5, &config_usart) != STATUS_OK) {
		// X? lý l?i kh?i t?o
	}
	usart_enable(&usart_instance);
}

// Truy?n 1 ký t?
void usart_putc(char ch)
{
	usart_write_buffer_wait(&usart_instance, (uint8_t *)&ch, 1);
}

// Truy?n chu?i
void usart_print(const char *str)
{
	for (int i = 0; str[i] != 0; i++)
	{
		usart_putc(str[i]);
	}
}

void Start(void)
{
	// C?u hình PA21 làm output
	struct port_config config;
	port_get_config_defaults(&config);
	config.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(DHT11_pin, &config);

	// Kéo low trong 20ms
	port_pin_set_output_level(DHT11_pin, false);
	delay_ms(20);

	// Kéo high trong 40µs
	port_pin_set_output_level(DHT11_pin, true);
	delay_us(40);
}

void Response(void)
{
	// config PA21 lam input voi pull-up
	struct port_config config;
	port_get_config_defaults(&config);
	config.direction = PORT_PIN_DIR_INPUT;
	config.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(DHT11_pin, &config);

	// Cho DHT11 keo low -> high -> low
	while (!port_pin_get_input_level(DHT11_pin)); // Cho low
	while (port_pin_get_input_level(DHT11_pin));  // Cho high
	while (!port_pin_get_input_level(DHT11_pin)); // Cho low
}

uint8_t Receive_data(void)
{
	c = 0;
	for (int q = 0; q < 8; q++)
	{
		// Cho bat ?au bit (low -> high)
		while (!port_pin_get_input_level(DHT11_pin));
		delay_us(30);

		// Neu van high -> 1, ng??c l?i -> 0
		if (port_pin_get_input_level(DHT11_pin))
		c = (c << 1) | 0x01;
		else
		c = (c << 1);

		// Cho DHT11 keo low ket thuc bit
		while (port_pin_get_input_level(DHT11_pin));
	}
	return c;
}
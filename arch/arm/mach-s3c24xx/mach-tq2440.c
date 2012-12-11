/* linux/arch/arm/mach-s3c2440/mach-tq2440.c
 *
 * Copyright (c) 2012 Pocograph
 *	David <david@pocograph.com>
 *
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>
#include <linux/io.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/hardware.h>
#include <asm/irq.h>
#include <asm/mach-types.h>

#include <plat/regs-serial.h>
#include <mach/regs-gpio.h>
#include <mach/regs-lcd.h>

#include <mach/idle.h>
#include <mach/fb.h>
#include <plat/iic.h>

#include <plat/s3c2410.h>
#include <plat/s3c244x.h>
#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <mach/regs-gpio.h>
#include <mach/leds-gpio.h>

#include <plat/common-smdk.h>

#include "common.h"

#define UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

static struct s3c2410_uartcfg tq2440_uartcfgs[] __initdata = {
	[0] = {
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	},
	[1] = {
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	},
	/* IR port */
	[2] = {
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x43,
		.ufcon	     = 0x51,
	}
};

static struct s3c24xx_led_platdata tq2440_led1_pdata = {
	.name		= "s3c24xx_led",
	.gpio		= S3C2410_GPB(7),
	.flags		= S3C24XX_LEDF_ACTLOW | S3C24XX_LEDF_TRISTATE,
	.def_trigger	= "mmc0",
};

static struct platform_device tq2440_led1 = {
	.name		= "s3c24xx_led",
	.id		= 1,
	.dev		= {
		.platform_data	= &tq2440_led1_pdata,
	},
};

static struct platform_device *tq2440_devices[] __initdata = {
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
  &tq2440_led1
};

static void __init tq2440_map_io(void)
{
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(tq2440_uartcfgs, ARRAY_SIZE(tq2440_uartcfgs));
}

static void __init tq2440_machine_init(void)
{
	platform_add_devices(tq2440_devices, ARRAY_SIZE(tq2440_devices));
}

MACHINE_START(TQ2440, "TQ2440")
	.atag_offset	= 0x100,
	.init_irq	= s3c24xx_init_irq,
	.map_io		= tq2440_map_io,
	.init_machine	= tq2440_machine_init,
	.timer		= &s3c24xx_timer,
	.restart	= s3c244x_restart,
MACHINE_END

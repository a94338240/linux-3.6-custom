ifeq ($(CONFIG_PM_H1940),y)
	zreladdr-y	+= 0x30108000
	params_phys-y	:= 0x30100100
  initrd_phys-y := 0x30800000
else
	zreladdr-y	+= 0x30008000
	params_phys-y	:= 0x30000100
  initrd_phys-y := 0x30800000
endif

/****************************************************************************
** Change Havit kb390l lighting pattern or compatible keyboards (Sharkoon)
*****************************************************************************/

#include "src/kb390l.h"


int main(int argc,  char** argv) {
	if (argc < 5) {
		printf("Usage:\n");
		printf("\t%s <lighting_type> <color_red> <color_green> <color_blue>\n", argv[0]);
		return 1;
	}
	int light = atoi(argv[1]);
	int r = atoi(argv[2]);
	int g = atoi(argv[3]);
	int b = atoi(argv[4]);

	static const int VENDOR = 0x04D9;
	static const int PRODUCT[] = {0xA131, 0xA232};
	for (unsigned int i=0; i<sizeof(PRODUCT)/sizeof(PRODUCT[0]); ++i)
	{
		try{
			KB390L kbDevice(VENDOR, PRODUCT[i]);
			printf("Found device: 0x%04x:0x%04x\n", VENDOR, PRODUCT[i]);
			//kbDevice.setLightType(KB390L::LightType::LightStatic);
			printf("Changing color to pattern %d with RGB = %d, %d, %d\n", light, r, g, b);
			kbDevice.setColot(r, g, b);
			kbDevice.setLightBrightness(KB390L::Constants::MaxLightBrightness);
			kbDevice.setLightType(light); //KB390L::LightType::LightBreath
			kbDevice.setLightDelay(0);
			return 0;
		} catch (...){
			// printf("Device not is found 0x%x:0x%x\n", VENDOR, PRODUCT[i]);
		}
	}

    printf("Error changing keyboard color pattern, could not access any device\n"
           "try executing with root privileges\n");
	return 1;
}

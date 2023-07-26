#ifndef HC_08_H
#define HC_08_H

#include <Arduino.h>

namespace HCv{
	uint8_t HC_Flag = 0;
	String data;
}

namespace HC_08namespace{
	using namespace HCv;
	
	void HCReceive(void *arg) {
		while (1) {
			if (Serial2.available()) {
				data = Serial2.readString();
				HC_Flag = 1;
			}
			vTaskDelay(50);
		}
	}
	
	class HCMdoel{
		public:
			void HCInit(uint8_t RXD, uint8_t TXD){
				Serial2.begin(9600, SERIAL_8N1, RXD, TXD);
				xTaskCreatePinnedToCore(HCReceive, "HCReceive", 4096, NULL, 1, &xHandle, 1);
			}
			/*uint8_t returnFlag(){
				return HC_Flag;
			}*/
			String returnData(){
				return data;
			}
			
			void HCsend(String temp){
				Serial2.println(temp);
			}
		private:
			TaskHandle_t xHandle;
			
			
	};
	HCMdoel bleHC;
}

namespace HCEnv{
	using HC_08namespace::bleHC;
	using HCv::HC_Flag;
}

#endif
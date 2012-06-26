
#ifndef COMMUNICATION_MODULE_H
#define COMMUNICATION_MODULE_H

void Fct_Transmit_OBC(void); // Transmit to On-Board Computer
void Fct_Transmit_VUE(unsigned char VUE_ID, unsigned int Variable, unsigned int data);
void Fct_Transmit_CMD_to_Motor(unsigned int CMD, unsigned char MOTOR);
void Fct_Transmit_Steering_Wheel(unsigned int DATA);



#endif //COMMUNICATION_MODULE_H




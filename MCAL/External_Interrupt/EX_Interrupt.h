
#ifndef EXI_H_
#define EXI_H_



typedef enum{
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}TriggerEdge_type;

typedef enum{
	EX_INT0=0,
	EX_INT1,
	EX_INT2
}ExInterruptSource_type;

void EXI_voidInit(void);


void EXI_voidEnable  ( ExInterruptSource_type Interrupt);
void EXI_voidDisable ( ExInterruptSource_type Interrupt);
void EXI_voidTriggerEdge( ExInterruptSource_type Interrupt , TriggerEdge_type Edge)  ;

void EXI_voidSetCallBack( ExInterruptSource_type Interrupt , void(*LocalFPtr)(void) );




#endif /* EXI_H_ */
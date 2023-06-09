/*
 * DMA_interface.h
 *
 *  Created on: May 13, 2023
 *      Author: Sherif Ahmed
 */

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

#include "stdTypes.h"
#include "errorStates.h"


/**** macros *****/
#define DMA_NT  2
#define DMA_TC  1
#define DMA_TE  0
/************************ Public data types ***********************/
/* DMA channels */
typedef enum {
	DMA_CH1 ,
	DMA_CH2 ,
	DMA_CH3 ,
	DMA_CH4 ,
	DMA_CH5 ,
	DMA_CH6 ,
	DMA_CH7
}DMA_Channels_t;
/*************************/
/* DMA states */
typedef enum {
	DMA_DISABLE ,
	DMA_ENABLE
}DMA_states_t;
/****************************/
/* DMA data size */
typedef enum {
	BIT_8  ,
	BIT_16 ,
	BIT_32
}DMA_dataSize_t;
/************************************/
/* DMA transfer modes */
typedef enum {
	MEM2MEM ,
	PER2MEM ,
	MEM2PER ,
	PER2PER
}DMA_transferModes_t;
/****************************************/
/* DMA priority levels*/
typedef enum {
	LOW ,
	MEDIUM ,
	HIGH ,
	VERY_HIGH
}DMA_priorityLevels_t;
/*******************************************************/
/* Configuration parameters used with DMA_voidConfigChannel */
/* Note that :  in all modes except for MEM2PER mode, mem is considered distantion
                and per is considered source */
typedef struct
{
	// Priority level for DMA channel refer to DMA_priorityLevels_t enum data type
	DMA_priorityLevels_t p_level;

	// DMA transfer mode refer to DMA_transferModes_t enum data type
	DMA_transferModes_t   tr_mode  ;

	// Size of the memory element refer to DMA_dataSize_t  enum data type considered destination size in all modes except for
	// MEM2PER mode
	DMA_dataSize_t        mem_size ;

	// Size of the peripheral element refer to DMA_dataSize_t  enum data type considered source size in all modes except
	// for MEM2PER mode
	DMA_dataSize_t        per_size ;

	// enable or disable increment for memory
	DMA_states_t          mem_increment ;

	// enable or disable increment for peripheral
	DMA_states_t          per_increment ;

	// enable or disable circular mode
	DMA_states_t          circular_mode ;

	// enable transfer complete interrupt
	DMA_states_t          TF_interrupt ;

	// enable half transfer complete interrupt
	DMA_states_t          HTF_interrupt;

	// enable error tranfer interrupt
	DMA_states_t          ETF_interrupt;

}DMA_configCh_t;

/********************************************************/

/*****************************************************************/
/*transfer parameters used with DMA_voidTransfer*/
typedef struct
{
	//DMA transfer mode refer to DMA_transferModes_t enum data type
	DMA_transferModes_t tr_mode;
	//source Address
	u32 * u32SourceAdress;
	// Distenation address
	u32 *u32DistAddress;
	// Block size (if one element you must write 1 )
	u16 u16BlockSize;

}DMA_TransData_t;


/******* Prototypes *******/

/*
  * DMA_voidConfigChannel - > Configure DMA channel
  * i/p :  DMA_Channels_t / pinter to DMA_configCh_t
*/
void DMA_voidConfigChannel (DMA_Channels_t copy_ch , DMA_configCh_t *copy_config);

/*
  * DMA_voidTransfer - > Sen data from one location to another according to configuration
  * i/p :  DMA_Channels_t / pinter to DMA_TransData_t
*/
void DMA_voidTransfer (DMA_Channels_t copy_ch  , DMA_TransData_t *copy_trans);

/*
  * DMA_u8GetStatus - > return status of DMA transfer complete or error
  * i/p :  DMA_Channels_t
*/
u8 DMA_u8GetStatus(DMA_Channels_t copy_ch);

/*
  * DMA_voidSetHandler - > Set the ISR call back function
  * i/p :  DMA_Channels_t / void function (void)
*/
void DMA_voidSetHandler (DMA_Channels_t copy_ch , void(*func)(void));




#endif /* DMA_INTERFACE_H_ */

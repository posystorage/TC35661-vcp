
#include "sys.h"
#include "common.h"
#include "usart.h"


volatile uint8_t Uart3_pos=0;

Usart::Usart()
{
}

void Usart::InitBuffers(uint8_t rx_size, uint8_t tx_size)
{
	Uart3_RcvCnt = 0;
	Uart3_pos = 0;

}


Usart::~Usart()
{

}

///**
// * Initialize usart
// *
// * \param usart Usart structure
// * \param port Port structure
// * \param tx Number of tx pin
// * \param n Object index for ISR handling
// * \param baud Baudrate
// *
// * \note There are predefined usart modules like usart0, usart1 which contains usart and port structure, tx pin number and module index
// */
void Usart::Init(uint8_t usart,uint32_t baud)
{

}

void Usart::Stop()
{
//	return (this->rx_len == 0);
}

void Usart::TxComplete()
{
	
}


/**
 * Test if RX buffer is empty (all received data read from RX buffer)
 *
 * \return true if RX buffer is empty
 */
bool Usart::isRxBufferEmpty()
{
	return !(Uart3_RcvCnt - Uart3_pos);
}


void Usart::ClearRxBuffer()
{
	Uart3_RcvCnt = 0;
	Uart3_pos = 0;
	//wait to send all data
//	this->rx_len = 0;
//	this->rx_index = 0;
}


/**
 * Set interrupt priority for this usart module
 *
 * \param p interrupt priority
 */
void Usart::SetInterruptPriority(uint8_t p)
{

}

void Usart::WriteBinary(uint8_t c)
{
	Uart1SendHex(c);
}

/**
 * Write character to TX buffer
 *
 * \param c character to write
 */
void Usart::Write(uint8_t c)
{
	Uart3SendHex(c);

}

/**
 * Read character from RX buffer
 *
 * \return character form RX buffer
 * \note this function will block if there is no character in RX buffer (use isRxBufferEmpty or Peek for non blocking behavior)
 */
uint8_t Usart::Read()
{
	uint8_t c;
	
	c = Uart3_Buff[Uart3_pos++];
	
	if(Uart3_RcvCnt == Uart3_pos){
		Uart3_RcvCnt = Uart3_pos = 0;
	}
	


	return c;

}


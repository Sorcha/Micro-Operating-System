/*
 * Timer.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: DVD
 */

#include "Timer.h"

#define	TIMER_TCR_COUNTER_DISABLE (0x0)
#define	TIMER_TCR_COUNTER_ENABLE (0x1)
#define	TIMER_TCR_COUNTER_RESET (0x2)

#define TIMER_IR_CLEAR_MR0_INTR (0x1)

///
///	Interrupt when MR0 == TC
///
#define TIMER_MCR_MR0_IRQ_ENABLE (0x1)

void Timer::Enable()
{
	DebugAssertNotEquals(0,_timer->PR);
	ResetInterruptRequest();

	///
	///	Enable timer interrupts.
	///
	_timer->MCR = TIMER_MCR_MR0_IRQ_ENABLE;

	///
	///	Enable timer.
	///
	_timer->TCR = TIMER_TCR_COUNTER_ENABLE;

}

void Timer::Disable()
{
	_timer->TCR = TIMER_TCR_COUNTER_DISABLE;
}

void Timer::SetClock(U32 clock)
{
	_timer->PR = clock;
}

U32 Timer::GetTimerCount()
{
	return _timer->TC;
}

void Timer::OnTimerIsrComplete(InterruptArgs* irq,Timer* timer)
{
	timer->ResetInterruptRequest();
}

void Timer::ResetInterruptRequest()
{
	///
	///	Clear the irq request first.
	///
	_timer->IR = TIMER_IR_CLEAR_MR0_INTR;

	///
	///	Set up the next one.
	///
	_timer->MR0 = GetTimerCount() + _intrPeriod;

}
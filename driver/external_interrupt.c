/*
 * File: external_interrupt.c
 * Author: phamtien758
 * 
 */

/*** INCLUDE ************************************/
#include "external_interrupt.h"

/*** PROTOTYPE **********************************/
static ReturnType Exti_IsLineValid(Exti_Line_e LineNum_e);

/*** VARIABLE ***********************************/
static Exti_RegDef *p_ExtiBase_st = EXTI;
static FuncHandler p_Handler = NULL;

/*** STATIC FUNCTION ****************************/
static ReturnType Exti_CheckLineValid(Exti_Line_e LineNum_e)
{
    ReturnType RetValue;

    if(((EXTI_LINE0 <= LineNum_e) && (EXTI_LINE18 >= LineNum_e)) || \
       (EXTI_LINE21 == LineNum_e) || (EXTI_LINE22 == LineNum_e))
    {
        RetValue = RET_NOT_OK;
    }
    else
    {
        RetValue = RET_OK;
    }

    return RetValue;
}

/*** FUNCTIONS **********************************/
ReturnType Exti_IntEnable(Exti_Line_e LineNum_e, FuncHandler p_Func)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_IMR |= EXTI_IMR_BIT_MASK(LineNum_e);
        p_Handler = p_Func;
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

ReturnType Exti_IntDisable(Exti_Line_e LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_IMR &= ~EXTI_IMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

ReturnType Exti_EventEnable(Exti_Line_e LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_EMR |= EXTI_EMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

ReturnType Exti_EventDisable(Exti_Line_e LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_EMR &= ~EXTI_EMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

ReturnType Exti_EdgeCfg(Exti_Line_e LineNum_e, Exti_Edge_e EdgeCfg_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        if(EXTI_EDGE_FALL == EdgeCfg_e)
        {
            p_ExtiBase_st->EXTI_FTSR |= EXTI_FTSR_BIT_MASK(LineNum_e);
            p_ExtiBase_st->EXTI_RTSR &= ~EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else if(EXTI_EDGE_RISE == EdgeCfg_e)
        {
            p_ExtiBase_st->EXTI_FTSR &= ~EXTI_FTSR_BIT_MASK(LineNum_e);
            p_ExtiBase_st->EXTI_RTSR |= EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else if(EXTI_EDGE_FALLRISE == EdgeCfg_e)
        {
            p_ExtiBase_st->EXTI_FTSR |= EXTI_FTSR_BIT_MASK(LineNum_e);
            p_ExtiBase_st->EXTI_RTSR |= EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else
        {
            /* Do nothing */
        }   
    }

    return RetValue;
}

ReturnType Exti_ClearPending(Exti_Line_e LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_PR |= EXTI_PR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

ReturnType Exti_SoftIntGenerate(Exti_Line_e LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_SWIER |= EXTI_SWIER_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

uint32_t Exti_GetPending(void)
{
    return (uint32_t)(p_ExtiBase_st->EXTI_PR);
}

void EXTI0_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE0);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE0);
    }
}

void EXTI1_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE1);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE1);
    }
}

void EXTI2_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE2);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE2);
    }
}

void EXTI3_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE3);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE3);
    }
}

void EXTI4_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE4);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE4);
    }
}

void EXTI9_5_IRQHandler(void)
{
    uint32_t PendValue_u32;
    Exti_Line_e Line_e;

    PendValue_u32 = Exti_GetPending();

    if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE5))
    {
        Line_e = EXTI_LINE5;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE6))
    {
        Line_e = EXTI_LINE6;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE7))
    {
        Line_e = EXTI_LINE7;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE8))
    {
        Line_e = EXTI_LINE8;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE9))
    {
        Line_e = EXTI_LINE9;
    }
    else
    {
        /* do nothing */
    }
    Exti_ClearPending(Line_e);
    if(NULL != p_Handler)
    {
        p_Handler(Line_e);
    }
}

void EXTI15_10_IRQHandler(void)
{
    uint32_t PendValue_u32;
    Exti_Line_e Line_e;

    PendValue_u32 = Exti_GetPending();

    if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE10))
    {
        Line_e = EXTI_LINE10;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE11))
    {
        Line_e = EXTI_LINE11;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE12))
    {
        Line_e = EXTI_LINE12;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE13))
    {
        Line_e = EXTI_LINE13;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE14))
    {
        Line_e = EXTI_LINE14;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE15))
    {
        Line_e = EXTI_LINE15;
    }
    else
    {
        /* do nothing */
    }
    Exti_ClearPending(Line_e);
    if(NULL != p_Handler)
    {
        p_Handler(Line_e);
    }
}
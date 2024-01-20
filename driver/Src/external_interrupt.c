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

/*** STATIC FUNCTION ****************************/
static ReturnType Exti_IsLineValid(Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;

    if(((EXTI_LINE0 <= LineNum_e) && (EXTI_LINE18 >= LineNum_e)) || \
       (EXTI_LINE21 == LineNum_e) || (EXTI_LINE22 == LineNum_e))
    {
        RetValue_b = RET_NOT_OK;
    }
    else
    {
        RetValue_b = RET_OK;
    }

    return RetValue_b;
}

/*** FUNCTIONS **********************************/
ReturnType Exti_Int(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        p_Exti_st->EXTI_IMR |= EXTI_IMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue_b;
}

ReturnType Exti_IntDisable(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        p_Exti_st->EXTI_IMR &= ~EXTI_IMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue_b;
}

ReturnType Exti_EventEnable(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        p_Exti_st->EXTI_EMR |= EXTI_EMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue_b;
}

ReturnType Exti_EventDisable(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        p_Exti_st->EXTI_EMR &= ~EXTI_EMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue_b;
}

ReturnType Exti_EdgeCfg(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e, \
                        Exti_Edge_e EdgeCfg_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        if(EXTI_EDGE_FALL == EdgeCfg_e)
        {
            p_Exti_st->EXTI_FTSR |= EXTI_FTSR_BIT_MASK(LineNum_e);
            p_Exti_st->EXTI_RTSR &= ~EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else if(EXTI_EDGE_RISE == EdgeCfg_e)
        {
            p_Exti_st->EXTI_FTSR &= ~EXTI_FTSR_BIT_MASK(LineNum_e);
            p_Exti_st->EXTI_RTSR |= EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else if(EXTI_EDGE_FALLRISE == EdgeCfg_e)
        {
            p_Exti_st->EXTI_FTSR |= EXTI_FTSR_BIT_MASK(LineNum_e);
            p_Exti_st->EXTI_RTSR |= EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else
        {
            /* Do nothing */
        }   
    }

    return RetValue_b;
}

ReturnType Exti_ClearPending(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        p_Exti_st->EXTI_PR |= EXTI_PR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue_b;
}

ReturnType Exti_SoftIntGenarate(Exti_RegDef *p_Exti_st, Exti_Line_e LineNum_e)
{
    ReturnType RetValue_b;
    
    RetValue_b = Exti_IsLineValid(LineNum_e);

    if(RET_OK == RetValue_b)
    {
        p_Exti_st->EXTI_SWIER |= EXTI_SWIER_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue_b;
}
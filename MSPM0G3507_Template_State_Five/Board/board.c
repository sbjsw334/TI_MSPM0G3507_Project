#include "board.h"

#include "ti_msp_dl_config.h"

void Board_Init(void)
{
    SYSCFG_DL_init();
}

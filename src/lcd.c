#include "main.h"

lv_obj_t * auton1;
lv_obj_t * auton2;
lv_obj_t * myLabel;

static lv_res_t btn_click_action(_lv_obj_t * btn)
{
  uint8_t id = lv_obj_get_free_num(btn);
  if(id == 0)
  {
    char buffer[100];
    sprintf(buffer, "button was licked %i milliseconds from start", millis());
    lv_label_set_text(myLabel, buffer);
  }
  return LV_RES_OK;
}

#include <lvgl.h>
#include "panel.h"
#include "../../core/data_setup.h"
#include "../../conf/global_config.h"
#include "../main_ui.h"

#include <HardwareSerial.h>
#include <HTTPClient.h>

LV_FONT_DECLARE(Montserrat_Bold_14)

extern Device myDevices[];
extern lv_style_t style_shadow;

// My Resolution is 240x320
#define TOTAL_WIDTH 320
#define TOTAL_HEIGHT 240
#define TOTAL_ICONX 3
#define TOTAL_ICONY 3
#define TOTAL_OFFSET_X 10
#define TOTAL_OFFSET_Y 10

//Calculate widgets size, 3 * 3
int Size_w = int(TOTAL_WIDTH / TOTAL_ICONX) -  TOTAL_OFFSET_X;
int Size_h = int(TOTAL_HEIGHT / TOTAL_ICONY) - TOTAL_OFFSET_Y;
//Icon size
int Size_icon = Size_h / 2;


static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    //int *d = (int*)lv_event_get_param(e);

    int * btn_no; // create a user data type pointer
    btn_no = (int*)lv_event_get_user_data(e); // cast the return pointer to data type pointer


    if(code == LV_EVENT_CLICKED) {
        //Serial.printf("Clic sur boutton: %d", * btn_no);
        Select_device(*btn_no);
    }
}

#if 0
static void button_draw_event_cb(lv_event_t* e)
{

    lv_obj_draw_part_dsc_t * part_dsc = lv_event_get_draw_part_dsc(e);
    if(part_dsc->class_p == &lv_obj_class &&
            (part_dsc->part == LV_OBJ_DRAW_PART_RECTANGLE || part_dsc->part == LV_OBJ_DRAW_PART_BORDER_POST))
    {
        lv_obj_t * obj = lv_event_get_target(e);
        lv_draw_rect_dsc_t draw_dsc;
        lv_draw_rect_dsc_init(&draw_dsc);
        draw_dsc.bg_opa = 0;
        draw_dsc.border_width = 3;//lv_obj_get_style_border_width(obj, 0);
        draw_dsc.border_color = LV_COLOR_MAKE(lv_rand(0,0xff), lv_rand(0,0xff), lv_rand(0,0xff));
        //draw_dsc.border_side = LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT;
        lv_draw_rect(part_dsc->draw_ctx, &draw_dsc, part_dsc->draw_area);
    }
}
#endif

void Widget_button(lv_obj_t* panel, char* desc, int x, int y, int w, int h, lv_color_t color, int *d, const lv_img_dsc_t* icon)
{

    /*Create a container with ROW flex direction*/
    lv_obj_t * Button_icon = lv_obj_create(panel);
    lv_obj_set_size(Button_icon, w, h);
    //lv_obj_align(Button_icon, LV_ALIGN_CENTER, x, y);
    lv_obj_set_pos(Button_icon, x, y);
    lv_obj_add_style(Button_icon, &style_shadow, LV_PART_MAIN);
    //lv_obj_set_drag(Button_icon, false);
    //lv_obj_set_flex_flow(Button_icon, LV_FLEX_FLOW_ROW);
    lv_obj_clear_flag( Button_icon, LV_OBJ_FLAG_SCROLLABLE );                     // Remove scrollbar
    lv_obj_add_event_cb(Button_icon, btn_event_cb, LV_EVENT_ALL, d);              /*Assign a callback to the button*/

    lv_obj_t *img = lv_img_create(Button_icon);
    //lv_img_set_src(img, LV_SYMBOL_OK "Accept");
    lv_img_set_src(img, icon);
    lv_obj_align(img, LV_ALIGN_TOP_MID , 0, -10);
    lv_obj_set_size(img, Size_icon, Size_icon);
    lv_obj_set_style_img_recolor_opa(img, 50, 0);
    lv_obj_set_style_img_recolor(img, color, 0);

    /*Create description*/
    lv_obj_t * label2 = lv_label_create(Button_icon);               /*Add a label to the button*/
    lv_label_set_long_mode(label2, LV_LABEL_LONG_WRAP);             /*Break the long lines*/
    lv_obj_set_style_text_font(label2, &lv_font_montserrat_10, 0);
    lv_obj_set_style_text_align(label2, LV_TEXT_ALIGN_CENTER, 0);
    //lv_label_set_recolor(label2, true);                           /*Activate coloring*/
    lv_label_set_text(label2, desc);                                /*Set the labels text*/
    //lv_obj_center(label2);
    lv_obj_set_size(label2, Size_w-10, 30);
    lv_obj_align_to(label2, img,  LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

}

void Widget_sensor(lv_obj_t* panel, char* desc, char* value, int x, int y, int w, int h, lv_color_t color, const lv_img_dsc_t *icon)
{

    /*Create a container*/
    lv_obj_t * Button_icon = lv_obj_create(panel);
    lv_obj_set_size(Button_icon, w, h);
    //lv_obj_align(Button_icon, LV_ALIGN_CENTER, x, y);
    lv_obj_set_pos(Button_icon, x, y);
    lv_obj_add_style(Button_icon, &style_shadow, LV_PART_MAIN);
    lv_obj_clear_flag( Button_icon, LV_OBJ_FLAG_SCROLLABLE );

    //lv_obj_add_event_cb(Button_icon,button_draw_event_cb,LV_EVENT_DRAW_PART_END,NULL); // To bypass drawing

    /*Create icon*/
    lv_obj_t *img = lv_img_create(Button_icon);
    //lv_img_set_src(img, LV_SYMBOL_OK "Accept");
    lv_img_set_src(img, icon);
    //lv_img_set_zoom(img,200);                         // Not working for this image type
    lv_obj_align(img, LV_ALIGN_TOP_LEFT , -10, -10);
    lv_obj_set_size(img, Size_icon, Size_icon);
    // lv_img_set_zoom(img, 350);                         // Zoom 256 = 100% Not working
    lv_obj_set_style_img_recolor_opa(img, 50, 0);
    lv_obj_set_style_img_recolor(img, color, 0);

     /*Create Value*/
     // Does _local_ is working here ?
    lv_obj_t * label = lv_label_create(Button_icon);

    // Set a new style
    //lv_style_set_text_font(&nav_button_text_style, &lv_font_montserrat_12);
    lv_obj_set_style_text_font(label, &Montserrat_Bold_14, 0);
    lv_label_set_text(label, value);
    lv_obj_align_to(label, img,  LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_color(label, color, 0);

    /*Create description*/
    lv_obj_t * label2 = lv_label_create(Button_icon);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label2, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label2, &lv_font_montserrat_10, 0);
    lv_label_set_text(label2, desc);
    lv_obj_set_size(label2, Size_w-10, 30);
    //lv_obj_align_to(label2, img,  LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_align(label2, LV_ALIGN_BOTTOM_MID, 0, 20);
}

void home_panel_init(lv_obj_t* panel)
{
    int x,y;
    int i = 0;

    for (x=0; x<TOTAL_ICONX; x=x+1)
    {
        for (y=0; y<TOTAL_ICONY; y=y+1)
        {
            //Serial.printf("set widget x: %i , y : %i\n", (Size_w + TOTAL_OFFSET_X) * x, (Size_h + TOTAL_OFFSET_Y) * y);
            lv_color_t device_color = Getcolor(myDevices[i].type);
            const lv_img_dsc_t *icon = Geticon(myDevices[i].type);

            int cx = TOTAL_OFFSET_X + (Size_w + TOTAL_OFFSET_X) * x -4;
            int cy = TOTAL_OFFSET_Y + (Size_h + TOTAL_OFFSET_Y) * y -4;

            myDevices[i].pointer = i;

            switch (myDevices[i].type)
            {
                case TYPE_TEMPERATURE:
                case TYPE_HUMIDITY:
                case TYPE_CONSUMPTION:
                {
                    Widget_sensor(panel, myDevices[i].name, myDevices[i].data, cx , cy , Size_w , Size_h, device_color, icon);
                }
                break;
                case TYPE_WARNING:
                {
                    Widget_button(panel, myDevices[i].name, cx, cy, Size_w , Size_h, device_color, &myDevices[i].pointer, icon); 
                }
                break;
                case TYPE_SWITCH:
                case TYPE_SPEAKER:
                case TYPE_SELECTOR:
                case TYPE_DIMMER:
                case TYPE_PLUG:
                case TYPE_COLOR:
                {
                    Widget_button(panel, myDevices[i].name, cx, cy, Size_w , Size_h, device_color, &myDevices[i].pointer, icon); 
                }
                break;
                default:
                break;
            }

            i = i + 1;
        }
    }

}
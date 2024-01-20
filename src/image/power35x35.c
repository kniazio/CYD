#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_POWER35X35
#define LV_ATTRIBUTE_IMG_POWER35X35
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_POWER35X35 uint8_t power35x35_map[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x16, 0xdb, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0x80, 0x00, 
  0x00, 0x3f, 0xff, 0xc0, 0x00, 
  0x00, 0x3f, 0xff, 0xc0, 0x00, 
  0x00, 0x78, 0x01, 0xe0, 0x00, 
  0x00, 0x10, 0x10, 0x80, 0x00, 
  0x00, 0x00, 0xf0, 0x00, 0x00, 
  0x00, 0x01, 0xf8, 0x00, 0x00, 
  0x00, 0x01, 0xf8, 0x00, 0x00, 
  0x00, 0x01, 0xf8, 0x00, 0x00, 
  0x00, 0xff, 0xff, 0xf8, 0x00, 
  0x01, 0xff, 0xff, 0xf8, 0x00, 
  0x01, 0xff, 0xff, 0xfc, 0x00, 
  0x03, 0xd5, 0x75, 0x5c, 0x00, 
  0x03, 0x80, 0x00, 0x1c, 0x00, 
  0x00, 0x07, 0x9e, 0x00, 0x00, 
  0x00, 0x07, 0x0e, 0x00, 0x00, 
  0x00, 0x07, 0x8e, 0x00, 0x00, 
  0x00, 0x0f, 0x9f, 0x00, 0x00, 
  0x00, 0x0f, 0xff, 0x00, 0x00, 
  0x00, 0x0e, 0x77, 0x00, 0x00, 
  0x00, 0x0e, 0x67, 0x00, 0x00, 
  0x00, 0x0e, 0xf7, 0x80, 0x00, 
  0x00, 0x1e, 0xdb, 0x80, 0x00, 
  0x00, 0x1d, 0x9b, 0x80, 0x00, 
  0x00, 0x1f, 0x0f, 0xc0, 0x00, 
  0x00, 0x3f, 0x0f, 0xc0, 0x00, 
  0x00, 0x3e, 0x07, 0xc0, 0x00, 
  0x00, 0x3c, 0x03, 0xc0, 0x00, 
  0x00, 0x7c, 0x01, 0xe0, 0x00, 
  0x00, 0x38, 0x01, 0xe0, 0x00, 
  0x00, 0x70, 0x00, 0xe0, 0x00, 
  0x00, 0x50, 0x00, 0x40, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t power35x35 = {
  .header.cf = LV_IMG_CF_ALPHA_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 35,
  .header.h = 35,
  .data_size = 175,
  .data = power35x35_map,
};